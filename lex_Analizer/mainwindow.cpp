#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_an_clicked()
{



    scan(0);
}

void MainWindow::on_open_clicked()
{
   readFile();
}

void MainWindow::on_save_clicked()
{
    saveFile();
}
