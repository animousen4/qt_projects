#ifndef EXPRESSIONCOMPLETER_H
#define EXPRESSIONCOMPLETER_H
#include <QCompleter>'
#include <CalculatorKernel.h>
class ExpressionCompleter : public QCompleter {
public:
    ExpressionCompleter(QObject * parent = nullptr) {
        //this->setFilterMode(Qt::Match)
    }
    QStringList splitPath(const QString& path) const override{
        auto v = CalculatorKernel().getCorrectExpression(path);
        return {v.expression};
    }
};
#endif // EXPRESSIONCOMPLETER_H
