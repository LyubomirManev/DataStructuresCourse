#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "Container.h"
#include "Stack.h"
#include "DoublyLinkedList.h"
#include "Queue.h"

#include "SortedIterator.h"
#include "MixedContainerIterator.h"
#include "ContainerByContainerIterator.h"

#include "StackIterator.h"
#include "QueueIterator.h"
#include "DoublyLinkedListIterator.h"


#include <vector>
#include <list>
#include <sstream>
using std::string;
using std::vector;
using std::cout;
using std::endl;

void split(const string &s, char delim, list<std::string> &elems)
{
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
}

list<string> split(const string &s, char delim)
{
    list<string> elems;
    split(s, delim, elems);
    return elems;
}

template <typename T>
class HeterogeneousLinkedList
{
    class Node
    {
    public:
        Container<T>* data;
        Node *next;

        Node(Container<T>* _data, Node*_next = NULL)
        {
            data = _data;
            next = _next;
        }

    };

    Node *head;
    Node *back;
    int size;

    void copy(const HeterogeneousLinkedList& other)
    {
        Stack<Container<T>*> tmpStack;
        Node *tmpPtr = other.head;
        while(tmpPtr != NULL)
        {
            tmpStack.push(tmpPtr->data);
            tmpPtr = tmpPtr->next;
        }
        while(!tmpStack.isEmpty())
        {
            insert(tmpStack.getTop());
            tmpStack.pop();
        }
        if(tmpPtr == NULL)
        {
            delete tmpPtr;
        }
    }


public:

    vector<Iterator<T>*> getIterators() const
    {
        vector<Iterator<T>*> iterators;
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            iterators.push_back(tmpPtr->data->getIterator());
            tmpPtr = tmpPtr->next;
        }
        return iterators;
    }

    SortedIterator<T> getSortedIterator()
    {
        this->sort();
        return SortedIterator<T>(getIterators());
    }

    MixedContainerIterator<T> getMixedIteratorToFirst(const T& data) const
    {
        MixedContainerIterator<T> iterator(getIterators());
        while(iterator->hasNext() && **iterator != data)
        {
            iterator->next();
        }
        if(!iterator->hasNext())
        {
            return MixedContainerIterator<T>();
        }
        return iterator;
    }


    ContainerByContainerIterator<T> getContainerIteratorToFirst(const T& data) const
    {
        ContainerByContainerIterator<T> iterator(getIterators());
        while(iterator->hasNext() && *iterator != data)
        {
            iterator.next();
        }
        if(!iterator.hasNext())
        {
            return ContainerByContainerIterator<T>();
        }
        return iterator;

    }

    MixedContainerIterator<T> getMixedContainerIterator() const
    {
        return MixedContainerIterator<T> (getIterators());
    }

    ContainerByContainerIterator<T> getContainerByContainerIterator() const
    {
        return ContainerByContainerIterator<T>(getIterators());
    }


    Container<T>* getAt(int index)
    {
        if(index >= size)
        {
            return NULL;
        }
        Node* tmpPtr = head;
        for(int i = 0; i < index; i++)
        {
            tmpPtr = tmpPtr->next;
        }
        return tmpPtr->data;
    }


    bool isEmpty()
    {
        return (head == NULL);
    }

    HeterogeneousLinkedList()
    {
        head = NULL;
        back = NULL;
        size = 0;
    }

    ~HeterogeneousLinkedList()
    {
    }

    HeterogeneousLinkedList(const HeterogeneousLinkedList& other)
    {
        head = NULL;
        back = NULL;
        size = 0;
        copy(other);
    }

    HeterogeneousLinkedList& operator=(const HeterogeneousLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            copy(other);
        }

        return *this;
    }

    void clear()
    {
        Node *tmp;
        while(head != NULL)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void insertAtBack(Container<T>* _data)
    {
        if(head == NULL && back == NULL)
        {
            head = new Node(_data);
            back = head;
            head->next = NULL;
            size++;
            return;
        }
        Node *tmpData = new Node(_data);
        back->next = tmpData;
        back = tmpData;
        size++;
    }

    void insertAtFront(Container<T>* _data)
    {
        if(head == NULL && back == NULL)
        {
            head = new Node(_data);
            back = head;
            head->next = NULL;
            size++;
            return;
        }
        Node *tmpData = new Node(_data);
        tmpData->next = head;
        head = tmpData;
        size++;
    }

    void remove(const Container<T>* _data)
    {
        if(head != NULL && head->data == _data)
        {
            Node* tmpPtr = head;
            head = head->next;
            delete head;
        }

        if(back != NULL && back->data == _data)
        {
            delete back;
            back = NULL;
        }


        Node* tmpPointer = head;
        if(head->data == _data)
        {
            head = head->next;
            size--;
            delete tmpPointer;
            return;
        }

        while( tmpPointer->next != NULL && (tmpPointer->next->data != _data) )
        {
            tmpPointer = tmpPointer->next;
        }

        if(tmpPointer->next == NULL)
        {
            return;
        }
        Node *target = tmpPointer->next;
        tmpPointer->next = target->next;
        delete target;
    }


    bool member(const T& element) const
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            if(tmpPtr->data->member(element))
            {
                return true;
            }
            tmpPtr = tmpPtr->next;
        }
        return false;
    }

    void showAll() const
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            tmpPtr->data->display();
            tmpPtr = tmpPtr->next;
        }
    }

    int getSize()
    {
        return size;
    }

    Container<T>* getContainerWithLowestSize() const
    {
        if(head == NULL)
        {
            return NULL;
        }
        Node* lowestPtr = head;
        Node* tmpPtr = head->next;
        int lowestSize = head->data->getSize();
        while(tmpPtr != NULL)
        {
            int tmpSize = tmpPtr->data->getSize();
            if(tmpSize <  lowestSize)
            {
                lowestSize = tmpSize;
                lowestPtr = tmpPtr;
            }
            tmpPtr = tmpPtr->next;
        }
        return lowestPtr->data;
    }

    void sort()
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            tmpPtr->data->sort();
            tmpPtr = tmpPtr->next;
        }
    }

    bool meetsCondition(Condition<T> condition)
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            if(tmpPtr->data->member(condition))
            {
                return true;
            }
            tmpPtr = tmpPtr->next;
        }
        return false;
    }

    void loadBalance(const T& element)
    {
        if(getSize() == 0)
        {
            return;
        }
        getContainerWithLowestSize()->add(element);
    }

    void conditionFilter(Condition<T> condition)
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            tmpPtr->data->filter(condition);
            tmpPtr = tmpPtr->next;
        }
    }

    void saveToFile(ofstream& os)
    {
        Node* tmpPtr = head;
        while(tmpPtr != NULL)
        {
            tmpPtr->data->saveToFile(os);
            os << '\n';
            tmpPtr = tmpPtr->next;
        }
    }

    void loadFromFile(ifstream& is)
    {
        string line;
        while(getline(is,line))
        {
            list<string> splitLine = split(line, ' ');
            string type = splitLine.front();
            splitLine.pop_front();
            Container<T>* container = containerFactory(type);
            container->loadFromFile(splitLine);
            insertAtBack(container);
        }
    }

    static Container<T>* containerFactory(string type)
    {
        if(type == "Stack")
        {
            return new Stack<T>;
        }
        else if (type == "Queue")
        {
            return new Queue<T>;
        }
        else if (type == "DoublyLinkedList")
        {
            return new DoublyLinkedList<T>;
        }

        return NULL;
    }
};



#endif // LINKEDLIST_H_INCLUDED
