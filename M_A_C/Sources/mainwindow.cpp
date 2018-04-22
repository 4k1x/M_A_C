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
    QPushButton *boton = ui->play_puaseButton;
    boton->setCheckable(true);

    QPixmap pixmap_pause(":/new/iconos/Iconos/icono-pause.png");
    QIcon icono_pausa(pixmap_pause);

    QPixmap pixmap_play(":/new/iconos/Iconos/icono_play.png");
    QIcon icono_play(pixmap_play);

    if (!boton->isChecked()) {
        boton->setIcon(icono_pausa);
    } else {
        boton->setIcon(icono_play);
    }
}


