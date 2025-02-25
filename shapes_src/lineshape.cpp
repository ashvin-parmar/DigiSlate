#include "shapes_header/lineshape.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include<QtMath>

int LineShape::count=1;
LineShape::LineShape(QObject *parent) : Drawing(parent), penColor(Qt::black), penWidth(1) {
    x1=0;
    x2=0;
    y1=0;
    y2=0;
    number=count++;
}

LineShape::~LineShape()
{

}

void LineShape::draw(QPainter &painter) {
    QPen pen(penColor, penWidth);
    painter.setPen(pen);
    painter.drawLine(x1,y1,x2,y2);
}

void LineShape::clear() {
    //line = QLine();  // Reset line, will be cleared on repaint
}
QString LineShape::toString()
{
    return QString("Line")+QString::number(number);
}
void LineShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    painter.drawPoint(this->x1,this->y1);
    painter.drawPoint(this->x2,this->y2);
}
bool LineShape::isPointInShapeRegion(const QPoint &point)
{
    //int because we want nearest click are allow
    int ao=qSqrt(pow(point.x()-x1,2)+pow(point.y()-y1,2));
    int ob=qSqrt(pow(x2-point.x(),2)+pow(y2-point.y(),2));
    int ab=qSqrt(pow(x2-x1,2)+pow(y2-y1,2));
//    printf("%d ,%d, %d\n",ao,ob,ab);
    if(ab==ao+ob) return true;
    return false;
}
QColor LineShape::getPenColor() const
{
    return penColor;
}

void LineShape::setPenColor(const QColor &value)
{
    penColor = value;
}

int LineShape::getPenWidth() const
{
    return penWidth;
}

void LineShape::setPenWidth(int value)
{
    penWidth = value;
}

int LineShape::getX1() const
{
    return x1;
}

void LineShape::setX1(int value)
{
    x1 = value;
}

int LineShape::getX2() const
{
    return x2;
}

void LineShape::setX2(int value)
{
    x2 = value;
}

int LineShape::getY1() const
{
    return y1;
}

void LineShape::setY1(int value)
{
    y1 = value;
}

int LineShape::getY2() const
{
    return y2;
}

void LineShape::setY2(int value)
{
    y2 = value;
}

//QFrame* LineShape::getFrameMenu() {
//    if (!frameMenu) {
//        setupFrameMenu();
//    }
//    return frameMenu;
//}
//void LineShape::setupFrameMenu() {
//    frameMenu = new QFrame();
//    frameMenu->setFrameStyle(QFrame::StyledPanel);
//    frameMenu->setFixedSize(250, 200);

//    QVBoxLayout *layout = new QVBoxLayout(frameMenu);

//    QHBoxLayout *pointLayout1 = new QHBoxLayout();
//    x1Input = new QSpinBox(); y1Input = new QSpinBox();
//    x2Input = new QSpinBox(); y2Input = new QSpinBox();
//    x1Input->setRange(0, 1000); y1Input->setRange(0, 1000);
//    x2Input->setRange(0, 1000); y2Input->setRange(0, 1000);
//    pointLayout1->addWidget(new QLabel("X1:")); pointLayout1->addWidget(x1Input);
//    pointLayout1->addWidget(new QLabel("Y1:")); pointLayout1->addWidget(y1Input);
//    layout->addLayout(pointLayout1);

//    QHBoxLayout *pointLayout2 = new QHBoxLayout();
//    pointLayout2->addWidget(new QLabel("X2:")); pointLayout2->addWidget(x2Input);
//    pointLayout2->addWidget(new QLabel("Y2:")); pointLayout2->addWidget(y2Input);
//    layout->addLayout(pointLayout2);

//    QHBoxLayout *widthLayout = new QHBoxLayout();
//    widthInput = new QSpinBox();
//    widthInput->setRange(1, 10);
//    widthLayout->addWidget(new QLabel("Pen Width:"));
//    widthLayout->addWidget(widthInput);
//    layout->addLayout(widthLayout);

//    QHBoxLayout *colorLayout = new QHBoxLayout();
//    colorButton = new QPushButton("Choose Color");
//    connect(colorButton, &QPushButton::clicked, this, &LineShape::chooseColor);
//    colorLayout->addWidget(colorButton);
//    layout->addLayout(colorLayout);

//    QHBoxLayout *buttonLayout = new QHBoxLayout();
//    saveButton = new QPushButton("Save");
//    cancelButton = new QPushButton("Cancel");
//    buttonLayout->addWidget(saveButton);
//    buttonLayout->addWidget(cancelButton);
//    layout->addLayout(buttonLayout);

//    connect(saveButton, &QPushButton::clicked, this, &LineShape::updateLineData);
//    connect(cancelButton, &QPushButton::clicked, frameMenu, &QFrame::hide);
//}

//void LineShape::updateLineData() {
//    line.setP1(QPoint(x1Input->value(), y1Input->value()));
//    line.setP2(QPoint(x2Input->value(), y2Input->value()));
//    penWidth = widthInput->value();
//    frameMenu->hide();
//}

//void LineShape::chooseColor() {
//    QColor newColor = QColorDialog::getColor(penColor);
//    if (newColor.isValid()) {
//        penColor = newColor;
//    }
//}
