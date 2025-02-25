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

}
bool RectangleShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
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
