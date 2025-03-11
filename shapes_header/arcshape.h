#ifndef ARCSHAPE_H
#define ARCSHAPE_H

#include <QObject>
#include <drawing.h>
class ArcShape : public Drawing
{
    Q_OBJECT
public:
    explicit ArcShape(QObject *parent=nullptr);
    ~ArcShape();

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

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    int getStartAngle() const;
    void setStartAngle(int value);

    int getSpanAngle() const;
    void setSpanAngle(int value);

    int getPenWidth() const;
    void setPenWidth(int value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

private:
    int x, y;               // Top-left of bounding rectangle
    int width, height;      // Bounding rectangle size
    int startAngle;         // [inputs in degree]       Start angle (in 1/16th degrees)
    int spanAngle;          // [inputs in degree]       Span angle (in 1/16th degrees)
    int penWidth;           // Line thickness
    QColor penColor;        // Arc color

    //To determine its address
    int number;
    static int count;
};

#endif // ARCSHAPE_H
