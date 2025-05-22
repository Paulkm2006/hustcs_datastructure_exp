#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <queue>
#include <map>

// 保存二叉树。文件格式为：<节点在线性序列中的位置> <key> <value>
template <typename Key, typename Value>
inline void BiTree<Key, Value>::save(const char *filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("无法打开文件");
	if (head == nullptr)
		throw NOT_INITIALIZED;
	std::queue<std::pair<int, Node<Key, Value>*>> q;
	q.push({1, head.get()});
	while (!q.empty())
	{
		auto [pos, current] = q.front();
		q.pop();

		if (current != nullptr)
		{
			file << pos << " " << current->data.first << " " << current->data.second << " ";
			q.push({pos * 2, current->left.get()});
			q.push({pos * 2 + 1, current->right.get()});
		}
	}
	file.close();
}

// 加载二叉树
template <typename Key, typename Value>
inline void BiTree<Key, Value>::load(const char *filename)
{
	if (head != nullptr)
		throw std::runtime_error("树已经存在");
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("无法打开文件");

	int pos;
	Key key;
	Value value;

	std::map<int, Node<Key, Value> *> positionMap; // 用于保存对应编号的节点

	while (file >> pos >> key >> value)
	{
		if (pos == 1)
		{
			head = std::make_unique<Node<Key, Value>>(key, value);
			positionMap[pos] = head.get();
			keys.insert(key);
		}
		else
		{
			int parentPos = pos / 2; // 父节点的编号

			auto parent_it = positionMap.find(parentPos);
			if (parent_it == positionMap.end())
			{
				throw std::runtime_error("文件格式错误，找不到父节点");
			}

			Node<Key, Value> *parentNode = parent_it->second; // 找到父节点

			std::unique_ptr<Node<Key, Value>> newNode =
				std::make_unique<Node<Key, Value>>(key, value);

			if (pos % 2 == 0) // 左子节点
			{
				parentNode->left = std::move(newNode);
				positionMap[pos] = parentNode->left.get();
			}
			else
			{
				parentNode->right = std::move(newNode);
				positionMap[pos] = parentNode->right.get();
			}
			keys.insert(key);
		}
	}

	file.close();
}

#endif