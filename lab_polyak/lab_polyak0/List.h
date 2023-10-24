template<class T>
class List {
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
