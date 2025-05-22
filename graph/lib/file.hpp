#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <set>

// 写文件
template <typename Key, typename Value>
inline void Graph<Key, Value>::save(const char *filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("无法打开文件");
	
	file << nodes.size() << std::endl;

	for (const auto &node : nodes)
	{
		file << node.data.first << " " << node.data.second << " ";
	}

	file << std::endl;

	std::set<std::pair<Key, Key>> visited;
	for (const auto &node : nodes)
	{
		for (const auto &arc : node.arcs)
		{
			if (visited.find({ node.data.first, arc->data.first }) == visited.end()) // 确保每条边只写一遍
			{
				file << node.data.first << " " << arc->data.first << " ";
				visited.insert({ arc->data.first, node.data.first });
			}
		}
	}
	file << -1 << " " << -1 << std::endl;
}

// 读文件
template <typename Key, typename Value>
inline void Graph<Key, Value>::load(const char *filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("无法打开文件");
	

	nodes.clear();
	keys.clear();
	
	int vertexCount;
	file >> vertexCount;
	
	for (int i = 0; i < vertexCount; i++) {
		Key key;
		Value value;
		
		file >> key >> value;
		
		insertVex({ key, value });
	}
	
	
	while (!file.eof()) {
		Key source, dest;
		
		file >> source >> dest;
		
		if (source == -1 && dest == -1)
			break;
		insertArc(source, dest);
	}
}

#endif