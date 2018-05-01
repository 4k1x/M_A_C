#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadplayer.h"
#include "mediaplayer.h"
#include "QWidget"
#include <QDir>
#include <QPushButton>
#include <QFileSystemModel>
#include <QException>

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

    btn_play = ui->play_puaseButton;
    btn_play->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete tPlayer;
    delete mPlayer;

}



void MainWindow::on_play_puaseButton_clicked()
{

    QPixmap pixmap_pause(":/new/iconos/Iconos/icono-pause.png");
    QIcon icono_pausa(pixmap_pause);

    QPixmap pixmap_play(":/new/iconos/Iconos/icono_play.png");
    QIcon icono_play(pixmap_play);

    if (btn_play->isChecked()) {
        btn_play->setIcon(icono_pausa);
        mPlayer->play();

    } else {
        btn_play->setIcon(icono_play);
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

}

void MainWindow::on_treeView_musica_pressed(const QModelIndex &index)
{
    QString path = modelo.filePath(index);
    QFileInfo *info = new QFileInfo(path);
    if (info->isDir()) {
        QDir *dir = new QDir(path);
        mPlayer->crear_playList(dir);
        mPlayer->play();
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

void MainWindow::on_btn_next_clicked()
{
    mPlayer->playlist->next();
}

void MainWindow::on_btn_back_clicked()
{
    mPlayer->playlist->previous();

}

void MainWindow::on_btn_stop_clicked()
{
    QPixmap pixmap_play(":/new/iconos/Iconos/icono_play.png");
    QIcon icono_play(pixmap_play);
    btn_play->setChecked(false);
    btn_play->setIcon(icono_play);
    mPlayer->stop();
}

void MainWindow::on_mute_clicked()
{
    if (mPlayer->isMuted()) {
        mPlayer->setMuted(false);
    }else {
        mPlayer->setMuted(true);
    }
}

void MainWindow::on_volumen_up_clicked()
{
   QSlider volumen = ui->volumen;
   volumen.setValue();
}
