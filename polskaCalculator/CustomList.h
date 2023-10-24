
#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H
#include <QDebug>
template<class T>
class CustomList {
protected:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* head = nullptr;
public:
    bool isEmpty();
    void push_head(T);
    void push_tail(T);
    void ChangeElement(Node*, T);
    void DeleteElement(T);
    Node* FindValueByData(T);
    bool FindValueByPtr(Node*);
    void ShowList();
    void ShowLikeString();
    T getfirst();
    T getlast();
};

template <typename T>
void CustomList<T>::ShowLikeString() {
    Node* temp = head;
    if (head == nullptr) qDebug() << "out: <пусто>";
            else {
            while (temp->next != nullptr) {
                qDebug() << temp->data;
                temp = temp->next;
            }
        }
}
template <typename T>
void CustomList<T>::DeleteElement(T data) {
    Node* temp = FindValueByData(data);
    Node* save = head;
    if (!isEmpty() and temp != nullptr) {
        if (temp == head) {
            Node* temp = head;
            temp = temp->next;
            delete head;
            head = temp;
        }
        else {
            while (save->next != temp)
                save = save->next;
            save->next = temp->next;
            delete temp;
        }
    }
}
template <typename T>
void CustomList<T>::push_head(T data) {
    Node* temp = new Node;
    temp->data = data;
    if (isEmpty() == false) {
        temp->next = head;
        head = temp;
    }
    else {
        temp->next = nullptr;
        head = temp;
    }
}
template <typename T>
void CustomList<T>::push_tail(T data) {
    Node* temp = new Node;

    if (head == nullptr) {
        head = new Node();
        head->next = nullptr;
        head->data = data;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new Node;
        temp->next->next = nullptr;
        temp->next->data = data;
    }
}
template <typename T>
void CustomList<T>::ShowList() {
    Node* temp = head;

    if (isEmpty()) qDebug() << "out: <пусто>";
            else {
            qDebug() << "out: [";
            qDebug() << temp->data;
            while (temp->next != NULL) {
                temp = temp->next;
                qDebug() << ", " << temp->data;
            }
            qDebug() << "]";
        }
}
template <typename T>
bool CustomList<T>::isEmpty() {
    if (head == nullptr)
        return true;
    return false;
}
template <typename T>
void CustomList<T>::ChangeElement(Node* temp, T data) {
    temp->data = data;
}
template <typename T>
typename CustomList<T>::Node* CustomList<T>::FindValueByData(T data) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}
template <typename T>
bool CustomList<T>::FindValueByPtr(Node* temp) {
    if (temp == nullptr) return false;
    return true;
}
template <typename T>
T CustomList<T>::getfirst() {
    if (!isEmpty())
        return head->data;
}
template <typename T>
T CustomList<T>::getlast() {
    if (!isEmpty()) {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->data;
    }
}

#endif // CUSTOMLIST_H
