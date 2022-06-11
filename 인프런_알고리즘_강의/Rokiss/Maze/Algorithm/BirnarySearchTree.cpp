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
    // ������ leaf Node�� ���� nullptr�� ����ϴ� ���� �ƴ϶�
    // nil Node�� ����� ����
    _nil = new Node(); // Black
    _root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
    delete _nil;
}

// � ������ ��ĵ�� �ϸ鼭 �����͸� ������� ����
// �ϴ� Root Node�� �־��ְ� ũ�� 3���� ��ȸ ����� ����

// 1) ���� ��ȸ (preorder traverse)
// 2) ���� ��ȸ (inorder)
// 3) ���� ��ȸ (postorder)

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

    // ���� ������ ���ؼ�
    SetCursorColor(ConsoleColor::WHITE);
}

// Ʈ���������� �����͸� ã�� ����
// Insert�� ���� ���� => ���� ������ Ÿ�� ���鼭
// ��� ���� �����͸� �־������� ã�� ������ �ʿ�
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

// ���� ������ �� �� ������ �ʿ�.. 
// �������δ� ���ذ� �� �ȵ�
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

// ����Լ� ���� vs Non ����Լ�����
// �������� ����Լ��� ������ ���������δ� Non ����Լ� ������ ����.
// ����Լ��� ������� ������ static �������� �Ƴ� �� �ֱ� ����

void BinarySearchTree::Insert(int key)
{
    Node* newNode = new Node();
    newNode->key = key;

    // �����Ͱ� �߰� �Ǿ��� �� 
    // => ��𿡴ٰ� �����͸� �߰�������ϴ� ã�ƾ���
    // => �ϴ� root���� ����
    Node* node = _root;
    Node* parent = _nil;

    // node�� nullptr�� �ƴ� ������
    while (node != _nil)
    {
        parent = node;
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    // �� �ܰ迡�� ���������� ����� node�� parent�� �ȴ�.
    newNode->parent = parent;

    if (parent == _nil)
        _root = newNode;
    // ���� �θ� ���(���� �ϴܿ� �ִ� node) �������� ������������ ����
    else if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Todo �ش� ��尡 ����� Ʈ�� Ư���� �������� üũ
    newNode->left = _nil;
    newNode->right = _nil;
    newNode->color = Color::Red;

    InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
    // ũ�� 3���� ������ ����
    // uncle => �θ��� ����
    // 1) parent = Red, uncle = Red 
    //  -> p = black, uncle = black, pp = red�� �ٲ�
    // 2) parent = Red, uncle = Black(triangle)
    //  -> ȸ���� ���� case 3���� �ٲ�
    // 3) parent = Red, uncle = Black(list)
    //  -> ���� ���� + ȸ��

    //     [pp(B)]
    // [p(R)]    [u(?)]
    //       [n(R)]

    // ����� �θ� Red��� 
    while (node->parent->color == Color::Red)
    {
        // ���� ����� �θ� ������ ��������
        if (node->parent == node->parent->parent->left)
        {
            Node* uncle = node->parent->parent->right;
            //     [pp(B)]
            // [p(R)]    [u(R)]
            //       [n(R)]
            if (uncle->color == Color::Red)
            {
                // ����� �θ�� ������ Black����
                // ����� ������ Red�� ��ü
                node->parent->color = Color::Black; // p
                uncle->color = Color::Black; // u
                node->parent->parent->color = Color::Red; // pp

                // ������ �θ� Red�� ��쿡 ���
                // �̷��� ���� ��带 ����� �������� �ٲ��ָ�
                // while�� �ȿ��� ��� ���鼭 �� ������ �ݺ�����
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
                 
                // �Ʒ��� ���� triangle�� list�� ������Ѵ�
                //      [pp(B)]
                //      [n(R)] [u(B)]
                // [p(R)]

                // triangle Ÿ��
                if (node == node->parent->right)
                {
                    node = node->parent;
                    LeftRotate(node);
                    // 3�� case
                    //      [pp(B)]
                    //      [p(R)] [u(B)]
                    // [n(R)]
                }

                // ������� ���� �Ǹ� �Ʒ� list Ÿ���� �ȴ�.
                //      [pp(B)]
                //   [p(R)]     [u(B)]
                // [n(R)]

                // Į�� ����
                //      [pp(R)]
                //   [p(B)]     [u(B)]
                // [n(R)]

                // RightRotate
                //      [p(B)]
                //   [n(R)]  [pp(B)]
                //                  [u(B)]    

                // ��m�ϸ� R -> R�� ���޾� ������ ��Ȳ�� �ٲٱ� ���ؼ�
                // ������ �����ϰ� RigthRotate�� �ؼ� R�� �翷���� �����ϰ� �� ����
                node->parent->color = Color::Black;
                node->parent->parent->color = Color::Red;
                RightRotate(node->parent->parent);
            }
        }
        // ���� ����� �θ� ������ ����������
        else
        {
            //     [pp(B)]
            // [u(B)]   [p(R)]    
            //                [n(R)]
            Node* uncle = node->parent->parent->left;

            //     [pp(R)]
            // [u(B)]   [p(B)]    
            //                [n(R)]
            if (uncle->color == Color::Red)
            {
                // ����� �θ�� ������ Black����
                // ����� ������ Red�� ��ü
                node->parent->color = Color::Black; // p
                uncle->color = Color::Black; // u
                node->parent->parent->color = Color::Red; // pp

                // ������ �θ� Red�� ��쿡 ���
                // �̷��� ���� ��带 ����� �������� �ٲ��ָ�
                // while�� �ȿ��� ��� ���鼭 �� ������ �ݺ�����
                node = node->parent->parent;
            }
            else
            {
                // triangle
                //     [pp(B)]
                // [u(B)]   [p(R)]    
                //         [n(R)] 

                // �Ʒ��� ���� triangle�� list�� ������Ѵ�
                //       [pp(B)]
                //       [u(B)]  [p(R)]
                //                 [n(R)]
                 
                // Triangle Ÿ��
                if (node == node->parent->left) 
                {
                    node = node->parent;
                    RightRotate(node);
                }

                // ������� ���� �Ǹ� �Ʒ� list Ÿ���� �ȴ�.
                //       [pp(B)]
                //       [u(B)]  [p(R)]
                //                 [n(R)]

                // Į�� ����
                //       [pp(R)]
                //       [u(B)]  [p(B)]
                //                 [n(R)]

                // RightRotate
                //         [p(B)]
                //    [pp(B)]  [n(R)]  
                //     [u(B)]                     

                // ����ϸ� R -> R�� ���޾� ������ ��Ȳ�� �ٲٱ� ���ؼ�
                // ������ �����ϰ� RigthRotate�� �ؼ� R�� �翷���� �����ϰ� �� ����

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
        u->parent->left = v;

    // ��ü ����� ���(u)�� �ش� ��� �θ��� �������� ���
    // ��ü�� �� ���(v)�� u ����� ���������� ����
    else
        u->parent->right = v;

    // v ����� �θ���� u����� �θ������ ����
    if (v)
        v->parent = u->parent;

    delete u;
}

// 1�� ��Ȳ
//       [p]
//     [y]
//   [x]  [3]
// [1] [2]

// 2�� ��Ȳ
//       [p]
//     [x]
//  [1]   [y]
//        [2] [3]

// 1�� -> 2�� : RightRotate
// 2�� -> 1�� : LeftRotate

void BinarySearchTree::LeftRotate(Node* x)
{
    Node* y = x->right;

    x->right = y->left; // [2];

    if (y->left != _nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == _nil)
        _root = y;
    // x�� �θ��� ���ʿ� �ִٸ�
    else if (x == x->parent->left)
        // �θ��� ������ y�� ����
        x->parent->left = y;
    // x�� �θ��� �����ʿ� �ִٸ�
    else
        // �θ��� �������� y�� ����
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
