#pragma once

using namespace std;

template <typename T>
struct Node
{
	T data = T();
	int index = -1;
	Node<T>* prev;
	Node<T>* next;
	Node(Node<T>* prev = nullptr, Node<T>* next = nullptr) : prev{ prev }, next{ next } {};
};

template <typename T>
class Array
{
public:
	Array() = default;
	int getSize() const;
	void setSize(int size, int grow = 1);
	bool isEmpty() const;
	void add(const T& data);
	int getUpperBound() const;
	void print() const;
	void printR() const;
	void freeExtra();
	void removeAll();
	T operator[](const int& index) const;
	T& operator[](const int& index);
	void operator+=(const Array<T>& other);
	Node<T>* getData(const T& data) const;
	void insertAt(const int& index, const T& data);
	void removeAt(const int& index);
private:
	int size = 0;
	int grow = 0;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	void alocate(int size);
	void remove();
	void add();
	bool notAlocated() const;
};

template<typename T>
inline int Array<T>::getSize() const
{
	return size;
}

template<typename T>
inline void Array<T>::setSize(int size, int grow)
{
	this->grow = grow;
	if (notAlocated()) {
		alocate(size);
		this->size = size;
	}
	else {
		if (this->size > size) {
			int change = this->size - size;
			for (size_t i = 0; i < change; i++)
			{
				remove();
			}
		}
		else {
			int change = size - this->size;
			for (size_t i = 0; i < change; i++)
			{
				add();
			}
		}
	}
}

template<typename T>
inline bool Array<T>::isEmpty() const
{
	return getUpperBound() == -1;
}

template<typename T>
inline bool Array<T>::notAlocated() const
{
	return head == nullptr;
}

template<typename T>
inline void Array<T>::alocate(int size)
{
	for (size_t i = 0; i < size; i++)
	{
		Node<T>* tmp = new Node<T>(nullptr, head);
		if (notAlocated()) {
			tail = tmp;
		}
		else {
			head->prev = tmp;
		}
		head = tmp;
	}
}

template<typename T>
inline void Array<T>::add(const T& data)
{
	if (notAlocated())
	{
		setSize(1, 1);
	}
	if (getUpperBound() + 1 == size) {
		setSize(size+grow);
	}
	auto tmp = head;
	for (int i = getUpperBound() + 1; i > 0; i--)
	{
		tmp = tmp->next;
	}
	tmp->data = data;
	tmp->index = getUpperBound() + 1;
}
template<typename T>
inline void Array<T>::add()
{
	Node<T>* tmp = new Node<T>(tail, nullptr);
	if (notAlocated()) {
		head = tmp;
	}
	else {
		tail->next = tmp;
	}
	tail = tmp;
	++size;
}

template<typename T>
inline int Array<T>::getUpperBound() const
{
	int counter = -1;
	auto tmp = head;
	while (tmp != nullptr && tmp->index != -1)
	{
		++counter;
		tmp = tmp->next;
	}
	return counter;
}

template<typename T>
inline void Array<T>::remove()
{
	if (notAlocated()) {
		return;
	}
	auto tmp = tail;
	tail = tmp->prev;
	if (notAlocated()) {
		head = nullptr;
	}
	else {
		tail->next = nullptr;
	}
	delete tmp;
	--size;
}

template<typename T>
inline void Array<T>::print() const
{
	auto tmp = head;
	while (tmp != nullptr)
	{
		cout << tmp->data << "\t";
		tmp = tmp->next;
	}
	cout << endl;
}

template<typename T>
inline void Array<T>::printR() const
{
	auto tmp = tail;
	while (tmp != nullptr)
	{
		cout << tmp->data << "\t";
		tmp = tmp->prev;
	}
	cout << endl;
}

template<typename T>
inline void Array<T>::freeExtra()
{
	const int start = getUpperBound()+1;
	const int end = getSize();
	for (size_t i = start; i < end; i++)
	{
		remove();
	}
}

template<typename T>
inline void Array<T>::removeAll()
{
	if (isEmpty())
	{
		return;
	}
	const int length = getUpperBound() + 1;
	auto tmp = head;
	for (int i = 0; i < length; i++)
	{
		tmp->data = T();
		tmp->index = -1;
		tmp = tmp->next;
	}
}

template<typename T>
inline T Array<T>::operator[](const int& index) const
{
	if (index > getUpperBound() || index < 0) {
		cout << "Invalid index" << endl;
		return T();
	}
	auto tmp = head;
	while (tmp->index != index)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}

template<typename T>
inline T& Array<T>::operator[](const int& index)
{
	if (index > getUpperBound() || index < 0) {
		cout << "Invalid index" << endl;
	}
	auto tmp = head;
	while (tmp->index != index)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}

template<typename T>
inline void Array<T>::operator+=(const Array<T>& other)
{
	freeExtra();
	auto tmp = other.head;
	for (size_t i = 0; i < other.getSize(); i++)
	{
		add(tmp->data);
		tmp = tmp->next;
	}
}

template<typename T>
inline Node<T>* Array<T>::getData(const T& data) const
{
	if (notAlocated() || isEmpty()) {
		cout << "List is empty" << endl;
		return nullptr;
	}
	auto tmp = head;
	for (size_t i = 0; i < getUpperBound() + 1; i++)
	{
		if (tmp->data == data)
		{
			return tmp;
			break;
		}
		tmp = tmp->next;
	}

	return nullptr;
}

template<typename T>
inline void Array<T>::insertAt(const int& index, const T& data)
{
	if (index > getUpperBound() || index < 0) {
		cout << "Invalid index" << endl;
	}
	operator[](index) = data;
}

template<typename T>
inline void Array<T>::removeAt(const int& index)
{
	if (index > getUpperBound() || index < 0) {
		cout << "Invalid index" << endl;
	}
	auto tmp = head;
	for (size_t i = 0; i < getUpperBound() + 1; i++)
	{
		if (tmp->index == index)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			--size;
			break;
		}
		tmp = tmp->next;
	}
}




