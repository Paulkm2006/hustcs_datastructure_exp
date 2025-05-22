#include <iostream>
#include <functional>
#include "lib/enum.hpp"
#include "lib/bitree.hpp"
#include "lib/multiple_bitree.hpp"

using namespace std;

int main(void)
{
	MultipleBiTree<int, char> BiTrees;
	int n = 0;
	BiTrees.addBiTree("default"); // 添加默认二叉树

	int op = 1;
	while (op)
	{
		system("cls");
		cout << "\n" << endl;
		cout << "      Menu for Binary Tree Structure " << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "    	  1.  CreateBiTree        2.  DestroyBiTree" << endl;
		cout << "    	  3.  ClearBiTree         4.  BiTreeEmpty" << endl;
		cout << "    	  5.  BiTreeDepth         6.  LocateNode" << endl;
		cout << "         7.  Assign              8.  GetSibling" << endl;
		cout << "    	  9.  InsertNode          10. DeleteNode" << endl << endl;

		cout << "         Traverse Options" << endl;
		cout << "         11. Pre                 12. In" << endl;
		cout << "    	  13. Post                14. Level" << endl << endl;

		cout << "         15. MaxPathSum          16. LCA" << endl;
		cout << "    	  17. InvertTree" << endl << endl;

		cout << "         18. SaveBiTree          19. LoadBiTree" << endl << endl;

		cout << "         20. ChooseBiTree          21. AddBiTree" << endl;
		cout << "         22. RemoveBiTree          23. LocateBiTree" << endl << endl;
		cout << "         24. PrintAllBiTree" << endl << endl;

		cout << "         0.  Exit" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "    Input your operation [0~24]: ";
		cin >> op;
		try{
			switch (op)
			{
			case 1:
			{
				cout << "请输入二叉树的初始化数据: " << endl;
				std::pair<int, char> def[100];
				int i = 0;
				do {
					cin >> def[i].first >> def[i].second;
				} while (def[i++].first != -1);
				BiTrees[n].create(def);
				cout << "二叉树创建成功!" << endl;
				break;
			}
			case 2:
				BiTrees[n].destroy();
				cout << "二叉树销毁成功!" << endl;
				break;
			case 3:
				BiTrees[n].clear();
				cout << "二叉树清除成功!" << endl;
				break;
			case 4:
			{
				bool ret = BiTrees[n].isEmpty();
				if (ret)
					cout << "二叉树为空！" << endl;
				else
					cout << "二叉树不为空!" << endl;
				break;
			}
			case 5:
			{
				int ret = BiTrees[n].depth();
				cout << "二叉树的深度为" << ret << endl;
				break;
			}
			case 6:
			{
				cout << "请输入需要获取的元素键: " << endl;
				int i;
				cin >> i;
				auto result = BiTrees[n][i];
				cout << "该键的元素值为" << result.second << endl;
				break;
			}
			case 7:
			{
				cout << "请输入需要赋值的元素键，新的键和和值: " << endl;
				int i, e;
				char k;
				cin >> i >> e >> k;
				BiTrees[n].assign(i, { e, k });
				cout << "赋值成功!" << endl;
				break;
			}
			case 8:
			{
				cout << "请输入需要查找兄弟结点的元素键: " << endl;
				int i;
				cin >> i;
				auto result = BiTrees[n].getSibling(i);
				if (result.first == 0 && result.second == 0)
					cout << "兄弟结点不存在!" << endl;
				else
					cout << "该键的兄弟结点为" << result.first << "," << result.second << endl;
				break;
			}
			case 9:
			{
				cout << "请输入需要插入的位置、元素键、值和方向: " << endl;
				int k, i, dir;
				char e;
				cin >> k >> i >> e >> dir;
				BiTrees[n].insert(k, { i, e }, static_cast<InsertDirections>(dir));
				cout << "插入成功!" << endl;
				break;
			}
			case 10:
			{
				cout << "请输入需要删除的元素键: " << endl;
				int i;
				cin >> i;
				BiTrees[n].deleteNode(i);
				cout << "删除成功!" << endl;
				break;
			}
			case 11:
				BiTrees[n].preOrderTraverse();
				cout << endl 
					 << "二叉树遍历成功!" << endl;
				break;
			case 12:
				BiTrees[n].inOrderTraverse();
				cout << endl
					 << "二叉树遍历成功!" << endl;
				break;
			case 13:
				BiTrees[n].postOrderTraverse();
				cout << endl
					 << "二叉树遍历成功!" << endl;
				break;
			case 14:
				BiTrees[n].levelOrderTraverse();
				cout << endl
					 << "二叉树遍历成功!" << endl;
				break;
			case 15:
			{
				auto result = BiTrees[n].maxPathSum();
				cout << "二叉树的最大路径和为" << result << endl;
				break;
			}
			case 16:
			{
				cout << "请输入需要查找的两个元素键: " << endl;
				int i, j;
				cin >> i >> j;
				auto result = BiTrees[n].LCA(i, j);
				cout << "最近公共祖先为" << result.first << "," << result.second << endl;
				break;
			}
			case 17:
				BiTrees[n].invert();
				cout << "二叉树反转成功!" << endl;
				break;
			case 18:
			{
				cout << "请输入文件路径: " << endl;
				char filename[100];
				cin >> filename;
				BiTrees[n].save(filename);
				cout << "数据保存成功!" << endl;
				break;
			}
			case 19:
			{
				cout << "请输入文件路径: " << endl;
				char filename[100];
				cin >> filename;
				BiTrees[n].load(filename);
				cout << "数据加载成功!" << endl;
				break;
			}
			case 20:
			{
				cout << "请选择需要操作的二叉树编号或名称:" << endl;
				char BiTreename[20];
				cin >> BiTreename;
				int f = BiTrees.locateBiTree(BiTreename);
				if (f == -1)
				{
					int t = atoi(BiTreename);
					cout << "二叉树编号为" << t << endl;
					n = t;
				}
				else
				{
					n = f;
					cout << "二叉树名称为" << BiTreename << endl;
				}
				break;
			}
			case 21:
			{
				cout << "请输入要添加的二叉树名: " << endl;
				char BiTreename[20];
				cin >> BiTreename;
				BiTrees.addBiTree(BiTreename);
				cout << "添加成功! 编号为" << BiTrees.locateBiTree(BiTreename) << endl;
				break;
			}
			case 22:
			{
				BiTrees.removeBiTree(n);
				cout << "二叉树删除成功!" << endl;
				break;

			}
			case 23:
			{
				cout << "请输入要查找的二叉树名: " << endl;
				char BiTreename[20];
				cin >> BiTreename;
				int f = BiTrees.locateBiTree(BiTreename);
				cout << "二叉树编号为" << f << endl;
				break;
			}
			case 24:
			{
				BiTrees.printAllBiTreeNames();
				break;
			}
			case 0:
				cout << "退出系统" << endl;
				return 0;
			}
		}
		catch (const std::exception& e) {
			cout << "发生异常: " << e.what() << endl;
		}
		catch (...) {
			cout << "发生未知异常!" << endl;
		}
		getchar();
		getchar();
	}
	return 0;
}