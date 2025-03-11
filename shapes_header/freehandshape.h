#ifndef FREEHANDSHAPE_H
#define FREEHANDSHAPE_H

#include <QObject>
#include<drawing.h>

class FreeHandShape : public Drawing
{
    Q_OBJECT
public:
    explicit FreeHandShape(QObject *parent=nullptr);
    ~FreeHandShape();

    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;
    void moveShape(const QPointF &diffPoint) override;
    static Drawing * fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

    void addPoint(const QPoint &point);
    int pathSize() const;

    QColor getColor() const;
    void setColor(const QColor &value);

    int getPenWidth() const;
    void setPenWidth(int value);

private:
    QPolygon drawPath;
    QColor color;
    int penWidth;
    static int count;
    int number;
};

#endif // FREEHANDSHAPE_H
