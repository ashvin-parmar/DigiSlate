#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<model.h>
#include<QPushButton>
#include<QMouseEvent>
#include<QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void PhaseIII();

private slots:
    void on_freeHandDraw_clicked();

    void on_pickShape_clicked();

    void on_blackColor_clicked();

    void on_redColor_clicked();

    void on_greenColor_clicked();

    void on_blueColor_clicked();

    void on_mixColor_clicked();


    void on_penWidthSlider_valueChanged(int value);

    void on_lineDraw_clicked();

    void on_rectangleDraw_clicked();

    void on_ellipseDraw_clicked();

private:
    Ui::MainWindow *ui;
    Model *model;
};
#endif // MAINWINDOW_H
