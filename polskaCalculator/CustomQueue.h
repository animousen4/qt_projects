#include "CustomList.h"
#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H
template<class T>
class CustomQueue : protected CustomList<T> {
public:
    void push(T data);
    void pop();
    void Show();
    void ShowLikeString();
    bool isEmpty();
    T get();
};

template <class T>
void CustomQueue<T>::ShowLikeString() {
    typename CustomList<T>::Node* temp = this->head;

    if (this->head == nullptr) qDebug() << "out: <пусто>";
            else {
            while (temp!= NULL) {
                qDebug() << temp->data << " ";
                temp = temp->next;
            }
        }
}
template <typename T>
void CustomQueue<T>::push(T data) {
    this->push_tail(data);
}
template <typename T>
void CustomQueue<T>::pop() {
    if (!isEmpty()) {
        typename CustomList<T>::Node* temp = this->head;
        temp = temp->next;
        delete this->head;
        this->head = temp;
    }
}
template <typename T>
void CustomQueue<T>::Show() {
    this->ShowList();
}
template <typename T>
bool CustomQueue<T>::isEmpty() {
    if (this->head == NULL)
        return true;
    return false;
}
template <typename T>
T CustomQueue<T>::get() {
    if (!isEmpty())
        return this->head->data;
}

#endif // CUSTOMQUEUE_H
