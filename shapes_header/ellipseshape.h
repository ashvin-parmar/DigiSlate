#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

#include <QObject>
#include<drawing.h>
#include<QPainter>
#include<QPoint>
#include<QRect>
#include<QColor>
#include<QPen>
#include<QBrush>

class EllipseShape : public Drawing
{
    Q_OBJECT
public:
    explicit EllipseShape(QObject *parent=nullptr);
    ~EllipseShape();

    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;
    void moveShape(const QPointF &diffPoint) override;
    static Drawing *fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;


    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getHorizontalRadius() const;
    void setHorizontalRadius(int value);

    int getVerticalRadius() const;
    void setVerticalRadius(int value);

    int getPenWidth() const;
    void setPenWidth(int value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    QBrush getBrush() const;
    void setBrush(const QBrush &value);

    bool getIsCenter() const;
    void setIsCenter(bool value);

private:
    int x,y;
    int horizontalRadius;       //[In degree]
    int verticalRadius;
    int penWidth;
    QColor penColor;
    QBrush brush;
    bool isCenter;
    int number;
    static int count;
};

#endif // ELLIPSESHAPE_H
