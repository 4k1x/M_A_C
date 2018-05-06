#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadplayer.h"
#include "mediaplayer.h"
#include "QWidget"
#include <QDir>
#include <QPushButton>
#include <QFileSystemModel>
#include <QException>
#include <QDateTime>

/*
 *  HAY QUE MODIFICAR LOS CONNECT PARA LA BARRA DE AUDIO
 *  Y MPLAYER DE DURACION ETC TENGO QUE CREAR SLOT PARA LA BARRA Y
 * UN METODO PARA QUE A;ADA TIEMPO
 *
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   mPlayer = new MediaPlayer();

   cargarTreeMusica();

    btn_play = ui->play_puaseButton;
    btn_play->setCheckable(true);
    ui->volumen->setValue(mPlayer->volume());
    connect(ui->volumen,SIGNAL(valueChanged(int)),mPlayer,SLOT(setVolume(int)));
    connect(mPlayer,SIGNAL(volumeChanged(int)),ui->volumen,SLOT(setValue(int)));
    connect(mPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    connect(mPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(mPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(posicion(qint64)));
    connect(mPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(duracion(qint64)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete mPlayer;
}



void MainWindow::on_play_puaseButton_clicked()
{
    if (btn_play->isChecked()) {
        setBtnToPause();
        mPlayer->play();
    } else {
        setBtnToPlay();
        mPlayer->pause();
    }
}

void MainWindow::cargarTreeMusica()
{
    modelo.setRootPath(QDir::homePath());
    modelo.index(QDir::homePath());
    treeMusica = ui->treeView_musica;
    treeMusica->setModel(&modelo);
    treeMusica->setRootIndex(modelo.index(QDir::homePath()));
    treeMusica->setColumnHidden(1,true);
    treeMusica->setColumnHidden(2,true);
    treeMusica->setColumnHidden(3,true);
}


void MainWindow::on_treeView_musica_pressed(const QModelIndex &index)
{
    QString path = modelo.filePath(index);
    QFileInfo *info = new QFileInfo(path);
    if (info->isDir()) {
        QDir *dir = new QDir(path);
        mPlayer->crear_playList(dir);
        setBtnToPause();
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
    int next = mPlayer->next();
    if (next == 1) {
        setBtnToPlay();
    }

}

void MainWindow::on_btn_back_clicked()
{
  int back = mPlayer->back();
   if (back == 1) {
       setBtnToPlay();
   }
   else {
       ui->duracion->setMaximum(back);
   }
}

void MainWindow::on_btn_stop_clicked()
{
    mPlayer->stop();
    setBtnToPlay();
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
    int volumen = mPlayer->volume();
    mPlayer->setVolume(volumen + 5);
    qDebug() << volumen;
}

void MainWindow::on_volumen_down_clicked()
{
    int volumen = mPlayer->volume();
    mPlayer->setVolume(volumen - 5);
    qDebug() << volumen;
}

void MainWindow::setBtnToPlay()
{
    QPixmap pixmap_play(":/new/iconos/Iconos/icono_play.png");
    QIcon icono_play(pixmap_play);
    btn_play->setChecked(false);
    btn_play->setIcon(icono_play);
}

void MainWindow::setBtnToPause()
{
    QPixmap pixmap_pause(":/new/iconos/Iconos/icono-pause.png");
    QIcon icono_pausa(pixmap_pause);
    btn_play->setChecked(true);
    btn_play->setIcon(icono_pausa);
}

void MainWindow::on_duracion_sliderMoved(int position)
{
    qint64 valor = position * 1000;
    mPlayer->setPosition(valor);
}

void MainWindow::durationChanged(qint64 duration)
{
    int m_duration = duration / 1000;
    ui->duracion->setMaximum(m_duration);
   // ui->duracionNum->display(m_duration);
}

void MainWindow::positionChanged(qint64 position)
{
    if (!ui->duracion->isSliderDown())
        ui->duracion->setValue(position / 1000);
}

void MainWindow::duracion(qint64 duration)
{
    QTime time(0,0,0,0);
    time = time.addMSecs(duration);
    QString tPosition;
    int min = time.minute();
    int sec = time.second();
    ui->duracionNum->display(QString::number(min) + ":" + QString::number(sec));
    qDebug() << time.minute();
    qDebug() << time.second();

}

void MainWindow::posicion(qint64 position)
{
    QTime time(0,0,0,0);
    time = time.addMSecs(position);
    QString tPosition;
    int min = time.minute();
    int sec = time.second();
    ui->posicion->display(QString::number(min) + ":" + QString::number(sec));
    qDebug() << time.minute();
    qDebug() << time.second();
}





