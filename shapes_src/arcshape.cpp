#include "shapes_header/arcshape.h"
int ArcShape::count=1;
ArcShape::ArcShape(QObject *parent):Drawing(parent),penWidth(2)
{
    this->penColor=Qt::black;
    this->x=10;
    this->y=10;
    this->width=100;
    this->height=100;
    this->number=count++;
}
ArcShape::~ArcShape()
{

}

void ArcShape::draw(QPainter &painter)
{
painter.setPen(QPen(penColor,penWidth));
QRect rect(x,y,width,height);
painter.drawArc(rect,startAngle*16,spanAngle*16);
}
void ArcShape::clear()
{

}
QString ArcShape::toString()
{
    return (QString("Arc")+QString::number(number));
}
void ArcShape::select(QPainter &painter)
{

}
bool ArcShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}


int ArcShape::getX() const
{
    return x;
}

void ArcShape::setX(int value)
{
    x = value;
}

int ArcShape::getY() const
{
    return y;
}

void ArcShape::setY(int value)
{
    y = value;
}

int ArcShape::getWidth() const
{
    return width;
}

void ArcShape::setWidth(int value)
{
    width = value;
}

int ArcShape::getHeight() const
{
    return height;
}

void ArcShape::setHeight(int value)
{
    height = value;
}

int ArcShape::getStartAngle() const
{
    return startAngle;
}

void ArcShape::setStartAngle(int value)
{
    startAngle = value;
}

int ArcShape::getSpanAngle() const
{
    return spanAngle;
}

void ArcShape::setSpanAngle(int value)
{
    spanAngle = value;
}

int ArcShape::getPenWidth() const
{
    return penWidth;
}

void ArcShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor ArcShape::getPenColor() const
{
    return penColor;
}

void ArcShape::setPenColor(const QColor &value)
{
    penColor = value;
}
