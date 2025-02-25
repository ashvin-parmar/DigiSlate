#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include <QObject>
#include<drawing.h>
class RectangleShape : public Drawing
{
    Q_OBJECT
public:
    explicit RectangleShape(QObject *parent=nullptr);
    ~RectangleShape();

    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    QBrush getBrush() const;
    void setBrush(const QBrush &value);

    int getPenWidth() const;
    void setPenWidth(int value);

private:
    int x,y;
    int width,height;
    QColor penColor;
    QBrush brush;
    int penWidth;
    int number;
    static int count;
};

#endif // RECTANGLESHAPE_H
