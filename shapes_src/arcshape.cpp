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
Q_UNUSED(painter);
}
bool ArcShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
void ArcShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
Drawing * ArcShape::fromJson(const QJsonObject &json)
{
    ArcShape *arcShape=new ArcShape();
    if(const QJsonValue value=json["x"]; value.isDouble())
    {
        arcShape->x=value.toInt();
    }
    if(const QJsonValue value=json["y"]; value.isDouble())
    {
        arcShape->y=value.toInt();
    }
    if(const QJsonValue value=json["width"]; value.isDouble())
    {
        arcShape->width=value.toInt();
    }
    if(const QJsonValue value=json["height"]; value.isDouble())
    {
        arcShape->height=value.toInt();
    }
    if(const QJsonValue value=json["penWidth"]; value.isDouble())
    {
        arcShape->penWidth=value.toInt();
    }
    if(const QJsonValue value=json["penColor"]; value.isString())
    {
        arcShape->penColor=QColor(value.toString());
    }
    return arcShape;
}
QJsonObject ArcShape::toJson() const
{
    QJsonObject json;
    json["x"]=x;
    json["y"]=y;
    json["width"]=width;
    json["height"]=height;
    json["startAngle"]=startAngle;
    json["spanAngle"]=spanAngle;
    json["penWidth"]=penWidth;
    json["penColor"]=penColor.name();
    return json;
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
