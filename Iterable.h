#include "Iterator.h"

template<typename T>
class Iterable{
public:
    virtual Iterator<T>* getIterator() const = 0;
};
