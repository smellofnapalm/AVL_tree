#pragma once

#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include "AVL_tree.h"
#include "List.h"

using namespace std;

const vector<string> v =
{
	"Make a new tree",
	"Add an element",
	"Delete an element",
	"Print tree",
	"Clear tree",

	"Copy from P to K to list",
	"Print list",
	"Clear list",
};

template<class T>
void make_tree(AVL_tree<T>* &tree);

template<class T>
void add_element(AVL_tree<T>* &tree);

template<class T>
void delete_element(AVL_tree<T>*& tree);

template<class T>
void print_tree(AVL_tree<T>*& tree);

template<class T>
void delete_tree(AVL_tree<T>*& tree);

template<class T>
void left_traversal(tree_node<T>* p, list<T>*& buffer, const T& P, const T& K);

template<class T>
void right_traversal(tree_node<T>* p, list<T>*& buffer, const T& P, const T& K);

template<class T>
void copy_from_P_to_K(AVL_tree<T>*& tree, list<T>* & buffer);

template<class T>
void print_list(list<T>* buffer);

template<class T>
void delete_list(list<T>* &buffer);

template<class T>
int print_menu(AVL_tree<T>*& tree, vector<string> mas = v);

template<class T>
void menu(AVL_tree<T>*& tree, list<T>*& buffer);


template<class T>
void make_tree(AVL_tree<T>* &tree)
{
	cout << "Please, enter how many elements you want to add:\n";
	try
	{
		size_t N;
		cin >> N;

		cout << "Now enter these elements:\n";
		vector<T> v(N);
		for (size_t i = 0; i < N; i++)
			cin >> v[i];

		AVL_tree<T>* new_tree = new AVL_tree<T>(v);
		cout << "Tree was built succesfully! :)\n";

		delete tree;
		tree = new_tree;
	}
	catch (const exception&)
	{
		cout << "Something went wrong, but your old tree is alright!\n";
	}
}

template<class T>
void add_element(AVL_tree<T>*& tree)
{
	try
	{
		cout << "Enter the element, that you want to push:\n";
		T elem;
		cin >> elem;
		tree->push_back(elem);
		cout << "The element have been succesfully pushed!\n";
	}
	catch (const exception&)
	{
		cout << "Something went wrong, but your old tree is alright!\n";
	}
}

template<class T>
void delete_element(AVL_tree<T>*& tree)
{
	try
	{
		cout << "Enter the element, you want to delete:\n";
		T val;
		cin >> val;
		if (tree->find(val))
		{
			tree->delete_node(val);
			cout << "The element was succesfully deleted!\n";
		}
		else
			cout << "The element is not in the tree! :(\n";
	}
	catch (const exception&)
	{
		cout << "Something went wrong, but your old tree is alright!\n";
	}
}

template<class T>
void print_tree(AVL_tree<T>*& tree)
{
	cout << "Here is your tree!\n\n";
	tree->print();
	cout << "\nThe size of the tree is " << tree->get_size() << "\n";
}

template<class T>
void delete_tree(AVL_tree<T>*& tree)
{
	cout << "Now we are going to clean the tree!\n";
	delete tree;
	tree = new AVL_tree<T>();
	cout << "Tree has been succesfully cleaned!\n";
}

template<class T>
void right_traversal(tree_node<T>* p, list<T>*& buffer, const T& P, const T& K)
{
	if (!p || p->value > K) return;
	left_traversal(p->left, buffer, P, K);
	if (p->value >= P && p->value <= K) buffer->push_back(p->value);
	right_traversal(p->right, buffer, P, K);
}

template<class T>
void left_traversal(tree_node<T>* p, list<T>*& buffer, const T& P, const T& K)
{
	if (!p || p->value < P) return;
	left_traversal(p->left, buffer, P, K);
	if (p->value >= P && p->value <= K) buffer->push_back(p->value);
	right_traversal(p->right, buffer, P, K);
}

template<class T>
void copy_from_P_to_K(AVL_tree<T>*& tree, list<T>*& buffer)
{
	cout << "Enter from where (P) to start copy and where to end (K):\n";
	T P, K;
	cin >> P >> K;
	if (tree->get_root())
	{
		left_traversal(tree->get_root()->left, buffer, P, K);
		if (tree->get_root()->value >= P && tree->get_root()->value <= K) buffer->push_back(tree->get_root()->value);
		right_traversal(tree->get_root()->right, buffer, P, K);
		cout << "Elements have been successfully added to the list!\n";
	}
	else cout << "The tree is empty, so there is nothing to push! :(\n";
}

template <class T>
void print_list(list<T>* buffer)
{
	cout << "Here is your list of elements from P to K:\n";
	node<T>* p = buffer->get_begin();
	while (p)
	{
		cout << p->value << " ";
		p = p->next;
	}
	cout << "\nThe size of the buffer is " << buffer->get_size() << "\n";
}

template <class T>
void delete_list(list<T>*& buffer)
{
	cout << "Here we destroy all elements of the list:\n";
	delete buffer;
	buffer = new list<T>();
	cout << "List has been succesfully cleaned!\n";
}

template<class T>
int print_menu(AVL_tree<T>*& tree, vector<string> mas)
{
	const int ENTER = 224;
	const int UP = 72;
	const int DOWN = 80;
	const int ESC = 27;
	const int CR = 13;

	int N = mas.size();
	int key = 0, move;
	while (true)
	{
		print_tree(tree);

		cout << "\n";

		cout << "Choose a menu item you need:\n\n";
		cout << "Press ESC to quit\n\n";

		for (int i = 0; i < N; i++)
		{
			if (i != key)
				cout << i + 1 << ". " << mas[i] << endl;
			else
				cout << "\x1B[34m" << i + 1 << ". " << mas[i] << "\033[0m\n";
		}
		cout << '\n';

		move = _getch();
		if (move == ESC)
		{
			system("cls");
			return N + 1;
		}
		if (move == ENTER)
			move = _getch();

		if (move == CR)
		{
			system("cls");
			return key;
		}
		else if (move == UP)
			key = ((key - 1) % N + N) % N;
		else if (move == DOWN)
			key = (key + 1) % N;
		system("cls");
	}
	return key;
}

template <class T>
void menu(AVL_tree<T>* &tree, list<T>* &buffer)
{
	while (true)
	{
		int key = print_menu(tree);
		if (key == 0) make_tree(tree);
		else if (key == 1) add_element(tree);
		else if (key == 2) delete_element(tree);
		else if (key == 3) print_tree(tree);
		else if (key == 4) delete_tree(tree);
		else if (key == 5) copy_from_P_to_K(tree, buffer);
		else if (key == 6) print_list(buffer);
		else if (key == 7) delete_list(buffer);
		else return;

		char x;
		cout << "Do you want to continue? (y/n):\n";
		cin >> x;
		if (x == 'y')
			system("cls");
		else
			return;
	}

}
