#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QScreen>
#include <QTimer>
#include <QApplication>
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel* imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap("mat/11.jpg"));
    imageLabel->setAlignment(Qt::AlignCenter);
    setCentralWidget(imageLabel);

    // Отключаем возможность открытия окна на полный экран
       setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

    // Создаем таймер, который будет вызывать метод обработки событий через каждые 20 миллисекунд
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moveImage);
    timer->start(9);

    // Отображаем окно на экране
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveImage()
{
    QLabel* imageLabel = dynamic_cast<QLabel*>(centralWidget());
    if (imageLabel)
    {
        QPoint cursorPos = QCursor::pos();
        QRect imageRect = imageLabel->geometry();
        QRect screenRect = this->rect();//QApplication::primaryScreen()->availableGeometry();
        double newX = imageRect.x() + (cursorPos.x() - screenRect.width() / 2) / 50.0;
        double newY = imageRect.y() + (cursorPos.y() - screenRect.height() / 2) / 50.0;

        // Проверяем, чтобы изображение не вышло за границы поля
        if (newX < -imageRect.width() || newX > screenRect.width() ||
            newY < -imageRect.height() || newY > screenRect.height())
        {
            // Если изображение вышло за пределы поля, перемещаем его в центр окна
            newX = (screenRect.width() - imageRect.width()) / 2.0;
            newY = (screenRect.height() - imageRect.height()) / 2.0;
        }

        int intNewX = static_cast<int>(newX);
        int intNewY = static_cast<int>(newY);
        imageLabel->move(intNewX, intNewY);
        imageLabel->update();
    }
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QLabel* imageLabel = dynamic_cast<QLabel*>(centralWidget());
        if (imageLabel) {
            QPoint cursorPos = QCursor::pos();
            QRect imageRect = imageLabel->geometry();
            QRect clickableRect = imageRect.adjusted(50, 50, -50, -50); // увеличиваем область на 50 пикселей по каждой стороне
            if (clickableRect.contains(cursorPos) && !isImageChanged_) {
                imageLabel->setPixmap(QPixmap("mat/22.jpg"));
                imageLabel->update();
                isImageChanged_ = true;
            }
            else if (clickableRect.contains(cursorPos) && isImageChanged_) {
                imageLabel->setPixmap(QPixmap("mat/33.jpg"));
                imageLabel->update();
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{

    Q_UNUSED(event);
}
