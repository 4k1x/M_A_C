/**
 *  @file    mediaplayer.h
 *  @author  Francisco Calleja Vazquez (4k1x)
 *  @date    12/05/2018
 *  @version 1.0
 *
 */

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QDir>

class MediaPlayer : public QMediaPlayer
{
private:
    QMediaPlaylist *playlist;

public:
    MediaPlayer();


    int crear_playList(const QDir *carpeta, QListWidget *lista);
    void silenciar();
    int next();
    int back();
    void setSound(int cancion);

};

#endif // MEDIAPLAYER_H
