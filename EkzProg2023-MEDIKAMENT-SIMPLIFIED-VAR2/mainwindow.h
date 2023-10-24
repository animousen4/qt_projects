#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mcl.h>
#include <QFile>
#include <TableModels.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ABS_Med * s1;
    ABS_Med * s2;
    ABS_Med * m;

    void loadData(bool bin = false);
    void updateData();

    Medicine_All mergeAB(Medicine_Section*a, Medicine_Price *b) {
        Medicine_All m;

        for (Items elItems : *a->mas) {
            Med med{BaseData{elItems.name,elItems.date}, ExtraItems{elItems.section, elItems.count}, ExtraPrice{0}};

            Price * p = b->selectWithLatestDate(elItems.name);

            if (p != nullptr) {
                med.price = p->price;
                if (QDateTime::fromString(med.date, "mm.yyyy") <  QDateTime::fromString(p->date, "mm.yyyy")) {
                    med.date = p->date;
                }

            }
            m.mas->append(med);
        }

        for (Price elPrice: *b->mas) {
            auto med = std::find_if(m.mas->begin(), m.mas->end(), [elPrice](Med& med){
                    return med.name == elPrice.name;
            });
            if (med == m.mas->end()) {
                Med newMed{BaseData{elPrice.name,elPrice.date}, ExtraItems{"Not defined", 0}, ExtraPrice{elPrice.price}};
                m.mas->append(newMed);
            }
            //Med med{BaseData{elItems.name,elItems.date}, ExtraItems{elItems.section, elItems.count}, ExtraPrice{0}};
        }

        return m;

    }

};


#endif // MAINWINDOW_H
