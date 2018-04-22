#include "threadplayer.h"
#include "mediaplayer.h"

ThreadPlayer::ThreadPlayer() : QThread()
{

}

void ThreadPlayer::run()
{
    player = new MediaPlayer();
}


