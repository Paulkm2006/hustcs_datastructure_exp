#ifndef BI_TREE_HPP
#define BI_TREE_HPP

#include <iostream>
#include <unordered_set>
#include <memory>
#include <stack>
#include <queue>

#include "enum.hpp"

template<typename Key, typename Value>
struct Node
{
	std::pair<Key, Value> data; // 结点数据
	std::unique_ptr<Node> left, right;// 左右子树指针
	Node() : left(nullptr), right(nullptr), data(Key(), Value()) {} // 默认构造函数
	Node(Key k, Value v) : left(nullptr), right(nullptr), data(k, v) {} // 带参数的构造函数
	Node(std::pair<Key, Value> d) : left(nullptr), right(nullptr), data(d) {} // 带参数的构造函数
};

template <typename Key, typename Value>
class BiTree
{
	using T = std::pair<Key, Value>;
private:
	std::unique_ptr<Node<Key, Value>> head; // 指向二叉树根结点的指针
	std::unordered_set<Key> keys; // 存储关键字的集合
	bool keyExists(Key k) const; // 判断关键字k是否存在于二叉树中
public:
	BiTree() = default;  // 构造函数
	~BiTree() = default; // 析构函数
	BiTree(BiTree &&other) noexcept = default;
	BiTree &operator=(BiTree &&other) noexcept = default;

	void create(T* def); // 初始化二叉树
	void destroy(); // 销毁二叉树
	void clear();   // 清空二叉树
	bool isEmpty() const; // 判断二叉树是否为空
	int depth() const; // 获取二叉树深度
	T operator[](Key k) const; // 重载下标运算符
	void assign(T data); // 修改二叉树中关键字为e的元素的值为newVal
	T getSibling(Key k) const; // 查找二叉树中关键字为e的元素的兄弟结点
	void insert(Key k, T data, InsertDirections dir); // 插入元素k和v
	void deleteNode(Key k); // 删除关键字为k的结点

	void preOrderTraverse() const; // 先序遍历二叉树
	void inOrderTraverse() const; // 中序遍历二叉树
	void postOrderTraverse() const; // 后序遍历二叉树
	void levelOrderTraverse() const; // 层序遍历二叉树

	Value maxPathSum() const; // 求二叉树的最大路径和
	T LCA(Key k1, Key k2) const; // 查找二叉树中k1和k2的最近公共祖先
	void invertTree(); // 反转二叉树

	void save(const char* filename) const; // 保存二叉树到文件
	void load(const char* filename);
};

template <typename Key, typename Value>
inline bool BiTree<Key, Value>::keyExists(Key k) const
{
	if (head == nullptr)
		return false;
	return keys.find(k) != keys.end();
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::create(T *def)
{
	if (head != nullptr)
		throw NOT_INITIALIZED;

	// 递归构造函数
	std::function<void(std::unique_ptr<Node<Key, Value>>&, int&)> buildTree = 
		[&](std::unique_ptr<Node<Key, Value>>& node, int& index) {
			if (def[index].first == 0) { // 节点为空
				node = nullptr;
				index++;
				return;
			} else if (def[index].first == -1) { // 结束定义
				return;
			}
			
			if (keyExists(def[index].first)) // 如果关键字已经存在，抛出异常
				throw CONFLICT;
			node = std::make_unique<Node<Key, Value>>(def[index]); // 创建新节点
			keys.insert(def[index].first);
			index++;
			
			if (node != nullptr) {
				buildTree(node->left, index);
				buildTree(node->right, index);
			}
		};

	int index = 0;
	buildTree(head, index);
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::destroy()
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	head.reset(); // unique_ptr 自动释放内存
	keys.clear(); // 清空关键字集合
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::clear()
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	destroy();
	head = std::make_unique<Node<Key, Value>>();
	head->left = nullptr;
	head->right = nullptr;
	keys.clear(); // 清空关键字集合
	return;
}

template <typename Key, typename Value>
inline bool BiTree<Key, Value>::isEmpty() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	return head->left == nullptr && head->right == nullptr ? 1:0;
}

template <typename Key, typename Value>
inline int BiTree<Key, Value>::depth() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;

	std::function<int(const std::unique_ptr<Node<Key, Value>>&)> getDepth = 
		[&](const std::unique_ptr<Node<Key, Value>>& node) -> int {
			if (node == nullptr)
				return 0;
			int leftDepth = getDepth(node->left);
			int rightDepth = getDepth(node->right);
			return std::max(leftDepth, rightDepth) + 1;
		};

	return getDepth(head);
}

template <typename Key, typename Value>
inline std::pair<Key, Value> BiTree<Key, Value>::operator[](Key k) const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;

	std::function<Node<Key, Value>*(Node<Key, Value>*)> findNode = 
		[&](Node<Key, Value>* node) -> Node<Key, Value>* {
			if (node == nullptr)
				return nullptr;
			
			if (node->data.first == k)
				return node;
				
			Node<Key, Value>* leftResult = findNode(node->left.get());
			if (leftResult != nullptr)
				return leftResult;
				
			return findNode(node->right.get());
		};

	// Start the search from the root
	Node<Key, Value>* result = findNode(head.get());
	if (result != nullptr)
		return result->data;
	throw NOT_FOUND;
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::assign(T data)
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	if (!keyExists(data.first))
		throw NOT_FOUND;
	std::function<void(Node<Key, Value>*)> assignHelper = [&](Node<Key, Value>* node) -> void {
		if (node == nullptr)
			return;
		
		if (node->data.first == data.first) {
			node->data.second = data.second;
			return;
		}

		assignHelper(node->left.get());
		assignHelper(node->right.get());
	};

	assignHelper(head.get());
}

template <typename Key, typename Value>
inline std::pair<Key, Value> BiTree<Key, Value>::getSibling(Key k) const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	using T = std::pair<Key, Value>;
	std::function<T(Node<Key, Value>*)> searchHelper = [&](Node<Key, Value>* node) -> T {
		if (node == nullptr)
			return T(0, 0); // 返回一个空的pair

		if (node->left && node->left->data.first == k) {
			return node->right ? node->right->data : T(0, 0);
		} else if (node->right && node->right->data.first == k) {
			return node->left ? node->left->data : T(0, 0);
		}

		T leftResult = searchHelper(node->left.get());
		if (leftResult.first != 0)
			return leftResult; // 如果找到了兄弟节点，返回结果

		return searchHelper(node->right.get()); // 否则继续搜索右子树
	};
	return searchHelper(head.get());
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::insert(Key k, T data, InsertDirections dir)
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	if (keyExists(data.first))
		throw CONFLICT;

	Node<Key, Value>* newNode = new Node<Key, Value>(data); // 创建新节点
	keys.insert(data.first); // 插入新节点的关键字到集合中
	
	if(dir==ROOT) // 如果插入到根节点
	{
		newNode->right = std::move(head); // 将原来的头赋值给新节点右子树
		head.reset(newNode); // 将新节点赋值给头
		return;
	}

	if (!keyExists(k))
		throw NOT_FOUND;

	std::function<void(Node<Key, Value> *)> insertHelper = [&](Node<Key, Value> *node) -> void { // 用于递归查找和插入的lambda表达式
		if (node == nullptr)
			return;
		if (node->data.first == k) {
			if (dir == LEFT) {
				newNode->right = std::move(node->left); // 将原来的左子树赋值给新节点的右子树
				node->left.reset(newNode);
			} else if (dir == RIGHT) {
				newNode->right = std::move(node->right); // 将原来的右子树赋值给新节点的右子树
				node->right.reset(newNode);
			}
			return;
		}
		insertHelper(node->left.get());
		insertHelper(node->right.get());
	};

	insertHelper(head.get());
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::deleteNode(Key k)
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	if (!keyExists(k))
		throw NOT_FOUND;

	std::function<void(std::unique_ptr<Node<Key, Value>> &)> deleteHelper = [&](std::unique_ptr<Node<Key, Value>> & node) -> void { // 用于递归查找和删除的lambda表达式
		if (node == nullptr)
			return;
		if (node->data.first == k) {
			if (node->left == nullptr && node->right == nullptr) { // 叶子节点
				node.reset();
			} else if (node->left == nullptr) { // 只有右子树
				node = std::move(node->right);
			} else if (node->right == nullptr) { // 只有左子树
				node = std::move(node->left);
			} else { // 两个子树都存在
				Node<Key, Value>* current = node->left.get();
				while (current->right != nullptr) {
					current = current->right.get();
				}
				current->right = std::move(node->right);
				node = std::move(node->left);
			}
			keys.erase(k); // 删除关键字k
			return;
		}
		deleteHelper(node->left);
		deleteHelper(node->right);
	};

	deleteHelper(head);
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::preOrderTraverse() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	std::stack<Node<Key, Value>*> stack;
	stack.push(head.get());
	while (!stack.empty()) {
		Node<Key, Value>* current = stack.top();
		stack.pop();
		std::cout << current->data.first << "," << current->data.second << " ";
		if (current->right != nullptr)
			stack.push(current->right.get());
		if (current->left != nullptr)
			stack.push(current->left.get());
	}
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::inOrderTraverse() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	std::stack<Node<Key, Value>*> stack;
	Node<Key, Value>* current = head.get();
	while (current != nullptr || !stack.empty()) {
		while (current != nullptr) {
			stack.push(current);
			current = current->left.get();
		}
		current = stack.top();
		stack.pop();
		std::cout << current->data.first << "," << current->data.second << " ";
		current = current->right.get();
	}
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::postOrderTraverse() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	std::stack<Node<Key, Value>*> stack;
	Node<Key, Value> *current = head.get();
	Node<Key, Value> *lastVisited = nullptr;

	while (current || !stack.empty())
	{
		if (current)
		{
			stack.push(current);
			current = current->left.get();
		}
		else
		{
			auto t = stack.top();
			if (t->right && lastVisited != t->right.get())
				current = t->right.get();
			else
			{
				std::cout << t->data.first << "," << t->data.second << " ";
				lastVisited = t;
				stack.pop();
				current = nullptr;
			}
		}
	}
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::levelOrderTraverse() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	std::queue<Node<Key, Value>*> queue;
	queue.push(head.get());
	while (!queue.empty()) {
		Node<Key, Value>* current = queue.front();
		queue.pop();
		std::cout << current->data.first << "," << current->data.second << " ";
		if (current->left != nullptr)
			queue.push(current->left.get());
		if (current->right != nullptr)
			queue.push(current->right.get());
	}
}

template <typename Key, typename Value>
inline Value BiTree<Key, Value>::maxPathSum() const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;

	if constexpr (std::is_arithmetic<Value>::value) {
		Value maxSum = std::numeric_limits<Value>::lowest();
		std::function<Value(Node<Key, Value> *)> maxPathHelper = [&](Node<Key, Value> *node) -> Value
		{
			if (node == nullptr)
				return 0;
			Value leftSum = maxPathHelper(node->left.get());
			Value rightSum = maxPathHelper(node->right.get());
			Value currentMax = std::max(node->data.second, std::max(leftSum + node->data.second, rightSum + node->data.second));
			maxSum = std::max(maxSum, std::max(currentMax, leftSum + rightSum + node->data.second));
			return currentMax;
		};
		maxPathHelper(head.get());
		return maxSum;
	} else {
		throw NOT_ARITHMETIC;
	}
}
template <typename Key, typename Value>
inline std::pair<Key, Value> BiTree<Key, Value>::LCA(Key k1, Key k2) const
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	if (!keyExists(k1) || !keyExists(k2))
		throw NOT_FOUND;

	using T = std::pair<Key, Value>;
	std::function<T(Node<Key, Value>*)> LCAHelper = [&](Node<Key, Value>* node) -> T {
		if (node == nullptr)
			return T(0, 0);
		if (node->data.first == k1 || node->data.first == k2)
			return node->data;
		T leftLCA = LCAHelper(node->left.get());
		T rightLCA = LCAHelper(node->right.get());
		if (leftLCA.first != 0 && rightLCA.first != 0)
			return node->data;
		return leftLCA.first != 0 ? leftLCA : rightLCA;
	};
	return LCAHelper(head.get());
}

template <typename Key, typename Value>
inline void BiTree<Key, Value>::invertTree()
{
	if (head == nullptr)
		throw NOT_INITIALIZED;
	std::function<void(Node<Key, Value>*)> invertHelper = [&](Node<Key, Value>* node) {
		if (node == nullptr)
			return;
		std::swap(node->left, node->right);
		invertHelper(node->left.get());
		invertHelper(node->right.get());
	};
	invertHelper(head.get());
}

#include "file.hpp"

#endif


