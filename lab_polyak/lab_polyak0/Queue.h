template<class T>
class Queue : protected List<T> {
public:
	void push(T data);
	void pop();
	void Show();
	void ShowLikeString();
	bool isEmpty();
	T get();
};
