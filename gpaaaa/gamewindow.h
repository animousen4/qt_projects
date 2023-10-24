#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QApplication>

class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    GameWindow() {
        setFixedSize(400, 400);
        setWindowTitle("Mouse Catcher Game");

        // Создаем картинку, которая будет двигаться
        QPixmap image("mat/1.jpg");


        this->setMouseTracking(true);
        //this->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);

        imageLabel = new QLabel(this);
        imageLabel->setPixmap(image.scaled(40, 70));
        imageLabel->move(0, 0);

        // Устанавливаем таймер для обновления картинки
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWindow::moveImage);
        timer->start(50);

        // Инициализируем счетчик жизней
        lives = 3;

        // Инициализируем значения для триггер-радиуса и коэффициента скорости
        triggerRadius = 250;
        speedCoefficient = 300;
    }
public slots:
    void moveImage() {
        // Получаем текущие координаты картинки
        int x = imageLabel->x();
        int y = imageLabel->y();

        // Получаем координаты курсора мыши
        QPoint cursorPos = mapFromGlobal(QCursor::pos());

        // Вычисляем расстояние между картинкой и курсором
        float distance = std::sqrt(std::pow(cursorPos.x() - x, 2) + std::pow(cursorPos.y() - y, 2));

        // Вычисляем коэффициент скорости в зависимости от расстояния до курсора
        float speed = speedCoefficient / distance;

        // Если расстояние меньше триггер-радиуса, начинаем убегать от курсора
        if (distance < triggerRadius) {
            // Вычисляем направление движения
            double dx = x - cursorPos.x();
            double dy = y - cursorPos.y();

            // Нормализуем вектор направления, чтобы получить единичный вектор
            float length = std::sqrt(dx * dx + dy * dy);
            if (length > 0) {
                dx /= length;
                dy /= length;
            }

            // Перемещаем картинку в направлении, противоположном курсору мыши
            x += speed * dx;
            y += speed * dy;

            // Проверяем, не выходит ли картинка за пределы окна
            if (x < 0) x = 0;
            if (y < 0) y = 0;
            if (x > width() - imageLabel->width()) x = width() - imageLabel->width();
            if (y > height() - imageLabel->height()) y = height() - imageLabel->height();

            // Устанавливаем новые координаты для картинки
            imageLabel->move(x, y);
        }
    }
protected:
    // Обработка событий мыши
    void mousePressEvent(QMouseEvent* event) override {
        if (imageLabel->geometry().contains(event->pos())) {
            // Если игрок попал по картинке, отнимаем жизнь и обновляем счетчик
            lives--;
            qDebug() << "Жизни: " << lives;

            if (lives == 0) {
                // Если жизней не осталось, выводим сообщение о проигрыше
                QMessageBox::information(this, "Конец", "Игра окончена! Вы проиграли.");
                QApplication::quit();
                }
                }
                }

private:
    QLabel* imageLabel; // Картинка, которая будет двигаться
    QTimer* timer; // Таймер для обновления картинки
    int lives; // Счетчик жизней
    int triggerRadius; // Триггер-радиус
    float speedCoefficient; // Коэффициент скорости

    // Обработчик таймера для перемещения картинки

};

#endif // GAMEWINDOW_H
