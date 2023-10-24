template <class T>
class Stack : protected List<T> {
public:
	void push(T data);
	void pop();
	void Show();
	bool isEmpty();
	void ShowLikeString();
	T get();
};
