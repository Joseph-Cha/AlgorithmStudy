#pragma once

//     [10]
// [nil]  [20]
//			  [30]
struct Node
{
	Node*	parent = nullptr;
	Node*	left = nullptr;;
	Node*	right = nullptr;
	 
	// 데이터 보관 => 차후 key & value 값으로 나눠서 보관도 가능하다.
	int		key = {}; 
};

class BinarySearchTree
{
public:
	void	Print() { Print(_root, 10, 0); }
	void	Print(Node* node, int x, int y);
	// root값을 전내주며 출력
	void	Print_Inorder() { Print_Inorder(_root); }
	void	Print_Inorder(Node* node);

	// 노드가 추가될 때 Search 기능 필요
	Node*	Search(Node* node, int key);
	Node*	Search2(Node* node, int key);

	// root를 주고 최소값, 최대값을 찾는 함수
	Node*	Min(Node* node);
	Node*	Max(Node* node);
	// 현재 노드 바로 다음 값 => 내 바로 다음으로 큰 값
	Node*	Next(Node* node);

	void	Insert(int key);

	void	Delete(int key);
	void	Delete(Node* node);

	void	Replace(Node* u, Node* v);

private:
	Node*	_root = nullptr;
};

