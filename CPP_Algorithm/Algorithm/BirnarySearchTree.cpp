#include "BirnarySearchTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}
	// 데이터가 추가 되었을 때 
	// => 어디에다가 데이터를 추가해줘야하는 찾아야함
	// => 일단 root부터 시작
	Node* node = _root;
	Node* parent = nullptr;

	// node가 nullptr이 아닐 때까지
	while (node)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	// 위 단계에서 마지막으로 검출된 node가 parent가 된다.
	newNode->parent = parent;

	// 현재 부모를 대상(가장 하단에 있는 node) 왼쪽인지 오른쪽인지를 결정
	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	// 노드 left == null일 때
	// 노드 right가 null 또는 !null일 수가 있다.
	// 그럼에도 Replace 사용해도 되는 이유는 
	// Replace에서 null 체크를 해주기 때문
	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	// 양쪽에 자식 노드가 있을 경우
	else
	{
		// 다음 데이터 찾기 
		// => 왜냐하면 다음으로 큰 데이터(Next Node)를 
		// => 제거한 노드의 대체자로 만들어주기 위해서
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// u 서브트리를 v 서브트리로 교체
// 그리고 delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	// 교체 대상 노드가 root일 경우
	if (u->parent == nullptr)
		_root = v;

	// 교체 대상의 노드(u)가 해당 노드 부모의 왼쪽일 경우
	// 교체를 할 노드(v)를 u 노드의 왼쪽으로 연결
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	// 교체 대상의 노드(u)가 해당 노드 부모의 오른쪽일 경우
	// 교체를 할 노드(v)를 u 노드의 오른쪽으로 연결
	else
	{
		u->parent->right = v;
	}

	// v 노드의 부모님을 u노드의 부모님으로 변경
	if (v)
		v->parent = u->parent;

	delete u;
}

// 어떤 식으로 스캔을 하면서 데이터를 출력할지 결정
// 일단 Root Node를 넣어주고 크게 3가지 순회 방법이 있음

// 1) 전위 순회 (preorder traverse)
// 2) 중위 순회 (inorder)
// 3) 후위 순회 (postorder)

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
		return;

	SetCursorPosition(x, y);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	//   [중]
	// [좌] [우]
	// 1) 전위 순회 => 중이 앞에 옴
	// 2) 중위 순회 => 중이 중간에
	// 3) 후위 순회 => 중이 마지막

	if (node == nullptr)
		return;

	// 전위
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

// 트리구조에서 데이터를 찾는 역할
// Insert와 거의 유사 => 왼쪽 오른쪽 타고 가면서
// 어느 곳에 데이터를 넣어줄지를 찾는 과정이 필요
Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;
	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

// 재귀함수를 사용하지 않는 버전
Node* BinarySearchTree::Search2(Node* node, int key)
{
	while (node && key != node->key)
	{
		if (key > node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left)
		node = node->left;
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right)
		node = node->right;
	return node;
}

// 여기 로직은 좀 더 연구가 필요.. 
// 설명으로는 이해가 잘 안됨
Node* BinarySearchTree::Next(Node* node)
{
	if (node->right)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}
	return nullptr;
}

// 재귀함수 버전 vs Non 재귀함수버전
// 가독성은 재귀함수가 좋지만 성능적으로는 Non 재귀함수 버전이 좋다.
// 재귀함수를 사용하지 않으면 static 프레임을 아낄 수 있기 때문