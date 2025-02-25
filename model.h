#ifndef MODEL_H
#define MODEL_H

#define NOFLAG -1
#define PICK 0
#define FREEHAND 1
#define LINE 2
#define CIRCLE 3
#define ELLIPSE 4
#define RECTANGLE 5

#include <QWidget>
#include <QList>
#include "drawing.h"
#include<QHash>
#include<QMouseEvent>
#include<QLabel>
#include<QListWidget>
#include<shapes_header/freehandshape.h>

class Model : public QWidget {
    Q_OBJECT

public:
    explicit Model(QWidget *parent = nullptr);
    ~Model();

    void addShape(Drawing *shape);  // Add shape and trigger redraw
    void removeShape(const QString &shape);
    void clearCanvas();                  // Clear canvas (painted shapes)
    void drawAll();
    QList<QString> getAllShapes();
    void processClicked(QPainter &painter);

    void setCordinates(QLabel *value);

    int getFlag() const;
    void setFlag(int value);
    QColor getColor() const;
    void setColor(const QColor &value);
    int getPenWidth() const;
    void setPenWidth(int value);

    QListWidget *getListWidget() const;
    void setListWidget(QListWidget *value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QList<Drawing*> shapes;
    QHash<QString,Drawing*> viewMap;
    int flag=NOFLAG;
    QLabel *cordinates;
    FreeHandShape *freeHandShape;
    Drawing *drawing;
    QColor color;
    int penWidth;
    QPoint pickPoint;
    QListWidget *listWidget;
};

#endif // MODEL_H
