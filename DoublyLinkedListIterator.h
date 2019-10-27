
template<typename T>
class DoublyLinkedListIterator : public Iterator<T>
{
    typename DoublyLinkedList<T>::Node* pointer;
public:
    DoublyLinkedListIterator(DoublyLinkedList<T> doublyLinkedList)
    {
        pointer = doublyLinkedList.front;
    }

    virtual bool hasNext()
    {
        return pointer != NULL;
    }

    virtual T& next()
    {
        T* data = &pointer->data;
        pointer = pointer->previous;
        return *data;
    }

    DoublyLinkedListIterator<T>& operator++()
    {
        pointer = pointer->previous;
        return *this;
    }

    DoublyLinkedListIterator<T> operator++(int)
    {
        DoublyLinkedListIterator* tmp = this;
        operator++();
        return *tmp;
    }

    T& operator*() const
    {
        return pointer->data;
    }
};
