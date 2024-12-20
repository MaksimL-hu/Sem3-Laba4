#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class LinkedList : public Sequence<T>
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    Node* tail;
    int length;

public:
    class LinkedListIterator : public Sequence<T>::Iterator {
    private:
        Node* current;

    public:
        LinkedListIterator(Node* start) : current(start) {}

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            const LinkedListIterator* otherIterator = dynamic_cast<const LinkedListIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }

        T& operator*() const override
        {
            return current->data;
        }

        typename Sequence<T>::Iterator& operator++() override
        {
            if (current)
            {
                current = current->next;
            }

            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() const override
    {
        return new LinkedListIterator(head);
    }

    typename Sequence<T>::Iterator* ToEnd() const override
    {
        return new LinkedListIterator(nullptr);
    }

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0)
    {
        for (int i = 0; i < count; ++i)
        {
            Append(items[i]);
        }
    }

    LinkedList(LinkedList<T>& list) : head(nullptr), tail(nullptr), length(0)
    {
        Node* current = list.head;

        while (current != nullptr)
        {
            Append(current->data);
            current = current->next;
        }
    }

    LinkedList(DynamicArray<T>& dynamicArray) : head(nullptr), tail(nullptr), length(0)
    {
        for (int i = 1; i < dynamicArray.GetLength(); i++)
        {
            Append(dynamicArray.GetElement(i));
        }
    }

    ~LinkedList()
    {
        Node* current = head;
        Node* next;

        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

    bool operator==(const LinkedList<T>& other)
    {
        if (GetLength() != other.GetLength())
            return false;

        auto thisIterBegin = ToBegin();
        auto thisIterEnd = ToEnd();
        auto otherIterBegin = other.ToBegin();
        auto otherIterEnd = other.ToEnd();

        while (*thisIterBegin != *thisIterEnd && *otherIterBegin != *otherIterEnd)
        {
            if (**thisIterBegin != **otherIterBegin)
                return false;

            ++(*thisIterBegin);
            ++(*otherIterBegin);
        }

        return true;
    }

    T& GetFirstElement() override
    {
        return head->data;
    }

    T& GetLastElement() override
    {
        return tail->data;
    }

    T& GetElement(int index) override
    {
        return GetNode(index)->data;
    }

    Node* GetNode(int index)
    {
        Node* current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current;
    }

    void Swap(T& a, T& b) override
    {
        T temp = a;
        a = b;
        b = temp;
    }

    void Set(int index, T value)
    {
        Node* current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        current->data = value;
    }

    LinkedList<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        if (endIndex >= length)
        {
            endIndex = length - 1;
        }

        LinkedList<T>* sublist = new LinkedList<T>();
        Node* current = head;
        
        for (int i = 0; i <= endIndex; i++)
        {
            if (i >= startIndex)
            {
                sublist->Append(current->data);
            }

            current = current->next;
        }

        return sublist;
    }

    int GetLength() const override
    {
        return length;
    }

    void Append(T item) override
    {
        Node* newNode = new Node(item);

        if (length == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        length++;
    }

    void Append(T* data, int dataSize) override
    {
        int i = 0;

        while (i < dataSize)
        {
            Append(data[i]);
            i++;
        }
    }

    void Prepend(T item) override
    {
        Node* newNode = new Node(item, head);

        if (length == 0)
        {
            head = tail = newNode;
        }
        else
        {
            head = newNode;
        }

        length++;
    }

    void InsertAt(T item, int index) override
    {
        if (index == 0)
        {
            Prepend(item);
        }
        else if (index == length)
        {
            Append(item);
        }
        else
        {
            Node* current = head;

            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }

            Node* newNode = new Node(item, current->next);
            current->next = newNode;
            length++;
        }
    }

    void Union(Sequence<T>* list) override
    {
        int length = list->GetLength();

        for (int i = 0; i < length; i++)
        {
            Append(list->GetElement(i));
        }
    }
};

#endif