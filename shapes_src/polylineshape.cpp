#include "shapes_header/polylineshape.h"
#include<QtMath>

int PolylineShape::count=1;
PolylineShape::PolylineShape(QObject *parent):Drawing(parent),penWidth(1)
{
this->penColor=Qt::black;
this->brush=QBrush(Qt::white,Qt::SolidPattern);
this->number=count++;
}
PolylineShape::~PolylineShape()
{

}
void PolylineShape::draw(QPainter &painter)
{
    if(this->points.size()>1)
    {
        painter.setPen(QPen(penColor,penWidth));
        painter.setBrush(brush);
        painter.drawPolyline(points);
    }
}
void PolylineShape::clear()
{

}
QString PolylineShape::toString()
{
    return QString("Polyline")+QString::number(number);
}
void PolylineShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    painter.drawPoints(points);
}
bool PolylineShape::isPointInShapeRegion(const QPoint &point)
{
    int x1,y1,x2,y2;
    int ao,ob,ab;
    QPoint p1=points.front();
    for(QPoint p2: points)
    {
         x1=p1.x();
         y1=p1.y();
         x2=p2.x();
         y2=p2.y();
         ao=qSqrt(pow(point.x()-x1,2)+pow(point.y()-y1,2));
         ob=qSqrt(pow(x2-point.x(),2)+pow(y2-point.y(),2));
         ab=qSqrt(pow(x2-x1,2)+pow(y2-y1,2));
         if(ab==ao+ob) return true;
         p1=p2;
    }
    return false;
}
void PolylineShape::moveShape(const QPointF &diffPoint)
{
    QPoint point((int)diffPoint.x(),(int)diffPoint.y());
    QPolygon polygon(this->points);
    polygon.translate(point);
    this->points=polygon.toList().toVector();
}
Drawing * PolylineShape::fromJson(const QJsonObject &json)
{
    PolylineShape *polyline=new PolylineShape();
    QJsonValue value=json["points"];
    if(value.isArray())
    {
        QJsonArray pointsArr=value.toArray();
        for(QJsonValue value:pointsArr)
        {
            if(value.isArray())
            {
                QJsonArray pointArr=value.toArray();
            polyline->points.append(QPoint(pointArr[0].toInt(),pointArr[1].toInt()));
            }
        }

    }
    polyline->penColor=QColor(json["penColor"].toString());
    polyline->penWidth=json["penWidth"].toInt();
    if(const QJsonValue value=json["brush"]; value.isObject())
    {
        QVariant variant(value.toVariant());
        QBrush bbrush=variant.value<QBrush>();
        polyline->brush=bbrush;
    }
    return polyline;
}
QJsonObject PolylineShape::toJson() const
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
QVector<QPoint> PolylineShape::getPoints() const
{
    return points;
}

void PolylineShape::setPoints(const QVector<QPoint> &value)
{
    points = value;
}
void PolylineShape::addPoint(const QPoint &point)
{
    this->points.append(point);
}

int PolylineShape::getPenWidth() const
{
    return penWidth;
}

void PolylineShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor PolylineShape::getPenColor() const
{
    return penColor;
}

void PolylineShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush PolylineShape::getBrush() const
{
    return brush;
}

void PolylineShape::setBrush(const QBrush &value)
{
    brush = value;
}
