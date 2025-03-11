#include "shapes_header/pointshape.h"
int PointShape::count=1;
PointShape::PointShape(QObject *parent):Drawing(parent),penColor(Qt::black),penWidth(1)
{
x=0;
y=0;
number=count++;
}
PointShape::~PointShape()
{

}
void PointShape::draw(QPainter &painter)
{
painter.setPen(QPen(penColor,penWidth));
painter.drawPoint(x,y);
}
void PointShape::clear()
{

}
QString PointShape::toString()
{
    return QString("Point")+QString::number(number);
}
void PointShape::select(QPainter &painter)
{

}
bool PointShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
void PointShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
Drawing * PointShape::fromJson(const QJsonObject &json)
{
    PointShape *shape=new PointShape();
    shape->x=json["x"].toInt();
    shape->y=json["y"].toInt();
    shape->penColor=json["penColor"].toString();
    shape->penWidth=json["penWidth"].toInt();
    return shape;
}
QJsonObject PointShape::toJson() const
{
    QJsonObject json;
    json["x"]=x;
    json["y"]=y;
    json["penColor"]=penColor.name();
    json["penWidth"]=penWidth;
    return json;
}
int PointShape::getX() const
{
    return x;
}

void PointShape::setX(int value)
{
    x = value;
}

int PointShape::getY() const
{
    return y;
}

void PointShape::setY(int value)
{
    y = value;
}

QColor PointShape::getPenColor() const
{
    return penColor;
}

void PointShape::setPenColor(const QColor &value)
{
    penColor = value;
}

int PointShape::getPenWidth() const
{
    return penWidth;
}

void PointShape::setPenWidth(int value)
{
    penWidth = value;
}
