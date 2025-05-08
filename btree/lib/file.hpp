#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <queue>

template <typename Key, typename Value>
inline void BiTree<Key, Value>::save(const char *filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("无法打开文件");
	if (head == nullptr)
		throw NOT_INITIALIZED;

	std::queue<Node<Key, Value>*> q;
	q.push(head.get());
	while (!q.empty())
	{
		Node<Key, Value> *current = q.front();
		q.pop();

		if (current == nullptr)
			file << Key() << " " << Value() << " ";
		else
		{
			file << current->data.first << " " << current->data.second << " ";
			q.push(current->left.get());
			q.push(current->right.get());
		}
	}
	file.close();
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::load(const char *filename)
{
	if (head != nullptr)
		throw std::runtime_error("树已经存在");
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("无法打开文件");

	Key k;
	Value v;
	file >> k >> v;
	head = std::make_unique<Node<Key, Value>>(k, v);

	std::queue<Node<Key, Value>*> q;
	q.push(head.get());

	while (!q.empty() && !file.eof())
	{
		Node<Key, Value> *current = q.front();
		q.pop();
		file >> k >> v;
		if (k != Key())
		{
			current->left = std::make_unique<Node<Key, Value>>(k, v);
			q.push(current->left.get());
		}
		file >> k >> v;
		if (k != Key())
		{
			current->right = std::make_unique<Node<Key, Value>>(k, v);
			q.push(current->right.get());
		}
	}

	file.close();
}

#endif