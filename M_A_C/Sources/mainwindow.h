#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threadplayer.h"
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


    void on_treeView_musica_clicked(const QModelIndex &index);

    void on_treeView_musica_pressed(const QModelIndex &index);

    void on_btn_next_clicked();

    void on_btn_back_clicked();

    void on_btn_stop_clicked();

    void on_mute_clicked();

    void on_volumen_up_clicked();

private:
    Ui::MainWindow *ui;
    ThreadPlayer *tPlayer;
    MediaPlayer *mPlayer;
    QThread *hilo ;
    QFileSystemModel modelo;
    QTreeView *treeMusica;
    void cargarTreeMusica();
    QPushButton *btn_play;

    
};

#endif // MAINWINDOW_H
