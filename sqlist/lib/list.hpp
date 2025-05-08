#ifndef MY_LIST_HPP
#define MY_LIST_HPP

#define MyList_INIT_SIZE 100
#define MyListINCREMENT 10
#include <iostream>
#include <string>
#include <algorithm>

#include "enum.hpp"

template<typename T>
class MyList {
private:
	int length; // 线性表当前长度
	int maxSize; // 线性表最大长度
	T* elem; // 元素
public:
	MyList(); // 构造函数
	~MyList(); // 析构函数
	int initList(); // 初始化线性表
	int destroyList(); // 销毁线性表
	int clearList(); // 清空线性表
	int isEmpty() const; // 判断线性表是否为空
	int listLength() const; // 获取线性表长度
	T getElem(int i) const; // 获取线性表第i个元素
	int locateElem(T e) const; // 查找线性表中第一个值为e的元素
	int priorElem(T e) const; // 查找线性表中第一个值为e的前驱元素
	int nextElem(T e) const; // 查找线性表中第一个值为e的后继元素
	int listInsert(int i, T e); // 在第i个位置插入元素e
	int listDelete(int i); // 删除第i个位置的元素e
	int listTraverse() const; // 遍历线性表

	int maxSubArray() const; // 求最大连续子数组和
	int subArrayNum(T k) const; // 求和为k的连续子数组数目
	int sortList(); // 排序线性表

	int saveList(const char* filename) const; // 保存线性表到文件
	int loadList(const char* filename); // 从文件加载线性表
};

// 构造函数
template <typename T>
inline MyList<T>::MyList()
{
	elem = nullptr;
	length = 0;
	maxSize = 0;
}

// 析构函数
template <typename T>
inline MyList<T>::~MyList()
{
	if (elem != nullptr)
	{
		delete[] elem;
		elem = nullptr;
	}
	length = 0;
	maxSize = 0;
}

// 初始化线性表
template <typename T>
inline int MyList<T>::initList()
{
	if (elem != nullptr)
		return INFEASIBLE;
	elem = new T[MyList_INIT_SIZE];
	if (!elem)
		return ERROR;
	length = 0;
	maxSize = MyList_INIT_SIZE;
	return OK;
}

// 销毁线性表
template <typename T>
inline int MyList<T>::destroyList()
{
	if (elem == nullptr)
		return INFEASIBLE;
	delete[] elem;
	elem = nullptr;
	length = 0;
	maxSize = 0;
	return OK;
}

// 清空线性表
template <typename T>
inline int MyList<T>::clearList()
{
	if (elem == nullptr)
		return INFEASIBLE;
	for (int i = 0; i < length; i++)
		elem[i] = 0;
	length = 0;
	return OK;
}

// 判断线性表是否为空
template <typename T>
inline int MyList<T>::isEmpty() const
{
	if (elem == nullptr)
		return INFEASIBLE;
	return length == 0 ? TRUE : FALSE;
}

// 获取线性表长度
template <typename T>
inline int MyList<T>::listLength() const
{
	if (elem == nullptr)
		return INFEASIBLE;
	return length;
}

// 获取线性表第i个元素
template <typename T>
inline T MyList<T>::getElem(int i) const
{
	if (elem == nullptr)
		return INFEASIBLE;
	if (i < 1 || i > length)
		return ERROR;
	return elem[i - 1];
}

// 查找线性表中第一个值为e的元素
template <typename T>
inline int MyList<T>::locateElem(T e) const
{
	if (elem == nullptr)
		return INFEASIBLE;
	for (int i = 0; i < length; i++)
	{
		if (elem[i] == e)
			return i + 1;
	}
	return ERROR;
}

// 查找线性表中第一个值为e的前驱元素
template <typename T>
inline int MyList<T>::priorElem(T e) const
{
	if (elem == nullptr)
		return INFEASIBLE;
	int i = locateElem(e);
	if (i <= 1 || i > length)
		return ERROR;
	return elem[i - 2];
}

// 查找线性表中第一个值为e的后继元素
template <typename T>
inline int MyList<T>::nextElem(T e) const
{
	if (elem == nullptr)
		return INFEASIBLE;
	int i = locateElem(e);
	if (i == 0 || i == length)
		return ERROR;
	return elem[i];
}

// 在第i个位置插入元素e
// i的范围为1到length+1，length+1表示在末尾插入
template <typename T>
inline int MyList<T>::listInsert(int i, T e)
{
	if (elem == nullptr)
		return INFEASIBLE;
	if (i < 1 || i > length + 1)
		return ERROR;
	if (length >= maxSize)
	{
		T* newElem = new T[maxSize + MyListINCREMENT];
		if (!newElem)
			return ERROR;
		for (int j = 0; j < length; j++)
			newElem[j] = elem[j];
		delete[] elem;
		elem = newElem;
		maxSize += MyListINCREMENT;
	}
	for (int j = length - 1; j >= i - 1; j--)
		elem[j + 1] = elem[j];
	elem[i - 1] = e;
	length++;
	return OK;
}

// 删除第i个位置的元素e
template <typename T>
inline int MyList<T>::listDelete(int i)
{
	if (elem == nullptr)
		return INFEASIBLE;
	if (i < 1 || i > length)
		return ERROR;
	T e = elem[i - 1];
	for (int j = i; j < length; j++)
		elem[j - 1] = elem[j];
	length--;
	return e;
}

// 遍历线性表
template <typename T>
inline int MyList<T>::listTraverse() const
{
	if (elem == nullptr)
		return INFEASIBLE;
	if (length == 0)
		return ERROR;
	for (int i = 0; i < length - 1; i++)
		std::cout << elem[i] << " ";
	std::cout << elem[length - 1] << std::endl;
	return OK;
}

// 求最大连续子数组和
template <typename T>
inline int MyList<T>::sortList()
{
	if (elem == nullptr)
		return INFEASIBLE;
	std::sort(elem, elem + length);
	return OK;
}

#include "file.hpp"
#include "subarray.hpp"

#endif