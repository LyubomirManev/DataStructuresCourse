#ifndef DOUBLYLINKEDLIST_H_INCLUDED
#define DOUBLYLINKEDLIST_H_INCLUDED
#include "Container.h"
#include <iostream>
#include <fstream>
using std::priority_queue;
using std::cout;

template <typename T>
class DoublyLinkedListIterator;

template <typename T>
class DoublyLinkedList : public Container<T>
{
    const static string type;
    class Node
    {
    public:
        T data;
        Node *previous;
        Node *next;


        Node()
        {
            previous = NULL;
            next = NULL;
        }

    };

    Node *front;
    Node *back;
    int size;

    void copy(const DoublyLinkedList& other)
    {
        Node* frontPtr = other.front;
        while(frontPtr != NULL)
        {
            insertAtBack(frontPtr->data);
            frontPtr = frontPtr->previous;
        }

    }

    void clear()
    {
        while(front != back)
        {
            deleteAtBack();
        }
    }

    friend class DoublyLinkedListIterator<T>;
public:

    virtual Iterator<T>* getIterator() const
    {
        return new DoublyLinkedListIterator<T>(*this);
    }

    DoublyLinkedList()
    {
        size = 0;
        front = NULL;
        back = NULL;
    }

    ~DoublyLinkedList()
    {
    }

    DoublyLinkedList(const DoublyLinkedList& other)
    {
        front = NULL;
        back = NULL;
        size = 0;
        copy(other);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            copy(other);
        }

        return *this;
    }

    bool operator==(const DoublyLinkedList& other)
    {
        if(size != other.size)
        {
            return false;
        }
        Node* tmpPtr = front;
        Node* tmpOtherPtr = other.front;
        while(tmpPtr != NULL && tmpOtherPtr != NULL)
        {
            if(tmpPtr->data != tmpOtherPtr->data)
            {
                return false;
            }
            tmpPtr = tmpPtr->previous;
            tmpOtherPtr = tmpOtherPtr->previous;
        }
        return true;
    }

    T& getFront()const
    {
        return front->data;
    }

    T& getBack()const
    {
        return back->data;
    }

    bool isEmpty() const
    {
        return (front==NULL && back==NULL);
    }

    void insertAtFront(T _data)
    {
        size++;
        Node *newNode = new Node;
        newNode->data = _data;

        if(isEmpty())
        {
            front = back = newNode;
            return;
        }
        front->next = newNode;
        newNode->previous = front;
        front = newNode;
    }

    void insertAtBack(const T& _data)
    {
        size++;
        Node *newNode = new Node;
        newNode->data = _data;

        if(isEmpty())
        {
            front = back = newNode;
            return;
        }

        back->previous = newNode;
        newNode->next = back;
        back = newNode;

    }

    void deleteAtBack()
    {
        if(back == NULL)
        {
            return;
        }
        if(front == back)
        {
            front = NULL;
            delete back;
            back = NULL;
            size--;
            return;
        }
        Node *tmpPtr = back;
        back = back->next;
        back->previous = NULL;
        delete tmpPtr;
        size--;
    }

    void deleteAtFront()
    {
        if(front == NULL)
        {
            return;
        }
        if(front == back)
        {
            front = NULL;
            delete back;
            back = NULL;
            size--;
            return;
        }
        Node *tmpPtr = front;
        front = front->previous;
        front->next = NULL;
        delete tmpPtr;
        size--;
    }


    virtual bool member(const T& _data) const
    {
        Node *tmpPtr = front;
        while(tmpPtr != NULL)
        {
            if(tmpPtr->data == _data)
            {
                return true;
            }
            tmpPtr = tmpPtr->next;
        }
        return false;
    }

    virtual void display() const
    {
        Node *tmpPtr = front;

        if(tmpPtr != NULL)
        {
            cout << type << " ";
        }
        while(tmpPtr != NULL)
        {
            cout<<tmpPtr->data << " ";
            tmpPtr = tmpPtr->previous;
        }
        cout<<'\n';
    }

    virtual void add(const T& element)
    {
        insertAtBack(element);
    }

    virtual int getSize() const
    {
        return size;
    }

    virtual void sort()
    {
        priority_queue<T,vector<T>, greater<T>> queue;
        while(!isEmpty())
        {
            queue.push(this->getFront());
            deleteAtFront();
        }
        while(!queue.empty())
        {
            insertAtBack(queue.top());
            queue.pop();
        }
    }

    virtual bool member(Condition<T> condition) const
    {
        Node* tmpPtr = front;
        while(tmpPtr != NULL)
        {
            if(condition(tmpPtr->data))
            {
                return true;
            }
            tmpPtr = tmpPtr->previous;
        }
        return false;
    }

    virtual void filter(Condition<T> condition)
    {
        DoublyLinkedList<T>* newDoublyLinkedList = new DoublyLinkedList<T>;
        Node* tmpPtr = front;
        while(tmpPtr != NULL)
        {
            T _data = tmpPtr->data;
            if(!condition(_data))
            {
                newDoublyLinkedList->insertAtBack(_data);
            }
            Node* nodeToDelete = tmpPtr;
            tmpPtr = tmpPtr->previous;
            delete nodeToDelete;
        }
        this->front = newDoublyLinkedList->front;
        this->back = newDoublyLinkedList->back;
        size = newDoublyLinkedList->size;
    }

    virtual void saveToFile(ofstream& os) const
    {
        os<<*this;

    }

    friend ostream& operator<<(ostream& os, const DoublyLinkedList& doublyLinkedList)
    {
        Node* tmpPtr = doublyLinkedList.front;
        os << type << " ";
        while(tmpPtr != NULL)
        {
            os << tmpPtr->data << " ";
            tmpPtr = tmpPtr->previous;
        }
        return os;
    }

    virtual void loadFromFile(list<string> numbers)
    {
        while(!numbers.empty())
        {
            insertAtBack(atoi(numbers.front().c_str()));
            numbers.pop_front();
        }
    }
};
template<typename T>
const string DoublyLinkedList<T>::type = "DoublyLinkedList";
#endif // DOUBLYLINKEDLIST_H_INCLUDED
