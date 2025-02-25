#ifndef PIXMAPSHAPE_H
#define PIXMAPSHAPE_H

#include <QObject>
#include <drawing.h>
#include <QPainter>
#include <QPixmap>

class PixmapShape : public Drawing
{
    Q_OBJECT
public:
    explicit PixmapShape(QObject *parent=nullptr);
    ~PixmapShape();

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

    double getScaleFactor() const;
    void setScaleFactor(double value);

    qreal getRotationAngle() const;
    void setRotationAngle(const qreal &value);

    Qt::TransformationMode getTransformationMode() const;
    void setTransformationMode(const Qt::TransformationMode &value);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

private:
    int x,y;
    int width,height;
    double scaleFactor;
    qreal rotationAngle;
    Qt::TransformationMode transformationMode;
    QPixmap pixmap;
    int number;
    static int count;
};

#endif // PIXMAPSHAPE_H
