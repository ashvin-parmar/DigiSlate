#include "shapes_header/textshape.h"
int TextShape::count=1;
TextShape::TextShape(QObject *parent):Drawing(parent),penColor(Qt::black),penWidth(1),font(QFont("Times new roman",72))
{
    x=0;
    y=0;
    number=count++;
}
TextShape::~TextShape()
{

}
void TextShape::draw(QPainter &painter)
{
    painter.setPen(QPen(penColor,penWidth));
    font.setPointSize(pointSize*1.33);
    painter.setFont(font);
    painter.drawText(x,y,text);
}
void TextShape::clear()
{

}
QString TextShape::toString()
{
    return QString("Text")+QString::number(number);
}
void TextShape::select(QPainter &painter)
{
    int width=(pointSize*1.33)*this->text.count();
    int height=(pointSize*1.33);
    QVector<QPoint> points;
    points.append(QPoint(x,y));
    points.append(QPoint(x+width,y));
    points.append(QPoint(x,y+height));
    points.append(QPoint(x+width,y+height));
    painter.drawPoints(points);
}
bool TextShape::isPointInShapeRegion(const QPoint &point)
{
    int width=(pointSize*1.33)*this->text.count();
    int height=(pointSize*1.33);
    int pointX,pointY;
    pointX=point.x();
    pointY=point.y();
    if((pointX>=x && pointY>=y) && (pointX<=(x+width) && pointY<=(y+height))) return true;
    return false;
}
void TextShape::moveShape(const QPointF &diffPoint)
{
    this->x+=diffPoint.x();
    this->y+=diffPoint.y();
}
Drawing * TextShape::fromJson(const QJsonObject &json)
{
    TextShape *shape=new TextShape();
    shape->text=json["text"].toString();
    shape->penWidth=json["pointSize"].toInt();
    shape->penWidth=json["penWidth"].toInt();
    shape->penColor=json["penColor"].toString();
    if(const QJsonValue value=json["font"]; value.isObject())
    {
        QVariant variant(value.toVariant());
        QFont ffont=variant.value<QFont>();
        shape->font=ffont;
    }
    return shape;
}
QJsonObject TextShape::toJson() const
{
    QJsonObject json;
    json["text"]=this->text;
    json["pointSize"]=this->pointSize;
    json["penWidth"]=this->penWidth;
    json["penColor"]=this->penColor.name();
    QVariant value=QVariant::fromValue(font);
    json["font"]=value.toJsonObject();
    return json;
}
QColor TextShape::getPenColor() const
{
    return penColor;
}

void TextShape::setPenColor(const QColor &value)
{
    penColor = value;
}

int TextShape::getPenWidth() const
{
    return penWidth;
}

void TextShape::setPenWidth(int value)
{
    penWidth = value;
}

QString TextShape::getText() const
{
    return text;
}

void TextShape::setText(const QString &value)
{
    text = value;
}

QFont TextShape::getFont() const
{
    return font;
}

void TextShape::setFont(const QFont &value)
{
    font = value;
}

int TextShape::getX() const
{
    return x;
}

void TextShape::setX(int value)
{
    x = value;
}

int TextShape::getY() const
{
    return y;
}

void TextShape::setY(int value)
{
    y = value;
}

int TextShape::getPointSize() const
{
    return pointSize;
}

void TextShape::setPointSize(int value)
{
    pointSize=value;
}
