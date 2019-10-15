#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "include/image.h"
#include "saveimagedialog.h"

#include <iostream>
#include <memory>
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mImagePixMap(),
      mImage(),
      ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    ui -> positionLabel -> setMargin(0);
    ui -> imageLabel -> setMouseTracking(true);
    ui -> centralwidget -> setMouseTracking(true);
    ui -> centralwidget -> installEventFilter(this);

    statusBar() -> hide();

    connectSignals();
    scaleImageLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Image MainWindow::image() const
{
    return mImage;
}

void MainWindow::setImage(const Image &image)
{
    mImage = image;
    mImagePixMap.convertFromImage(mImage.image());
    ui -> imageLabel -> setPixmap(mImagePixMap);
}

void MainWindow::cloneWindow()
{
    MainWindow* newWindow = new MainWindow();
    newWindow -> setImage(mImage);
    newWindow -> setAttribute(Qt::WA_DeleteOnClose);
    newWindow -> show();
}

void MainWindow::openNewWindow()
{
    MainWindow* newWindow = new MainWindow();
    newWindow -> setAttribute(Qt::WA_DeleteOnClose);
    newWindow -> show();
}

void MainWindow::connectSignals()
{
    connect(ui -> actionOpen, &QAction::triggered,
            this, &MainWindow::openImage);
    connect(ui -> actionClone, &QAction::triggered,
            this, &MainWindow::cloneWindow);
    connect(ui -> actionNew, &QAction::triggered,
            this, &MainWindow::openNewWindow);
    connect(ui -> actionSave, &QAction::triggered,
            this, &MainWindow::saveImage);
    connect(ui -> actionSave_As, &QAction::triggered,
            this, &MainWindow::saveImageAs);
}

//void ui -> centralWidget()::mouseMoveEvent(QMouseEvent* event)
//{
//    QString text;
//    text = QString("(%1 , %2)").arg(event->pos().x()).arg(event->pos().y());
//    ui -> imageLabel ->setText(text);
//}

void MainWindow::openImage(){
    QString filepath = QFileDialog::getOpenFileName((this), "Open the file");
    Image image = Image(filepath);
    setImage(image);
}

void MainWindow::saveImage()
{

    mImage.image().save(mImage.filePath(), mImage.fileFormat().toStdString().c_str() , 100);

}

void MainWindow::saveImageAs()
{

    // Gets the directory path where the user wants to store the image.
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select target directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    // Opens a Dialog to retrieve the name, format and quality of the image to be saved.
    SaveImageDialog* imageDialog = new SaveImageDialog(this);

    imageDialog -> exec();
    QString fileName   = imageDialog -> getFileName();
    QString fileFormat = imageDialog -> getFileFormat();
    int fileQuality = imageDialog -> getFileQuality();


    QString newPath(dir + "/" + fileName);
    mImage.image().save(newPath, fileFormat.toStdString().c_str() , fileQuality);

    delete imageDialog;

}

void MainWindow::scaleImageLabel()
{
    ui -> imageLabel -> setScaledContents( true );
    ui -> imageLabel -> setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (dynamic_cast<QWidget*>(obj) == ui -> centralwidget){
        if(event -> type() == QMouseEvent::MouseMove){
                QString text;
                QMouseEvent* ev_ = static_cast<QMouseEvent*>(event);
                text = QString("Position: (%1 , %2)").arg(ev_->pos().x()).arg(ev_->pos().y());
                ui -> positionLabel ->setText(text);
                return true;
        }else return false;
    }else return QMainWindow::eventFilter(obj, event);
   }

