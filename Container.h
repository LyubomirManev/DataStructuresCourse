#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED
#include "Iterable.h"
#include <iostream>
#include <list>

using namespace std;
template <typename T>
using Condition = bool (*) (const T&);

template <typename T>
class Container : public Iterable<T>
{

public:
    virtual void display() const = 0;
    virtual void add(const T&) = 0;
    virtual int getSize() const = 0;
    virtual void sort() = 0;
    virtual bool member(const T&) const = 0;
    virtual bool member(Condition<T>) const = 0;
    virtual void filter(Condition<T>) = 0;
    virtual void saveToFile(ofstream&) const = 0;
    virtual void loadFromFile(list<string>) = 0;
    virtual ~Container() {}
};


#endif // CONTAINER_H_INCLUDED
