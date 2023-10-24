#include <QString>

template <typename T>
void List<T>::ShowLikeString() {
	Node* temp = head;
        if (head == nullptr) qDebug() << QString::toStdString("out: <empty>");
	else {
                while (temp->next != nullptr) {
                        qDebug() << temp->data;
			temp = temp->next;
		}
	}
}
template <typename T>
void List<T>::DeleteElement(T data) {
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
void List<T>::push_head(T data) {
	Node* temp = new Node;
	temp->data = data;
	if (isEmpty() == false) {
		temp->next = head;
		head = temp;
	}
	else {
		temp->next = NULL;
		head = temp;
	}
}
template <typename T>
void List<T>::push_tail(T data) {
	Node* temp = new Node;

	if (head == NULL) {
		head = new Node();
		head->next = NULL;
		head->data = data;
	}
	else {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new Node;
		temp->next->next = NULL;
		temp->next->data = data;
	}
}
template <typename T>
void List<T>::ShowList() {
	Node* temp = head;

        if (isEmpty()) qDebug() << QString::toStdString("out: <empty>");
	else {
                qDebug() << QString::toStdString("out: [");
                qDebug() << temp->data;
		while (temp->next != NULL) {
			temp = temp->next;
                        qDebug() << QString::toStdString(", ") << temp->data;
		}
                qDebug() << QString::toStdString("]");
	}
}
template <typename T>
bool List<T>::isEmpty() {
	if (head == NULL)
		return true;
	return false;
}
template <typename T>
void List<T>::ChangeElement(Node* temp, T data) {
	temp->data = data;
}
template <typename T>
typename List<T>::Node* List<T>::FindValueByData(T data) {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->data == data)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
template <typename T>
bool List<T>::FindValueByPtr(Node* temp) {
	if (temp == NULL) return false;
	return true;
}
template <typename T>
T List<T>::getfirst() {
	if (!isEmpty())
		return head->data;
}
template <typename T>
T List<T>::getlast() {
	if (!isEmpty()) {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		return temp->data;
	}
}
