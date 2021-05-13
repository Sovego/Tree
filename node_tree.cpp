#include<iostream>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
struct node_tree {
	int value;
	node_tree* left;
	node_tree* right;
};

bool is_empty(node_tree* root_tree)
{
	return root_tree == nullptr;
}

node_tree* add(node_tree* root_tree, int a) {
	if (root_tree == nullptr) {
		root_tree = new node_tree;
		root_tree->value=a;
		root_tree->right = nullptr;
		root_tree->left = nullptr;
	}
	else {
		if (a < root_tree->value) {
			root_tree->left=add(root_tree->left, a);
		}
		else {
			root_tree->right=add(root_tree->right, a); }
	}
	return root_tree;
}

node_tree* del_elem(node_tree* root_tree, int element) {
	if (element == root_tree->value) {
		node_tree* temp = nullptr;
		if ((root_tree->right == nullptr) && (root_tree->left == nullptr)) {
			delete root_tree;
			return temp;
		}
		if ((root_tree->right == nullptr) || (root_tree->left == nullptr))
		{

			if (root_tree->right == nullptr) {
				root_tree = root_tree->left;
			}
			else {
				root_tree = root_tree->right;
			}
			return root_tree;
		}

		else {
			node_tree* temp = root_tree->right;
			node_tree* prev=root_tree->right;
			while (temp->left != nullptr) {
				prev = temp;
				temp = temp->left;
			}
			root_tree->value = temp->value;
			if (temp->right == nullptr) {
				prev->left = nullptr;
			}
			else {
				prev->left = prev->left->right;
				prev->left->right = nullptr;
			}
			temp = root_tree;
			return temp;
		}
	}
	if (element <= root_tree->value)
		root_tree->left = del_elem(root_tree->left, element);
	else
		root_tree->right = del_elem(root_tree->right, element);
	return root_tree;
}

void search(node_tree* root_tree,int a) {

	while (root_tree != nullptr) {
		if (root_tree->value == a) { std::cout << "This item exists in the tree\n"; return; }
		if (a < root_tree->value) { root_tree = root_tree->left; }
		else(root_tree = root_tree->right);
	}
	std::cout << "There is no such element in the tree\n";
}

void go_to_xy (short x, short y)
{
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}

void print (node_tree * root_tree, short x, short y, short a, char c)
{
    if (root_tree)
    {
        if (a>0 && c!='k')
        {
            if (c=='l')
                x-=10;
            else
                x+=10;
        }
        else if (c!='k')
            if (c=='l')
                x-=4;
            else
                x+=4;
        go_to_xy (x,y+=2);
        a--;
        printf ("%5d", root_tree->value);
        print (root_tree->left,x,y,a,'l');
        print (root_tree->right,x,y,a,'r');
    }
}

void output(node_tree* current) {
	if (current != nullptr) {
		output(current->left);
		std::cout << current->value << " ";
		output(current->right);

	}
}

void del_all(node_tree* Tree1) {
	if (Tree1 != nullptr) {
		del_all(Tree1->left);
		del_all(Tree1->right);
		delete Tree1;
	}
}

int main() {
	system("cls");
	
	node_tree* root_tree=new node_tree;
	root_tree = nullptr;
	int a=0;
	int b;
	while (a!=6)
	{
		system("cls");
		std::cout << "1 Add element\n";
		std::cout << "2 Del element\n";
		std::cout << "3 Search\n";
		std::cout << "4 Output\n";
		std::cout << "5 Del all\n";
		std::cout << "6 Exit\n";
		std::cin >> a;
		switch (a)
		{
		case 1:
			std::cout << "Enter element: ";
			std::cin >> b;
			root_tree = add(root_tree, b);
			break;
		case 2:
			if (is_empty(root_tree))
			{
				std::cout << "Tree not create";
			} else
			{
				std::cout << "Enter the element you want to remove\n";
			std::cin >> b;
			root_tree = del_elem(root_tree,b);
			}
			break;
		case 3:
			if (is_empty(root_tree))
			{
				std::cout << "Tree not create";
			} else
			{
				std::cout << "Enter element: ";
				std::cin >> b;
				search(root_tree, b);
			}
			break;
		case 4:
			if (is_empty(root_tree))
			{
				std::cout << "Tree not create";
			} else
			{
				print (root_tree,37,5,2,'k');
				//output(root_tree);
				std::cout << std::endl;
			}
			break;
		case 5:
			if (is_empty(root_tree))
			{
				std::cout << "Tree not create";
			} else
			{
				del_all(root_tree);
				root_tree = nullptr;
			}
			break;
		case 6:
			{
				delete root_tree;
				break;
			}
		default: std::cout << "ERROR";
				break;
		}
		std::cout << std::endl << "Press any key";
		_getch();
	}
	
}