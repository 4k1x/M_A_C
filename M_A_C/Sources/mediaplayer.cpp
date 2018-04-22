#include "mediaplayer.h"
#include <QObject>
#include <QMediaPlayer>

MediaPlayer::MediaPlayer()
{
    this->setMedia(QUrl::fromLocalFile("/home/clase/Descargas/Canserbero-Mundo-de-piedra.mp3"));
}
