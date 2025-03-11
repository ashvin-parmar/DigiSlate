#include "shapes_header/freehandshape.h"
int FreeHandShape::count=1;
FreeHandShape::FreeHandShape(QObject *parent):Drawing(parent)
{
    this->color=Qt::black;
    this->penWidth=1;
    number=count++;
}
FreeHandShape::~FreeHandShape()
{

}
void FreeHandShape::draw(QPainter &painter)
{
    painter.setRenderHint(painter.Antialiasing);
    painter.setPen(QPen(color,penWidth/*,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap,Qt::PenJoinStyle::RoundJoin*/));
    //    painter.setBrush(QBrush(Qt::green,Qt::BrushStyle::SolidPattern));
    painter.drawPolyline(drawPath);
}
void FreeHandShape::clear()
{

}
QString FreeHandShape::toString()
{
 return (QString("FreeHand")+QString::number(number));
}
void FreeHandShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    painter.drawPoint(this->drawPath.front());
    painter.drawPoint(this->drawPath.back());
}
bool FreeHandShape::isPointInShapeRegion(const QPoint &point)
{
    if(drawPath.containsPoint(point,Qt::FillRule::OddEvenFill))
    {
        return true;
    }
    return false;
}
void FreeHandShape::moveShape(const QPointF &diffPoint)
{
    QPoint point((int)diffPoint.x(),(int)diffPoint.y());
    this->drawPath.translate(point);
}
Drawing *FreeHandShape::fromJson(const QJsonObject &json)
{
    FreeHandShape *freeHand=new FreeHandShape();
    QJsonValue value=json["drawPath"];
    if(value.isArray())
    {
        QJsonArray pointsArr=value.toArray();
        for(QJsonValue value:pointsArr)
        {
            if(value.isArray())
            {
                QJsonArray pointArr=value.toArray();
            freeHand->drawPath.append(QPoint(pointArr[0].toInt(),pointArr[1].toInt()));
            }
        }

    }
    freeHand->color=QColor(json["penColor"].toString());
    freeHand->penWidth=json["penWidth"].toInt();
    return freeHand;
}
QJsonObject FreeHandShape::toJson() const
{
    QJsonObject json;
    QJsonArray pointsArr;
    for(QPoint point:this->drawPath)
    {
        QJsonArray pointArr({point.x(),point.y()});
        pointsArr.append(pointArr);
    }
    json["drawPath"]=pointsArr;
    json["penColor"]=this->color.name();
    json["penWidth"]=this->penWidth;
    return json;
}
void FreeHandShape::addPoint(const QPoint &point)
{
    this->drawPath.append(point);
}
int FreeHandShape::pathSize() const
{
    return this->drawPath.size();
}

QColor FreeHandShape::getColor() const
{
    return color;
}

void FreeHandShape::setColor(const QColor &value)
{
    color = value;
}

int FreeHandShape::getPenWidth() const
{
    return penWidth;
}

void FreeHandShape::setPenWidth(int value)
{
    penWidth = value;
}
