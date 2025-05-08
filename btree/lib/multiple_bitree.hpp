#include <cstring>
#include "bitree.hpp"

template <typename Key, typename Value>
class MultipleBiTree {
private:
	int length; // 二叉树个数
	int maxSize; // 二叉树最大个数
	BiTree<Key, Value>* BiTrees; // 二叉树数组
	char** names; // 二叉树名称数组
public:
	MultipleBiTree(); // 构造函数
	~MultipleBiTree(); // 析构函数
	void addBiTree(const char* name); // 添加二叉树
	void removeBiTree(int n); // 删除二叉树
	int locateBiTree(const char* name) const; // 查找二叉树
	BiTree<Key, Value> &operator[](int index); // 通过索引选择二叉树
	BiTree<Key, Value> &operator[](const char *name); // 通过名称选择二叉树
	void printAllBiTreeNames() const
	{
		if (BiTrees == nullptr || names == nullptr)
			throw NOT_INITIALIZED;
		for (int i = 0; i < length; i++)
			std::cout << i << " " << names[i] << std::endl;
	}
};


// 多二叉树初始化
template <typename Key, typename Value>
inline MultipleBiTree<Key, Value>::MultipleBiTree()
{
	length = 0;
	maxSize = 10;
	BiTrees = new BiTree<Key, Value>[maxSize];
	names = new char*[maxSize];
	if (!BiTrees || !names)
	{
		throw std::runtime_error("Memory allocation failed");
	}
}

// 多二叉树析构
template <typename Key, typename Value>
inline MultipleBiTree<Key, Value>::~MultipleBiTree()
{
	for (int i = 0; i < length; i++)
	{
		delete[] names[i];
	}
	delete[] BiTrees;
	delete[] names;
	BiTrees = nullptr;
	names = nullptr;
	length = 0;
	maxSize = 0;
}


// 添加二叉树
template <typename Key, typename Value>
inline void MultipleBiTree<Key, Value>::addBiTree(const char *name)
{
	if (locateBiTree(name) != -1)
		throw CONFLICT;
	if (length >= maxSize) // 扩容
	{
		BiTree<Key, Value> *newBiTrees = new BiTree<Key, Value>[maxSize * 2];
		char** newNames = new char*[maxSize * 2];
		if (!newBiTrees || !newNames)
		{
			throw std::runtime_error("Memory allocation failed");
		}
		for (int i = 0; i < length; i++)
		{
			newBiTrees[i] = std::move(BiTrees[i]);
			newNames[i] = names[i];
		}
		delete[] BiTrees;
		delete[] names;
		BiTrees = newBiTrees;
		names = newNames;
		maxSize *= 2;
	}
	names[length] = new char[strlen(name) + 1];
	strcpy(names[length], name);
	length++;
}

// 删除二叉树
template <typename Key, typename Value>
inline void MultipleBiTree<Key, Value>::removeBiTree(int n)
{
	if (n < 0 || n >= length)
		throw OUT_OF_RANGE;
	if (!BiTrees[n].isEmpty()) throw std::runtime_error("树非空");
	delete[] names[n];
	for (int i = n; i < length - 1; i++)
	{
		std::swap(BiTrees[i], BiTrees[i + 1]);
		names[i] = names[i + 1];
	}
	length--;
}

// 查找二叉树
template <typename Key, typename Value>
inline int MultipleBiTree<Key, Value>::locateBiTree(const char *name) const
{
	if (BiTrees == nullptr || names == nullptr)
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
inline BiTree<Key, Value> &MultipleBiTree<Key, Value>::operator[](int index)
{
	if (index < 0 || index >= length)
		throw OUT_OF_RANGE;
	return BiTrees[index];
}


// 通过名称选择二叉树
template <typename Key, typename Value>
inline BiTree<Key, Value> &MultipleBiTree<Key, Value>::operator[](const char *name)
{
	if (BiTrees == nullptr || names == nullptr)
		throw NOT_INITIALIZED;
	int index = locateBiTree(name);
	if (index == -1)
		throw NOT_FOUND;
	return BiTrees[index];
}
