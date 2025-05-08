#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>

template <typename T>
inline int MyList<T>::saveList(const char* filename) const
{
	if (head == nullptr)
		return INFEASIBLE;
	std::ofstream file(filename);
	if (!file.is_open())
		return ERROR;
	file << length << " ";
	Node<T>* current = head.get();
	for (int i = 1; i <= length; i++)
	{
		file << current->data << " ";
		current = current->next.get();
	}
	file.close();
	return OK;
}

template <typename T>
inline int MyList<T>::loadList(const char *filename)
{
	if (head != nullptr)
		return INFEASIBLE;
	std::ifstream file(filename);
	if (!file.is_open())
		return ERROR;
	file >> length;
	if (length <= 0)
	{
		file.close();
		return ERROR;
	}
	head = std::make_unique<Node<T>>();
	Node<T>* current = head.get();
	for (int i = 1; i <= length; i++)
	{
		current->next = std::make_unique<Node<T>>();
		file >> current->data;
		current = current->next.get();
	}
	current->next = nullptr;
	file.close();
	return OK;
}

#endif