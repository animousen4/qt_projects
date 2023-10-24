template <typename T>
void Stack<T>::push(T data) {
	this->push_tail(data);
}
template <typename T>
void Stack<T>::ShowLikeString() {
	typename List<T>::Node* temp = this->head;

        if (this->head == nullptr) qDebug() << QString::toStdString("out: <empty>");
	else {
                qDebug() << temp->data;
		while (temp->next != NULL) {
			temp = temp->next;
                        qDebug() << temp->data;
		}
	}
}
template <typename T>
void Stack<T>::pop() {
	if (!isEmpty()) {
		typename List<T>::Node* temp = this->head;
		if (this->head->next == NULL) {
			if (!isEmpty()) {
				typename List<T>::Node* temp = this->head;
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
void Stack<T>::Show() {
	this->ShowList();
}
template <typename T>
bool Stack<T>::isEmpty() {
	if (this->head == NULL)
		return true;
	return false;
}
template <typename T>
T Stack<T>::get() {
	if (!isEmpty()) {
		typename List<T>::Node* temp = this->head;
		while (temp->next) {
			temp = temp->next;
		}
		return temp->data;
	}
};
