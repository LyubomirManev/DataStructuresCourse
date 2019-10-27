#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "Container.h"
#include <stdlib.h>
#include <fstream>
#include <queue>

using std::priority_queue;

template<typename T>
class StackIterator;


template <typename T>
class Stack : public Container<T>
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

    Node *top;
    int size;

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void copy(const Stack& other)
    {
        size = other.size;
        if (other.top == NULL)
            top = NULL;
        else
        {
            Node *tmpOther = other.top;
            Node *tmp = new Node(tmpOther->data);
            top = tmp;
            tmpOther = tmpOther->next;
            while (tmpOther != NULL)
            {
                tmp->next = new Node(tmpOther->data);
                tmp = tmp->next;
                tmpOther = tmpOther->next;
            }
        }
    }
    friend class StackIterator<T>;

public:

    virtual Iterator<T>* getIterator() const
    {
        return new StackIterator<T>(*this);
    }

    Stack()
    {
        top = NULL;
        size = 0;
    }

    Stack(const Stack& other)
    {
        copy(other);
    }

    Stack& operator=(const Stack& other)
    {
        if (this != &other)
        {
            clear();
            copy(other);
        }

        return *this;
    }

    bool operator==(const Stack& other)
    {
        if(size != other.size)
        {
            return false;
        }
        Node* tmpPtr = top;
        Node* tmpOtherPtr = other.top;
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

    ~Stack()
    {
    }

    bool isEmpty() const
    {
        return top == NULL;
    }

    const T& getTop() const
    {
        return top->data;
    }

    void push(const T element)
    {
        top = new Node(element, top);
        size++;
    }

    void pop()
    {
        Node *toDel = top;
        top = top->next;
        delete toDel;
        size--;
    }

    virtual bool member(const T& other) const
    {
        Node* tmpPtr = top;
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
        Node *tmpPtr = top;
        if(tmpPtr != NULL)
        {
            cout<<type << " ";
        }
        while (tmpPtr != NULL)
        {
            std::cout << tmpPtr->data << " ";
            tmpPtr = tmpPtr->next;
        }
        std::cout << '\n';
    }

    virtual void add(const T& element)
    {
        push(element);
    }

    virtual int getSize() const
    {
        return size;
    }

    virtual void sort()
    {
        priority_queue<T> queue;
        while(!isEmpty())
        {
            queue.push(getTop());
            pop();
        }
        while(!queue.empty())
        {
            push(queue.top());
            queue.pop();
        }
    }

    virtual bool member(Condition<T> condition) const
    {
        Node* tmpPtr = top;
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
        Node* tmpPtr = top;
        T* tmpArray = new T[size];
        int i = 0;
        while(!isEmpty())
        {
            T _data = getTop();
            if(!condition(_data))
            {
                tmpArray[i] = _data;
                i++;
            }
            pop();
        }
        for(int j = i - 1; j >= 0; j--)
        {
            push(tmpArray[j]);
        }

        delete [] tmpArray;
    }

    virtual void saveToFile(ofstream& os) const
    {
        os<<*this;

    }

    friend ostream& operator<<(ostream& os, const Stack& stack)
    {
        Node* tmpPtr = stack.top;
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
            push(atoi(numbers.back().c_str()));
            numbers.pop_back();
        }
    }
};

template<typename T>
const string Stack<T>::type = "Stack";

#endif // STACK_H_INCLUDED
