#include <iostream>

class ListElement {
public:
	int value;
	ListElement* next;

	ListElement(int v) : value(v), next(nullptr) {};
	ListElement() : value(), next(nullptr) {};
	~ListElement() { std::cout << "Destructor for list element called"; }
};

class List {
public:
	ListElement* head;
	ListElement* cursor;

	List() : head(nullptr), cursor(nullptr) {};
	List(const List&);
	friend std::ostream& operator<<(std::ostream& os, const List& list);
	~List() { std::cout << "Destructor called!"; }
	
	void prepend(ListElement& e) {
		e.next = head;
		head = &e;
	}


};

List::List(const List& list) {
	if (list.head == nullptr) {
		head = nullptr;
		cursor = nullptr;
	}
	else {
		ListElement* h = new ListElement(list.head->value);
		ListElement* previous;
		head = h;
		previous = h;
		for (cursor = list.head->next; cursor != nullptr; ) {
			ListElement* le = new ListElement(cursor->value);
			previous->next = le;
			previous = le;
			cursor = cursor->next;
		}
		cursor = head;
	}
}

std::ostream& operator<<(std::ostream& os, const List& list) {
	ListElement* cursor = list.head;
	while (cursor) {
		os << cursor->value << std::endl;
		cursor = cursor->next;
	}
	return os;
}

/*int main() {
	List list;
	ListElement a(1);
	ListElement b(3);
	ListElement c(5);
	ListElement d(7);

	list.prepend(a);
	list.prepend(b);
	list.prepend(c);
	list.prepend(d);

	List copiedList = List(list);

	std::cout << copiedList;

	return 0;
}*/