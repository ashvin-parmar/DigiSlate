#include "shapes_header/roundedrectangleshape.h"
int RoundedRectangleShape::count=1;
RoundedRectangleShape::RoundedRectangleShape(QObject *parent):Drawing(parent),penWidth(1)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::white,Qt::SolidPattern);
    this->x=100;
    this->y=100;
    this->width=100;
    this->height=100;
    this->xRadius=0;
    this->yRadius=0;
    this->number=count++;
}
RoundedRectangleShape::~RoundedRectangleShape()
{

}
void RoundedRectangleShape::draw(QPainter &painter)
{
    painter.setPen(QPen(penColor,penWidth));
    painter.setBrush(brush);
    painter.drawRoundedRect(x,y,width,height,xRadius,yRadius,Qt::SizeMode::AbsoluteSize);
}
void RoundedRectangleShape::clear()
{

}
QString RoundedRectangleShape::toString()
{
    return QString("RoundedRectangle")+QString::number(number);
}
void RoundedRectangleShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    QVector<QPoint> points;
    points.append(QPoint(x+width/2,y));
    points.append(QPoint(x+width,y+height/2));
    points.append(QPoint(x+width/2,y+height));
    points.append(QPoint(x,y+height/2));
}
bool RoundedRectangleShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);

    return false;
}
void RoundedRectangleShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
Drawing * RoundedRectangleShape::fromJson(const QJsonObject &json)
{
   RoundedRectangleShape *shape=new RoundedRectangleShape();
   shape->x=json["x"].toInt();
   shape->y=json["y"].toInt();
   shape->width=json["width"].toInt();
   shape->height=json["height"].toInt();
   shape->xRadius=json["xRadius"].toInt();
   shape->yRadius=json["yRadius"].toInt();
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
QJsonObject RoundedRectangleShape::toJson() const
{
    QJsonObject json;
    json["x"]=x;
    json["y"]=y;
    json["width"]=width;
    json["height"]=height;
    json["penColor"]=this->penColor.name();
    json["penWidth"]=this->penWidth;
    json["xRadius"]=this->xRadius;
    json["yRadius"]=this->yRadius;
    QVariant value=QVariant::fromValue(brush);
    json["brush"]=value.toJsonObject();
    return json;
}
int RoundedRectangleShape::getX() const
{
    return x;
}
void RoundedRectangleShape::setX(int value)
{
    x = value;
}

int RoundedRectangleShape::getY() const
{
    return y;
}

void RoundedRectangleShape::setY(int value)
{
    y = value;
}

int RoundedRectangleShape::getWidth() const
{
    return width;
}

void RoundedRectangleShape::setWidth(int value)
{
    width = value;
}

int RoundedRectangleShape::getHeight() const
{
    return height;
}

void RoundedRectangleShape::setHeight(int value)
{
    height = value;
}

int RoundedRectangleShape::getXRadius() const
{
    return xRadius;
}

void RoundedRectangleShape::setXRadius(int value)
{
    xRadius = value;
}

int RoundedRectangleShape::getYRadius() const
{
    return yRadius;
}

void RoundedRectangleShape::setYRadius(int value)
{
    yRadius = value;
}

QColor RoundedRectangleShape::getPenColor() const
{
    return penColor;
}

void RoundedRectangleShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush RoundedRectangleShape::getBrush() const
{
    return brush;
}

void RoundedRectangleShape::setBrush(const QBrush &value)
{
    brush = value;
}

int RoundedRectangleShape::getPenWidth() const
{
    return penWidth;
}

void RoundedRectangleShape::setPenWidth(int value)
{
    penWidth = value;
}
