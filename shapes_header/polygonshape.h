#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include <QObject>
#include <QPainter>
#include <QVector>
#include <drawing.h>
#include <QColor>

class PolygonShape : public Drawing
{
    Q_OBJECT
public:
    explicit PolygonShape(QObject *parent=nullptr);
    ~PolygonShape();

    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;
    void moveShape(const QPointF &diffPoint) override;
    static Drawing *fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

    QVector<QPoint> getPoints() const;
    void setPoints(const QVector<QPoint> &value);
    void addPoint(const QPoint &point);

    int getPenWidth() const;
    void setPenWidth(int value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    QBrush getBrush() const;
    void setBrush(const QBrush &value);

private:
    QVector<QPoint> points;
    int penWidth;
    QColor penColor;
    QBrush brush;
    int number;
    static int count;
};

#endif // POLYGONSHAPE_H
