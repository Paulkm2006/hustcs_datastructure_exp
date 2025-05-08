#ifndef ENUM_HPP
#define ENUM_HPP

#define NOT_FOUND std::out_of_range("元素不存在")
#define NOT_INITIALIZED std::runtime_error("树未初始化")
#define CONFLICT std::invalid_argument("键值冲突")
#define NOT_ARITHMETIC std::runtime_error("值类型无法进行运算")
#define OUT_OF_RANGE std::out_of_range("索引超出范围")

enum InsertDirections
{
	LEFT = 0,
	RIGHT = 1,
	ROOT = -1
};

#endif // ENUM_HPP