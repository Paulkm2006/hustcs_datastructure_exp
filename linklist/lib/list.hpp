#ifndef MY_LIST_HPP
#define MY_LIST_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

#include "enum.hpp"

template<typename T>
struct Node
{
	T data;
	std::unique_ptr<Node> next;
	Node() : next(nullptr), data(T()) {} // 默认构造函数
	Node<T>(T d) : next(nullptr), data(d) {} // 带参数的构造函数
};

template<typename T>
class MyList {
private:
	int length; // 单链表当前长度
	std::unique_ptr<Node<T>> head; // 指向单链表头结点的指针
public:
	MyList(); // 构造函数
	~MyList(); // 析构函数
	
	MyList(MyList&& other) noexcept = default;
	MyList& operator=(MyList&& other) noexcept = default;
	
	int initList(); // 初始化单链表
	int destroyList(); // 销毁单链表
	int clearList(); // 清空单链表
	int isEmpty() const; // 判断单链表是否为空
	int listLength() const; // 获取单链表长度
	T operator[](int i) const; // 重载下标运算符
	template <class Compare = std::less<T>>
	int locateElem(T e, Compare cmp) const; // 查找单链表中第一个与e满足cmp的元素
	int priorElem(T e) const; // 查找单链表中第一个值为e的前驱元素
	int nextElem(T e) const; // 查找单链表中第一个值为e的后继元素
	int listInsert(int i, T e); // 在第i个位置插入元素e
	int listDelete(int i); // 删除第i个位置的元素e
	int listTraverse() const; // 遍历单链表

	int reverseList(); // 反转单链表
	int removeNthFromEnd(int n); // 删除倒数第n个节点
	int sortList(); // 排序单链表

	int saveList(const char* filename) const; // 保存单链表到文件
	int loadList(const char* filename); // 从文件加载单链表
};

// 构造函数
template <typename T>
inline MyList<T>::MyList()
{
	head = nullptr;
	length = 0;
}

// 析构函数
template <typename T>
inline MyList<T>::~MyList()
{
	head = nullptr; // unique_ptr 自动释放内存
	length = 0;
}

// 初始化单链表
template <typename T>
inline int MyList<T>::initList()
{
	if (head != nullptr)
		return INFEASIBLE;
	head = std::make_unique<Node<T>>();
	head->next = nullptr;
	length = 0;
	return OK;
}

// 销毁单链表
template <typename T>
inline int MyList<T>::destroyList()
{
	if (head == nullptr)
		return INFEASIBLE;
	head = nullptr; // unique_ptr 自动释放内存
	length = 0;
	return OK;
}

// 清空单链表
template <typename T>
inline int MyList<T>::clearList()
{
	if (head == nullptr)
		return INFEASIBLE;
	head = std::make_unique<Node<T>>();
	head->next = nullptr;
	length = 0;
	return OK;
}

// 判断单链表是否为空
template <typename T>
inline int MyList<T>::isEmpty() const
{
	if (head == nullptr)
		return INFEASIBLE;
	return length == 0 ? TRUE : FALSE;
}

// 获取单链表长度
template <typename T>
inline int MyList<T>::listLength() const
{
	if (head == nullptr)
		return INFEASIBLE;
	return length;
}

// 查找单链表中第一个与e满足cmp的元素
template <typename T>
template <class Compare>
inline int MyList<T>::locateElem(T e, Compare cmp) const
{
	if (head == nullptr)
		return INFEASIBLE;
	Node<T> *current = head.get();
	for(int i = 1; i <= length; i++)
	{
		if (cmp(current->data, e))
			return i;
		current = current->next.get();
	}
	return ERROR;
}

// 查找单链表中第一个值为e的前驱元素
template <typename T>
inline int MyList<T>::priorElem(T e) const
{
	if (head == nullptr)
		return INFEASIBLE;
	int i = locateElem(e, std::equal_to<T>());
	if (i <= 1 || i > length)
		return ERROR;
	return (*this)[i-1];
}

// 查找单链表中第一个值为e的后继元素
template <typename T>
inline int MyList<T>::nextElem(T e) const
{
	if (head == nullptr)
		return INFEASIBLE;
	int i = locateElem(e, std::equal_to<T>());
	if (i < 1 || i >= length)
		return ERROR;
	return (*this)[i+1];
}

// 在第i个位置插入元素e
// i的范围为1到length+1，length+1表示在末尾插入
template <typename T>
inline int MyList<T>::listInsert(int i, T e)
{
	if (head == nullptr)
		return INFEASIBLE;
	if (i < 1 || i > length + 1)
		return ERROR;
	
	if (i == 1) {
		auto newNode = std::make_unique<Node<T>>(e);
		newNode->next = std::move(head);
		head = std::move(newNode);
	} else {
		Node<T>* current = head.get();
		for (int j = 1; j < i - 1; j++) {
			current = current->next.get();
		}
		auto newNode = std::make_unique<Node<T>>(e);
		newNode->next = std::move(current->next);
		current->next = std::move(newNode);
	}
	
	length++;
	return OK;
}

// 删除第i个位置的元素e
template <typename T>
inline int MyList<T>::listDelete(int i)
{
	if (head == nullptr)
		return INFEASIBLE;
	if (i < 1 || i > length)
		return ERROR;
	if(i == 1)
	{
		head = std::move(head->next);
		length--;
		return OK;
	}
	Node<T>* current = head.get();
	for (int j = 2; j < i; j++)
	{
		current = current->next.get();
	}
	current->next = std::move(current->next->next);
	length--;
	return OK;
}

// 遍历单链表
template <typename T>
inline int MyList<T>::listTraverse() const
{
	if (head == nullptr)
		return INFEASIBLE;
	Node<T>* current = head.get();
	for (int i = 1; i <= length; i++)
	{
		std::cout << current->data << " ";
		current = current->next.get();
	}
	std::cout << std::endl;
	return OK;
}

// 排序单链表
// 使用插入排序算法
template <typename T>
inline int MyList<T>::sortList()
{
	if (head == nullptr)
		return INFEASIBLE;
	if (length <= 1)
		return OK;
	std::unique_ptr<Node<T>> sorted = nullptr;
	std::unique_ptr<Node<T>> current = std::move(head);

	while (current->next) {
		std::unique_ptr<Node<T>> next = std::move(current->next);
		
		if (!sorted || sorted->data >= current->data) {
			current->next = std::move(sorted);
			sorted = std::move(current);
		} else {
			Node<T>* temp_ptr = sorted.get();
			while (temp_ptr->next && temp_ptr->next->data < current->data) {
				temp_ptr = temp_ptr->next.get();
			}
			current->next = std::move(temp_ptr->next);
			temp_ptr->next = std::move(current);
		}
		current = std::move(next);
	}

	head = std::move(sorted);
	
	Node<T>* tail = head.get();
	while (tail->next) {
		tail = tail->next.get();
	}
	tail->next = std::make_unique<Node<T>>(0);
	return OK;
}

// 重载下标运算符
template <typename T>
inline T MyList<T>::operator[](int i) const
{
	if (head == nullptr)
		throw std::runtime_error("List is not initialized.");
	if (i < 1 || i > length)
		throw std::out_of_range("Index out of range.");
	Node<T>* current = head.get();
	for (int j = 1; j < i; j++)
	{
		current = current->next.get();
	}
	return current->data;
}

// 反转单链表
template <typename T>
inline int MyList<T>::reverseList()
{
	if (head == nullptr)
		return INFEASIBLE;
	if (length <= 1)
		return OK;
	std::unique_ptr<Node<T>> prev = std::make_unique<Node<T>>();
	std::unique_ptr<Node<T>> current = std::move(head);
	std::unique_ptr<Node<T>> next = nullptr;
	
	while (current->next) {
		next = std::move(current->next);
		current->next = std::move(prev);
		prev = std::move(current);
		current = std::move(next);
	}

	
	
	head = std::move(prev);
	return OK;
}

// 删除倒数第n个节点
// 使用快慢指针
template <typename T>
inline int MyList<T>::removeNthFromEnd(int n)
{
	if (head == nullptr)
		return INFEASIBLE;
	if (n <= 0 || n > length)
		return ERROR;
		
	auto newHead = std::make_unique<Node<T>>();
	newHead->next = std::move(head);

	Node<T> *fast = newHead.get();
	Node<T> *slow = newHead.get();

	for (int i = 0; i < n; i++) {
		if (!fast) return ERROR;
		fast = fast->next.get();
	}
	
	while (fast->next->next) {
		fast = fast->next.get();
		slow = slow->next.get();
	}
	
	if (slow->next) {
		slow->next = std::move(slow->next->next);
	}

	head = std::move(newHead->next);
	length--;
	return OK;
}

#include "file.hpp"

#endif