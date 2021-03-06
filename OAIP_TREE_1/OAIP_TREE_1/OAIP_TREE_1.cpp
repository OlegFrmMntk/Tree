#include "pch.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

class Tree
{
public:
	Tree();
	~Tree();

	void add(int Number, string Pass);
	void remove(int Number);
	void rm_mx_lf();
	void balance();
	void cout_prm();
	void cout_obrat();
	void cout_sort();
	void derevom();
	string find(int Number);

private:

	class Node
	{
	public:
		Node *pLeft, *pRight;
		int Number;
		string Pass;

		Node(int Number = int(), string Pass = string(), Node *pLeft = nullptr, Node *pRight = nullptr)
		{
			this->Number = Number;
			this->Pass = Pass;
			this->pLeft = pLeft;
			this->pRight = pRight;
		}
	};

	void clear1(Node *nNode);
	void bfs(int x);
	void rec(Node nNode, int level);
	void balance1(int l, int r);

	Node *Root;
	int amt;
	int met[111];
	vector <pair <int, string>> ans11;
};

Tree a;

Tree::Tree()
{
	Root = nullptr;
	amt = 0;
}

Tree::~Tree()
{
	clear1(Root);
}

void Tree::clear1(Node *nNode)
{
	Node *temp = nNode;
	if (nNode->pLeft) clear1(nNode->pLeft);
	if (nNode->pRight) clear1(nNode->pRight);

	delete temp;
}

void Tree::add(int Number, string Pass)
{
	if (!Root)
	{
		Root = new Node(Number, Pass);
	}
	else
	{
		Node *nNode = this->Root;
		while (true)
		{
			if (Number < nNode->Number)
			{
				if (!nNode->pLeft) break;
				nNode = nNode->pLeft;
			}
			else
			{
				if (!nNode->pRight) break;
				nNode = nNode->pRight;
			}
		}

		Node *xNode = new Node(Number, Pass);
		if (Number < nNode->Number) nNode->pLeft = xNode;
		else nNode->pRight = xNode;
	}
	amt++;
}

void Tree::remove(int Number)
{
	Node *nNode = this->Root, *left = nNode->pLeft, *right = nNode->pRight;
	while (nNode->Number != Number)
	{
		left = nNode->pLeft;
		right = nNode->pRight;

		if ((left && left->Number == Number) || (right && right->Number == Number)) break;

		if (Number < nNode->Number) nNode = nNode->pLeft;
		else nNode = nNode->pRight;
	}

	if (nNode->Number > Number)
	{
		Node *xNode = nNode->pLeft;

		nNode->pLeft = nullptr;
		left = xNode->pLeft;
		right = xNode->pRight;

		if (left) add(left->Number, left->Pass);
		if (right) add(right->Number, right->Pass);
	}
	else
	{
		Node *xNode = nNode->pRight;

		nNode->pRight = nullptr;
		left = xNode->pLeft;
		right = xNode->pRight;

		if (left) add(left->Number, left->Pass);
		if (right) add(right->Number, right->Pass);
	}
}

void Tree::rm_mx_lf()
{
	Node *Root = this->Root;

	if (!Root->pLeft) return;

	Node *xNode = Root->pLeft, *predNode = Root;

	while (true)
	{
		if (xNode->pRight)
		{
			predNode = xNode;
			xNode = xNode->pRight;
		}
		else break;
	}

	if (predNode == Root) Root->pLeft = nullptr;
	else predNode->pRight = nullptr;

	clear1(xNode);
}

void Tree::balance1(int l, int r)
{
	if (l == r)
	{
		if (!met[l])
		{
			a.add(ans11[l].first, ans11[l].second);
			met[l] = 1;
		}
		return;
	}
	int mid = (l + r) / 2;
	if (!met[mid])
	{
		a.add(ans11[mid].first, ans11[mid].second);
		met[mid] = 1;
	}

	if (mid > 0 && mid - 1 >= l) balance1(l, mid - 1);
	if (mid < r && mid + 1 <= r) balance1(mid + 1, r);
}

void Tree::balance()
{
	vector <Node> och;

	och.push_back(*Root);
	int p1 = -1, p2 = 0;

	while (p1 <= p2)
	{
		p1++;

		if (p1 > p2) break;

		if (och[p1].pLeft)
		{
			och.push_back(*och[p1].pLeft);
			p2++;
		}

		if (och[p1].pRight)
		{
			och.push_back(*och[p1].pRight);
			p2++;
		}
	}

	ans11.clear();
	for (int i = 0; i < och.size(); i++)
	{
		ans11.push_back(make_pair(och[i].Number, och[i].Pass));
	}

	sort(ans11.begin(), ans11.end());

	
	clear1(this->Root);
	Root = nullptr;
	
	for (int i = 0; i <= ans11.size(); i++)
		met[i] = 0;

	balance1(0, ans11.size() - 1);
}


string Tree::find(int Number)
{
	Node *nNode = this->Root;
	while (nNode->Number != Number)
	{
		if (Number < nNode->Number) nNode = nNode->pLeft;
		else nNode = nNode->pRight;
		if (!nNode)
		{
			cout << "\n";
			return "Такого номера не существует!!! ";
		}
	}
	return nNode->Pass;
}

void Tree::bfs(int x)
{
	vector <Node> och;

	och.push_back(*Root);
	int p1 = -1, p2 = 0;

	while (p1 <= p2)
	{
		p1++;

		if (p1 > p2) break;

		if (och[p1].pLeft)
		{
			och.push_back(*och[p1].pLeft);
			p2++;
		}

		if (och[p1].pRight)
		{
			och.push_back(*och[p1].pRight);
			p2++;
		}
	}

	vector <pair <int, string>> ans;

	ans.clear();

	for (int i = 0; i < och.size(); i++)
	{
		ans.push_back(make_pair(och[i].Number, och[i].Pass));
	}

	if (x == 2) reverse(ans.begin(), ans.end());
	else if (x == 3) sort(ans.begin(), ans.end());

	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i].first << " " << ans[i].second << endl;
	}
}

void Tree::cout_prm()
{
	bfs(1);
}

void Tree::cout_obrat()
{
	bfs(2);
}

void Tree::cout_sort()
{
	bfs(3);
}

void Tree::rec(Node nNode, int level)
{
	if (!nNode.pLeft && !nNode.pRight)
	{
		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << nNode.Number << "\n";
		return;
	}
	else {

		if (nNode.pRight)
		{
			rec(*nNode.pRight, level + 1);
		}

		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << nNode.Number << "\n";

		if (nNode.pLeft)
		{
			rec(*nNode.pLeft, level + 1);
		}
	}
}

void Tree::derevom()
{
	rec(*Root, 0);
}

void wrt()
{
	cout << "\nВыберите номер операции:\n";
	cout << "1)Добавить в дерево поиска новую запись.\n";
	cout << "2)Удалить из дерева поиска информацию с заданным ключом.\n";
	cout << "3)По заданному ключу найти информацию и отобразить её.\n";
	cout << "4)Сбалансировать дерево \n";
	cout << "5)Удалить из левой ветви дерева узел с максимальным значением ключа и все связаные с ним узлы.\n";
	cout << "6)Вывести дерево на экран\n";
	cout << "0)Завершить программу.\n\n";
	cout << "Введите номер операции:  ";
	
}

int main()
{
	setlocale(LC_ALL, "ru");
	ifstream fin("input.txt");

	int n;
	fin >> n;

	for (int i = 0; i < n; i++)
	{

		int x;
		string y;
		fin >> x >> y;
		a.add(x, y);
	}

	while (true)
	{
		wrt();
		int k;
		cin >> k;
		switch (k)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			cout << "Введите номер и фамилию:  ";
			int x;
			string y;
			cin >> x >> y;
			a.add(x, y);
			break;
		}
		case 2:
		{
			cout << "Введите ключ для удаления информации:  ";
			int x;
			cin >> x;
			a.remove(x);
			break;
		}
		case 3:
		{
			cout << "Введите ключ для нахождения информации:  ";
			int x;
			cin >> x;
			cout << endl << a.find(x) << endl;
			break;
		}
		case 4:
		{
			a.balance();
			cout << endl << "Балансировка успешно произведена" << endl;
			break;
		}
		case 5:
		{
			a.rm_mx_lf();
			cout << "\n Операция успешно произведена. \n";
			break;
		}
		case 6:
		{
			cout << "Выберите вариант вывода дерева: \n 1)Прямым обходом.\n 2)Обратным обхором.\n 3)В отсортированом порядке.\n 4)Деревом.\n\n";
			cout << "Введите номер операции:  ";
			int z;
			cin >> z;
			switch (z)
			{
			case 1:
			{
				a.cout_prm();
				break;
			}
			case 2:
			{
				a.cout_obrat();
				break;
			}
			case 3:
			{
				a.cout_sort();
				break;
			}
			case 4:
			{
				a.derevom();
				break;
			}
			default: break;
			}
			break;
		}
		}
	}

	return 0;
}
