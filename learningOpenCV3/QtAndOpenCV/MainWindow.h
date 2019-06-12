#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/opencv.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool open(std::string file);

  public slots:
    void nextFrame();

  protected:
    void changeEvent(QEvent *e);

    virtual void paintEvent(QPaintEvent *e) override;

  private:
    void copyImage();

    Ui::MainWindow *ui;

    cv::VideoCapture cap;
    QImage qtImg;
    cv::Mat cvImg;
    QTimer *timer;
};

#endif  // MAINWINDOW_H
