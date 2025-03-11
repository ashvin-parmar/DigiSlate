#ifndef MODEL_H
#define MODEL_H

#define ENABLE true
#define DISABLE false

#define NOFLAG -1
#define PICK 0
#define FREEHAND 1
#define LINE 2
#define CIRCLE 3
#define ELLIPSE 4
#define RECTANGLE 5
#define IMAGE 6
#define GROUPPICK 7
#define UNGROUPPICK 8
#define RUBBER 9


#include <QWidget>
#include <QList>
#include "drawing.h"
#include<QHash>
#include<QMouseEvent>
#include<QLabel>
#include<QJsonArray>

#include<QListWidget>
#include<shapes_header/freehandshape.h>
#include<groupshape.h>

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

    static Model* fromJson(const QJsonObject &json,QWidget *parent=nullptr);
    QJsonObject toJson() const;

    void setCordinates(QLabel *value);

    int getFlag() const;
    void setFlag(int value);
    QColor getColor() const;
    void setColor(const QColor &value);
    int getPenWidth() const;
    void setPenWidth(int value);

    QListWidget *getListWidget() const;
    void setListWidget(QListWidget *value);

    QString getFilePath() const;
    void setFilePath(const QString &value);

    bool getDrag() const;
    void setDrag(bool value);

    bool getPageLines() const;
    void setPageLines(bool value);
    void alterPageLines();

    bool getResize() const;
    void setResize(bool value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QList<Drawing*> shapes;
    QHash<QString,Drawing*> viewMap;
    int flag=NOFLAG;
    bool drag=DISABLE;
    bool resize=DISABLE;
    QLabel *cordinates;
    FreeHandShape *freeHandShape;
    QRect *rubber;
    bool pageLines=false;
    Drawing *drawing;
    QColor color;
    int penWidth;
    QPoint pickPoint;
    QListWidget *listWidget;
    QString filePath;
    GroupShape *groupShapes;
    QPoint initialPoint;
    QPoint currentPoint;
    QPoint finalPoint;
};

#endif // MODEL_H
