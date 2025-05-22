#include <cstring>
#include "graph.hpp"

template <typename Key, typename Value>
class MultipleGraph {
private:
	int length; // 二叉树个数
	int maxSize; // 二叉树最大个数
	Graph<Key, Value>* Graphs; // 二叉树数组
	char** names; // 二叉树名称数组
public:
	MultipleGraph(); // 构造函数
	~MultipleGraph(); // 析构函数
	void addGraph(const char* name); // 添加二叉树
	void removeGraph(int n); // 删除二叉树
	int locateGraph(const char* name) const; // 查找二叉树
	Graph<Key, Value> &operator[](int index); // 通过索引选择二叉树
	Graph<Key, Value> &operator[](const char *name); // 通过名称选择二叉树
	void printAllGraphNames() const
	{
		if (Graphs == nullptr || names == nullptr)
			throw NOT_INITIALIZED;
		for (int i = 0; i < length; i++)
			std::cout << i << " " << names[i] << std::endl;
	}
};


// 多二叉树初始化
template <typename Key, typename Value>
inline MultipleGraph<Key, Value>::MultipleGraph()
{
	length = 0;
	maxSize = 10;
	Graphs = new Graph<Key, Value>[maxSize];
	names = new char*[maxSize];
	if (!Graphs || !names)
	{
		throw std::runtime_error("Memory allocation failed");
	}
}

// 多二叉树析构
template <typename Key, typename Value>
inline MultipleGraph<Key, Value>::~MultipleGraph()
{
	for (int i = 0; i < length; i++)
	{
		delete[] names[i];
	}
	delete[] Graphs;
	delete[] names;
	Graphs = nullptr;
	names = nullptr;
	length = 0;
	maxSize = 0;
}


// 添加二叉树
template <typename Key, typename Value>
inline void MultipleGraph<Key, Value>::addGraph(const char *name)
{
	if (locateGraph(name) != -1)
		throw CONFLICT;
	if (length >= maxSize) // 扩容
	{
		Graph<Key, Value> *newGraphs = new Graph<Key, Value>[maxSize * 2];
		char** newNames = new char*[maxSize * 2];
		if (!newGraphs || !newNames)
		{
			throw std::runtime_error("Memory allocation failed");
		}
		for (int i = 0; i < length; i++)
		{
			newGraphs[i] = std::move(Graphs[i]);
			newNames[i] = names[i];
		}
		delete[] Graphs;
		delete[] names;
		Graphs = newGraphs;
		names = newNames;
		maxSize *= 2;
	}
	names[length] = new char[strlen(name) + 1];
	strcpy(names[length], name);
	length++;
}

// 删除二叉树
template <typename Key, typename Value>
inline void MultipleGraph<Key, Value>::removeGraph(int n)
{
	if (n < 0 || n >= length)
		throw OUT_OF_RANGE;
	delete[] names[n];
	for (int i = n; i < length - 1; i++)
	{
		std::swap(Graphs[i], Graphs[i + 1]);
		names[i] = names[i + 1];
	}
	length--;
}

// 查找二叉树
template <typename Key, typename Value>
inline int MultipleGraph<Key, Value>::locateGraph(const char *name) const
{
	if (Graphs == nullptr || names == nullptr)
		throw NOT_INITIALIZED;
	for (int i = 0; i < length; i++)
	{
		if (strcmp(names[i], name) == 0)
			return i;
	}
	return -1; // 未找到
}


// 通过索引选择二叉树
template <typename Key, typename Value>
inline Graph<Key, Value> &MultipleGraph<Key, Value>::operator[](int index)
{
	if (index < 0 || index >= length)
		throw OUT_OF_RANGE;
	return Graphs[index];
}


// 通过名称选择二叉树
template <typename Key, typename Value>
inline Graph<Key, Value> &MultipleGraph<Key, Value>::operator[](const char *name)
{
	if (Graphs == nullptr || names == nullptr)
		throw NOT_INITIALIZED;
	int index = locateGraph(name);
	if (index == -1)
		throw NOT_FOUND;
	return Graphs[index];
}
