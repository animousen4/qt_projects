#include "CustomList.h"
#ifndef CUSTOMSTACK_H
#define CUSTOMSTACK_H
\
template <class T>
class CustomStack : protected CustomList<T> {
public:
    void push(T data);
    void pop();
    void Show();
    bool isEmpty();
    void ShowLikeString();
    T get();
};

template <typename T>
void CustomStack<T>::push(T data) {
    this->push_tail(data);
}
template <typename T>
void CustomStack<T>::ShowLikeString() {
    typename CustomList<T>::Node* temp = this->head;

    if (this->head == nullptr) qDebug() << "out: <пусто>";
            else {
            qDebug() << temp->data;
            while (temp->next != NULL) {
                temp = temp->next;
                qDebug() << temp->data;
            }
        }
}
template <typename T>
void CustomStack<T>::pop() {
    if (!isEmpty()) {
        typename CustomList<T>::Node* temp = this->head;
        if (this->head->next == NULL) {
            if (!isEmpty()) {
                typename CustomList<T>::Node* temp = this->head;
                temp = temp->next;
                delete this->head;
                this->head = temp;
            }
        }
        else {
            while (temp->next->next != NULL)
                temp = temp->next;
            temp->next = NULL;
        }
    }
}
template <typename T>
void CustomStack<T>::Show() {
    this->ShowList();
}
template <typename T>
bool CustomStack<T>::isEmpty() {
    if (this->head == NULL)
        return true;
    return false;
}
template <typename T>
T CustomStack<T>::get() {
    if (!isEmpty()) {
        typename CustomList<T>::Node* temp = this->head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->data;
    }
};
#endif // CUSTOMSTACK_H
