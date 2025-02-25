#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QWidget>
#include<QFontDatabase>
#include<QBrush>
#include<QGridLayout>
#include<QFileDialog>
#include<QMessageBox>
#include<QGuiApplication>
#include<QScreen>
#include<QDebug>
#include<QStringListModel>
#include<QListView>
#include<QListWidget>
#include<QTreeView>
#include<QStyledItemDelegate>
#include<QAbstractItemView>
#include<QTreeWidgetItem>

#include<drawing.h>
#include<model.h>
#include<shapes_header/arcshape.h>
#include<shapes_header/lineshape.h>
#include<shapes_header/textshape.h>
#include<shapes_header/pointshape.h>
#include<shapes_header/polylineshape.h>
#include<shapes_header/polygonshape.h>
#include<shapes_header/ellipseshape.h>
#include<shapes_header/rectangleshape.h>
#include<shapes_header/roundedrectangleshape.h>
#include<shapes_header/pixmapshape.h>
#include<shapes_header/freehandshape.h>

#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    showFullScreen();
    ui->setupUi(this);
    PhaseIII();

}

void MainWindow::PhaseIII()
{
    this->ui->phaseIII->setVisible(true);
    this->ui->phaseIII->setGeometry(QRect(0,0,1369,900));
    this->model=new Model(this->ui->board);

    this->model->setColor(Qt::black);
    this->model->setPenWidth(1);
    this->model->setListWidget(this->ui->listWidget);

    this->model->setVisible(true);
    this->model->setGeometry(0,0,1144,700);
    this->model->setCordinates(this->ui->coordinatesModel);

    connect(this->ui->closeApp, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->model->setFlag(NOFLAG);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->ui->coordinatesScreen->setText(QString("x=%1,y=%2").arg(event->globalX()).arg(event->globalY()));
}

void MainWindow::on_blackColor_clicked()
{
    this->model->setColor(Qt::black);
}


void MainWindow::on_redColor_clicked()
{
    this->model->setColor(Qt::red);
}

void MainWindow::on_greenColor_clicked()
{
    this->model->setColor(Qt::green);
}

void MainWindow::on_blueColor_clicked()
{
    this->model->setColor(Qt::blue);
}

void MainWindow::on_mixColor_clicked()
{
    this->model->setColor(Qt::black);
}

void MainWindow::on_penWidthSlider_valueChanged(int value)
{
   this->model->setPenWidth(value);
}
void MainWindow::on_pickShape_clicked()
{
    this->model->setFlag(PICK);
}
void MainWindow::on_freeHandDraw_clicked()
{
    this->model->setFlag(FREEHAND);
}
void MainWindow::on_lineDraw_clicked()
{
    this->model->setFlag(LINE);
}
void MainWindow::on_rectangleDraw_clicked()
{
    this->model->setFlag(RECTANGLE);
}
void MainWindow::on_ellipseDraw_clicked()
{
    this->model->setFlag(ELLIPSE);
}
