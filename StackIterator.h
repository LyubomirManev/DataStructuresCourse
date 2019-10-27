template<typename T>
class StackIterator : public Iterator<T>
{
    typename Stack<T>::Node* pointer;
public:
    StackIterator(Stack<T> stack)
    {
        pointer = stack.top;
    }

    virtual bool hasNext()
    {
        return pointer != NULL;
    }

    virtual T& next()
    {
        T* data = &pointer->data;
        pointer = pointer->next;
        return *data;
    }

    StackIterator& operator++()
    {
        pointer = pointer->next;
        return *this;
    }

    StackIterator operator++(int)
    {
        StackIterator* tmp = this;
        operator++();
        return *tmp;
    }

    T& operator*() const
    {
        return pointer->data;
    }
};
