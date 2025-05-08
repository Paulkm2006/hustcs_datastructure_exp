#include <cstring>
#include "list.hpp"

template <typename T>
class MultipleList {
private:
	int length; // 线性表个数
	int maxSize; // 线性表最大个数
	MyList<T>* lists; // 线性表数组
	char** names; // 线性表名称数组
public:
	MultipleList(); // 构造函数
	~MultipleList(); // 析构函数
	int addList(const char* name); // 添加线性表
	int removeList(int n); // 删除线性表
	int locateList(const char* name) const; // 查找线性表
	MyList<T>& operator[](int index); // 通过索引选择线性表
	MyList<T>& operator[](const char* name); // 通过名称选择线性表
	int printAllListNames() const
	{
		if (lists == nullptr || names == nullptr)
			return INFEASIBLE;
		for (int i = 0; i < length; i++)
		{
			std::cout << i << " " << names[i] << std::endl;
		}
		return OK;
	}
};


// 多线性表初始化
template <typename T>
inline MultipleList<T>::MultipleList()
{
	length = 0;
	maxSize = 10;
	lists = new MyList<T>[maxSize];
	names = new char*[maxSize];
	if (!lists || !names)
	{
		throw std::runtime_error("Memory allocation failed");
	}
}

// 多线性表析构
template <typename T>
inline MultipleList<T>::~MultipleList()
{
	for (int i = 0; i < length; i++)
	{
		delete[] names[i];
	}
	delete[] lists;
	delete[] names;
	lists = nullptr;
	names = nullptr;
	length = 0;
	maxSize = 0;
}


// 添加线性表
template <typename T>
inline int MultipleList<T>::addList(const char *name)
{
	if (length >= maxSize) // 扩容
	{
		MyList<T>* newLists = new MyList<T>[maxSize * 2];
		char** newNames = new char*[maxSize * 2];
		if (!newLists || !newNames)
		{
			return ERROR;
		}
		for (int i = 0; i < length; i++)
		{
			newLists[i] = std::move(lists[i]);
			newNames[i] = names[i];
		}
		delete[] lists;
		delete[] names;
		lists = newLists;
		names = newNames;
		maxSize *= 2;
	}
	names[length] = new char[strlen(name) + 1];
	strcpy(names[length], name);
	length++;
	return OK;
}

// 删除线性表
template <typename T>
inline int MultipleList<T>::removeList(int n)
{
	if (n < 0 || n >= length)
		return ERROR;
	if (lists[n].listLength() > 0)
		return INFEASIBLE;
	delete[] names[n];
	for (int i = n; i < length - 1; i++)
	{
		std::swap(lists[i], lists[i + 1]);
		names[i] = names[i + 1];
	}
	length--;
	return OK;
}

// 查找线性表
template <typename T>
inline int MultipleList<T>::locateList(const char *name) const
{
	if (lists == nullptr || names == nullptr)
		return -1;
	for (int i = 0; i < length; i++)
	{
		if (strcmp(names[i], name) == 0)
			return i;
	}
	return -1;
}


// 通过索引选择线性表
template <typename T>
inline MyList<T> &MultipleList<T>::operator[](int index)
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index out of range");
	return lists[index];
}


// 通过名称选择线性表
template <typename T>
inline MyList<T> &MultipleList<T>::operator[](const char *name)
{
	if (lists == nullptr || names == nullptr)
		throw std::runtime_error("List not found");
	int index = locateList(name);
	if (index == -1)
		throw std::runtime_error("List not found");
	return lists[index];
}
