#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>

class MediaPlayer : public QMediaPlayer
{
private:
    QMediaPlaylist *playlist;

public:
    MediaPlayer();


    void crear_playList(const QDir *carpeta);
    void silenciar();
    int next();
    int back();

};

#endif // MEDIAPLAYER_H
