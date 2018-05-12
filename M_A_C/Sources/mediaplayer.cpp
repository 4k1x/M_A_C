#include "mediaplayer.h"
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QFileInfo>
#include <QListWidget>
#include <QMainWindow>

MediaPlayer::MediaPlayer()
{
    playlist = new QMediaPlaylist;
    this->setPlaylist(playlist);
    //playlist->addMedia(QUrl::fromLocalFile("/home/clase/Descargas/Canserbero-Mundo-de-piedra.mp3"));

}

int MediaPlayer::crear_playList(const QDir *carpeta, QListWidget *lista)
{

    QFileInfoList listaFicheros = carpeta->entryInfoList(QDir::Files);
    for (int i = 1; i < listaFicheros.size(); i++)
    {
        if (listaFicheros.at(i).suffix() == "mp3") {
            QString item = carpeta->entryInfoList(QDir::Files).at(i).fileName();
            if (lista->findItems(item,Qt::MatchExactly).size() <= 0) {
                lista->addItem(carpeta->entryInfoList(QDir::Files).at(i).fileName());
                playlist->addMedia(QUrl::fromLocalFile(listaFicheros.at(i).filePath()));

                qDebug() << listaFicheros.at(i).filePath();
            }
        }

    }
    return playlist->mediaCount();
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


void MediaPlayer::setSound(int cancion)
{
    playlist->setCurrentIndex(cancion);
}


