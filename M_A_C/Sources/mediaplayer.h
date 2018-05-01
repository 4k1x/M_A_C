#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>

class MediaPlayer : public QMediaPlayer
{
private:

public:
    MediaPlayer();
    QMediaPlaylist *playlist;

    void crear_playList(const QDir *carpeta);

};

#endif // MEDIAPLAYER_H
