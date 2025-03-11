#ifndef DRAWING_H
#define DRAWING_H

#include <QPainter>
#include <QFrame>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
class Drawing : public QObject
{
    Q_OBJECT
public:
    explicit Drawing(QObject *parent = nullptr):QObject(parent) {}
    virtual ~Drawing() {}

    virtual void draw(QPainter &painter) = 0;   // Must be implemented in derived classes
    virtual void clear() = 0;                   // Clears the shape
    virtual QString toString()=0;
    virtual void select(QPainter &painter)=0;
    virtual bool isPointInShapeRegion(const QPoint &point)=0;
    virtual void moveShape(const QPointF &diffPoint)=0;

//    static void fromJson(Drawing *shape,const QJsonObject &json);
    virtual QJsonObject toJson() const=0;

};

#endif // DRAWING_H
