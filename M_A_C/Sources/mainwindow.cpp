#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadplayer.h"
#include "mediaplayer.h"
#include "QWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     mPlayer = new MediaPlayer();
     //ui->statusBar->setMaximum(mPlayer->duration());

}

MainWindow::~MainWindow()
{
    delete ui;
    delete tPlayer;
    delete mPlayer;
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
        mPlayer->play();
    } else {
        boton->setIcon(icono_play);
        mPlayer->pause();
    }
}





void MainWindow::on_statusBar_valueChanged(int value)
{
    mPlayer->setPosition(value);
}
