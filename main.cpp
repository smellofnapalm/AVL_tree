#include "Menu.h"
AVL_tree<int>* tree = new AVL_tree<int>();
list<int>* buffer = new list<int>();
int main()
{
	menu(tree, buffer);
	/* AVL_tree<int>* tree = new AVL_tree<int>();
	for (int i = 1; i < (1 << 5); i++)
	{
		tree->push_back(i);
		if (i % 2) tree->delete_node(i);
	}
	tree->print();
	delete tree; */
}