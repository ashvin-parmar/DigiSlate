#include "model.h"
#include <QPainter>
#include <QDebug>

#include<shapes_header/arcshape.h>
#include<shapes_header/lineshape.h>
#include<shapes_header/textshape.h>
#include<shapes_header/pointshape.h>
#include<shapes_header/polylineshape.h>
#include<shapes_header/polygonshape.h>
#include<shapes_header/ellipseshape.h>
#include<shapes_header/rectangleshape.h>
#include<shapes_header/roundedrectangleshape.h>
#include<shapes_header/pixmapshape.h>

#include<iostream>
using namespace std;

Model::Model(QWidget *parent) : QWidget(parent)
{
    pickPoint=QPoint();
}
Model::~Model()
{
        qDeleteAll(shapes);
        shapes.clear();
}

void Model::addShape(Drawing *drawing)
{
    if (drawing) {
        shapes.append(drawing);
//        cout<<drawing->toString().toStdString().c_str();
        viewMap.insert(drawing->toString().toUpper(),drawing);
        update();  // Redraw the canvas
    }
}
void Model::removeShape(const QString &shape)
{
    Drawing *drawing=viewMap[shape.toUpper()];
//    printf("Shape: %s\n",shape.toStdString().c_str());
    if(drawing!=nullptr)
    {
        this->shapes.removeOne(drawing);
        this->viewMap.remove(shape.toUpper());
        delete drawing;
    }
}
QList<QString> Model::getAllShapes()
{
    return this->viewMap.keys();
}
void Model::clearCanvas() {
    QList<Drawing*> cloneShape=shapes;
    shapes.clear();
    update();
    shapes=cloneShape;
}
void Model::drawAll()
{
    update();
}
void Model::processClicked(QPainter &painter)
{
    if(this->flag==PICK)
    {
        painter.setPen(QPen(Qt::yellow,penWidth+5,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap));
        for(Drawing *shape: shapes)
        {
            if(shape->isPointInShapeRegion(pickPoint))
            {
                shape->select(painter);
                break;
            }
        }
    }
    else
    {
        this->pickPoint=QPoint();
    }
    update();
}
void Model::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rect=this->rect();
    painter.setClipRect(0,0,rect.width(),rect.height());
    painter.eraseRect(0,0,rect.width(),rect.height());
    cout<<"Painting got called size: "<<shapes.size()<<endl;
    for (Drawing *shape : shapes) {
        shape->draw(painter);  // Call each shape’s draw method
    }

    if(this->flag==PICK)
    {
        processClicked(painter);
    }
}
void Model::mousePressEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    if(this->flag==PICK) this->pickPoint=point;
    if(this->flag==FREEHAND)
    {
        freeHandShape=new FreeHandShape();
        freeHandShape->setColor(color);
        freeHandShape->setPenWidth(penWidth);
        this->addShape(freeHandShape);
    }
    if(this->flag==LINE)
    {
        LineShape *lineShape=new LineShape();
        lineShape->setX1(event->x());
        lineShape->setY1(event->y());
        lineShape->setX2(event->x());
        lineShape->setY2(event->y());
        lineShape->setPenColor(this->color);
        lineShape->setPenWidth(penWidth);
        this->drawing=lineShape;
        this->addShape(this->drawing);
    }
    if(this->flag==RECTANGLE)
    {
        RectangleShape *shape=new RectangleShape();
        shape->setX(event->x());
        shape->setY(event->y());
        shape->setWidth(0);
        shape->setHeight(0);
        shape->setPenColor(this->color);
        shape->setPenWidth(penWidth);
        this->drawing=shape;
        this->addShape(this->drawing);
    }
}
void Model::mouseMoveEvent(QMouseEvent *event)
{
    cordinates->setText(QString("x=%1,y=%2").arg(event->x()).arg(event->y()));
    QPoint point=event->pos();
    if(this->flag==PICK) this->pickPoint=point;
    if(this->flag==FREEHAND)
    {
        if(freeHandShape!=nullptr) this->freeHandShape->addPoint(point);
    }
    if(this->flag==LINE)
    {
        if(drawing!=nullptr)
        {
            LineShape *shape=dynamic_cast<LineShape *>(this->drawing);
            shape->setY2(event->y());
            shape->setX2(event->x());
        }
    }
    if(this->flag==RECTANGLE)
    {
        if(drawing!=nullptr)
        {
            RectangleShape *shape=dynamic_cast<RectangleShape *>(this->drawing);
            shape->setWidth((event->x()-shape->getX()));
            shape->setHeight((event->y()-shape->getY()));
        }
    }
    update();
}

void Model::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point=event->pos();
    if(this->flag==PICK) this->pickPoint=point;
    if(this->flag==FREEHAND)
    {
        if(freeHandShape!=nullptr)
        {
            this->freeHandShape->addPoint(point);
            this->listWidget->insertItem(0,this->freeHandShape->toString());
            freeHandShape=nullptr;
        }
    }
    if(this->flag==LINE)
    {
        if(drawing!=nullptr)
        {
            LineShape *shape=dynamic_cast<LineShape *>(this->drawing);
            if(shape->getX1()==event->x() && shape->getY1()==event->y())
            {
                this->removeShape(shape->toString());
                return;
            }
            shape->setY2(event->y());
            shape->setX2(event->x());
            this->listWidget->insertItem(0,shape->toString());
            drawing=nullptr;
        }
    }
    if(this->flag==RECTANGLE)
    {
        if(drawing!=nullptr)
        {
            RectangleShape *shape=dynamic_cast<RectangleShape *>(this->drawing);
            if(shape->getX()==event->x() && shape->getY()==event->y())
            {
                this->removeShape(shape->toString());
                return;
            }
            shape->setWidth((event->x()-shape->getX()));
            shape->setHeight((event->y()-shape->getY()));
            this->listWidget->insertItem(0,shape->toString());
            drawing=nullptr;
        }
    }
    update();

}

int Model::getPenWidth() const
{
    return penWidth;
}

void Model::setPenWidth(int value)
{
    penWidth = value;
}

QColor Model::getColor() const
{
    return color;
}

void Model::setColor(const QColor &value)
{
    color = value;
}

int Model::getFlag() const
{
    return flag;
}

void Model::setFlag(int value)
{
    flag = value;
}

void Model::setCordinates(QLabel *value)
{
    cordinates = value;
}
QListWidget *Model::getListWidget() const
{
    return listWidget;
}

void Model::setListWidget(QListWidget *value)
{
    listWidget = value;
}
