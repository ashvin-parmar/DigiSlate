#include "shapes_header/polygonshape.h"
int PolygonShape::count=1;
PolygonShape::PolygonShape(QObject *parent):Drawing(parent)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::NoBrush);
    this->number=count++;
}
PolygonShape::~PolygonShape()
{

}
void PolygonShape::draw(QPainter &painter)
{
    if(this->points.size()>2)
    {
        painter.setPen(QPen(penColor,penWidth));
        painter.setBrush(brush);
        painter.drawPolygon(points,Qt::FillRule::WindingFill);
    }
}
void PolygonShape::clear()
{

}
QString PolygonShape::toString()
{
    return QString("Polygon")+QString::number(number);
}
void PolygonShape::select(QPainter &painter)
{
    painter.drawPoints(points);
}
bool PolygonShape::isPointInShapeRegion(const QPoint &point)
{
    return QPolygon(points).contains(point);
}
void PolygonShape::moveShape(const QPointF &diffPoint)
{
    QPoint point((int)diffPoint.x(),(int)diffPoint.y());
    QPolygon polygon(this->points);
    polygon.translate(point);
    this->points=polygon.toList().toVector();
}
Drawing * PolygonShape::fromJson(const QJsonObject &json)
{
    PolygonShape *polygon=new PolygonShape();
    QJsonValue value=json["points"];
    if(value.isArray())
    {
        QJsonArray pointsArr=value.toArray();
        for(QJsonValue value:pointsArr)
        {
            if(value.isArray())
            {
                QJsonArray pointArr=value.toArray();
            polygon->points.append(QPoint(pointArr[0].toInt(),pointArr[1].toInt()));
            }
        }

    }
    polygon->penColor=QColor(json["penColor"].toString());
    polygon->penWidth=json["penWidth"].toInt();
    if(const QJsonValue value=json["brush"]; value.isObject())
    {
        QVariant variant(value.toVariant());
        QBrush bbrush=variant.value<QBrush>();
        polygon->brush=bbrush;
    }
    return polygon;
}
QJsonObject PolygonShape::toJson() const
{
    QJsonObject json;
    QJsonArray pointsArr;
    for(QPoint point:this->points)
    {
        QJsonArray pointArr({point.x(),point.y()});
        pointsArr.append(pointArr);
    }
    json["points"]=pointsArr;
    json["penColor"]=this->penColor.name();
    json["penWidth"]=this->penWidth;
    QVariant value=QVariant::fromValue(brush);
    json["brush"]=value.toJsonObject();
    return json;
}
QVector<QPoint> PolygonShape::getPoints() const
{
    return points;
}

void PolygonShape::setPoints(const QVector<QPoint> &value)
{
    points = value;
}
void PolygonShape::addPoint(const QPoint &point)
{
    this->points.append(point);
}
int PolygonShape::getPenWidth() const
{
    return penWidth;
}

void PolygonShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor PolygonShape::getPenColor() const
{
    return penColor;
}

void PolygonShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush PolygonShape::getBrush() const
{
    return brush;
}

void PolygonShape::setBrush(const QBrush &value)
{
    brush = value;
}
