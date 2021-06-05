#ifndef DOORS_H
#define DOORS_H

#include "defines.h"

class doors: public QObject
{
    Q_OBJECT

    enum doors_state
    {
        CLOSED,
        OPENING,
        OPENED,
        CLOSING
    };

public:
    explicit doors(QObject *parent = nullptr);

signals:
    void doors_closed();
    void doors_opened();

public slots:
    void closing();
    void opening();
    void closed();
    void opened();

private:
    doors_state state = CLOSED;
    QTimer opening_timer;
    QTimer stay_timer;
    QTimer closing_timer;
};

#endif // DOORS_H
