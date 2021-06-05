#ifndef DOORS_H
#define DOORS_H

#include "defines.h"

class doors : public QObject
{
    Q_OBJECT
    enum doors_state
    {
        OPENING,
        OPENED,
        CLOSING,
        CLOSED
    };

public:
    explicit doors(QObject *parent = nullptr);

signals:
    void closed_doors();
    void opened_doors();

public slots:
    void start_opening();
    void start_closing();

private slots:
    void open();
    void close();

private:
    doors_state cur_state;

    QTimer doors_open_timer;
    QTimer doors_close_timer;
    QTimer doors_stay_opened_timer;
};

#endif // DOORS_H
