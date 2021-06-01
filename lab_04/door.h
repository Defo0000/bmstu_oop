#ifndef DOOR_H
#define DOOR_H

#include "defines.h"

class door : public QObject
{
    Q_OBJECT
    enum door_state
    {
        OPENED,
        CLOSING,
        CLOSED,
        OPENING
    };

public:
    explicit door(QObject *parent = nullptr);

public slots:
    

private slots:

signals:
    void open();
    void close();

private:
    door_state _state;
};

#endif // DOOR_H
