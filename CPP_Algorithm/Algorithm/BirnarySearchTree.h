#pragma once

//     [10]
// [nil]  [20]
//			  [30]
struct Node
{
	Node*	parent = nullptr;
	Node*	left = nullptr;;
	Node*	right = nullptr;
	 
	// ������ ���� => ���� key & value ������ ������ ������ �����ϴ�.
	int		key = {}; 
};

class BinarySearchTree
{
public:
	void	Print() { Print(_root, 10, 0); }
	void	Print(Node* node, int x, int y);
	// root���� �����ָ� ���
	void	Print_Inorder() { Print_Inorder(_root); }
	void	Print_Inorder(Node* node);

	// ��尡 �߰��� �� Search ��� �ʿ�
	Node*	Search(Node* node, int key);
	Node*	Search2(Node* node, int key);

	// root�� �ְ� �ּҰ�, �ִ밪�� ã�� �Լ�
	Node*	Min(Node* node);
	Node*	Max(Node* node);
	// ���� ��� �ٷ� ���� �� => �� �ٷ� �������� ū ��
	Node*	Next(Node* node);

	void	Insert(int key);

	void	Delete(int key);
	void	Delete(Node* node);

	void	Replace(Node* u, Node* v);

private:
	Node*	_root = nullptr;
};

