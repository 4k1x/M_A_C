#include "mediaplayer.h"
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QFileInfo>

MediaPlayer::MediaPlayer()
{
    this->setMedia(QUrl::fromLocalFile("/home/clase/Descargas/Canserbero-Mundo-de-piedra.mp3"));
}

void MediaPlayer::crear_playList(const QDir *carpeta)
{
    playlist = new QMediaPlaylist;
    QFileInfoList listaFicheros = carpeta->entryInfoList(QDir::Files);
    for (int i = 1; i < listaFicheros.size(); i++)
    {
        if (listaFicheros.at(i).suffix() == "mp3") {
            playlist->addMedia(QUrl::fromLocalFile(listaFicheros.at(i).filePath()));
            qDebug() << listaFicheros.at(i).filePath();
        }

    }
    this->setPlaylist(playlist);
}
