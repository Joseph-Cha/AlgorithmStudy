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
	 
	// 데이터 보관 => 차후 key & value 값으로 나눠서 보관도 가능하다.
	int		key = {}; 
	Color	color = Color::Black;
};

// Red-Black Tree
// 1) 모든 노드는 Red or Black
// 2) Root는 Black
// 3) Leaf(NIL)는 Black
// 4) Red 노드의 자식은 Black (연속해서 Red-Red X)
// 5) 각 노드로부터 ~ 리프까지 가는 경로들은 모두 같은 수의 Black 노드를 만난다.
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void	Print() { Print(_root, 10, 0); }
	void	Print(Node* node, int x, int y);

	// 노드가 추가될 때 Search 기능 필요
	Node*	Search(Node* node, int key);
	Node*	Search2(Node* node, int key);

	// root를 주고 최소값, 최대값을 찾는 함수
	Node*	Min(Node* node);
	Node*	Max(Node* node);
	// 현재 노드 바로 다음 값 => 내 바로 다음으로 큰 값
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
	// 이렇게 더미 노드를 사용하면 nullptr 체크를 매번 해줄 필요가 없어진다.
	Node*	_nil = nullptr; 
};

