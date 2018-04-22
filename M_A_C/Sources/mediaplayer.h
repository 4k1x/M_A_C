#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMultimedia>
#include <QMediaPlayer>

class MediaPlayer : public QMediaPlayer
{
public:
    MediaPlayer();
    void play();
    void pause();
    void stop();
    void duration();
    void position();
    void MediaPlayer

};

#endif // MEDIAPLAYER_H
