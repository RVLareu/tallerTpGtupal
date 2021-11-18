#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Seteo un Objeto QGraphicsScene para manejar la escena del juego
    ui->view->setScene(&this->scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

