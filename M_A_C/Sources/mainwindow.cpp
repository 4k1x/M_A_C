#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "QWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_play_puaseButton_clicked()
{
    QPixmap pixmap(":/new/iconos/Iconos/icono-pause.png");
    QIcon icono_pausa(pixmap);
    ui->play_puaseButton->setIcon(icono_pausa);
}
