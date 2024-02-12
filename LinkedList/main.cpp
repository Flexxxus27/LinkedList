#include <iostream>
#include <vector>
//создание шаблонного связного списка
#include <chrono>

template <typename Type>
class LinkedList {
public:
	//конст. по умолчанию
	LinkedList():start_(nullptr),end_(nullptr),size_(0) {}

	LinkedList(int n) :LinkedList() { //лист с уже созданными n элементами
		if (n < 0)throw - 1;
		if (n == 0)return;
		Node* tmp{};
		//---- 1 вариант, сложно читаемый
		/*
		size_ = n;
		
		do {
			
			tmp = new Node;
			if (start_ == nullptr) {
				start_ = tmp;
			}
			 
			n -= 1;
		} while (n > 0);
		*/
		//----------
		int addedNodes{ 0 };
		tmp = new Node{};
		start_ = tmp;
		end_ = tmp;
		addedNodes += 1;
		while (addedNodes < n) {
			tmp = new Node{}; // создаем новую точку
			end_->Next(tmp); // старому концу списка говорим что новый конечный элемент существует  
			end_ = tmp; // запоминаем в списке какой элемент сейчас последний
			addedNodes += 1;
		}
		size_ = n;
	}

	LinkedList(const LinkedList& other):LinkedList() {
		if (other.size() == 0)return;
		start_ = new Node(other.start_->Data());
		end_ = start_;
		for (Node* current = other.start_->Next();current != nullptr;current = current->Next()){
			//Node* tmp = new Node(other[i]);

			Node* tmp = new Node(current->Data());
			end_->Next(tmp);
			end_ = tmp;
		}
		size_ = other.size_;
	}
	LinkedList(LinkedList&& other):LinkedList() { //можно не делать, но для оптимизации скорости работы программы полезно. //тут не будет реализации конструкора от списка инициализации, внесем позже.
		std::swap(start_, other.start_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);
	}

	~LinkedList() {
		 Node* current = start_; 
		 while (current != nullptr) {
			 Node* tmp = current->Next();
			 delete current;
			 current = tmp;
		 }
	}

	void clear() {
		Node* current = start_;
		while (current != nullptr) {
			Node* tmp = current->Next();
			delete current;
			current = tmp;
		}
		start_=nullptr;
		end_=nullptr;
		size_=0;
	}
	
	// присваивание копированием
	LinkedList& operator = (const LinkedList& other) {
		clear();
		if (other.size() == 0) return *this;
		start_ = new Node(other.start_->Data());
		end_ = start_;
		for (Node* current = other.start_->Next(); current != nullptr; current = current->Next()) {
			Node* tmp = new Node(current->Data());
			end_->Next(tmp);
			end_ = tmp;
		}
		size_ = other.size_;
		return *this;
	}
	// присваивание переносом
	LinkedList& operator = (LinkedList&& other) {
		clear();
		std::swap(start_, other.start_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);

		return *this;
	}

	//оператор доступа к хранящимся элементам 
	Type& operator[](int i) {
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	const Type& operator[](int i)const {
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	Type& at(int i) {
		if (i < 0 || i >= size_) throw - 1;
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}
	const Type& at(int i)const {
		if (i < 0 || i >= size_) throw - 1;
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;
		}
		return tmp->Data();
	}

	void push_back(const Type& obj) { // добавиить данные в конец списка
		Node* tmp = new Node{obj};
		if (size_ == 0) {
			start_ = tmp;
			end_ = tmp;
		}
		else {
			end_->Next(tmp);
			end_ = tmp;
		}
		size_ += 1;
	}

	void push_front(const Type& obj) { // добавить данные в начало списка

		Node* tmp = new Node{ obj };
		if (size_ == 0) {
			start_ = tmp;
			end_ = tmp;
		}
		else {
			tmp->Next(start_);
			start_= tmp;
		}
		size_ += 1;
	}

	void pop_back() { // уничтожить данные в конце списка

		if (end_) {
			auto tmp = start_;
			//цикл поиска предпоследнего элемента
			while(tmp->Next() != end_){
				tmp = tmp->Next();
			}
			//освобождение и замена последнего элемента
			delete end_;
			end_ = tmp;
			size_--;
		}
		if (!size_) {
			end_ = start_;
		}
	}

	void pop_front() { // уничтожить данные в начале списка

		if (start_) {
			auto tmp = start_;
			start_ = start_->Next();
			delete tmp;
			size_--;
		}
		if (!size_) {
			end_ = start_;
		}
		
	}

	/*
	 * emplace/insert - методы дщобавления новых данных в произвольное место колекции
	 * erise - метод для уничтожения данных в произвольной точке колекции
	*/
	
	
	int size()const {
		return size_;
	}

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

	int arr[10]{};
	std::vector<int> vec;
	LinkedList<int> list;
	arr;
	for (size_t i = 0; i < 100000; i++) {
		vec.push_back(i + 1);
	}
	arr;
	for (size_t i = 0; i < 100000; i++) {
		list.push_back(i + 1);
	}
	arr;
	for (size_t i = 0; i < vec.size(); i++) {
		vec[i];
	}
	arr;
	for (size_t i = 0; i < list.size(); i++) {
		list[i];
	}
	arr;
	
	//for(/*переменная для хранения элементов*/: /*коллекция элементов которую нужно перебрать*/)

	//for (int &e : arr) {
	//	std::cout << e << ' ';
	//}
	//for (auto & e : arr) {
	//	std::cout << e << ' ';
	//}
	//std::chrono::duration<float> time_length; 




	return 0;
}
