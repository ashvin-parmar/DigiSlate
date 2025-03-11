#include "shapes_header/rectangleshape.h"
int RectangleShape::count=1;
RectangleShape::RectangleShape(QObject *parent):Drawing(parent),penWidth(1)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::NoBrush);
    x=100;
    y=100;
    width=100;
    height=100;
    number=count++;
}
RectangleShape::~RectangleShape()
{

}
void RectangleShape::draw(QPainter &painter)
{
    painter.setPen(QPen(penColor,penWidth));
    painter.setBrush(brush);
    painter.drawRect(x,y,width,height);
}
void RectangleShape::clear()
{

}
QString RectangleShape::toString()
{
        return QString("Rectangle")+QString::number(number);
}
void RectangleShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    QVector<QPoint> points;
    points.append(QPoint(x,y));
    points.append(QPoint(x+width,y));
    points.append(QPoint(x,y+height));
    points.append(QPoint(x+width,y+height));
    painter.drawPoints(points);
}
bool RectangleShape::isPointInShapeRegion(const QPoint &point)
{
    int pointX,pointY;
    pointX=point.x();
    pointY=point.y();
    if((pointX>=x && pointY>=y) && (pointX<=(x+width) && pointY<=(y+height))) return true;
    return false;
}
void RectangleShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
Drawing * RectangleShape::fromJson(const QJsonObject &json)
{
    RectangleShape *shape=new RectangleShape();
    shape->x=json["x"].toInt();
    shape->y=json["y"].toInt();
    shape->width=json["width"].toInt();
    shape->height=json["height"].toInt();
    shape->penColor=QColor(json["penColor"].toString());
    shape->penWidth=json["penWidth"].toInt();
    if(const QJsonValue value=json["brush"]; value.isObject())
    {
        QVariant variant(value.toVariant());
        QBrush bbrush=variant.value<QBrush>();
        shape->brush=bbrush;
    }
    return shape;
}
QJsonObject RectangleShape::toJson() const
{
    QJsonObject json;
    json["x"]=x;
    json["y"]=y;
    json["width"]=width;
    json["height"]=height;
    json["penColor"]=this->penColor.name();
    json["penWidth"]=this->penWidth;
    QVariant value=QVariant::fromValue(brush);
    json["brush"]=value.toJsonObject();
    return json;
}
int RectangleShape::getX() const
{
    return x;
}

void RectangleShape::setX(int value)
{
    x = value;
}

int RectangleShape::getY() const
{
    return y;
}

void RectangleShape::setY(int value)
{
    y = value;
}

int RectangleShape::getWidth() const
{
    return width;
}

void RectangleShape::setWidth(int value)
{
    width = value;
}

int RectangleShape::getHeight() const
{
    return height;
}

void RectangleShape::setHeight(int value)
{
    height = value;
}

QColor RectangleShape::getPenColor() const
{
    return penColor;
}

void RectangleShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush RectangleShape::getBrush() const
{
    return brush;
}

void RectangleShape::setBrush(const QBrush &value)
{
    brush = value;
}

int RectangleShape::getPenWidth() const
{
    return penWidth;
}

void RectangleShape::setPenWidth(int value)
{
    penWidth = value;
}
