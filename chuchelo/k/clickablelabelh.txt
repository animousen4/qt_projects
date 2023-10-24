#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QLabel>
#include <QObject>
#include <QMouseEvent>
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    ClickableLabel(QWidget* w) : QLabel(w) {

    }

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            emit clicked();
        }
    }
};
#endif // CLICKABLELABEL_H
