#ifndef WINDOWLINKNAMES_H
#define WINDOWLINKNAMES_H

#include <QString>
#include <QMap>
class CommonHelper {

    public:
        QString topic;
        QString description;
        CommonHelper(const QString t, const QString descr) {
            topic = t;
            description = descr;
        }
};

class WindowLinkNames
{
public:
    WindowLinkNames();
    static inline QString fileLink = "fileHelpLink";
    static inline QString editLink = "editHelpLink";
    static inline QString saveLink = "saveHelpLink";
    static inline QString countLink = "countHelpLink";
    static inline QString nearLink = "nearHelpLink";

    static inline QMap<QString, CommonHelper> helpMap =
    {
        {fileLink, CommonHelper("Открытие файла", "Файл, к которому будет прилагаться статистика, можно открыть с помощью ввода в поле под меню 'File'."
                                "После ввода имени файла и нажатии кнопки 'Calculate', содержимое файла отобразиться во вкладке edit")},
        {editLink, CommonHelper("Редактирование файла", "Файл можно редактировать. Изменения оперативно будут обработаны в окне статистики")},
        {saveLink, CommonHelper("Сохранение файла", "Файл можно сохранить. Для этого достаточно просто закрыть программу")},
        {countLink, CommonHelper("Подсчет", "Окно с подсчетом сразу же появляется после нажатия кнопки 'Calculate'. В нем указывается отсортированное "
                                 "по убыванию число символов и рядом стоящие")},
        {nearLink, CommonHelper("Рядом стоящие", "Пример: мама - ма(3 штуки). Потому что ма и ам - одно и то же")},
    };
    static const QString text() {
        return QString("Помощь по программе<br>Программа позволяет открывать <a href='%1'>файл</a>, <a href='%2'>редактировать</a> его, <a href='%3'>сохранять</a>, "
                       "а также выполняет <a href='%4'>подсчеты</a> встречаемости символов"
                       "с сортировкой, а также считает количество <a href='%5'>рядом стоящих символов</a>")
                .arg(fileLink)
                .arg(editLink)
                .arg(saveLink)
                .arg(countLink)
                .arg(nearLink);
    }
    //static const QString text()
};

#endif // WINDOWLINKNAMES_H
