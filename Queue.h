#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "Container.h"
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class QueueIterator;

template <typename T>
class Queue : public Container<T>
{
    const static string type;
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T _data, Node*_next = NULL)
        {
            data = _data;
            next = _next;
        }
    };


    Node* head;
    Node* tail;
    int size;
    void copy(const Queue& other)
    {
        Node* otherIterator = other.head;
        while (otherIterator != NULL)
        {
            enqueue(otherIterator->data);
            otherIterator = otherIterator->next;
        }
    }

    void clear()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    friend class QueueIterator<T>;
public:

    Queue()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    Queue(const Queue& other): head(NULL), tail(NULL)
    {
        size = 0;
        copy(other);
    }

    Queue& operator=(const Queue& other)
    {
        if (this != &other)
        {
            clear();
            copy(other);
        }

        return *this;
    }

    bool operator==(const Queue& other)
    {
        if(size != other.size)
        {
            return false;
        }
        Node* tmpPtr = head;
        Node* tmpOtherPtr = other.head;
        while(tmpPtr != NULL && tmpOtherPtr != NULL)
        {
            if(tmpPtr->data != tmpOtherPtr->data)
            {
                return false;
            }
            tmpPtr = tmpPtr->next;
            tmpOtherPtr = tmpOtherPtr->next;
        }
        return true;
    }

    ~Queue()
    {
    }

    bool isEmpty() const
    {
        return head == NULL;
    }

    const T& getHead() const
    {
        return head->data;
    }

    void enqueue(const T& data)
    {
        if (isEmpty())
        {
            tail = new Node(data, NULL);
            head = tail;
        }
        else
        {
            tail->next = new Node(data, NULL);
            tail = tail->next;
        }
        size++;
    }

    void dequeue()
    {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;

        if (isEmpty())
        {
            tail = NULL;
        }
        if(size > 0)
        {
            size--;
        }
    }


    virtual Iterator<T>* getIterator() const
    {
        return new QueueIterator<T>(*this);
    }

    virtual bool member(const T& other) const
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            if(tmpPtr->data == other)
            {
                return true;
            }
            tmpPtr = tmpPtr->next;
        }
        return false;
    }

    virtual void display() const
    {
        Node* tmpPtr = head;
        if(tmpPtr != NULL)
        {
            cout<<type << " ";
        }

        while(tmpPtr != NULL)
        {
            std::cout<< tmpPtr->data << " ";
            tmpPtr = tmpPtr->next;
        }
        std::cout<<'\n';
    }

    virtual void add(const T& element)
    {
        enqueue(element);
    }

    virtual int getSize() const
    {
        return size;
    }

    virtual void sort()
    {
        priority_queue<T, vector<T>, greater<T>> queue;
        while(!isEmpty())
        {
            queue.push(getHead());
            dequeue();
        }
        while(!queue.empty())
        {
            enqueue(queue.top());
            queue.pop();
        }
    }

    virtual bool member(Condition<T> condition) const
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            if(condition(tmpPtr->data))
            {
                return true;
            }
            tmpPtr = tmpPtr->next;
        }
        return false;
    }

    virtual void filter(Condition<T> condition)
    {
        Node* tmpPtr = head;
        Queue<T>* newQueue = new Queue<T>;
        while(!isEmpty())
        {
            T _data = head->data;
            if(!condition(_data))
            {
                newQueue->enqueue(_data);
            }
            dequeue();
        }
        head = newQueue->head;
        tail = newQueue->tail;
        size = newQueue->size;
    }

    virtual void saveToFile(ofstream& os) const
    {
        os<<*this;
    }

    friend ostream& operator<<(ostream& os, const Queue& queue)
    {
        Node* tmpPtr = queue.head;
        os << type << " ";
        while(tmpPtr != NULL)
        {
            os << tmpPtr->data << " ";
            tmpPtr = tmpPtr->next;
        }
        return os;
    }

    virtual void loadFromFile(list<string> numbers)
    {
        while(!numbers.empty())
        {
            enqueue(atoi(numbers.front().c_str()));
            numbers.pop_front();
        }
    }
};

template<typename T>
const string Queue<T>::type = "Queue";

#endif // QUEUE_H_INCLUDED
