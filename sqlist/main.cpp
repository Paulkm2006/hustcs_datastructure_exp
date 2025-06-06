﻿#include <iostream>
#include "lib/enum.hpp"
#include "lib/list.hpp"
#include "lib/multiple_list.hpp"

using namespace std;

int main(void)
{
	MultipleList<int> Lists;
	int n = 0;
	Lists.addList("default"); // 添加默认线性表

	int op = 1;
	int ret = 0;
	while (op)
	{
		system("cls");
		cout << "\n" << endl;
		cout << "      Menu for Linear Table Structure " << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "    	  1.  InitList          2.  DestroyList" << endl;
		cout << "    	  3.  ClearList         4.  ListEmpty" << endl;
		cout << "    	  5.  ListLength        6.  GetElem" << endl;
		cout << "         7.  LocateElem        8.  PriorElem" << endl;
		cout << "    	  9.  NextElem          10. ListInsert" << endl;
		cout << "         11. ListDelete        12. ListTraverse" << endl << endl;

		cout << "         13. MaxSubArray       14. SubArrayNum" << endl;
		cout << "    	  15. SortList" << endl << endl;

		cout << "         16. SaveList          17. LoadList" << endl << endl;

		cout << "         18. ChooseList        19. AddList" << endl;
		cout << "         20. RemoveList        21. LocateList" << endl << endl;
		cout << "         22. PrintAllList" << endl << endl;

		cout << "         0.  Exit" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "    Input your operation [0~24]: ";
		cin >> op;
		switch (op)
		{
		case 1:
			if (Lists[n].initList() == OK)
				cout << "线性表初始化成功！" << endl;
			else
				cout << "线性表初始化失败！" << endl;
			break;
		case 2:
			if (Lists[n].destroyList() == OK)
				cout << "线性表销毁成功！" << endl;
			else
				cout << "线性表销毁失败！" << endl;
			break;
		case 3:
			if (Lists[n].clearList() == OK)
				cout << "线性表已清除！" << endl;
			else
				cout << "线性表清除失败！" << endl;
			break;
		case 4:
			ret = Lists[n].isEmpty();
			if (ret == TRUE)
				cout << "线性表为空！" << endl;
			else if (ret == FALSE)
				cout << "线性表不为空!" << endl;
			else
				cout << "线性表不存在!" << endl;
			break;
		case 5:
		{
			ret = Lists[n].listLength();
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else
				cout << "线性表的长度为" << ret << endl;

			break;
		}
		case 6:
		{
			cout << "请输入需要获取的元素位置: " << endl;
			int i;
			cin >> i;
			ret = Lists[n].getElem(i);
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == ERROR)
				cout << "输入的位置不在线性表有效范围内!" << endl;
			else
				cout << "该位置的元素值为" << ret << endl;
			break;
		}
		case 7:
		{
			cout << "请输入要查找的元素: " << endl;
			int e;
			cin >> e;
			ret = Lists[n].locateElem(e);
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == ERROR)
				cout << "该数据不存在!" << endl;
			else
				cout << "该元素在线性表中第一次出现的位置序号为" << ret << endl;
			break;
		}
		case 8:
		{
			int e;
			cout << "请输入需要查找前驱的元素: " << endl;
			cin >> e;
			ret = Lists[n].priorElem(e);
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == ERROR)
				cout << "前驱不存在!" << endl;
			else
				cout << "前驱值为" << ret << endl;
			break;
		}
		case 9:
		{
			int e;
			cout << "请输入需要查找后继的元素: " << endl;
			cin >> e;
			ret = Lists[n].nextElem(e);
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == ERROR)
				cout << "后继不存在!" << endl;
			else
				cout << "后继值为" << ret << endl;
			break;
		}
		case 10:
		{
			cout << "请输入要插入的位置和元素值 " << endl;
			int i, e2;
			cin >> i >> e2;
			int m = Lists[n].listInsert(i, e2);
			if (m == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (m == ERROR)
				cout << "插入位置不正确!" << endl;
			else
				cout << "插入成功！" << endl;
			break;
		}
		case 11:
		{
			cout << "请输入要删除的元素位置 " << endl;
			int i;
			cin >> i;
			int j = Lists[n].listDelete(i);
			if (j == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (j == ERROR)
				cout << "删除位置不正确!" << endl;
			else
				cout << "删除成功！" << endl;
			break;
		}
		case 12:
		{
			int j = Lists[n].listTraverse();
			if (j == INFEASIBLE)
				cout << "线性表不存在！" << endl;
			if (j == OK && Lists[n].listLength() == 0)
				cout << "空线性表" << endl;
			break;
		}
		case 13:
		{
			ret = Lists[n].maxSubArray();
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == ERROR)
				cout << "线性表为空!" << endl;
			else
				cout << "最大连续子数组和为" << ret << endl;
			break;
		}
		case 14:
		{
			int k;
			cout << "请输入要查找的元素和k的值: " << endl;
			cin >> k;
			ret = Lists[n].subArrayNum(k);
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == ERROR)
				cout << "线性表为空!" << endl;
			else
				cout << "和为" << k << "的连续子数组数目为" << ret << endl;
			break;
		}
		case 15:
		{
			if (Lists[n].sortList() == OK)
				cout << "线性表排序成功!" << endl;
			else
				cout << "线性表排序失败!" << endl;
			break;
		}
		case 16:
		{
			cout << "请输入文件路径: " << endl;
			char filename[100];
			cin >> filename;
			if (Lists[n].saveList(filename) == OK)
				cout << "数据保存成功!" << endl;
			else
				cout << "保存失败!" << endl;
			break;
		}
		case 17:
		{
			cout << "请输入文件路径: " << endl;
			char filename[100];
			cin >> filename;
			if (Lists[n].loadList(filename) == OK)
				cout << "数据加载成功!" << endl;
			else
				cout << "加载失败!" << endl;
			break;
		}
		case 18:
		{
			cout << "请选择需要操作的线性表编号或名称:" << endl;
			char listname[20];
			cin >> listname;
			int f = Lists.locateList(listname);
			if (f == -1)
			{
				int t = atoi(listname);
				try {
					MyList<int>& L = Lists[t];
					cout << "线性表编号为" << t << endl;
					n = t;
				} catch (const std::out_of_range& e) {
					cout << "线性表不存在!" << endl;
				}
			}
			else
			{
				n = f;
				cout << "线性表名称为" << listname << endl;
			}
			break;
		}
		case 19:
		{
			cout << "请输入要添加的线性表名: " << endl;
			char listname[20];
			cin >> listname;
			if (Lists.locateList(listname) != -1)
				cout << "线性表已存在!" << endl;
			else{
				Lists.addList(listname);
				cout << "添加成功! 编号为" << Lists.locateList(listname) << endl;
			}
			break;
		}
		case 20:
		{
			ret = Lists.removeList(n);
			if (ret == OK)
				cout << "线性表删除成功!" << endl;
			else if (ret == ERROR)
				cout << "线性表不存在!" << endl;
			else if (ret == INFEASIBLE)
				cout << "线性表为空!" << endl;
			else
				cout << "删除失败!" << endl;
			break;
		}
		case 21:
		{
			cout << "请输入要查找的线性表名: " << endl;
			char listname[20];
			cin >> listname;
			int f = Lists.locateList(listname);
			if (f == -1)
				cout << "线性表不存在!" << endl;
			else
				cout << "线性表编号为" << f << endl;
			break;
		}
		case 22:
		{
			ret = Lists.printAllListNames();
			if (ret == INFEASIBLE)
				cout << "线性表不存在!" << endl;
			else if (ret == OK)
				cout << "打印成功!" << endl;
			else
				cout << "打印失败!" << endl;
			break;
		}
		case 0:
			cout << "退出系统" << endl;
			return 0;
		}
		getchar();
		getchar();
	}
	return 0;
}