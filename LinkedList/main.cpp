#include <iostream>
#include <vector>
//создание шаблонного связного списка


template <typename Type>
class LinkedList {
public:

	LinkedList();
	LinkedList(int n); //лист с уже созданными n элементами

	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other);//можно не делать, но для оптимизации скорости работы программы полезно.
	//тут не будет реализации конструкора от списка инициализации, внесем позже.

	~LinkedList();

	// присваивание копированием
	LinkedList& operator = (const LinkedList& other);
	// присваивание переносом
	LinkedList& operator = (LinkedList&& other);


	Type& operator[](int i);
	const Type& operator[](int i)const;

	Type &at (int i);
	const Type &at (int i)const;

	void push_back(const Type& obj);// добавиить данные в конец списка
	void push_front(const Type& obj);// добавить данные в начало списка

	void pop_back(); // уничтожить данные в конце списка
	void pop_front();// уничтожить данные в начале списка

	/*
	 * emplace/insert - методы дщобавления новых данных в произвольное место колекции
	 * erise - метод для уничтожения данных в произвольной точке колекции
	*/
	
	
	int size()const;

	/*
	* методы для прохода по коллекции умными указателями мы пока сознательно опустим
	*/

private:
	class Node {
	public:
		Node():Node(Type()){}; // при делигации мы вызываем конструктор по умолчанию хранимого типа данных. Данный синтаксис корректно отработает даже если прямой вызов такого метода
								//(например конструктора встроенных типов) недоступен.
		Node(const Type& data, Node* place = nullptr) :data_(data), next_(place){}

		Type& Data() {
			return data_;
		}
		const Type& Data()const {
			return data_;
		}

		Node* Next()const {
			return next_;
		}

		void Next(Node* next) {
			next_ = next;
		}

	private:
		Type data_;
		Node* next_;
	};

	Node* end_;
	Node* start_;
	int size_;
};



int main() {
	setlocale(0, "");

	int arr[10];
	std::vector<int> vec(10);
	LinkedList<int> list;
	arr[5] = 34;
	vec[5] = 23;
	list[5] = 12;





	return 0;
}
