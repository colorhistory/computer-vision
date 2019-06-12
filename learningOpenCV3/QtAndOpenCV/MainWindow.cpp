#include "bits/stdc++.h"

#include "MainWindow.h"
#include "QPainter"
#include "QTimer"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::open(std::string file) {
    if (!cap.open(file)) {
        return false;
    }

    cap.read(cvImg);
    qtImg = QImage(QSize(cvImg.cols, cvImg.rows), QImage::Format_RGB888);
    ui->frame->setMinimumSize(qtImg.width(), qtImg.height());
    ui->frame->setMaximumSize(qtImg.width(), qtImg.height());
    copyImage();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::nextFrame);
    timer->start(1000.0 / cap.get(cv::CAP_PROP_FPS));

    return true;
}

void MainWindow::nextFrame() {
    if (!cap.isOpened()) {
        return;
    }

    cap.read(cvImg);
    copyImage();

    this->update();
}

void MainWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawImage(QPoint(ui->frame->x(), ui->frame->y()), qtImg);
}

void MainWindow::copyImage() {
    cv::Mat cvHeader2QtImg(cv::Size(qtImg.width(), qtImg.height()), CV_8UC3, qtImg.bits());
    cv::cvtColor(cvImg, cvHeader2QtImg, cv::COLOR_BGR2RGB);
}
