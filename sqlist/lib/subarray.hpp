#ifndef SUBARRAY_HPP
#define SUBARRAY_HPP



// maxSubArray 获取最大连续子数组
template <typename T>
inline int MyList<T>::maxSubArray() const
{
	if (elem == nullptr)
		return INFEASIBLE;
	int maxSum = 0; // 初始化最大为0
	int currentSum = 0; // 初始化目前和为0
	for (int i = 0; i < length; i++)
	{
		currentSum += elem[i]; //添加本元素
		if (currentSum > maxSum)
			maxSum = currentSum; // 如果增加则覆盖最大
		if (currentSum < 0)
			currentSum = 0; // 若小于0则清零
	}
	return maxSum;
}


// subArrayNum 获取和为k的连续子数组个数
// 该方法使用了暴力法，时间复杂度为O(n^2)，可以用前缀和优化为O(n)的算法
template <typename T>
inline int MyList<T>::subArrayNum(T k) const
{
	if (elem == nullptr)
		return INFEASIBLE;
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		int currentSum = 0;
		for (int j = i; j < length; j++)
		{
			currentSum += elem[j];
			if (currentSum == k) {
				count++;
				break;
			}
		}
	}
	return count;
}

#endif