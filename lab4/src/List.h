#pragma once
#include "Point.h"
#include "../../lab1/src/myString.h"

struct Node{
	Node* prev;		//указатель на предыдущий элемент
	Node* next;		//указатель на следующий элемент
	Circle data;	

    // конструктор узла
    Node(const Circle& data, Node* prev = nullptr, Node* next = nullptr) : data(data), prev(prev), next(next) {}

    // деструктор
    ~Node() {
        if (prev) prev->next = next; // редактируем связи предшестенника
        if (next) next->prev = prev; // редактируем связи наследника
    }
};

class List{
public:
	// конструктор
	List() : head(nullptr), tail(nullptr), size(0) {}
	~List() { clear(); }

	// методы
	void push_back(const Circle& given);
	void push_front(const Circle& given);
	bool pop_back();
	bool pop_front();
	void clear() { while (head) pop_front();};
	void print() const;
	size_t getSize() const { return size;};
	bool delete_el(const Circle& given);
	bool delete_all_el(const Circle& given);

	void sort();

	// TODO: сделать перегрузки для std::ostream и std::istream
	friend std::istream& operator>>(std::istream& stream, List& list);
	friend std::ostream& operator<<(std::ostream& stream, const List& list);

	void saveToFile(const MyString& filename) const;
	void loadFromFile(const MyString& filename);
	void loadFromFile();
	
private:
	Node* head;  // голова (начало 1 - ый эл) (появ после пушбэка)
	Node* tail;  // хвост (конец n - ый эл) (появляется после фронтпуша)
	size_t size; // кол-во эл
};



