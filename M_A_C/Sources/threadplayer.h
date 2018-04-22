#ifndef THREADPLAYER_H
#define THREADPLAYER_H

#include <QThread>

class ThreadPlayer : public QThread
{
    Q_OBJECT
public:
    explicit ThreadPlayer(QObject *parent = nullptr);

    void run();

 private:

};

#endif // THREADPLAYER_H
