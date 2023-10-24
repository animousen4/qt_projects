#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "List.h"
#include "List.cpp"
#include "Queue.h"
#include "Queue.cpp"
#include "Stack.h"
#include "Stack.cpp"
#include <QDebug>
#include <fstream>
#include <QMessageBox>
using namespace std;


class Calculator
{
public:
    Calculator();

    template <typename K, typename V>
    struct Pair {
        K key;
        V value;
    };

    template <typename K, typename V>
    class Map : protected List < Pair <K, V> > {
    public:

        void add(K key, V value) {
            this->push_tail( {key, value} );
        }

        bool exist(K key) {
                try {
                    this->get(key);
                }
                catch (exception e) {
                    return false;
                }
                return true;
        }

        V get(K key) {
            typename List < Pair <K, V> >::Node* temp = this->head;

            while (temp != nullptr) {
                if (temp->data.key == key)
                    return temp->data.value;
                temp = temp->next;
            }
            throw exception();
        }
    };

    QString BalancedBrackets(QString expression) {
        QString result = expression;
        Stack <QChar> brackets;
        for (int i = 0; i < result.size(); i++) {
            QChar c = result[i];
            if (c == '(' || c == '[' || c == '{') brackets.push(c);
            else if (c == ')' || c == ']' || c == '}') {
                if (brackets.isEmpty()) {
                    QChar open_bracket;
                    if (c == ')') open_bracket = '(';
                    else if (c == ']') open_bracket = '[';
                    else if (c == '}') open_bracket = '{';
                    result.insert(i, open_bracket);
                    brackets.push(open_bracket);
                }
                else {
                    QChar open_bracket = brackets.get();
                    if (c == ')' && open_bracket != '(') {
                        result[i] = '(';
                        brackets.pop();
                        brackets.push('(');
                    }
                    else if (c == ']' && open_bracket != '[') {
                        result[i] = '[';
                        brackets.pop();
                        brackets.push('[');
                    }
                    else if (c == '}' && open_bracket != '{') {
                        result[i] = '{';
                        brackets.pop();
                        brackets.push('{');
                    }
                    else brackets.pop();
                }
            }
        }

        while (!brackets.isEmpty()) {
            QChar c = brackets.get();
            QChar close_bracket;
            if (c == '(') close_bracket = ')';
            else if (c == '[') close_bracket = ']';
            else if (c == '{') close_bracket = '}';
            result += close_bracket;
            brackets.pop();
        }

        return result;
    }

    QString OperatorsBetweenBrackets(QString str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ')' or str[i] == '}' or str[i] == ']')
                if (str[i + 1] == '(' or str[i + 1] == '{' or str[i + 1] == '[') {
                    str.insert(i+1, '*');
                    return str;
                }

        }
        return str;
    }

    QString EmptyBrackets(QString str) {
        for (int i = 0; i < str.length() - 1; i++) {

        if ((str[i] == '(' && str[i + 1] == ')') || (str[i] == '[' && str[i + 1] == ']') || (str[i] == '{' && str[i + 1] == '}')) {
          str.remove(i, 2);
          return str;
        }
        }
        return str;
    }

    QString EnoughOperator(QString str) {

        for (int i = 0; i <= str.length(); i++) {
            if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/')
                if (str[i + 1] == '+' or str[i + 1] == '-' or str[i + 1] == '*' or str[i + 1] == '/') {
                    str.remove(i + 1, 1);
                    return str;
                }
                else if (str[i + 1] == ')' or str[i + 1] == '}' or str[i + 1] == ']') {
                    str.remove(i, 1);
                    return str;
                }

            if (str[i] == '(' or str[i] == '{' or str[i] == '[')
                if (str[i + 1] == '*' or str[i + 1] == '/') {
                    str.remove(i + 1, 1);
                    return str;
                }
        }

        if (str[0] == '*' or str[0] == '/') {
            str.remove(0, 1);
            return str;
        }

        if (str[str.length() - 1] == '+' or str[str.length() - 1] == '-' or str[str.length() - 1] == '*' or str[str.length() - 1] == '/') {
            str.remove(str.length() - 1, 1);
            return str;
        }

        return str;
    }

    QString numberAndBracket(QString str) {
        for (int i = 0; i < str.length() - 1; i++) {
            if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
                if (str[i + 1] == '(' || str[i + 1] == '{' || str[i + 1] == '[') {
                    str.insert(i + 1, '*');
                    return str;
                }

            if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
                if (str[i + 1] >= '0' && str[i + 1] <= '9') {
                        str.insert(i + 1, '*');
                        return str;
                    }
        }
        return str;
    }

    bool isOperator(QChar c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isBracket(QChar c) {
        return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
    }

    bool isNumber(QChar c) {
        return c >= '0' && c <= '9';
    }

    int priority(QString a) {
        if (a == "+" or a == "-") return 2;
        if (a == "*" or a == "/") return 3;
    }


    double getValue(QString s, Map<QChar, double> v) {
        QString num;
        double value = 1;

        if (s[0] == '-') {
            value = -1;
            s.remove(0, 1);
        }

        for (QChar c : s) {

            if (isNumber(c)) num = num + c;
            else {
                if (!num.isEmpty()) {
                    value = value * num.toDouble();
                    num = "";
                }
                value = value * v.get(c);
            }
        }

        if (!num.isEmpty()) value = value * num.toDouble();

        return value;
    }

    void assess(QString vars) {

            Map <QChar, double> main_map;
            QString rawExp = enteredExpression;
            QString exp;
            bool badVarInduck = false;

            QString line;
            //while (getline(fin, line)) {
                if (!line.isEmpty()) {
                    int rposition = line.indexOf('=');
                    QChar variableName = line.mid(0, rposition)[0];
                    double variableValue = (line.mid(rposition + 1, line.length() - 1)).toDouble();

                    main_map.add(variableName, variableValue);

                    qDebug() << variableName << " = " << variableValue;
                }
            //}

            for (QChar c : rawExp) {

                if (c != ' ') {
                    exp += c;

                    if (!isOperator(c) && !isBracket(c) && !isNumber(c))
                        if (!main_map.exist(c)) {
                            qDebug() << "there is no variable " << c << " in the file";
                            badVarInduck = true;
                        }
                }
            }

            if (badVarInduck) {
                qDebug() << "enter missing variables";
                //system("pause");
                return;
            }

            qDebug() << exp;

            QString temp, globaltemp = temp, niceExp = exp;
            bool induck;
            bool globalInduck;

            globalInduck = true;
            while (globalInduck) {

                globaltemp = niceExp;

                induck = true;
                while (induck) {
                    temp = BalancedBrackets(niceExp);
                    if (niceExp != temp) niceExp = temp;
                    else induck = false;
                }

                induck = true;
                while (induck) {
                    temp = EmptyBrackets(niceExp);
                    if (niceExp != temp) niceExp = temp;
                    else induck = false;
                }

                induck = true;
                while (induck) {
                    temp = OperatorsBetweenBrackets(niceExp);
                    if (niceExp != temp) niceExp = temp;
                    else induck = false;
                }

                induck = true;
                while (induck) {
                    temp = numberAndBracket(niceExp);
                    if (niceExp != temp) niceExp = temp;
                    else induck = false;
                }

                induck = true;
                while (induck) {
                    temp = EnoughOperator(niceExp);
                    if (niceExp != temp) niceExp = temp;
                    else induck = false;
                }

                if (niceExp == globaltemp)
                    globalInduck = false;
            }

            if (niceExp != exp) qDebug() << "New expression " << niceExp;

            Queue <QString> queue;
            QString str;

            for (QChar a : niceExp) {
                if (isOperator(a) || isBracket(a)) {
                    if (str != "") {
                        queue.push(str);
                        str = "";
                    }
                    if (a != '-') queue.push(QString(QChar(a)));
                    else {
                        queue.push("+");
                        queue.push("-1");
                        queue.push("*");
                    }
                }
                else str += a;
            }

            if (str != "") queue.push(str);

            Stack<QString> s;
            Queue<QString> q;

            if (!queue.isEmpty())
                if (queue.get() == "+") queue.pop();

            while (!queue.isEmpty()) {
                str = queue.get();
                queue.pop();
                if (str == "+" or str == "-" or str == "*" or str == "/") {
                    if (s.isEmpty() or (priority(str) > priority(s.get()))) s.push(str);
                    else {
                        if (s.get() == "(" or s.get() == "{" or s.get() == "[") {
                            s.push(str);
                            continue;
                        }
                        else
                            while (!s.isEmpty() && ((priority(str) <= priority(s.get())) && (s.get() != "(" && s.get() != "{" && s.get() != "["))) {
                                q.push(s.get());
                                s.pop();
                            }
                        s.push(str);
                    }
                }
                else if (str == "(" or str == "{" or str == "[") {
                if (queue.get() == "+") queue.pop();
                s.push(str);
              }
              else if (str == ")" or str == "}" or str == "]") {
                    while (!s.isEmpty() and (s.get() != "(" and s.get() != "{" and s.get() != "[")) {
                      q.push(s.get());
                      s.pop();
                    }
                    s.pop();
                  }
                  else q.push(str);
            }

            while (!s.isEmpty()) {
                q.push(s.get());
                s.pop();
            }

            //q.ShowLikeString();
            //cout << endl;

            Stack <double> numBuf;
            QString current;
            double num1, num2;

            while (!q.isEmpty()) {
                current = q.get();

                if (current == "+" or current == "-" or current == "*" or current == "/") {
                    num2 = numBuf.get();
                    numBuf.pop();
                    num1 = numBuf.get();
                    numBuf.pop();

                    if (current == "+") numBuf.push(num1 + num2);
                    else
              if (current == "*") numBuf.push(num1 * num2);
              else
                if (current == "/") numBuf.push(num1 / num2);
                }
                else numBuf.push(getValue(current, main_map));
                q.pop();
            }

            qDebug() << "The answer is " << numBuf.get();
        }
 QString enteredExpression = "";

private:

};

#endif // CALCULATOR_H
