template <class T>
void Queue<T>::ShowLikeString() {
	typename List<T>::Node* temp = this->head;

        if (this->head == nullptr) qDebug() << QString::toStdString("out: <empty>");
	else {
		while (temp->next != NULL) {
                        qDebug() << temp->data << QString::toStdString(" ");
			temp = temp->next;
		}
	}
}
template <typename T>
void Queue<T>::push(T data) {
	this->push_tail(data);
}
template <typename T>
void Queue<T>::pop() {
	if (!isEmpty()) {
		typename List<T>::Node* temp = this->head;
		temp = temp->next;
		delete this->head;
		this->head = temp;
	}
}
template <typename T>
void Queue<T>::Show() {
	this->ShowList();
}
template <typename T>
bool Queue<T>::isEmpty() {
	if (this->head == NULL)
		return true;
	return false;
}
template <typename T>
T Queue<T>::get() {
	if (!isEmpty())
		return this->head->data;
}
