#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H
\

#include <QThread>
#include <QWidget>

class QMediaPlayer;

class media_player : public QThread
{
public:
    // constructor
    // set name using initializer
    explicit media_player(QUrl *url = nullptr);

    // overriding the QThread's run() method
    void run();
private:
   QUrl *url = nullptr;
   QMediaPlayer *m_player = nullptr;
};

#endif
