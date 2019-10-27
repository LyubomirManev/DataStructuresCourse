#include <iostream>
#include "HeterogeneousLinkedList.h"

int main()
{
    HeterogeneousLinkedList<int> test;

    ifstream file("database.txt");
    test.loadFromFile(file);
    test.showAll();

    return 0;
}

