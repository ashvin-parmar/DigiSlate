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
    font.setPointSize(pointSize*4);
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

}
bool TextShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
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
