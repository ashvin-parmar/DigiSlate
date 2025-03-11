#ifndef LINESHAPE_H
#define LINESHAPE_H

#include "drawing.h"
#include <QColor>
#include <QPainter>

class LineShape : public Drawing {
    Q_OBJECT

public:
    //constructor and destructor
    explicit LineShape(QObject *parent = nullptr);
    ~LineShape();

    //Overridden methods
    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;
    void moveShape(const QPointF &diffPoint) override;
    static Drawing * fromJson(const QJsonObject &json);
    QJsonObject toJson() const override;

    //Setter getter
    QColor getPenColor() const;
    void setPenColor(const QColor &value);
    int getPenWidth() const;
    void setPenWidth(int value);
    int getX1() const;
    void setX1(int value);
    int getX2() const;
    void setX2(int value);
    int getY1() const;
    void setY1(int value);
    int getY2() const;
    void setY2(int value);

private:
    QColor penColor;
    int penWidth;
    int x1,x2,y1,y2;
    int number;
    static int count;
};

#endif // LINESHAPE_H
