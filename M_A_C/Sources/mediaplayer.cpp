#include "mediaplayer.h"
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QFileInfo>
#include <QMainWindow>

MediaPlayer::MediaPlayer()
{
    playlist = new QMediaPlaylist;
    this->setPlaylist(playlist);
    playlist->addMedia(QUrl::fromLocalFile("/home/clase/Descargas/Canserbero-Mundo-de-piedra.mp3"));

}

void MediaPlayer::crear_playList(const QDir *carpeta)
{
    QStringList lista;
    QFileInfoList listaFicheros = carpeta->entryInfoList(QDir::Files);
    for (int i = 1; i < listaFicheros.size(); i++)
    {
        if (listaFicheros.at(i).suffix() == "mp3") {
            lista << carpeta->entryInfoList(QDir::Files).at(i).fileName();
            playlist->addMedia(QUrl::fromLocalFile(listaFicheros.at(i).filePath()));

            qDebug() << listaFicheros.at(i).filePath();
        }

    }
     qDebug() << playlist->mediaCount();
}

int MediaPlayer::next()
{
    if (playlist->mediaCount() > 1) {
        playlist->next();
        if (playlist->currentIndex() < 0) {
           return 1;
           qDebug() << playlist->currentIndex();
        }
        return 0;
         qDebug() << playlist->currentIndex();
    }
}

int MediaPlayer::back()
{
    if (playlist->mediaCount() > 1) {
       playlist->previous();
       if (playlist->currentIndex() < 0) {
          return 1;
          qDebug() << playlist->currentIndex();
       }
       return 0;
    }
}



