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
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void PhaseIII(); 

private:
    void createLook();
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

    void on_circleDraw_clicked();

    void on_imageDraw_clicked();

    void on_addNewPage_clicked();

    void on_saveFile_clicked();

    void on_openFile_clicked();

    void on_drag_clicked();

    void on_group_shape_clicked();

    void on_rubber_clicked();

    void on_clearScreen_clicked();

    void on_penWidthSpinBox_valueChanged(int arg1);

    void on_pageScreen_clicked();

    void on_resizeShape_clicked();

private:
    Ui::MainWindow *ui;
    QListWidget *listWidget;
    Model *model;
    int countPage=1;
    QMap<int,Model *> pages;
};
#endif // MAINWINDOW_H
