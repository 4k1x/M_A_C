#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mediaplayer.h"
#include "QWidget"
#include <QDir>
#include <QPushButton>
#include <QFileSystemModel>
#include <QException>
#include <QDateTime>
#include <QStorageInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   this->setFixedSize(size());

   mPlayer = new MediaPlayer();

   cargarTreeMusica(QDir::homePath());
   cargarListUsb();

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

void MainWindow::on_treeView_musica_pressed(const QModelIndex &index)
{
    QString path = modelo.filePath(index);
    QFileInfo *info = new QFileInfo(path);
    if (info->isDir()) {
        QDir *dir = new QDir(path);
        int numSongs = mPlayer->crear_playList(dir, ui->listPlay);
        if (numSongs > 0) {
            //setBtnToPause(); // Si se quiere que inicie nada mas pulsar la carpeta
            //mPlayer->play();
        }
    }
    else {
        if ("mp3" == info->suffix()) {
            qDebug() << info->absoluteFilePath();
            qDebug() << info->suffix();
            mPlayer->pause();
            mPlayer->setMedia(QUrl::fromLocalFile(info->absoluteFilePath()));
            mPlayer->play();
            setBtnToPause();
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
}

void MainWindow::on_volumen_down_clicked()
{
    int volumen = mPlayer->volume();
    mPlayer->setVolume(volumen - 5);
    qDebug() << volumen;
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
    if (!ui->duracion->isSliderDown()){
        ui->duracion->setValue(position / 1000);
    }
    if (mPlayer->state() == QMediaPlayer::StoppedState){
        setBtnToPlay();
    }
}

void MainWindow::duracion(qint64 duration)
{
    QTime time(0,0,0,0);
    time = time.addMSecs(duration);
    QString tPosition;
    int min = time.minute();
    int sec = time.second();
    ui->duracionNum->display(QString::number(min) + ":" + QString::number(sec));
}

void MainWindow::posicion(qint64 position)
{
    QTime time(0,0,0,0);
    time = time.addMSecs(position);
    QString tPosition;
    int min = time.minute();
    int sec = time.second();
    ui->posicion->display(QString::number(min) + ":" + QString::number(sec));
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

void MainWindow::cargarTreeMusica(QString path)
{
    modelo.setRootPath(path);
    modelo.index(path);
    treeMusica = ui->treeView_musica;
    treeMusica->setModel(&modelo);
    treeMusica->setRootIndex(modelo.index(path));
    treeMusica->setColumnHidden(1,true);
    treeMusica->setColumnHidden(2,true);
    treeMusica->setColumnHidden(3,true);
}

void MainWindow::cargarListUsb()
{
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
           if (storage.isValid() && storage.isReady()) {
               if (!storage.isReadOnly()) {
                   if (storage.device() != "tmpfs") {
                       QPixmap pixmap_usb(":/new/iconos/Iconos/icono-usb.ico");
                       QIcon icono_usb(pixmap_usb);
                       QListWidgetItem *item = new QListWidgetItem();
                       item->setIcon(icono_usb);
                       item->setText(storage.name());
                       if (storage.rootPath() == "/") {
                           item->setData(2,QVariant("home"));
                           item->setData(3,QVariant(storage.rootPath()));
                       }
                       else {
                           item->setData(2,QVariant(storage.name()));
                           item->setData(3,QVariant(storage.rootPath()));
                       }
                       ui->listUsb->addItem(item);
                   }
               }
           }
       }
}

void MainWindow::on_listPlay_itemClicked(QListWidgetItem *item)
{
   int fila = item->listWidget()->row(item);
   mPlayer->setSound(fila);
}



void MainWindow::on_listUsb_itemClicked(QListWidgetItem *item)
{
    if (item->data(3) == "/") {
        cargarTreeMusica(QDir::homePath());
    }
    else {
        cargarTreeMusica(item->data(3).toString());
    }
}
