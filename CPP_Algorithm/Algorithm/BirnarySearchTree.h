#pragma once

//     [10]
// [nil]  [20]
//			  [30]

enum class Color
{
	Red = 0,
	Black = 1,
};
struct Node
{
	Node*	parent = nullptr;
	Node*	left = nullptr;;
	Node*	right = nullptr;
	 
	// ������ ���� => ���� key & value ������ ������ ������ �����ϴ�.
	int		key = {}; 
	Color	color = Color::Black;
};

// Red-Black Tree
// 1) ��� ���� Red or Black
// 2) Root�� Black
// 3) Leaf(NIL)�� Black
// 4) Red ����� �ڽ��� Black (�����ؼ� Red-Red X)
// 5) �� ���κ��� ~ �������� ���� ��ε��� ��� ���� ���� Black ��带 ������.
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void	Print() { Print(_root, 10, 0); }
	void	Print(Node* node, int x, int y);

	// ��尡 �߰��� �� Search ��� �ʿ�
	Node*	Search(Node* node, int key);
	Node*	Search2(Node* node, int key);

	// root�� �ְ� �ּҰ�, �ִ밪�� ã�� �Լ�
	Node*	Min(Node* node);
	Node*	Max(Node* node);
	// ���� ��� �ٷ� ���� �� => �� �ٷ� �������� ū ��
	Node*	Next(Node* node);

	void	Insert(int key);
	void	InsertFixup(Node* node);

	void	Delete(int key);
	void	Delete(Node* node);
	void	Replace(Node* u, Node* v);

	// Red-Black Tree
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

private:
	Node*	_root = nullptr;
	// �̷��� ���� ��带 ����ϸ� nullptr üũ�� �Ź� ���� �ʿ䰡 ��������.
	Node*	_nil = nullptr; 
};

