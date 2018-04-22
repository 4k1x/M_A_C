#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threadplayer.h"


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


    void on_horizontalSlider_valueChanged(int value);

    void on_statusBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    ThreadPlayer *tPlayer;
    MediaPlayer *mPlayer;
    QThread *hilo ;

    
};

#endif // MAINWINDOW_H
