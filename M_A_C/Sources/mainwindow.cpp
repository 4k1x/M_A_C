#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadplayer.h"
#include "mediaplayer.h"
#include "QWidget"
#include <QDir>
#include <QPushButton>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);



   QThread *th = new QThread();
   mPlayer = new MediaPlayer();
   mPlayer->moveToThread(th);
   th->start();
   qDebug() << th->isRunning();
   cargarTreeMusica();

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

void MainWindow::cargarTreeMusica()
{
    modelo.setRootPath("/home/clase");
    modelo.index("/home/clase");
    treeMusica = ui->treeView_musica;
    treeMusica->setModel(&modelo);
    treeMusica->setRootIndex(modelo.index("/home/clase"));
    treeMusica->setColumnHidden(1,true);
    treeMusica->setColumnHidden(2,true);
    treeMusica->setColumnHidden(3,true);
}

void MainWindow::on_treeView_musica_clicked(const QModelIndex &index)
{
    QString path = modelo.filePath(index);
    QFileInfo *info = new QFileInfo(path);
    if (info->isDir()) {
        QDir dir = info->dir();

    }
    else {
        if ("mp3" == info->suffix()) {
            qDebug() << info->absoluteFilePath();
            qDebug() << info->suffix();
            mPlayer->pause();
            mPlayer->setMedia(QUrl::fromLocalFile(info->absoluteFilePath()));
            mPlayer->play();
        }
    }
}
