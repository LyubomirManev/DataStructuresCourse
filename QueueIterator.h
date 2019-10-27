template<typename T>
class QueueIterator : public Iterator<T>
{
    typename Queue<T>::Node* pointer;
public:
    QueueIterator(Queue<T> queue)
    {
        pointer = queue.head;
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

    QueueIterator& operator++()
    {
        pointer = pointer->next;
        return *this;
    }

    QueueIterator operator++(int)
    {
        QueueIterator* tmp = this;
        operator++();
        return *tmp;
    }

    T& operator*() const
    {
        return pointer->data;
    }
};
