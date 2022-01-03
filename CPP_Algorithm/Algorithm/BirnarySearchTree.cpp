#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

BinarySearchTree::BinarySearchTree()
{
	// 앞으로 leaf Node의 경우는 nullptr을 사용하는 것이 아니라
	// nil Node를 사용할 예정
	_nil = new Node(); // Black
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

// 어떤 식으로 스캔을 하면서 데이터를 출력할지 결정
// 일단 Root Node를 넣어주고 크게 3가지 순회 방법이 있음

// 1) 전위 순회 (preorder traverse)
// 2) 중위 순회 (inorder)
// 3) 후위 순회 (postorder)

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
		return;

	SetCursorPosition(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	// 원상 복구를 위해서
	SetCursorColor(ConsoleColor::WHITE);
}

// 트리구조에서 데이터를 찾는 역할
// Insert와 거의 유사 => 왼쪽 오른쪽 타고 가면서
// 어느 곳에 데이터를 넣어줄지를 찾는 과정이 필요
Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == _nil || key == node->key)
		return node;

	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left != _nil)
		node = node->left;

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right != _nil)
		node = node->right;

	return node;
}

// 여기 로직은 좀 더 연구가 필요.. 
// 설명으로는 이해가 잘 안됨
Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != _nil)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

// 재귀함수 버전 vs Non 재귀함수버전
// 가독성은 재귀함수가 좋지만 성능적으로는 Non 재귀함수 버전이 좋다.
// 재귀함수를 사용하지 않으면 static 프레임을 아낄 수 있기 때문

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	// 데이터가 추가 되었을 때 
	// => 어디에다가 데이터를 추가해줘야하는 찾아야함
	// => 일단 root부터 시작
	Node* node = _root;
	Node* parent = _nil;

	// node가 nullptr이 아닐 때까지
	while (node != _nil)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	// 위 단계에서 마지막으로 검출된 node가 parent가 된다.
	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;
	// 현재 부모를 대상(가장 하단에 있는 node) 왼쪽인지 오른쪽인지를 결정
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	// Todo 해당 노드가 레드블랙 트리 특성에 부합한지 체크
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
	// 크게 3가지 유형이 있음
	// uncle => 부모의 형제
	// 1) parent = Red, uncle = Red 
	//  -> p = black, uncle = black, pp = red로 바꿈
	// 2) parent = Red, uncle = Black(triangle)
	//  -> 회전을 통해 case 3으로 바꿈
	// 3) parent = Red, uncle = Black(list)
	//  -> 색상 변경 + 회전

	//     [pp(B)]
	// [p(R)]	[u(?)]
	//	   [n(R)]

	// 노드의 부모가 Red라면 
	while (node->parent->color == Color::Red)
	{
		// 현재 노드의 부모가 조상의 왼쪽인지
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			//     [pp(B)]
			// [p(R)]	[u(R)]
			//	   [n(R)]
			if (uncle->color == Color::Red)
			{
				// 노드의 부모와 삼촌은 Black으로
				// 노드의 조상은 Red로 교체
				node->parent->color = Color::Black; // p
				uncle->color = Color::Black; // u
				node->parent->parent->color = Color::Red; // pp

				// 조상의 부모가 Red일 경우에 대비
				// 이렇게 현재 노드를 노드의 조상으로 바꿔주면
				// while문 안에서 계속 돌면서 위 과정을 반복해줌
				node = node->parent->parent;
			}
			else
			{
				//       [pp(B)]
				//   [p(R)]     [u(B)]
				//      [n(R)]

				//        [pp(B)]
				//      [p(R)]  [u(B)]
				//   [n(R)]   
				 
				// 아래와 같이 triangle을 list로 펴줘야한다
				//      [pp(B)]
				// 	 [n(R)] [u(B)]
				// [p(R)]

				// triangle 타입
				if (node == node->parent->right)
				{
					node = node->parent;
					LeftRotate(node);
					// 3번 case
					//      [pp(B)]
					// 	 [p(R)] [u(B)]
					// [n(R)]
				}

				// 여기까지 오게 되면 아래 list 타입이 된다.
				//      [pp(B)]
				//   [p(R)]	 [u(B)]
				// [n(R)]

				// 칼라 변경
				//      [pp(R)]
				//   [p(B)]	 [u(B)]
				// [n(R)]

				// RightRotate
				//      [p(B)]
				//   [n(R)]  [pp(B)]
				// 		         [u(B)]	

				// 요챡하면 R -> R가 연달아 나오는 상황을 바꾸기 위해서
				// 색상을 변경하고 RigthRotate을 해서 R가 양옆으로 존재하게 끔 변경
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		// 현재 노드의 부모가 조상의 오른쪽인지
		else
		{
			//     [pp(B)]
			// [u(B)]   [p(R)]	
			//				[n(R)]
			Node* uncle = node->parent->parent->left;

			//     [pp(R)]
			// [u(B)]   [p(B)]	
			//				[n(R)]
			if (uncle->color == Color::Red)
			{
				// 노드의 부모와 삼촌은 Black으로
				// 노드의 조상은 Red로 교체
				node->parent->color = Color::Black; // p
				uncle->color = Color::Black; // u
				node->parent->parent->color = Color::Red; // pp

				// 조상의 부모가 Red일 경우에 대비
				// 이렇게 현재 노드를 노드의 조상으로 바꿔주면
				// while문 안에서 계속 돌면서 위 과정을 반복해줌
				node = node->parent->parent;
			}
			else
			{
				// triangle
				//     [pp(B)]
				// [u(B)]   [p(R)]	
				//		 [n(R)] 

				// 아래와 같이 triangle을 list로 펴줘야한다
				//       [pp(B)]
				// 	  [u(B)]  [p(R)]
				//				 [n(R)]
				 
				// Triangle 타입
				if (node == node->parent->left) 
				{
					node = node->parent;
					RightRotate(node);
				}

				// 여기까지 오게 되면 아래 list 타입이 된다.
				//       [pp(B)]
				// 	  [u(B)]  [p(R)]
				//				 [n(R)]

				// 칼라 변경
				//       [pp(R)]
				// 	  [u(B)]  [p(B)]
				//				 [n(R)]

				// RightRotate
				//         [p(B)]
				//    [pp(B)]  [n(R)]  
				// 	[u(B)]		         	

				// 요약하면 R -> R가 연달아 나오는 상황을 바꾸기 위해서
				// 색상을 변경하고 RigthRotate을 해서 R가 양옆으로 존재하게 끔 변경

				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}

	_root->color = Color::Black;
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
		u->parent->left = v;

	// 교체 대상의 노드(u)가 해당 노드 부모의 오른쪽일 경우
	// 교체를 할 노드(v)를 u 노드의 오른쪽으로 연결
	else
		u->parent->right = v;

	// v 노드의 부모님을 u노드의 부모님으로 변경
	if (v)
		v->parent = u->parent;

	delete u;
}

// 1번 상황
//       [p]
//     [y]
//   [x]  [3]
// [1] [2]

// 2번 상황
//       [p]
//     [x]
//  [1]   [y]
//	    [2] [3]

// 1번 -> 2번 : RightRotate
// 2번 -> 1번 : LeftRotate

void BinarySearchTree::LeftRotate(Node* x)
{
	Node* y = x->right;

	x->right = y->left; // [2];

	if (y->left != _nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == _nil)
		_root = y;
	// x가 부모의 왼쪽에 있다면
	else if (x == x->parent->left)
		// 부모의 왼쪽을 y로 변경
		x->parent->left = y;
	// x가 부모의 오른쪽에 있다면
	else
		// 부모의 오른쪽을 y로 변경
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

//     [y]
//  [x]   [3]
// [1][2]

//    [x]  
// [1]   [y]
//      [2][3]

void BinarySearchTree::RightRotate(Node* y)
{
	Node* x = y->left;

	y->left = x->right; // [2];

	if (x->right != _nil)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == _nil)
		_root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}
