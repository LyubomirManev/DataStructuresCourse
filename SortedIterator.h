#ifndef SORTEDITERATOR_H_INCLUDED
#define SORTEDITERATOR_H_INCLUDED

#include "Container.h"
#include <vector>
#include <queue>


template <typename E>
class SortedIterator : public Iterator<E>
{
    std::priority_queue<E> queue;
    bool isValid;
public:
    SortedIterator()
    {
        isValid = false;
    }

    SortedIterator(std::vector<Iterator<E>*> iterators)
    {
        for(int i = 0, n = iterators.size(); i < n; i++)
        {
            while(iterators[i]->hasNext())
            {
                queue.push(iterators[i]->next());
            }
        }
        isValid = true;
    }

    virtual bool hasNext()
    {
        return (isValid && !queue.empty());
    }

    virtual E& next()
    {
        E data = queue.top();
        queue.pop();
        return data;
    }

    E& operator*() const
    {
        E data = queue.top();
        return data;
    }

    SortedIterator& operator++()
    {
        if(queue.empty())
        {
            return *this;
        }
        queue.pop();
        return *this;
    }

    SortedIterator operator++(int)
    {
        SortedIterator* tmp = this;
        operator++();
        return *tmp;
    }
};


#endif // SORTEDITERATOR_H_INCLUDED
