#ifndef ROUNDEDRECTANGLESHAPE_H
#define ROUNDEDRECTANGLESHAPE_H

#include <QObject>
#include<drawing.h>
#include<QPainter>
#include<QPen>
#include<QColor>
#include<QBrush>

class RoundedRectangleShape : public Drawing
{
    Q_OBJECT
public:
    explicit RoundedRectangleShape(QObject *parent=nullptr);
    ~RoundedRectangleShape();

    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;
    void moveShape(const QPointF &diffPoint) override;
    static Drawing * fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    int getXRadius() const;
    void setXRadius(int value);

    int getYRadius() const;
    void setYRadius(int value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    QBrush getBrush() const;
    void setBrush(const QBrush &value);

    int getPenWidth() const;
    void setPenWidth(int value);

private:
    int x,y;
    int width,height;
    int xRadius,yRadius;
    QColor penColor;            //       size 200×100 pixels:
    QBrush brush;               //xRadius = 20 → 20% of 200 = 40 pixels
    int penWidth;               //yRadius = 20 → 20% of 100 = 20 pixels
    int number;
    static int count;
};

#endif // ROUNDEDRECTANGLESHAPE_H
