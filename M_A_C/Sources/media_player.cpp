#include "media_player.h"

#include <QtWidgets>


    media_player::media_player(QUrl *url)
{
        this->url = url;
}


void media_player::run()
{
    m_player = new QMediaPlayer(this);


}
