#ifndef THREADPLAYER_H
#define THREADPLAYER_H

#include <QThread>
#include "mediaplayer.h"

class ThreadPlayer : public QThread
{
    Q_OBJECT
public:
    explicit ThreadPlayer();

    void run() override;
     MediaPlayer * reproductor(){return player;}
private:
    MediaPlayer *player;
};

#endif // THREADPLAYER_H
