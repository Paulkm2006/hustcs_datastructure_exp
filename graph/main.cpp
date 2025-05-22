#include <iostream>
#include <functional>
#include <string>
#include "lib/enum.hpp"
#include "lib/graph.hpp"
#include "lib/multiple_graph.hpp"

using namespace std;
using T = std::pair<int, std::string>;

int main(void)
{
	MultipleGraph<int, std::string> Graphs; // 创建多图
	int gr = 0;
	Graphs.addGraph("default"); // 添加默认图

	int op = 1;
	while (op)
	{
		system("cls");
		cout << "\n" << endl;
		cout << "      Menu for Graph Structure " << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "    	  1.  CreateGraph        2.  DestroyGraph" << endl;
		cout << "    	  3.  LocateVex          4.  PutVex " << endl;
		cout << "    	  5.  FirstAdjVex        6.  NextAdjVex" << endl;
		cout << "         7.  InsertVex          8.  DeleteVex" << endl;
		cout << "    	  9.  InsertArc          10. DeleteArc" << endl
			 << endl;

		cout << "         Traverse Options" << endl;
		cout << "         11. DFS                12. BFS" << endl << endl;

		cout << "         13. LessThanK          14. ShortestPathLength" << endl;
		cout << "    	  15. ConnectedComponentsNums" << endl
			 << endl;

		cout << "         16. SaveGraph          17. LoadGraph" << endl << endl;

		cout << "         18. ChooseGraph          19. AddGraph" << endl;
		cout << "         20. RemoveGraph          21. LocateGraph" << endl << endl;
		cout << "         22. PrintAllGraph" << endl << endl;

		cout << "         0.  Exit" << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << "    Input your operation [0~24]: ";
		cin >> op;
		try{
			switch (op)
			{
			case 1:
			{
				cout << "请输入初始化数据: " << endl;
				std::list<T> data;
				std::list<std::pair<int, int>> arcs;
				int n;
				std::string name;
				cin >> n >> name;
				while (name != "nil")
				{
					data.push_back({ n, name });
					cin >> n >> name;
				}
				int m;
				cin >> n >> m;
				while (m != -1)
				{
					arcs.push_back({ n, m });
					cin >> n >> m;
				}
				Graphs[gr].create(data, arcs);
				cout << "图创建成功!" << endl;
				break;
			}
			case 2:
				Graphs[gr].destroy();
				cout << "图销毁成功!" << endl;
				break;
			case 3:
			{
				cout << "请输入需要查找的元素键: " << endl;
				int i;
				cin >> i;
				auto result = Graphs[gr][i];
				cout << "该键的元素值为" << result.second << endl;
				break;
			}
			case 4:
			{
				cout << "请输入需要赋值的元素键、新的键和值: " << endl;
				int i, e;
				std::string name;
				cin >> i >> e >> name;
				Graphs[gr].set(i, {e, name});
				cout << "赋值成功!" << endl;
				break;
			}
			case 5:
			{
				cout << "请输入需要查找的元素键: " << endl;
				int i;
				cin >> i;
				T result = Graphs[gr].firstAdj(i);
				cout << "该键的第一个邻接点为" << result.first << " " << result.second << endl;

				break;
			}
			case 6:
			{
				cout << "请输入需要查找的元素键和邻接点: " << endl;
				int i, j;
				cin >> i >> j;
				T result = Graphs[gr].nextAdj(i, j);
				cout << "该键的下一个邻接点为" << result.first << " " << result.second << endl;
				break;
			}
			case 7:
			{
				cout << "请输入需要插入的元素键和元素值: " << endl;
				int i;
				std::string name;
				cin >> i >> name;
				Graphs[gr].insertVex({i, name});
				cout << "插入成功!" << endl;
				break;
			}
			case 8:
			{
				cout << "请输入需要删除的元素键: " << endl;
				int i;
				cin >> i;
				Graphs[gr].deleteVex(i);
				cout << "删除成功!" << endl;
				break;
			}
			case 9:
			{
				cout << "请输入需要插入的弧的起点、终点: " << endl;
				int i, j;
				cin >> i >> j;
				Graphs[gr].insertArc(i, j);
				cout << "插入成功!" << endl;
				break;
			}
			case 10:
			{
				cout << "请输入需要删除的弧的起点和终点: " << endl;
				int i, j;
				cin >> i >> j;
				Graphs[gr].deleteArc(i, j);
				cout << "删除成功!" << endl;
				break;
			}
			case 11:
			{
				Graphs[gr].DFS();
				cout << endl << "深度优先遍历完成!" << endl;
				break;
			}
			case 12:
			{
				Graphs[gr].BFS();
				cout << endl << "广度优先遍历完成!" << endl;
				break;
			}
			case 13:
			{
				cout << "请输入需要查找的元素键和k值: " << endl;
				int i, k;
				cin >> i >> k;
				auto result = Graphs[gr].maxN(i, k);
				if (result.empty())
					cout << "没有找到符合条件的元素!" << endl;
				else
					cout << "符合条件的元素为: ";
				for (const auto& elem : result)
					cout << elem.first << " ";
				cout << endl;
				break;
			}
			case 14:
			{
				cout << "请输入需要查找的元素键1，键2: " << endl;
				int i, j;
				cin >> i >> j;
				int result = Graphs[gr].shortestPath(i, j);
				if (result == -1)
					cout << "没有找到路径!" << endl;
				else
					cout << "最短路径: " << result << endl;
				break;
			}
			case 15:
			{
				int result = Graphs[gr].connectedComponents();
				cout << "连通分量个数为: " << result << endl;
				break;
			}
			case 16:
			{
				cout << "请输入文件路径: " << endl;
				char filename[100];
				cin >> filename;
				Graphs[gr].save(filename);
				cout << "数据保存成功!" << endl;
				break;
			}
			case 17:
			{
				cout << "请输入文件路径: " << endl;
				char filename[100];
				cin >> filename;
				Graphs[gr].load(filename);
				cout << "数据加载成功!" << endl;
				break;
			}
			case 18:
			{
				cout << "请选择需要操作的图编号或名称:" << endl;
				char Graphname[20];
				cin >> Graphname;
				int f = Graphs.locateGraph(Graphname);
				if (f == -1)
				{
					int t = atoi(Graphname);
					cout << "图编号为" << t << endl;
					gr = t;
				}
				else
				{
					gr = f;
					cout << "图名称为" << Graphname << endl;
				}
				break;
			}
			case 19:
			{
				cout << "请输入要添加的图名: " << endl;
				char Graphname[20];
				cin >> Graphname;
				Graphs.addGraph(Graphname);
				cout << "添加成功! 编号为" << Graphs.locateGraph(Graphname) << endl;
				break;
			}
			case 20:
			{
				Graphs.removeGraph(gr);
				cout << "图删除成功!" << endl;
				break;

			}
			case 21:
			{
				cout << "请输入要查找的图名: " << endl;
				char Graphname[20];
				cin >> Graphname;
				int f = Graphs.locateGraph(Graphname);
				cout << "图编号为" << f << endl;
				break;
			}
			case 22:
			{
				Graphs.printAllGraphNames();
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