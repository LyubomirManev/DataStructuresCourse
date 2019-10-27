#ifndef CONTAINERBYCONTAINERITERATOR_H_INCLUDED
#define CONTAINERBYCONTAINERITERATOR_H_INCLUDED

#include "Container.h"
#include <vector>

template <typename E>
class ContainerByContainerIterator : public Iterator<E>
{
    bool isValid;
    std::vector<Iterator<E>*> iterators;
    Iterator<E>* iterator;
    int currentContainer;
public:
    ContainerByContainerIterator()
    {
        isValid = false;
    }

    ContainerByContainerIterator(std::vector<Iterator<E>*> iterators)
    {
        this->iterators = iterators;
        currentContainer = 0;
        iterator = iterators[currentContainer];
        isValid = true;
    }

    virtual bool hasNext()
    {
        if(!isValid)
        {
            return false;
        }
        if(iterators.empty())
        {
            return false;
        }

        if(iterator->hasNext())
        {
            return true;
        }
        if(iterators.size() == currentContainer + 1)
        {
            return false;
        }
        currentContainer++;
        iterator = iterators[currentContainer];
        return hasNext();
    }

    virtual E& next()
    {
        return iterator->next();
    }

    E& operator*() const
    {
        return **iterator;
    }

    ContainerByContainerIterator& operator++()
    {
        if(!iterator->hasNext())
        {
            iterator = iterators[++currentContainer];
            return *this;
        }
        iterator->next();
        return *this;
    }

    ContainerByContainerIterator operator++(int)
    {
        ContainerByContainerIterator* tmp = this;
        operator++();
        return *tmp;
    }

};
#endif // CONTAINERBYCONTAINERITERATOR_H_INCLUDED
