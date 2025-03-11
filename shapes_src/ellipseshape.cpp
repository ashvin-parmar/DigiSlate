#include "shapes_header/ellipseshape.h"
int EllipseShape::count=1;
EllipseShape::EllipseShape(QObject *parent):Drawing(parent),penWidth(1)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::NoBrush);
    this->isCenter=true;
    this->number=count++;
}
EllipseShape::~EllipseShape()
{

}

void EllipseShape::draw(QPainter &painter)
{
painter.setPen(QPen(penColor,penWidth));
painter.setBrush(brush);
if(isCenter) painter.drawEllipse(QPoint(x,y),horizontalRadius,verticalRadius);
else painter.drawEllipse(x,y,horizontalRadius*2,verticalRadius*2);
}
void EllipseShape::clear()
{

}
QString EllipseShape::toString()
{
    if(horizontalRadius!=verticalRadius) return (QString("Ellipse")+QString::number(number));
    else return QString("Circle")+QString::number(number);
}
void EllipseShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    QVector<QPoint> points;
    if(this->isCenter==false)
    {
        points.append(QPoint(x+horizontalRadius,y));
        points.append(QPoint(x+horizontalRadius*2,y+verticalRadius));
        points.append(QPoint(x+horizontalRadius,y+verticalRadius*2));
        points.append(QPoint(x,y+verticalRadius));
    }
    else
    {
        points.append(QPoint(x+horizontalRadius,y));
        points.append(QPoint(x,y+verticalRadius));
        points.append(QPoint(x-horizontalRadius,y));
        points.append(QPoint(x,y-verticalRadius));
    }
    painter.drawPoints(points);
}
bool EllipseShape::isPointInShapeRegion(const QPoint &point)
{
    if(horizontalRadius==verticalRadius && this->isCenter)  //Circle
    {
        int dx=point.x()-this->x;
        int dy=point.y()-this->y;
        return (dx * dx + dy * dy)<=(horizontalRadius*horizontalRadius);
    }
    else
    {
        int x_c=this->x+horizontalRadius;   //Center
        int y_c=this->y+verticalRadius;     //Center
        int a =horizontalRadius;
        int b =verticalRadius;
        int x = point.x();
        int y = point.y();
        return ((x - x_c) * (x - x_c)) / (a * a) + ((y - y_c) * (y - y_c)) / (b * b) <= 1;
    }
    return false;
}
void EllipseShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
Drawing *EllipseShape::fromJson(const QJsonObject &json)
{
    EllipseShape *ellipseShape=new EllipseShape();
//    printf("Object Created");
    if(const QJsonValue value=json["x"]; value.isDouble())
    {
        ellipseShape->x=value.toInt();
    }
    if(const QJsonValue value=json["y"]; value.isDouble())
    {
        ellipseShape->y=value.toInt();
    }
    if(const QJsonValue value=json["horizontalRadius"]; value.isDouble())
    {
        ellipseShape->horizontalRadius=value.toInt();
    }
    if(const QJsonValue value=json["verticalRadius"]; value.isDouble())
    {
        ellipseShape->verticalRadius=value.toInt();
    }
    if(const QJsonValue value=json["penColor"]; value.isString())
    {
        ellipseShape->penColor=value.toString();
    }
    if(const QJsonValue value=json["penWidth"]; value.isDouble())
    {
        ellipseShape->penWidth=value.toInt();
    }
    if(const QJsonValue value=json["brush"]; value.isObject())
    {
        QVariant variant(value.toVariant());
        QBrush bbrush=variant.value<QBrush>();
        ellipseShape->brush=bbrush;
    }
    if(const QJsonValue value=json["isCenter"]; value.isBool())
    {
        ellipseShape->isCenter=value.toBool();
    }
    printf("%d, %d, %d, %d ",ellipseShape->x,ellipseShape->y,ellipseShape->verticalRadius,ellipseShape->horizontalRadius);
return ellipseShape;
}
QJsonObject EllipseShape::toJson() const
{
    QJsonObject json;
    json["x"]=x;
    json["y"]=y;
    json["horizontalRadius"]=horizontalRadius;
    json["verticalRadius"]=verticalRadius;
    json["penWidth"]=penWidth;
    json["penColor"]=penColor.name();
    QVariant value=QVariant::fromValue(brush);
    json["brush"]=value.toJsonObject();
    json["isCenter"]=isCenter;
    return json;
}
int EllipseShape::getX() const
{
    return x;
}

void EllipseShape::setX(int value)
{
    x = value;
}

int EllipseShape::getY() const
{
    return y;
}

void EllipseShape::setY(int value)
{
    y = value;
}

int EllipseShape::getHorizontalRadius() const
{
    return horizontalRadius;
}

void EllipseShape::setHorizontalRadius(int value)
{
    horizontalRadius = value;
}

int EllipseShape::getVerticalRadius() const
{
    return verticalRadius;
}

void EllipseShape::setVerticalRadius(int value)
{
    verticalRadius = value;
}

int EllipseShape::getPenWidth() const
{
    return penWidth;
}

void EllipseShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor EllipseShape::getPenColor() const
{
    return penColor;
}

void EllipseShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush EllipseShape::getBrush() const
{
    return brush;
}

void EllipseShape::setBrush(const QBrush &value)
{
    brush = value;
}

bool EllipseShape::getIsCenter() const
{
    return isCenter;
}

void EllipseShape::setIsCenter(bool value)
{
    isCenter = value;
}
