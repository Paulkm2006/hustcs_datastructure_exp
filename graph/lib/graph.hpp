#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_set>
#include <memory>
#include <stack>
#include <queue>
#include <list>

#include "enum.hpp"

template<typename Key, typename Value>
struct Node
{
	std::pair<Key, Value> data; // 结点数据
	std::list<Node<Key, Value>*> arcs; // 结点的邻接表
	Node() : data(Key(), Value()), arcs() {} // 默认构造函数
};

template <typename Key, typename Value>
class Graph
{
	using T = std::pair<Key, Value>;
private:
	std::list<Node<Key, Value>> nodes; // 存储图的节点
	std::unordered_set<Key> keys; // 存储关键字的集合
	bool keyExists(Key k) const; // 判断关键字k是否存在
public:
	Graph() = default;	 // 构造函数
	~Graph() = default;	 // 析构函数
	Graph(Graph &&other) noexcept = default;
	Graph &operator=(Graph &&other) noexcept = default;

	void create(std::list<T> vexdef, std::list<std::pair<Key, Key>> arcdef); // 创建图
	void destroy(); // 销毁
	void set(Key k, T data); // 修改
	T operator[](Key k) const; // 使用序号查找
	T firstAdj(Key k) const; // 查找第一个邻接点
	T nextAdj(Key k, Key k1) const; // 查找下一个邻接点
	void insertVex(T data); // 插入元素k和v
	void deleteVex(Key k); // 删除关键字为k的结点及其所有邻接边
	void insertArc(Key k1, Key k2); // 插入弧
	void deleteArc(Key k1, Key k2); // 删除弧

	void DFS() const; // 深度优先遍历
	void BFS() const; // 广度优先遍历

	std::list<T> maxN(Key k, int n) const; // 查找与关键字为k的距离小于n的所有结点
	int shortestPath(Key k1, Key k2) const; // 查找k1到k2的最短路径
	int connectedComponents() const; // 查找连通分量

	void save(const char* filename) const; // 保存
	void load(const char* filename);
};

// 判断关键字k是否存在于二叉树中
template <typename Key, typename Value>
inline bool Graph<Key, Value>::keyExists(Key k) const
{
	if (nodes.empty())
		return false;
	return keys.find(k) != keys.end();
}

// 创建图
template <typename Key, typename Value>
inline void Graph<Key, Value>::create(std::list<T> vexdef, std::list<std::pair<Key, Key>> arcdef)
{
	keys.clear();
	for (const auto& vex : vexdef)
	{
		insertVex(vex);
	}
	for (const auto& arc : arcdef)
	{
		insertArc(arc.first, arc.second);
	}
}

// 销毁图
template <typename Key, typename Value>
inline void Graph<Key, Value>::destroy()
{
	nodes.clear();
	keys.clear();
}

// 查找关键字为k的结点
template <typename Key, typename Value>
inline std::pair<Key, Value> Graph<Key, Value>::operator[](Key k) const
{
	if (keyExists(k))
	{
		for (const auto& node : nodes)
		{
			if (node.data.first == k)
				return node.data;
		}
	}
	throw NOT_FOUND;
}

// 修改关键字为k的结点
template <typename Key, typename Value>
inline void Graph<Key, Value>::set(Key k, T data)
{
	if (keyExists(k))
	{
		for (auto& node : nodes)
		{
			if (node.data.first == k)
			{
				node.data = data;
				keys.erase(k);
				keys.insert(data.first);
				break;
			}
		}
	}
}

// 查找第一个邻接点
template <typename Key, typename Value>
inline std::pair<Key, Value> Graph<Key, Value>::firstAdj(Key k) const
{
	if (keyExists(k))
	{
		for (const auto& node : nodes)
		{
			if (node.data.first == k)
			{
				if (!node.arcs.empty())
					return node.arcs.front()->data;
				else
					throw NOT_FOUND;
			}
		}
	}
	throw NOT_FOUND;
}

// 查找下一个邻接点
template <typename Key, typename Value>
inline std::pair<Key, Value> Graph<Key, Value>::nextAdj(Key k, Key k1) const
{
	if (keyExists(k))
	{
		for (const auto& node : nodes)
		{
			if (node.data.first == k)
			{
				auto it = std::find_if(node.arcs.begin(), node.arcs.end(), [&](const Node<Key, Value>* n) { return n->data.first == k1; });
				if (it != node.arcs.end())
				{
					++it;
					if (it != node.arcs.end())
						return (*it)->data;
					else
						throw NOT_FOUND;
				}
			}
		}
	}
	throw NOT_FOUND;
}

// 插入顶点
template <typename Key, typename Value>
inline void Graph<Key, Value>::insertVex(T data)
{
	if (!keyExists(data.first))
	{
		Node<Key, Value> node;
		node.data = data;
		nodes.push_back(node);
		keys.insert(data.first);
	}
	else
	{
		throw CONFLICT;
	}
}

// 删除顶点
template <typename Key, typename Value>
inline void Graph<Key, Value>::deleteVex(Key k)
{
	if (keyExists(k))
	{
		for (auto &n : nodes)
		{
			deleteArc(k, n.data.first); // 删除与k的所有弧
		}
		auto it = std::remove_if(nodes.begin(), nodes.end(), 
			[&](const Node<Key, Value>& node) { return node.data.first == k; });
		nodes.erase(it, nodes.end());
		keys.erase(k);
	}
	else
	{
		throw NOT_FOUND;
	}
}

// 插入弧
template <typename Key, typename Value>
inline void Graph<Key, Value>::insertArc(Key k1, Key k2)
{
	if (keyExists(k1) && keyExists(k2))
	{
		Node<Key, Value>* node1Ptr = nullptr;
		Node<Key, Value>* node2Ptr = nullptr;

		for (auto& node : nodes)
		{
			if (node.data.first == k1)
				node1Ptr = &node;
			else if (node.data.first == k2)
				node2Ptr = &node;
			if (node1Ptr && node2Ptr)
				break;
		}

		node1Ptr->arcs.push_back(node2Ptr);
		node2Ptr->arcs.push_back(node1Ptr);
	}
	else
	{
		throw NOT_FOUND;
	}
}

// 删除弧
template <typename Key, typename Value>
inline void Graph<Key, Value>::deleteArc(Key k1, Key k2)
{
	if (keyExists(k1) && keyExists(k2))
	{
		for (auto& node : nodes)
		{
			if (node.data.first == k1)
			{
				auto it = std::remove_if(node.arcs.begin(), node.arcs.end(), [&](const Node<Key, Value> *n)
										 { return n->data.first == k2; });
				node.arcs.erase(it, node.arcs.end());
			}
			if (node.data.first == k2)
			{
				auto it = std::remove_if(node.arcs.begin(), node.arcs.end(), [&](const Node<Key, Value>* n) { return n->data.first == k1; });
				node.arcs.erase(it, node.arcs.end());
			}
		}
	}
	else
	{
		throw NOT_FOUND;
	}
}

// DFS 使用栈实现
template <typename Key, typename Value>
inline void Graph<Key, Value>::DFS() const
{
	std::unordered_set<Key> vis;
	std::stack<const Node<Key, Value>*> stack;

	for (const auto& node : nodes)
	{
		if (vis.find(node.data.first) == vis.end())
		{
			stack.push(&node);
			while (!stack.empty())
			{
				const Node<Key, Value>* current = stack.top();
				stack.pop();
				if (vis.find(current->data.first) == vis.end())
				{
					std::cout << "{ " << current->data.first << " " << current->data.second << " } "; // visit()
					vis.insert(current->data.first);
					for (const auto& arc : current->arcs)
					{
						stack.push(arc);
					}
				}
			}
		}
	}
}

// BFS 使用队列实现
template <typename Key, typename Value>
inline void Graph<Key, Value>::BFS() const
{
	std::unordered_set<Key> vis;
	std::queue<const Node<Key, Value>*> queue;

	for (const auto& node : nodes)
	{
		if (vis.find(node.data.first) == vis.end())
		{
			queue.push(&node);
			while (!queue.empty())
			{
				auto current = queue.front();
				queue.pop();
				if (vis.find(current->data.first) == vis.end()) // 未经过这个节点
				{
					std::cout << "{ " << current->data.first << " " << current->data.second << " } "; // visit()
					vis.insert(current->data.first);
					for (const auto& arc : current->arcs)
					{
						queue.push(arc);
					}
				}
			}
		}
	}
}

// 查找与关键字为k的距离小于n的所有结点, 使用BFS
template <typename Key, typename Value>
inline std::list<std::pair<Key, Value>> Graph<Key, Value>::maxN(Key k, int n) const
{
	if (keyExists(k))
	{
		for (const auto& node : nodes)
		{
			if (node.data.first == k)
			{
				std::list<T> result;
				std::unordered_set<Key> vis;
				std::queue<std::pair<const Node<Key, Value>*, int>> q;

				q.push({&node, 0});
				vis.insert(k);

				while (!q.empty()) {
					auto [current, distance] = q.front();
					q.pop();
					
					if (current->data.first != k) { // 排除起始节点
						result.push_back(current->data);
					}
	
					if (distance < n) { // 限制距离
						for (const auto& neighbor : current->arcs) { // 遍历邻接点
							if (vis.find(neighbor->data.first) == vis.end()) {
								vis.insert(neighbor->data.first);
								q.push({neighbor, distance + 1}); // 增加距离
							}
						}
					}
				}

				return result;
			}
		}
	} 
	else
	{
		throw NOT_FOUND;
	}
	return std::list<T>();
}

// 查找k1到k2的最短路径, 使用Dijkstra算法
template <typename Key, typename Value>
inline int Graph<Key, Value>::shortestPath(Key k1, Key k2) const
{
	if (keyExists(k1) && keyExists(k2))
	{
		std::unordered_map<Key, int> dst;
		// 优先队列<数据类型, 数据容器, 比较>
		std::priority_queue<std::pair<int, const Node<Key, Value> *>, std::vector<std::pair<int, const Node<Key, Value> *>>, std::greater<>> pq;

		for (const auto& node : nodes)
		{
			dst[node.data.first] = INT_MAX;
		}

		dst[k1] = 0;
		pq.push({ 0, &nodes.front() });

		while (!pq.empty())
		{
			auto [dist, current] = pq.top();
			pq.pop();

			if (current->data.first == k2) // 到达目标节点
				return dist;

			for (const auto& arc : current->arcs)
			{
				int newDist = dist + 1;
				if (newDist < dst[arc->data.first])
				{
					dst[arc->data.first] = newDist;
					pq.push({ newDist, arc });
				}
			}
			
		}
	}
	return -1;
}

// 查找连通分量，使用DFS
template <typename Key, typename Value>
inline int Graph<Key, Value>::connectedComponents() const
{
	std::unordered_set<Key> vis;
	int count = 0;

	for (const auto& node : nodes)
	{
		if (vis.find(node.data.first) == vis.end())
		{
			++count;
			std::stack<const Node<Key, Value>*> stack;
			stack.push(&node);
			while (!stack.empty())
			{
				const Node<Key, Value>* current = stack.top();
				stack.pop();
				if (vis.find(current->data.first) == vis.end())
				{
					vis.insert(current->data.first);
					for (const auto& arc : current->arcs)
					{
						stack.push(arc);
					}
				}
			}
		}
	}
	return count;
}

#include "file.hpp"

#endif // GRAPH_HPP