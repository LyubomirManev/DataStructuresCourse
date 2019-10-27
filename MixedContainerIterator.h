#ifndef MIXEDCONTAINERITERATOR_H_INCLUDED
#define MIXEDCONTAINERITERATOR_H_INCLUDED

#include "Container.h"
#include <vector>

template <typename E>
class MixedContainerIterator : public Iterator<E>
{
    std::vector<Iterator<E>*> iterators;
    int currentContainer;
    int iteratorsSize;
    bool isValid;
public:
    MixedContainerIterator()
    {
        isValid = false;
    }

    MixedContainerIterator(vector<Iterator<E>*> iterators)
    {
        this->iterators = iterators;
        currentContainer = 0;
        iteratorsSize = iterators.size();
        isValid = true;
    }

    virtual bool hasNext()
    {
        if(!isValid)
        {
            return false;
        }
        if(currentContainer >= iteratorsSize)
        {
            currentContainer = 0;
        }
        for(currentContainer; currentContainer <  iteratorsSize; currentContainer++)
        {
            if(iterators[currentContainer]->hasNext())
            {
                return true;
            }
        }
        currentContainer = 0;
        for(currentContainer; currentContainer <  iteratorsSize; currentContainer++)
        {
            if(iterators[currentContainer]->hasNext())
            {
                return true;
            }
        }
        return false;
    }

    virtual E& next()
    {
        return iterators[currentContainer++]->next();
    }

    E& operator*() const
    {
        return **iterators[currentContainer];
    }

    MixedContainerIterator& operator++()
    {
        this->next();
        return *this;
    }

    MixedContainerIterator operator++(int)
    {
        MixedContainerIterator* tmp = this;
        operator++();
        return *tmp;
    }
};


#endif // MIXEDCONTAINERITERATOR_H_INCLUDED
