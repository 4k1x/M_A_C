#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadplayer.h"
#include "mediaplayer.h"
#include "QWidget"
#include <QDir>
#include <QPushButton>

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
   cargarTree();

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
        mPlayer->stop();
    }
}

void MainWindow::cargarTree()
{
    modelo.setRootPath("/home/clase");
    modelo.index("/home/clase");
    QTreeView *tree = ui->treeView;
    tree->setModel(&modelo);
    tree->setRootIndex(modelo.index("/home/clase"));
    tree->setColumnHidden(1,true);
    tree->setColumnHidden(2,true);
    tree->setColumnHidden(3,true);
}
