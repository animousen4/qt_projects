#include <QString>
#include <QException>
#include <functional>
#include "CustomStack.h"
#include "CustomQueue.h"
#include "CustomList.h"
#include <QList>
#include <QVector>
using namespace std;
#ifndef CALCULATORKERNEL_H
#define CALCULATORKERNEL_H

struct FuncDescription {
    QString description;
    QString (*function)(QString badExp);

};

struct SolvedError {
    QString expression;
    QVector<QString> errors;

    bool hasError() {
        return !errors.isEmpty();
    }
};

class CalculatorKernel {

    static int preority(QString a) {
        if (a == "+" or a == "-") return 2;
        if (a == "*" or a == "/") return 3;
        return 2;
    }


    static bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }


    static bool isOpeningBracket(QChar c) {
        return (c == '(' || c == '{' || c == '[');
    }

    static bool isClosingBracket(QChar c) {
        return (c == ')' || c == '}' || c == ']');
    }

    static bool isValidBracketPair(QChar open, QChar close) {
        return (open == '(' && close == ')') || (open == '{' && close == '}') || (open == '[' && close == ']');
    }

    static char getReverseCloseBracket(QChar br) {
        return br == '{' ? '}' : br == '[' ? ']' : ')';
    }

    static char getReverseOpenBracket(QChar br) {
        return br == '}' ? '{' : br == ']' ? '[' : '(';
    }


    static bool isOperator(QString s) {
        return s == "+" or s == "-" or s == "*" or s == "/";
    }
    static bool isLetter(QChar c) {
        int code = c.unicode();
        return (code >= 0x41 and code <= 0x5A) ||
               (code >= 0x61 && code <= 0x7A);
    }
    static bool isNumber(QChar c) {
        int code = c.unicode();
        return (code >= 0x30 && code <= 0x39);
    }

    static QString offerEquationOperator(QString str, int pos) {
        //str.insert(pos + 1, 1, '*');
        str.insert(pos + 1, '*');
        return str;
    }

    static QString offerRemoveSymbol(QString str, int pos) {
        str.remove(pos, 1);
        return str;
    }

    static QString offerRemoveEmptyBrackets(QString str, int firstBracketPos) {
        str.remove(firstBracketPos, 2);
        return str;
    }
    static QString OperatorsBetweenBrackets(QString str) {
        for (int i = 0; i < str.length() - 1; i++) {
            if (str[i] == ')' or str[i] == '}' or str[i] == ']')
                if (str[i + 1] == '(' or str[i + 1] == '{' or str[i + 1] == '[') {
                    return offerEquationOperator(str, i);
                }

        }
        return str;
    }
    static QString EmptyBrackets(QString str) {
        for (int i = 0; i < str.length() - 1; i++) {
            if (str[i] == '(' or str[i] == '{' or str[i] == '[')
                if (str[i + 1] == ')' or str[i + 1] == '}' or str[i + 1] == ']') {
                    return offerRemoveEmptyBrackets(str, i);
                }
        }
        return str;
    }
    static QString EnoughOperator(QString str) {
        for (int i = 0; i < str.length() - 1; i++) {
            if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/')
                if (str[i + 1] == '+' or str[i + 1] == '-' or str[i + 1] == '*' or str[i + 1] == '/') {

                    return offerRemoveSymbol(str, i);
                }
                else if (str[i + 1] == ')' or str[i + 1] == '}' or str[i + 1] == ']') {
                    return offerRemoveSymbol(str, i);
                }

            if (str[i] == '(' or str[i] == '{' or str[i] == '[')
                if (str[i + 1] == '*' or str[i + 1] == '/') {
                    return offerRemoveSymbol(str, i);
                }
        }
        if (str[0] == '*' or str[0] == '/') {
            return offerRemoveSymbol(str, 0);
        }

        if (str[str.length() - 1] == '+' or str[str.length() - 1] == '-' or str[str.length() - 1] == '*' or str[str.length() - 1] == '/') {
            return offerRemoveSymbol(str, str.length() - 1);
        }
        return str;
    }
    static QString BracketAndOperand(QString str) {
        for (int i = 0; i < str.length() - 1; i++) {
            if (str[i] != '(' and str[i] != '{' and str[i] != '[')
                if (str[i] != '+' and str[i] != '-' and str[i] != '*' and str[i] != '/')
                    if (str[i + 1] == '(' or str[i + 1] == '{' or str[i + 1] == '[') {
                        return offerEquationOperator(str, i);
                    }

            if (str[i] == ')' or str[i] == '}' or str[i] == ']')
                if (str[i + 1] != '+' and str[i + 1] != '-' and str[i + 1] != '*' and str[i + 1] != '/')
                    if (str[i + 1] != ')' and str[i + 1] != '}' and str[i + 1] != ']') {
                        return offerEquationOperator(str, i);
                    }
        }
        return str;
    }


    double calculateExpression(QString exp, QMap<QChar, double> m) {

        double result = 1;
        int i;

        QChar c;
        if (exp[0] == '-') {
            exp = exp.mid(1, exp.length() - 1);
            result = -1;
        }

        i = 0;

        QString curr = "";
        while (i < exp.length()) {
            c = exp[i];
            if (!isLetter(c))
                curr += c;
            else {
                if (curr != "")
                    result *= curr.toDouble();

                if (m.contains(c))
                    result *= m[c];
                curr = "";
            }
            i = i + 1;
        }

        if (curr != "")
            result *= curr.toDouble();

        return result;

    }

    static bool isCorrectSymbol(QChar c) {
        int code = c.unicode();
        return (isLetter(c) ||
                (code >= 0x28 && code <= 0x2B) ||
                code == 0x2D || c == '/'
                || c == '[' || c == ']'
                || c == '{' || c == '}' || c == '.'
                || isNumber(c)
                );
    }

    static QString ValidSymbols(QString str) {
        int i;
        i = 0;

        while (i < str.length()) {
            if (isCorrectSymbol(str[i]))
                i = i + 1;
            else {
                return offerRemoveSymbol(str, i);
            }
        }
        return str;
    }

public:

    static QString ValidBrackets(QString str) {

        CustomStack<QChar> openingBrackets;

        QString res = str;
        bool changed = true;
        while (changed) {
            changed = false;
            while (!openingBrackets.isEmpty()) {
                openingBrackets.pop();
            }
            for (int i = 0; i < res.length(); i++) {
                if (isOpeningBracket(res[i])) {
                    openingBrackets.push(res[i]);
                } else if (isClosingBracket(res[i])) {
                    if (openingBrackets.isEmpty()) {
                        QChar br = getReverseOpenBracket(res[i]);
                        res.remove(i, 1);
                        res.insert(i-1, br);
                        changed = true;
                        break;

                    } else if (openingBrackets.get() == getReverseOpenBracket(res[i])) {
                        openingBrackets.pop();
                    } else {
                        if (isClosingBracket(res[i])) {
                            QChar br = getReverseOpenBracket(res[i]);
                            res.remove(i, 1);
                            res.insert(i-1, br);
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }

        while (!openingBrackets.isEmpty()) {
            res += getReverseCloseBracket(openingBrackets.get());

            openingBrackets.pop();
        }
        return res;
    }

    SolvedError getCorrectExpression(QString exp) {
        QVector<QString> errors;
        bool changed = true;
        QString newExp = exp;
        int currFuncIndex = 0;
        static const QVector<FuncDescription> functions = {
            {"Unacceptable symbols", ValidSymbols},
            {"Unnecessary operator", EnoughOperator},
            {"Emptry brackets", EmptyBrackets},
            {"Brackets position error", ValidBrackets},
            {"Unspecified operator between brackets", OperatorsBetweenBrackets},
            {"Unspecified operator with operand between brackets", BracketAndOperand}
        };
        while (changed) {
            changed = false;
            if (newExp != "") {
                newExp = functions[currFuncIndex].function(newExp);
            }

            if (newExp != exp) {
                exp = newExp;
                changed = true;
                errors.append(functions[currFuncIndex].description);
                currFuncIndex = 0;
                continue;
            }
            else {
                currFuncIndex = currFuncIndex + 1;
                if (currFuncIndex < 6)
                    changed = true;
            }

        }

        return SolvedError{newExp, errors};
    }

    QList<QChar> getRequiredVars(QString strInput) {
        QList<QChar> v;
        for (QChar c : strInput) {
            if (isLetter(c) && !v.contains(c)) {
                v.append(c);
            }
        }

        sort(v.begin(), v.end(), [](QChar a, QChar b){
            return a.unicode() < b.unicode();
        });
        return v;
    }

    double calculateAll(QString strInput, QMap<QChar, double> vars) {

        QString str = "";

        // input
        CustomQueue<QString> queue;

        QChar a;

        int i = 0;
        while (i < strInput.length()) {
            a = strInput[i];
            if (a == '+' or a == '-' or a == '*' or a == '/' or a == '(' or a == ')'
                or a == '{' or a == '}' or a == '[' or a == ']') {

                if (str != "") {
                    queue.push(str);
                    str = "";
                }
                if (a == '-') {
                    queue.push("+");
                    queue.push("-1");
                    queue.push("*");
                }
                else
                    queue.push(QString(a));
            }
            else str += a;

            i = i + 1;
        }

        if (str != "")
            queue.push(str);

        CustomStack<QString> s;
        CustomQueue<QString> q;
        if (!queue.isEmpty())
            if (queue.get() == "+")
                queue.pop();
        while (!queue.isEmpty()) {
            str = queue.get();
            queue.pop();
            if (str == "+" or str == "-" or str == "*" or str == "/") {
                if (s.isEmpty() or (preority(str) > preority(s.get()))) {
                    s.push(str);
                }
                else {
                    if (s.get() == "(" or s.get() == "{" or s.get() == "[") {
                        s.push(str);
                        continue;
                    }
                    else
                        while (!s.isEmpty() and
                               (s.get() != "(" and s.get() != "{" and s.get() != "[" and ((preority(str) <= preority(s.get()))))) {
                            q.push(s.get());
                            s.pop();
                        }
                    s.push(str);
                }
            }
            else if (str == "(" or str == "{" or str == "[") {
                if (queue.get() == "-") {
                    queue.pop();
                    q.push("-" + queue.get());
                    queue.pop();
                } else
                    if (queue.get() == "+")
                        queue.pop();
                s.push(str);
            }
            else if (str == ")" or str == "}" or str == "]") {
                while (!s.isEmpty() and (s.get() != "(" and s.get() != "{" and s.get() != "[")) {
                    q.push(s.get());
                    s.pop();
                }
                s.pop();
            }
            else {
                q.push(str);
            }

        }
        while (!s.isEmpty()) {
            q.push(s.get());
            s.pop();
        }

        CustomStack<double> countStack;
        QString och;
        double first, second;
        while (!q.isEmpty()) {
            och = q.get();

            if (isOperator(och)) {
                second = countStack.get();
                countStack.pop();
                first = countStack.get();
                countStack.pop();


                if (och == "+")
                    countStack.push(first + second);
                else
                    if (och == "-")
                        countStack.push(first - second);
                    else
                        if (och == "*")
                            countStack.push(first * second);
                        else
                            if (och == "/")
                                countStack.push(first / second);

            }

            else {
                try {
                    countStack.push(calculateExpression(och, vars));
                }
                catch (QException e) {
                    qDebug() << e.what();

                }
            }
            q.pop();
        }

        return countStack.get();
    }

};
#endif // CALCULATORKERNEL_H
