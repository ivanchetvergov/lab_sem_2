#include "List.h"
#include <iostream>
#include <algorithm> // swap
#include <fstream> // файлик

using std::cout;

std::ostream& operator<<(std::ostream& stream, const List& list) {
    Node* cur = list.head;
    while (cur) {
        stream << "radius: " << cur->data.get_radius() \
            << " center(x, y): (" << cur->data.get_x() \
            << ", " << cur->data.get_y() << ")\n";
        cur = cur->next;
    }
    stream << "operator << (list)\n\n";
    return stream;
}

std::istream& operator>>(std::istream& stream, List& list) {
    list.clear();

    double r, x, y;
    while (stream >> r >> x >> y) {
        list.push_back(Circle(r, x, y));
    }
    return stream;
}

void List::sort(){ // пузырьком 
	if (!head) return;

	bool flag = true;
    // мб переписать через сайз??
	while (flag) {
		Node* cur = head; // текущий узел
		flag = false;
		while (cur -> next){ // если есть след эл
			if (cur -> data.square() < cur -> next -> data.square()){ // 
				std::swap(cur -> data, cur -> next -> data);
				flag = true;
			}
			cur = cur -> next;
		}
	}
}

void List::push_back(const Circle& given){
	Node* newNode = new Node(given, tail, nullptr); // новый крайний узел (хвост)
	if (!head) head = newNode; // пустой
	if (tail) tail -> next = newNode; // если есть хвост, то в старом хвосте сохраняем указатель на новый хвост
    tail = newNode;
    ++size;
}

void List::push_front(const Circle& given){
	Node* newNode = new Node(given, nullptr, head); // новый крайний узел (голова)
	if (!tail) tail = newNode; // пустой
	if (head) head -> prev = newNode; // если есть голова, то в старой голове сохраняем указатель на новую голову
    head = newNode;
    ++size;
}

bool List::pop_back(){ 
	if (!tail || size == 0) return false;
	Node* toDel = tail; // копия

	tail = tail -> prev; // обновляем указ хвоста
	if (tail) tail-> next = nullptr; // если пред операция не нуллптр и есть хвост
	else head = nullptr;

    delete toDel;
	--size;
	return true;
}

bool List::pop_front(){
	if (!head || size == 0) return false;
	Node* toDel = head; // копия

	head = head -> next; // обновляем указ голову
	if (head) head -> prev = nullptr; // если пред операция не нуллптр и есть голова
	else tail = nullptr;

    delete toDel;
	--size;
	return true;
}

void List::print() const {
	if (head){
		Node* cur = head;
		while (cur){
			cur -> data.print();
			cur = cur -> next;
		}
	} else { cout << "is empty!"; };
	cout << "\n";
}

bool List::delete_el(const Circle& given) {  
    if (!head) return false;

    Node* cur = head;  

    while (cur) {  
        if (cur->data.get_radius() == given.get_radius()) { 
            if (cur == head) {   
                head = cur->next; 
                if (head) head->prev = nullptr; 
            } else {  
                cur->prev->next = cur->next;
            }  
 
            if (cur == tail) {   
                tail = cur->prev;   
                if (tail) tail->next = nullptr;
            } else {  
                if (cur->next) {  
                    cur->next->prev = cur->prev;
                }  
            }  

            delete cur;  
            --size;  
            return true;  
        }  
        cur = cur->next;
    }  
    return false;   
}

bool List::delete_all_el(const Circle& given) {  
    if (!head) return false;   

    bool flag = false;  
    Node* cur = head;  

    while (cur) {  
        if (cur->data.get_radius() == given.get_radius()) {  
            Node* toDelete = cur;   

            if (cur == head) {   
                head = cur->next;   
                if (head) head->prev = nullptr;   
            } else {  
                cur->prev->next = cur->next;   
            }  

            if (cur == tail) {   
                tail = cur->prev;  
                if (tail) tail->next = nullptr;   
            } else {  
                if (cur->next) {  
                    cur->next->prev = cur->prev;  
                }  
            }  

            cur = cur->next; 
            delete toDelete;   
            --size;  
            flag = true;   
        } else {  
            cur = cur->next;   
        }   
    }  
    return flag;  
}

void List::saveToFile(const MyString& filename) const{
    std::ofstream fout(filename.c_str());

    if (!fout){ 
        cout << "error file not open(save)\n"; 
        return; 
    }

    Node* cur = head;
    while (cur){
        fout << cur->data.get_radius() << " " \
             << cur->data.get_x() << " " \
             << cur->data.get_y() << "\n";
        cur = cur -> next;
    }
    fout.close();
}

void List::loadFromFile(const MyString& filename) {
    std::ifstream fin(filename.c_str());
    if (!fin) {
        cout << "error file not open(load)\n";
        return;
    }
    
    clear();
    double r, x, y;
    
    while (fin >> r >> x >> y) {
        push_back(Circle(r, x, y));
    }
    
    fin.close();
}

void List::loadFromFile() {
    MyString filename;
    cout << "enter filename: \n";
    filename.read_line();
    std::ifstream fin(filename.c_str());
    if (!fin) {
        cout << "error file not open(load)\n";
        return;
    }
    
    clear();
    double r, x, y;
    
    while (fin >> r >> x >> y) {
        push_back(Circle(r, x, y));
    }
    
    fin.close();
}


