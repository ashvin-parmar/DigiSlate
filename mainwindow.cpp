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
#include<QJsonDocument>
#include<QColorDialog>
#include<QRadioButton>

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

#define MAX_PAGES 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    showFullScreen();
    ui->setupUi(this);
    //Work on later ==> In Self Application [Commend those lines for them to be whike working on it.]
    this->ui->rubber->setVisible(false);
    this->ui->logo->setVisible(false);
    this->ui->resizeShape->setVisible(false);
    this->ui->coordinatesScreen->setVisible(false);

    createLook();
    PhaseIII();

}
void MainWindow::createLook()
{
    QString mainWindowStyleSheet="QMainWindow {background-color: #D4ECFF;}";
    QString frameStyleSheet="QFrame {border: none;}";
//"QFrame#boardFrame { background-color: rgba(255, 255, 255, 0.9); border: none; border-radius: 4px; }";
    QString transparentButtonStyleSheet="QPushButton{ background-color: rgba(0, 0, 0, 0); color: white; border: none;}";
    QString borderedButtonStyleSheet="QPushButton { }";
    QString fancyButtonStyleSheet="QPushButton {background: white; border: 0px solid gray; border-radius: 5px;}";
    QString groupBoxStyleSheet="QGroupBox {background-color: transparent; border: none;}";


    setStyleSheet(mainWindowStyleSheet);
    this->ui->dynamicShape->setStyleSheet(frameStyleSheet+borderedButtonStyleSheet);
//    this->ui->dynamicShape->setStyleSheet(frameStyleSheet+fancyButtonStyleSheet);
    this->ui->otherToolFrame->setStyleSheet(frameStyleSheet+transparentButtonStyleSheet);
    this->ui->boardWindow->setStyleSheet(groupBoxStyleSheet);
    this->ui->closeApp->setStyleSheet(fancyButtonStyleSheet);

}
void MainWindow::PhaseIII()
{
    this->ui->phaseIII->setVisible(true);
    this->ui->phaseIII->setGeometry(QRect(0,0,1369,900));

    QHBoxLayout *hl=new QHBoxLayout();
    this->ui->boardWindow->setLayout(hl);
    this->ui->boardWindow->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    hl->setAlignment(Qt::AlignmentFlag::AlignLeft);

    QRadioButton *radioButton=new QRadioButton(this->ui->boardWindow);
    radioButton->setVisible(true);
    radioButton->setToolTip("Page "+QString::number(countPage));
    connect(radioButton,&QRadioButton::clicked,this,[this,radioButton](bool checked){
        if(checked==true)
        {
            QString value=radioButton->toolTip();
            QString toSearch=value.right(value.size()-5);       //"Page " are of 5 character
            int val=toSearch.toInt();
            Model *newModel=this->pages[val];
            if(newModel==nullptr) return;
            newModel->setVisible(true);
            this->model->setVisible(false);

            QListWidget *newListWidget=newModel->getListWidget();
            newListWidget->setVisible(true);
            this->listWidget->setVisible(false);
            this->model=newModel;
            this->listWidget=newListWidget;
            this->listWidget->setParent(this);
            this->ui->penWidthSlider->setValue(this->model->getPenWidth());
            this->model->update();
        }
        else
        {
            QString value=radioButton->toolTip();
            QString toSearch=value.right(value.size()-5);       //"Page " are of 5 character
            int val=toSearch.toInt();
            Model *newModel=this->pages[val];
            if(newModel==nullptr) return;
            newModel->setVisible(false);
            newModel->getListWidget()->setVisible(false);
        }
    });
    hl->addWidget(radioButton);
    radioButton->setChecked(true);

    this->model=new Model(this->ui->board);
    pages[countPage]=model;
    this->ui->boardWindow->setChecked(true);

//    this->model->setColor(Qt::black);
//    this->model->setPenWidth(1);
//    this->model->setListWidget(this->ui->listWidget);
    listWidget=this->model->getListWidget();
    listWidget->setParent(this);
    listWidget->setGeometry(1232,42,131,371);
    listWidget->setToolTip("List of Shapes");
    listWidget->setVisible(true);


    this->model->setVisible(true);
    this->model->setGeometry(0,0,1144,700);
    this->model->setCordinates(this->ui->coordinatesModel);
    QPixmap pixmap(":/images/icon2/watermark.png","PNG");
    QPixmap scaledPixmap=pixmap.scaled(200,100,Qt::AspectRatioMode::KeepAspectRatio,Qt::TransformationMode::SmoothTransformation);
    this->ui->watermark->setPixmap(scaledPixmap);

    connect(this->ui->closeApp, &QPushButton::clicked, this, [=]() {
//        this->close();
        exit(0);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
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
//    this->model->setColor(Qt::black);
    QColor selectedColor=QColorDialog::getColor(Qt::black,this,"Select Color");
    if(selectedColor.isValid())
    {
        this->model->setColor(selectedColor);
    }
    else
    {
        this->model->setColor(Qt::black);
    }
}

void MainWindow::on_penWidthSlider_valueChanged(int value)
{
   this->model->setPenWidth(value);
   this->ui->penWidthSpinBox->setValue(value);
}

void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    this->model->setPenWidth(arg1);
    this->ui->penWidthSlider->setValue(arg1);
}

void MainWindow::on_pickShape_clicked()
{
    this->model->setFlag(PICK);
}
void MainWindow::on_freeHandDraw_clicked()
{
    this->model->setFlag(FREEHAND);
}
void MainWindow::on_rubber_clicked()
{
    this->model->setFlag(RUBBER);
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

void MainWindow::on_circleDraw_clicked()
{
    this->model->setFlag(CIRCLE);
}

void MainWindow::on_imageDraw_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::homePath(),"Images (*.jpg *.png)");
    if(filePath.compare("")==1)
    {
        QPixmap pixmap(filePath);
        if(pixmap.isNull()==false)
        {
        this->model->setFlag(IMAGE);
        this->model->setFilePath(filePath);
        return;
        }
    }
    QMessageBox::warning(this,"File Error","File not select");
}

void MainWindow::on_addNewPage_clicked()
{
    if(countPage>MAX_PAGES)
    {
           QMessageBox::warning(this,"Page Limit Exceed","Page limit reached. \nNo more pages added.");
           return ;
    }
    this->model=new Model();
    this->model->setParent(this->ui->board);
    this->model->setGeometry(0,0,1144,700);

    this->ui->penWidthSlider->setValue(this->model->getPenWidth());
    this->listWidget=this->model->getListWidget();
    listWidget->setParent(this);
    listWidget->setGeometry(1232,42,131,371);
    listWidget->setToolTip("List of Shapes");
    listWidget->setVisible(true);

    this->model->setVisible(true);
    this->model->setCordinates(this->ui->coordinatesModel);
    this->model->update();

    if(countPage==MAX_PAGES)
    {
           QMessageBox::warning(this,"Page Limit Reached","You cannot add more pages from next time.\nBecause maximum number of pages reached.");
    }
    QRadioButton *radioButton=new QRadioButton(this->ui->boardWindow);
    radioButton->setChecked(true);
    radioButton->setToolTip("Page "+QString::number(++countPage));
    this->ui->boardWindow->layout()->addWidget(radioButton);
    this->pages[countPage]=model;

    connect(radioButton,&QRadioButton::clicked,this,[this,radioButton](bool checked){
            if(checked==true)
            {
                QString value=radioButton->toolTip();
                QString toSearch=value.right(value.size()-5);       //"Page " are of 5 character
                int val=toSearch.toInt();
                Model *newModel=this->pages[val];
                if(newModel==nullptr) return;
                newModel->setVisible(true);
                this->model->setVisible(false);

                QListWidget *newListWidget=newModel->getListWidget();
                newListWidget->setVisible(true);
                this->listWidget->setVisible(false);

                this->model=newModel;
                this->listWidget=newListWidget;

                this->listWidget->setParent(this);
                this->ui->penWidthSlider->setValue(this->model->getPenWidth());
                this->model->update();
            }
            else
            {
                QString value=radioButton->toolTip();
                QString toSearch=value.right(value.size()-5);       //"Page " are of 5 character
                int val=toSearch.toInt();
                Model *newModel=this->pages[val];
                if(newModel==nullptr) return;
                newModel->setVisible(false);
                newModel->getListWidget()->setVisible(false);
            }
        });
}

void MainWindow::on_saveFile_clicked()
{
QString saveFile=QFileDialog::getSaveFileName(this,tr("Save File"),QDir::homePath(),tr("Files (*.slate)"));
if(saveFile.compare("")==1)
{
    if(saveFile.endsWith(".slate")==false)
    {
        saveFile+=".slate";
    }
    QFile file(saveFile);
    if(file.exists()==true)
    {
        QMessageBox::warning(this,"File Error","File already exist");
        return;
    }
    cout<<(saveFile.toStdString())<<endl;
    QJsonObject json=this->model->toJson();
    QJsonDocument *docs=new QJsonDocument();
    docs->setObject(json);
    QByteArray byteArray=docs->toJson();
    if(!file.open(QIODevice::WriteOnly | QIODevice::ReadOnly))
    {
//        qWaring("Couldn't open file");
        return ;
    }
    file.write(byteArray);
    file.close();
    delete docs;
}
}

void MainWindow::on_openFile_clicked()
{
    QString openFile=QFileDialog::getOpenFileName(this,tr("Open File"),QDir::homePath(),tr("Files (*.slate)"));
    if(openFile.compare("")==1)
    {
        QFile file(openFile);
        if(file.exists()==false)
        {
            QMessageBox::warning(this,"File Error","File not exist");
            return;
        }
        cout<<(openFile.toStdString())<<endl;
        if(!file.open(QIODevice::WriteOnly | QIODevice::ReadOnly))
        {
    //        qWaring("Couldn't open file");
            return ;
        }
        QJsonDocument docs(QJsonDocument::fromJson(file.readAll()));
        if(docs.isNull()) printf("Null");
        QJsonObject jsonObject=docs.object();
        if(jsonObject.isEmpty()) printf("Empty");
        this->model=Model::fromJson(jsonObject,this->ui->board);
        this->model->setParent(this->ui->board);
        this->model->setGeometry(0,0,1144,700);

        this->ui->penWidthSlider->setValue(this->model->getPenWidth());
        this->listWidget=this->model->getListWidget();
        listWidget->setParent(this);
        listWidget->setGeometry(1232,42,131,371);
        listWidget->setToolTip("List of Shapes");
        listWidget->setVisible(true);

        this->model->setVisible(true);
        this->model->setCordinates(this->ui->coordinatesModel);
        this->model->update();
        if(countPage>MAX_PAGES)
        {
               QMessageBox::warning(this,"Page Limit Exceed","Page limit reached, Necessary changes have been done on the same page.");
               return ;
        }
        if(countPage==MAX_PAGES)
        {
               QMessageBox::warning(this,"Page Limit Reached","You cannot add more pages from next time.\nBecause maximum number of pages reached.");
        }
        QRadioButton *radioButton=new QRadioButton(this->ui->boardWindow);
        radioButton->setChecked(true);
        radioButton->setToolTip("Page "+QString::number(++countPage));
        this->ui->boardWindow->layout()->addWidget(radioButton);
        this->pages[countPage]=model;

        connect(radioButton,&QRadioButton::clicked,this,[this,radioButton](bool checked){
            if(checked==true)
            {
                QString value=radioButton->toolTip();
                QString toSearch=value.right(value.size()-5);       //"Page " are of 5 character
                int val=toSearch.toInt();
                Model *newModel=this->pages[val];
                if(newModel==nullptr) return;
                newModel->setVisible(true);
                this->model->setVisible(false);

                QListWidget *newListWidget=newModel->getListWidget();
                newListWidget->setVisible(true);
                this->listWidget->setVisible(false);
                this->model=newModel;
                this->listWidget=newListWidget;
                this->listWidget->setParent(this);
                this->ui->penWidthSlider->setValue(this->model->getPenWidth());
                this->model->update();
            }
            else
            {
                QString value=radioButton->toolTip();
                QString toSearch=value.right(value.size()-5);       //"Page " are of 5 character
                int val=toSearch.toInt();
                Model *newModel=this->pages[val];
                if(newModel==nullptr) return;
                newModel->setVisible(false);
                newModel->getListWidget()->setVisible(false);
            }
        });
    }
}

void MainWindow::on_drag_clicked()
{
    this->model->setDrag(ENABLE);
//    this->model->setFlag(PICK);
    this->model->setResize(DISABLE);
//    int flag=this->model->getFlag();
//    if(!(flag==PICK || flag==GROUPPICK)) this->model->setFlag(NOFLAG);

}

void MainWindow::on_group_shape_clicked()
{
    this->model->setFlag(GROUPPICK);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key::Key_Control) this->model->setFlag(GROUPPICK);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    //if(event->key()==Qt::Key::Key_Control) this->model->setFlag(UNGROUPPICK);
}
void MainWindow::on_clearScreen_clicked()
{
    this->model->clearCanvas();
}

void MainWindow::on_pageScreen_clicked()
{
    this->model->alterPageLines();
}

void MainWindow::on_resizeShape_clicked()
{
    this->model->setResize(ENABLE);
    this->model->setDrag(DISABLE);
}
