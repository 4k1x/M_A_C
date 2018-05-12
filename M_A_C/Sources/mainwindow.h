#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mediaplayer.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QDir>
#include <QFileSystemModel>
#include <QTreeView>


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_play_puaseButton_clicked();

    void on_treeView_musica_pressed(const QModelIndex &index);

    void on_btn_next_clicked();

    void on_btn_back_clicked();

    void on_btn_stop_clicked();

    void on_mute_clicked();

    void on_volumen_up_clicked();

    void on_volumen_down_clicked();

    void durationChanged(qint64 duration);

    void positionChanged(qint64 position);

    void on_duracion_sliderMoved(int position);

    void duracion(qint64 duration);

    void posicion(qint64 position);

    void on_listPlay_itemClicked(QListWidgetItem *item);

    void on_listUsb_itemClicked(QListWidgetItem *item);

signals:


private:
    Ui::MainWindow *ui;

    MediaPlayer *mPlayer;

    QFileSystemModel modelo;
    QTreeView *treeMusica;
    QPushButton *btn_play;

    void cargarListUsb();
    void cargarTreeMusica(QString path);
    void setBtnToPlay();
    void setBtnToPause();
    void setPosicion();

};

#endif // MAINWINDOW_H
