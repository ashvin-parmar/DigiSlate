#ifndef TEXTSHAPE_H
#define TEXTSHAPE_H

#include <QObject>
#include<drawing.h>
#include<QPainter>
#include<QColor>

class TextShape : public Drawing
{
    Q_OBJECT
public:
    explicit TextShape(QObject *parent = nullptr);
    ~TextShape();

    //Overridden methods
    void draw(QPainter &painter) override;
    void clear() override;
    QString toString() override;
    void select(QPainter &painter) override;
    bool isPointInShapeRegion(const QPoint &point) override;

    //Setter getter
    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    int getPenWidth() const;
    void setPenWidth(int value);

    QString getText() const;
    void setText(const QString &value);

    QFont getFont() const;
    void setFont(const QFont &value);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getPointSize() const;
    void setPointSize(int value);

private:
    QColor penColor;
    int penWidth;
    int pointSize;
    QString text;
    QFont font;
    int x,y;
    int number;
    static int count;
};

#endif // TEXTSHAPE_H
