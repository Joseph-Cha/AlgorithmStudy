#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "BinarySearchTree.h"
using namespace std;
#include <thread>

//     [20]
// [10]      [30]
//         [25] [40]
//		     [26] [50]

int main()
{
	BinarySearchTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(40);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(50);
	bst.Print();
	this_thread::sleep_for(1s);
}