#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStatusBar"
#include "QGLWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //statusBar()->showMessage(tr("Выберите фигуру"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

