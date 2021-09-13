#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
class Vector
{
public:
    Vector()
    {

    }
    ~Vector()
    {
        if (_data)
            delete[] _data;
    }

    // [ ] [ ] [ ] [ ] [ ] [ ]
    void push_back(const T& value)
    {
        // 실제 데이터 공간이 모두 찼다면
        if (_size == _capacity)
        {
            // 증설 작업
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
                newCapacity++;
            reserve(newCapacity);
        }

        // 메모리는 충분한 상황
        // 데이터 저장
        _data[_size] = value;

        // 데이터 갯수 증가
        _size++;
    }

    void reserve(int capacity)
    {
        if (_capacity >= capacity)
            return;

        _capacity = capacity;

        T* newData = new T[_capacity];

        // 데이터 복사
        for (int i = 0; i < _size; i++)
            newData[i] = _data[i];

        if (_data)
            delete[] _data;

        // 교체
        _data = newData;
    }

    // 데이터를 꺼내 쓰거나 고칠 때 사용
    T& operator[](const int pos) { return _data[pos]; }

    int size() { return _size; }
    int capacity() { return _capacity; }

    void clear()
    {
        if (_data)
        {
            delete[] _data;
            _data = new T[_capacity];
        }
        _size = 0;
    }

private:
    T* _data = nullptr;
    int     _size = 0;
    int     _capacity = 0;
};

template<typename T>
class Node
{
public:
    Node() : _prev(nullptr), _next(nullptr), _data(T())
    {

    }
    Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
    {

    }
public:
    Node* _prev;
    Node* _next;
    T       _data;
};

template<typename T>
class Iterator
{
public:
    Iterator() : _node(nullptr)
    {

    }

    // 어떤 특정 노드와 연동을 시켰을 때
    Iterator(Node<T>* node) : _node(node)
    {

    }

    // ++it
    Iterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    // it++
    Iterator& operator++(int)
    {
        Iterator<T> temp = *this;
        _node = _node->_next;
        return temp;
    }

    // --it
    Iterator& operator--()
    {
        _node = _node->_prev;
        return *this;
    }


    // it--
    Iterator& operator--(int)
    {
        Iterator<T> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    // *il
    T& operator*()
    {
        return _node->_data;
    }

    bool operator==(const Iterator& other)
    {
        return _node == other._node;
    }

    bool operator!=(const Iterator& other)
    {
        return _node != other._node;
    }
public:
    Node<T>* _node;
};


// 양반향 단반향?
// 앞뒤로 연결 => 양반향 리스트
template<typename T>
class List
{
public:
    List() : _size(0)
    {
        // [head] <-> ... <-> [tail]
        _haed = new Node<T>();
        _tail = new Node<T>();
        // 기본 node 값으로 양옆으로 연결
        // => 이렇게 하면 null 체크를 매번 하지 않아도 된다.
        _head->_next = _tail;
        _tail->_prev = _head;
    }
    ~List()
    {
        while (_size > 0)
            pop_back();
        delete _head;
        delete _tail;
    }

    void push_back(const T& value)
    {
        AddNode(_tail, value);
    }

    void pop_back()
    {
        RemoveNode(_tail->_prev);
    }

private:
    // [head] <-> [1] <-> [preNode] <-> [before] <-> [tail]                 => before
    // [head] <-> [1] <-> [preNode] <-> [newNode] <-> [before] <-> [tail]   => after
    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        // 여기서 before가 head라고 할지라도 로직에는 상관이 없다.
        // 더미 node가 없었다면 이 상황에서 null체크를 했어야 했다.
        Node<T>* prevNode = before->_prev;

        prevNode->_next = newNode;
        newNode->_prev = prevNode;

        newNode->_next = before;
        before->_prev = newNode;

        _size++;

        return newNode;
    }

    // [head] <-> [preNode] <-> [node] <-> [nextNode] <-> [tail]    // before
    // [head] <-> [preNode] <-> [nextNode] <-> [tail]               // after
    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;

        delete node;
        _size--;
        return nextNode;
    }

    int size() { return _size; }
public:
    using iterator = Iterator<T>;

    iterator begin() { return iterator(_head->_next); }
    iterator end() { return iterator(_tail); }

    // it : 추가할 위치, 바로 앞에다가 추가
    // it 다음이 아니라 it 이전에 값을 추가함 => 혼돈 주의
    iterator insert(iterator it, const T& value)
    {
        Node<T>* node = AddNode(it._node, value);
        return iterator(node);
    }

    iterator erase(iterator it)
    {
        Node<T>* node = RemoveNode(it._node);
        return iterator(node);
    }
private:
    Node<T>* _head;
    Node<T>* _tail;
    int         _size;
};



int main()
{
    List<int> li;
    List<int>::iterator eraselt;
    // [ ] <-> [ ] <-> [ ]
    for (int i = 0; i < 10; i++)
    {
        // vector에는 없는 기능 => front 기능이 느리기 때문에 굳이 제공 x
        //li.push_front(i);
        if (i == 5)
            eraselt = li.insert(li.end(), i);
        else
        {
            li.push_back(i);
        }
    }
    li.pop_back();
    // 중간 산입 삭제
    li.erase(eraselt);

    // 임의 접근이 막히기 때문에 이렇게는 작동 x
    //li[3] = 3;
    for (List<int>::iterator it = li.begin(); it != li.end(); it++)
    {
        cout << (*it) << endl;
    }
}