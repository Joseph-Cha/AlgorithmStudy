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
	// �����Ͱ� �߰� �Ǿ��� �� 
	// => ��𿡴ٰ� �����͸� �߰�������ϴ� ã�ƾ���
	// => �ϴ� root���� ����
	Node* node = _root;
	Node* parent = nullptr;

	// node�� nullptr�� �ƴ� ������
	while (node)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	// �� �ܰ迡�� ���������� ����� node�� parent�� �ȴ�.
	newNode->parent = parent;

	// ���� �θ� ���(���� �ϴܿ� �ִ� node) �������� ������������ ����
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

	// ��� left == null�� ��
	// ��� right�� null �Ǵ� !null�� ���� �ִ�.
	// �׷����� Replace ����ص� �Ǵ� ������ 
	// Replace���� null üũ�� ���ֱ� ����
	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	// ���ʿ� �ڽ� ��尡 ���� ���
	else
	{
		// ���� ������ ã�� 
		// => �ֳ��ϸ� �������� ū ������(Next Node)�� 
		// => ������ ����� ��ü�ڷ� ������ֱ� ���ؼ�
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// u ����Ʈ���� v ����Ʈ���� ��ü
// �׸��� delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	// ��ü ��� ��尡 root�� ���
	if (u->parent == nullptr)
		_root = v;

	// ��ü ����� ���(u)�� �ش� ��� �θ��� ������ ���
	// ��ü�� �� ���(v)�� u ����� �������� ����
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	// ��ü ����� ���(u)�� �ش� ��� �θ��� �������� ���
	// ��ü�� �� ���(v)�� u ����� ���������� ����
	else
	{
		u->parent->right = v;
	}

	// v ����� �θ���� u����� �θ������ ����
	if (v)
		v->parent = u->parent;

	delete u;
}

// � ������ ��ĵ�� �ϸ鼭 �����͸� ������� ����
// �ϴ� Root Node�� �־��ְ� ũ�� 3���� ��ȸ ����� ����

// 1) ���� ��ȸ (preorder traverse)
// 2) ���� ��ȸ (inorder)
// 3) ���� ��ȸ (postorder)

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
	//   [��]
	// [��] [��]
	// 1) ���� ��ȸ => ���� �տ� ��
	// 2) ���� ��ȸ => ���� �߰���
	// 3) ���� ��ȸ => ���� ������

	if (node == nullptr)
		return;

	// ����
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

// Ʈ���������� �����͸� ã�� ����
// Insert�� ���� ���� => ���� ������ Ÿ�� ���鼭
// ��� ���� �����͸� �־������� ã�� ������ �ʿ�
Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;
	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

// ����Լ��� ������� �ʴ� ����
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

// ���� ������ �� �� ������ �ʿ�.. 
// �������δ� ���ذ� �� �ȵ�
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

// ����Լ� ���� vs Non ����Լ�����
// �������� ����Լ��� ������ ���������δ� Non ����Լ� ������ ����.
// ����Լ��� ������� ������ static �������� �Ƴ� �� �ֱ� ����