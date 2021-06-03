#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct tree_node
{
	T value;
	tree_node* left = nullptr;
	tree_node* right = nullptr;
	int height = -1;
	bool is_leaf() const { return left == nullptr && right == nullptr; }
	tree_node(const T& val) { value = val; }
};

template <class T>
struct AVL_tree
{
private:

	tree_node<T>* root = nullptr;
	size_t size = 0;

	int height(tree_node<T>* p, int key)
	{
		if (!p) return 0;
		if (p->height != -1 && key == 0) return p->height;

		p->height = max(height(p->left), height(p->right)) + 1;

		return p->height;
	}

	int balance_factor(tree_node<T>* p)
	{
		return height(p->right) - height(p->left);
	}

	tree_node<T>* rot_right(tree_node<T>* p)
	{
		tree_node<T>* q = p->left;
		p->left = q->right;
		q->right = p;
		height(p, 1);
		height(q, 1);
		return q;
	}

	tree_node<T>* rot_left(tree_node<T>* q)
	{
		tree_node<T>* p = q->right;
		q->right = p->left;
		p->left = q;
		height(q, 1);
		height(p, 1);
		return p;
	}

	tree_node<T>* balance(tree_node<T>* p)
	{
		height(p, 1);
		if (balance_factor(p) == 2)
		{
			if (balance_factor(p->right) < 0)
				p->right = rot_right(p->right);
			p = rot_left(p);
		}
		if (balance_factor(p) == -2)
		{
			if (balance_factor(p->left) > 0)
				p->left = rot_left(p->left);
			p = rot_right(p);
		}
		return p;
	}

	void push_element(tree_node<T>*& p, const T& val)
	{
		if (!p) { p = new tree_node<T>(val); root = p; size++; return; }

		if (p->value > val)
		{
			if (!p->left)
			{
				p->left = new tree_node<T>(val);
				size++;
				return;
			}
			push_element(p->left, val);
		}
		else if (p->value < val)
		{
			if (!p->right)
			{
				p->right = new tree_node<T>(val);
				size++;
				return;
			}
			push_element(p->right, val);
		}
		p = balance(p);
	}

	tree_node<T>* find(tree_node<T>* p, const T& val) const
	{
		if (!p) return nullptr;

		if (p->value == val)
			return p;

		if (val < p->value)
			return find(p->left, val);
		else if (val >= p->value)
			return find(p->right, val);
	}

	tree_node<T>* node_with_min_value(tree_node<T>* p) const
	{
		if (p->left)
			return node_with_min_value(p->left);
		return p;
	}

	tree_node<T>* remove_node_with_min_value(tree_node<T>* p)
	{
		if (!p->left) return p->right;
		p->left = remove_node_with_min_value(p->left);
		balance(p);
		return p;
	}

	tree_node<T>* delete_node(tree_node<T>* p, const T& val)
	{
		bool flag = false;
		if (!p) return nullptr;
		if (val < p->value) p->left = delete_node(p->left, val);
		else if (val > p->value) p->right = delete_node(p->right, val);
		else
		{
			tree_node<T>* left = p->left;
			tree_node<T>* right = p->right;
			tree_node<T>* temp = nullptr;

			if (root == p)
				flag = true;
			delete p;
			if (!right)
			{
				if (flag) root = left;
				return left;
			}

			temp = node_with_min_value(right);
			temp->right = remove_node_with_min_value(right);
			temp->left = left;

			tree_node<T>* q = balance(temp);
			if (flag) root = q;
			return q;
		}

		return balance(p);
	}

	void print(tree_node<T>* where, int level = 0) const
	{
		if (!where) return;
		print(where->right, level + 1);
		for (int i = 0; i < level; i++) cout << '\t';
		cout << where->value << endl;
		print(where->left, level + 1);
	}

	void del_tree(tree_node<T>* p)
	{
		if (!p) return;
		if (p->is_leaf()) { delete p; return; }

		del_tree(p->left);
		del_tree(p->right);
		delete p;
	}

public:
	// GETTERS
	tree_node<T>* get_root() const { return root; }
	size_t get_size() const { return size; }

	// CTORS
	AVL_tree(T* mas, size_t sz)
	{
		for (size_t i = 0; i < sz; i++)
			push_element(root, mas[i]);
	}
	AVL_tree(vector<T> vec)
	{
		for (auto el : vec)
			push_element(root, el);
	}
	AVL_tree() {}

	~AVL_tree() { del_tree(root); }

	// WRAP PRIVATE FUNCTIONS IN A NICE WAY
	void push_back(const T& val) { push_element(root, val); }
	int height(tree_node<T>* p) { return height(p, 0); }
	tree_node<T>* find(const T& val) const { return find(root, val); }
	void delete_node(const T& val) { delete_node(root, val); }
	void print() const { print(root); }
};