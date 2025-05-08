#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>

template <typename T>
inline int MyList<T>::saveList(const char* filename) const
{
	if (elem == nullptr)
		return INFEASIBLE;
	std::ofstream file(filename);
	if (!file.is_open())
		return ERROR;
	file << length << " ";
	for (int i = 0; i < length; i++)
		file << elem[i] << " "; 
	file.close();
	return OK;
}

template <typename T>
inline int MyList<T>::loadList(const char *filename)
{
	if (elem == nullptr)
		return INFEASIBLE;
	std::ifstream file(filename);
	if (!file.is_open())
		return ERROR;
	file >> length;
	if (length > maxSize)
	{
		delete[] elem;
		elem = new T[length];
		if (!elem)
			return OVERFLOW;
		maxSize = length;
	}
	for (int i = 0; i < length; i++)
		file >> elem[i];
	file.close();
	return OK;
}

#endif