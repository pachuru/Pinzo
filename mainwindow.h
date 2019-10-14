#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "include/image.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*!
     * \brief  mImage's getter.
     * \return mImage.
     */
    Image image() const;

    /*!
     * \brief sets mImage and mImagePixmap attributes.
     * \param image
     */
    void setImage(const Image &image);

    /*!
     * \brief clone Opens a new window with the current
     * image.
     */
    void clone();

private:
    /*!
     * \brief connectSignals connects menu options
     *  with its functions.
     *
     */
    void connectSignals();
    /*!
     * \brief openImageViewer opens a new ImageViewer
     * widget in a new window.
     */
    void openImageViewer();

    /*!
     * \brief scales and sets the size policy of the
     * ui's QLabel's element.
     */
    void scaleImage();

private:

    /*!
     * \brief mImagePixMap is a QPixmap needed to
     * represent the image in the GUI.
     */
    QPixmap mImagePixMap;
    Image mImage;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
