#ifndef STATCOLLECTORDIALOG_H
#define STATCOLLECTORDIALOG_H

#include <QDialog>
#include <QTextEdit>
struct KV{
    QChar k;
    int v;
};
namespace Ui {

class StatCollectorDialog;
}

class StatCollectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatCollectorDialog(QWidget *parent = nullptr, QTextEdit * textEdit = nullptr);
    QTextEdit * textEdit;
    ~StatCollectorDialog();

private:
    Ui::StatCollectorDialog *ui;
    QChar sootvSymbols[65536];
    int symbolAmount[65536];
    QString displaySymbol(QChar s);
    QString getCase(int num);
    const QString separators = ":;!?., \\|/()[]{}\n";
    bool isSeparator(QChar c);

public slots:
    void collectStat();
    void collectPairStat();
};

#endif // STATCOLLECTORDIALOG_H
