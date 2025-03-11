#include "model.h"
#include <QPainter>
#include <QDebug>
#include <QPointF>
#include<QJsonDocument>
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
    //Initialization
    flag=NOFLAG;
    drag=DISABLE;
    resize=DISABLE;
    listWidget=new QListWidget(parent);
    cordinates=nullptr;
    freeHandShape=nullptr;
    rubber=nullptr;
    drawing=nullptr;
    this->color=Qt::black;
    this->penWidth=1;
    pickPoint=QPoint();
    this->filePath="";
    this->groupShapes=new GroupShape();
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

    this->shapes.clear();
    this->viewMap.clear();
    this->listWidget->clear();
    update();
}
void Model::drawAll()
{
    update();
}
void Model::processClicked(QPainter &painter)
{
    if(this->flag==PICK)
    {
        this->groupShapes->removeAllShape();
        for(Drawing *shape: shapes)
        {
            if(shape->isPointInShapeRegion(pickPoint))
            {
//                painter.setPen(QPen(Qt::yellow,penWidth+5,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap));
//                this->groupShapes->addShape(shape);
                shape->select(painter);
                drawing=shape;
                break;
            }
        }
    }else if(this->flag==GROUPPICK)
    {
        for(Drawing *shape: shapes)
        {
            if(this->groupShapes->containShape(shape)) continue;
            if(shape->isPointInShapeRegion(pickPoint))
            {
//                painter.setPen(QPen(Qt::yellow,penWidth+5,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap));
                this->groupShapes->addShape(shape);
                break;
            }
        }
        for(Drawing *shape: this->groupShapes->getShapes()) shape->select(painter);
    }
    else if(this->flag==UNGROUPPICK)
    {
        this->groupShapes->removeAllShape();
        update();
    }
    else
    {
        this->pickPoint=QPoint();
        this->groupShapes->removeAllShape();
        update();
    }
}
void Model::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rect=this->rect();
    painter.setClipRect(0,0,rect.width(),rect.height());
    painter.eraseRect(0,0,rect.width(),rect.height());
    cout<<"Painting got called size: "<<shapes.size()<<endl;
    if(this->pageLines)
    {
        for(int y=30;y<rect.height();y+=30)
        {
            painter.setPen(QPen(Qt::gray,1));
            painter.drawLine(0,y,rect.width(),y);
//            printf("%d, %d, \n",y,rect.width());
        }
    }
    for (Drawing *shape : shapes) {
        shape->draw(painter);  // Call each shape’s draw method
    }

    if(this->flag==PICK || this->flag==GROUPPICK || this->flag==UNGROUPPICK)
    {
        processClicked(painter);
    } else if(this->drag==DISABLE)
    {
        this->groupShapes->removeAllShape();
    }
    if(this->flag==RUBBER)
    {
        if(this->rubber!=nullptr) painter.eraseRect(*(this->rubber));
    }
}
void Model::mousePressEvent(QMouseEvent *event)
{
    if(this->flag==NOFLAG) return;
    initialPoint=event->pos();
    QPoint point=event->pos();
    if(this->flag==PICK || this->flag==GROUPPICK)
    {
        this->pickPoint=point;
        update();
    }
    else
    {
        pickPoint=QPoint();
    }

    if(this->flag==FREEHAND)
    {
        freeHandShape=new FreeHandShape();
        freeHandShape->setColor(color);
        freeHandShape->setPenWidth(penWidth);
        this->addShape(freeHandShape);
    }
    if(this->flag==RUBBER)
    {
        freeHandShape=new FreeHandShape();
        freeHandShape->setColor(Qt::white);
        freeHandShape->setPenWidth(penWidth);
        this->addShape(freeHandShape);
//        this->rubber=new QRect(point.x(),point.y(),penWidth,penWidth);
//        update();
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
    if(this->flag==ELLIPSE)
    {
        EllipseShape *shape=new EllipseShape();
        shape->setX(event->x());
        shape->setY(event->y());
        shape->setIsCenter(false);
        shape->setHorizontalRadius(0);
        shape->setVerticalRadius(0);
        shape->setPenColor(this->color);
        shape->setPenWidth(penWidth);
        this->drawing=shape;
        this->addShape(this->drawing);
    }
    if(this->flag==CIRCLE)
    {
        EllipseShape *shape=new EllipseShape();
        shape->setX(event->x());
        shape->setY(event->y());
        shape->setIsCenter(true);
        shape->setHorizontalRadius(0);
        shape->setVerticalRadius(0);
        shape->setPenColor(this->color);
        shape->setPenWidth(penWidth);
        this->drawing=shape;
        this->addShape(this->drawing);
    }
    if(this->flag==IMAGE)
    {
        if(this->filePath.compare("")==0) return ;
        QPixmap image(this->filePath);
        if(image.isNull())
        {
            this->drawing=nullptr;
            return;
        }

        PixmapShape *shape=new PixmapShape();
        shape->setX(event->x());
        shape->setY(event->y());
        shape->setWidth(0);
        shape->setHeight(0);
        shape->setFileName(filePath);
        shape->setPixmap(image);
        filePath="";
        this->drawing=shape;
        this->addShape(this->drawing);
    }

    update();
}
void Model::mouseMoveEvent(QMouseEvent *event)
{
    cordinates->setText(QString("x=%1,y=%2").arg(event->x()).arg(event->y()));
    currentPoint=event->pos();
    if(this->flag==NOFLAG) return;
//    if(this->flag==PICK || this->flag==GROUPPICK)
//    {
//        this->drag=ENABLE;
//    }
    if(this->flag==FREEHAND)
    {
        if(freeHandShape!=nullptr) this->freeHandShape->addPoint(currentPoint);
    }
    if(this->flag==RUBBER)
    {
        if(freeHandShape!=nullptr) this->freeHandShape->addPoint(currentPoint);
//        if(rubber!=nullptr)
//        {
//            this->rubber->setRect(currentPoint.x(),currentPoint.y(),penWidth,penWidth);
//            update();
//        }
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
    if(this->flag==ELLIPSE)
    {
        if(drawing!=nullptr)
        {
            EllipseShape *shape=dynamic_cast<EllipseShape *>(this->drawing);
            shape->setHorizontalRadius((event->x()-shape->getX()));
            shape->setVerticalRadius((event->y()-shape->getY()));
        }
    }
    if(this->flag==CIRCLE)
    {
        if(drawing!=nullptr)
        {
            EllipseShape *shape=dynamic_cast<EllipseShape *>(this->drawing);
            shape->setHorizontalRadius((event->x()-shape->getX()));
            shape->setVerticalRadius((event->x()-shape->getX()));
        }
    }
    if(this->flag==IMAGE)
    {
        if(drawing!=nullptr)
        {
            PixmapShape *shape=dynamic_cast<PixmapShape *>(this->drawing);
            shape->setWidth((event->x()-shape->getX()));
            shape->setHeight((event->y()-shape->getY()));
        }
    }

    if(this->drag==ENABLE)
    {
        //Traverse on groupShapes and call drawing(shapes) method for dragMove Event specific [Change position/Calculate Difference from clicked place]
        QPointF diff=QPoint(currentPoint.x()-initialPoint.x(),currentPoint.y()-initialPoint.y());
        if(this->flag==PICK)
        {
            if(drawing!=nullptr) drawing->moveShape(diff);
        }
        if(this->flag==GROUPPICK)
        {
        for(Drawing *shape:this->groupShapes->getShapes())
        {
            shape->moveShape(diff);
        }
        }

    }
    else if(this->resize==ENABLE)
    {

    }
    initialPoint=currentPoint;
    update();
}

void Model::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->flag==NOFLAG)
    {
        this->drawing=nullptr;
        return;
    }
    finalPoint=event->pos();
    QPoint point=event->pos();

    if(this->flag==FREEHAND)
    {
        if(freeHandShape!=nullptr)
        {
            this->freeHandShape->addPoint(point);
            this->listWidget->insertItem(0,this->freeHandShape->toString());
            freeHandShape=nullptr;
        }
    }
    if(this->flag==RUBBER)
    {
        if(freeHandShape!=nullptr)
        {
            this->freeHandShape->addPoint(point);
            freeHandShape=nullptr;
        }
//        if(rubber!=nullptr)
//        {
//            this->rubber->setRect(point.x(),point.y(),penWidth,penWidth);
//            update();
//            delete rubber;
//            rubber=nullptr;
//        }
    }
    if(this->flag==LINE)
    {
        if(drawing!=nullptr)
        {
            LineShape *shape=dynamic_cast<LineShape *>(this->drawing);
            if(shape->getX1()==event->x() && shape->getY1()==event->y())
            {
                this->removeShape(shape->toString());
                drawing=nullptr;
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
                drawing=nullptr;
                return;
            }
            shape->setWidth((event->x()-shape->getX()));
            shape->setHeight((event->y()-shape->getY()));
            this->listWidget->insertItem(0,shape->toString());
            drawing=nullptr;
        }
    }
    if(this->flag==ELLIPSE)
    {
        if(drawing!=nullptr)
        {
            EllipseShape *shape=dynamic_cast<EllipseShape *>(this->drawing);
            if(shape->getX()==event->x() && shape->getY()==event->y())
            {
                this->removeShape(shape->toString());
                drawing=nullptr;
                return;
            }
            shape->setHorizontalRadius((event->x()-shape->getX()));
            shape->setVerticalRadius((event->y()-shape->getY()));
            this->listWidget->insertItem(0,shape->toString());
            drawing=nullptr;
        }
    }
    if(this->flag==CIRCLE)
    {
        if(drawing!=nullptr)
        {
            EllipseShape *shape=dynamic_cast<EllipseShape *>(this->drawing);
            if(shape->getX()==event->x() && shape->getY()==event->y())
            {
                this->removeShape(shape->toString());
                drawing=nullptr;
                return;
            }

            shape->setHorizontalRadius((event->x()-shape->getX()));
            shape->setVerticalRadius((event->x()-shape->getX()));
            this->listWidget->insertItem(0,shape->toString());
            drawing=nullptr;
        }
    }
    if(this->flag==IMAGE)
    {
        if(drawing!=nullptr)
        {
            PixmapShape *shape=dynamic_cast<PixmapShape *>(this->drawing);
            if(shape->getX()==event->x() && shape->getY()==event->y())
            {
                this->removeShape(shape->toString());
                drawing=nullptr;
                return;
            }
            shape->setWidth((event->x()-shape->getX()));
            shape->setHeight((event->y()-shape->getY()));
            this->listWidget->insertItem(0,shape->toString());
            drawing=nullptr;
            this->flag=NOFLAG;
        }
    }

    if(this->drag==ENABLE)
    {
        QPointF diff=QPoint(currentPoint.x()-initialPoint.x(),currentPoint.y()-initialPoint.y());
        if(this->flag==PICK)
        {
            if(drawing!=nullptr) drawing->moveShape(diff);
            drawing=nullptr;
        }
        if(this->flag==GROUPPICK)
        {
        for(Drawing *shape:this->groupShapes->getShapes())
        {
            shape->moveShape(diff);
        }
        }
    }
    else if(this->resize==ENABLE)
    {

    }

//    if(this->flag==PICK || this->flag==GROUPPICK)
//    {
//       this->drag=DISABLE;
//    }
    update();
}

Model* Model::fromJson(const QJsonObject &jsonObject,QWidget *parent)
{
    Model *model=new Model(parent);
    QStringList list=jsonObject.keys();
    for(QString key:list)
    {
        Drawing *shape=nullptr;
        QJsonValue value=jsonObject.value(key);
        if(key.contains("Arc"))
        {
            shape=ArcShape::fromJson(value.toObject());
        }
        else if(key.contains("Ellipse"))
        {
            shape=EllipseShape::fromJson(value.toObject());
        }
        else if(key.contains("Circle"))
        {
            shape=EllipseShape::fromJson(value.toObject());
        }
        else if(key.contains("FreeHand"))
        {
            shape=FreeHandShape::fromJson(value.toObject());
        }
        else if(key.contains("Line"))
        {
            shape=LineShape::fromJson(value.toObject());
        }
        else if(key.contains("Image"))
        {
            shape=PixmapShape::fromJson(value.toObject());
        }
        else if(key.contains("Point"))
        {
            shape=PointShape::fromJson(value.toObject());
        }
        else if(key.contains("Polygon"))
        {
            shape=PolygonShape::fromJson(value.toObject());
        }
        else if(key.contains("Polyline"))
        {
            shape=PolylineShape::fromJson(value.toObject());
        }
        else if(key.contains("Rectangle"))
        {
            shape=RectangleShape::fromJson(value.toObject());
        }
        else if(key.contains("RoundedRectangle"))
        {
            shape=RoundedRectangleShape::fromJson(value.toObject());
        }
        else if(key.contains("Text"))
        {
            shape=TextShape::fromJson(value.toObject());
        }
        if(shape!=nullptr)
        {
            model->addShape(shape);//donedone
            model->listWidget->insertItem(0,shape->toString());
        }
    }
    return model;
}
QJsonObject Model::toJson() const
{
    QJsonObject json;
    for(int i=shapes.size()-1;i>=0;i--)
    {
        Drawing *shape=shapes[i];
        QJsonObject shapeJson=shape->toJson();
        if(shapeJson.isEmpty()) continue;
        json[shape->toString()]=shapeJson;
    }
    return json;
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
    if(!(flag==PICK || flag==GROUPPICK))
    {
        this->drag=DISABLE;
        this->resize=DISABLE;
        this->groupShapes->removeAllShape();
    }
    update();
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

QString Model::getFilePath() const
{
    return filePath;
}

void Model::setFilePath(const QString &value)
{
    filePath = value;
}
bool Model::getDrag() const
{
    return drag;
}

void Model::setDrag(bool value)
{
    drag = value;
}
bool Model::getPageLines() const
{
    return pageLines;
}
void Model::setPageLines(bool value)
{
    pageLines = value;
}
void Model::alterPageLines()
{
    if(pageLines==false) pageLines=true;
    else                 pageLines=false;
    update();
}

bool Model::getResize() const
{
    return resize;
}

void Model::setResize(bool value)
{
    resize = value;
}
