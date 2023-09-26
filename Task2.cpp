#include <Windows.h>
#include <clocale>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>

using namespace std;

class Node
{
public:
	int a;
	char c;
	Node* left, * right;

	Node() {}

	Node(Node* L, Node* R)
	{
		left = L;
		right = R;
		a = L->a + R->a;
	}

};

vector <bool> code;
map<char, vector<bool> > table;

void BuildTable(Node* root)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->right);
	}
	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->left);
	}
	if (root->c) table[root->c] = code;
	if (code.empty())
	{
		
	}
	else
	{
		code.pop_back();
	}
}

void Print(Node* root, unsigned k = 0)
{
	if (root != NULL)
	{
		Print(root->left, k + 3);
		for (unsigned i = 0; i < k; i++)
		{
			cout << " ";
		}

		if (root->c) cout << root->a << " (" << root->c << ") " << endl;
		else cout << root->a << endl;
		Print(root->right, k + 3);
	}
}

struct MyCompare
{
	bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};


int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	setlocale(0, "rus");
	string s = "Гусяев Максим Игоревич";
	list <Node*> t;
	map <char, int> m;

	for (char c : s)
	{
		m[c]++;
	}

	cout << "Частота появления буквы в заданном алфавите" << endl;
	//double sr = 0;
	map<char, int>::iterator itr;
	for (itr = m.begin(); itr != m.end(); itr++)
	{
		//sr += double(itr->second) / double(s.size());
		if (((itr->second) / (s.size())) == 1)
		{
			cout << endl << "Построить дерево не удалось" << endl;
			break;
		}
		cout << itr->first << " : " << double(itr->second) / double(s.size()) << endl;
	}
	
	//cout << sr;

	map<char, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		Node* p = new Node;
		p->c = it->first;
		p->a = it->second;
		t.push_back(p);
	}

	while (t.size() != 1)
	{
		t.sort(MyCompare());
		Node* SonL = t.front();
		t.pop_front();
		Node* SonR = t.front();
		t.pop_front();

		Node* parent = new Node(SonL, SonR);
		t.push_back(parent);
	}

	Node* root = t.front();

	vector <bool> s1;
	vector <bool> s2; // ошибка
	cout << endl << "Дерево:" << endl;
	Print(root);
	BuildTable(root);
	cout << endl << "Код каждой буквы" << endl;
	for (size_t i = 0; i < s.length(); i++)
	{
		char c = s[i];
		vector <bool> x = table[c];
		cout << c << " : ";
		for (size_t n = 0; n < x.size(); n++)
		{
			s1.push_back(x[n]);
			cout << x[n];
		}
		cout << endl;
	}
	
	cout << endl << "Кодирование: ";
	for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i];
	}
	cout << endl << "Декодирование: ";
	Node* p = root;
	for (size_t i = 0; i < s1.size(); i++)
	{
		if (s1[i]) p = p->left; else p = p->right;
		if (p->c) { cout << p->c; p = root; }
	}
	s2.assign(s1.begin(), s1.end());
	if (s2[0] == 0)
	{
		s2[0] = 1;
	}
	else
	{
		s2[0] = 0;
	}
	cout << endl << endl << "Декодирование с ошибкой: ";
	for (size_t i = 0; i < s2.size(); i++)
	{
		if (s2[i]) p = p->left; else p = p->right;
		if (p->c) { cout << p->c; p = root; }
	}
	cout << endl << "Кодирование: ";
	for (size_t i = 0; i < s2.size(); i++)
	{
		cout << s2[i];
	}

	cout << endl << endl << "Исходный вес: " << (double(s.size())) * 8 << " бит" << endl << "Вес после кодировки: " << s1.size() << " бит " << "(" << ((double(s1.size()))/ ((double(s.size())) * 8)) * 100 << " %)" << endl;

	return 0;
}
