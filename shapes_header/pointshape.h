#ifndef POINTSHAPE_H
#define POINTSHAPE_H

#include <QObject>
#include<drawing.h>
#include<QColor>
#include<QPainter>

class PointShape : public Drawing
{
    Q_OBJECT
public:
    explicit PointShape(QObject *parent=nullptr);
    ~PointShape();
    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;
    void moveShape(const QPointF &diffPoint) override;
    static Drawing* fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    int getPenWidth() const;
    void setPenWidth(int value);

private:
    int x,y;
    QColor penColor;
    int penWidth;
    int number;
    static int count;
};

#endif // POINTSHAPE_H
