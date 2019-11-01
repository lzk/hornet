#ifndef WATCHER_H
#define WATCHER_H

#include <QThread>
class Watcher : public QThread
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = 0);
    ~Watcher();
    void run();
    void watcher_job();

signals:
    void server_restart();

private:
    bool abort;
};

#endif // WATCHER_H
