#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threadplayer.h"
#include <QWidget>
#include <QPushButton>
#include <QDir>
#include <QFileSystemModel>


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


private:
    Ui::MainWindow *ui;
    ThreadPlayer *tPlayer;
    MediaPlayer *mPlayer;
    QThread *hilo ;
    QFileSystemModel modelo;
    QDir path;
    void cargarTree();


    
};

#endif // MAINWINDOW_H
