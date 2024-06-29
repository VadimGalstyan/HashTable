#ifndef __HASH__
#define __HASH__

#include <iostream>

template <typename TKey,typename TValue>
struct pair
{
    TKey key;
    TValue data;

    pair()
    {
    }
    pair(TKey key1,TValue val) : key(key1),data(val)
    {
    }
};


template <typename TKey,typename TValue>
struct Node
{
    pair<TKey,TValue> obj;
    Node<TKey,TValue>* next = nullptr;

    Node()
    {
    }
    Node(const Node& object)
    {
        obj = object.obj;
    }
};


template <typename TKey,typename TValue>
class HashTable
{
public:
    HashTable();
    HashTable(const int& size);
    HashTable(const HashTable<TKey,TValue>& obj);
    HashTable& operator=(const HashTable<TKey,TValue>& obj);
    ~HashTable();


    int hashFunc(const std::string& key) const;
    int hashFunc(const int& key) const;

    int bucket() const;
    int bucket_count(const TKey& key) const;

    int size() const;

    void add(const pair<TKey,TValue>& obj);
    void add(const TKey& key,const TValue& value);

    void deleteTable();

    bool empty() const;

    void print() const;


private:
    Node<TKey,TValue>** ptr;
    int tableSize = 19;

};

#endif //__HASH__

template <typename TKey,typename TValue>
HashTable<TKey,TValue>::HashTable()
{
    ptr = new Node<TKey,TValue>*[tableSize];
    for (int i = 0; i < tableSize; ++i)
    {
        ptr[i] = nullptr;
    }
    
    
}

template <typename TKey,typename TValue>
HashTable<TKey,TValue>::HashTable(const int& size) : tableSize(size)
{
    ptr = new Node<TKey,TValue>*[tableSize];
    for (int i = 0; i < tableSize; ++i)
    {
        ptr[i] = nullptr;
    }
}


template <typename TKey,typename TValue>
HashTable<TKey,TValue>::HashTable(const HashTable<TKey,TValue>& obj)
{
    tableSize = obj.tableSize;

    ptr  = new Node<TKey,TValue>*[tableSize];
    for (int i = 0; i < tableSize; ++i)
    {
        ptr[i] = nullptr;
    }


    for (int i = 0; i < tableSize; ++i)
    {
        if (obj.ptr[i] == nullptr)
        {
            continue;
        }


        Node<TKey,TValue>* temp1 = obj.ptr[i];
        Node<TKey,TValue>* temp2 = temp1->next;

        ptr[i] = new Node<TKey,TValue>(*temp1);

        Node<TKey,TValue>* current = ptr[i];


        while (temp2 != nullptr)
        {
            temp1 = temp2;
            temp2 = temp2->next;

            current->next = new Node<TKey,TValue>(*temp1);
            current = current->next;
        }
        
        
    }
    
}

template <typename TKey,typename TValue>
void HashTable<TKey,TValue>::deleteTable()
{
    for (int i = 0; i < tableSize; ++i)
    {
        if (ptr[i] == nullptr)
        {
            continue;
        }
        
        Node<TKey,TValue>* temp1 = ptr[i];
        Node<TKey,TValue>* temp2 = temp1->next;

        delete temp1;

        while (temp2 != nullptr)
        {
            temp1 = temp2;
            temp2 = temp2->next;

            delete temp1;
        }
    }

    delete[] ptr;
}


template <typename TKey,typename TValue>
HashTable<TKey,TValue>& HashTable<TKey,TValue>::operator=(const HashTable<TKey,TValue>& obj)
{
    if (this != &obj)
    {
        this->deleteTable();

        tableSize = obj.tableSize;

        ptr  = new Node<TKey,TValue>*[tableSize];
        for (int i = 0; i < tableSize; ++i)
        {
            ptr[i] = nullptr;
        }


        for (int i = 0; i < tableSize; ++i)
        {
            if (obj.ptr[i] == nullptr)
            {
                continue;
            }


            Node<TKey,TValue>* temp1 = obj.ptr[i];
            Node<TKey,TValue>* temp2 = temp1->next;

            ptr[i] = new Node<TKey,TValue>(*temp1);

            Node<TKey,TValue>* current = ptr[i];


            while (temp2 != nullptr)
            {
                temp1 = temp2;
                temp2 = temp2->next;

                current->next = new Node<TKey,TValue>(*temp1);
                current = current->next;
            }
            
            
        }
            
    }
        
        return *this;
}




template <typename TKey,typename TValue>
HashTable<TKey,TValue>::~HashTable()
{
    for (int i = 0; i < tableSize; ++i)
    {
        if (ptr[i] == nullptr)
        {
            continue;
        }
        
        Node<TKey,TValue>* temp1 = ptr[i];
        Node<TKey,TValue>* temp2 = temp1->next;

        delete temp1;

        while (temp2 != nullptr)
        {
            temp1 = temp2;
            temp2 = temp2->next;

            delete temp1;
        }
    }

            delete[] ptr;

}


template <typename TKey,typename TValue>
int HashTable<TKey,TValue>::hashFunc(const std::string& key) const
{
    int index = 0;
    for (int i = 0; i < key.length(); ++i)
    {
        
        index += (int)key[i];
    }
    
    index = index % tableSize;

    return index;
}

template <typename TKey,typename TValue>
int HashTable<TKey,TValue>::hashFunc(const int& key) const
{
    return key % tableSize;
}


template <typename TKey,typename TValue>
void HashTable<TKey,TValue>::add(const pair<TKey,TValue>& obj)
{
    int index = hashFunc(obj.key);

    if (ptr[index] == nullptr)
    {
        ptr[index] = new Node<TKey,TValue>;
        ptr[index]->obj = obj;
        return;
    }
    else
    {
        Node<TKey,TValue>* temp = ptr[index];
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        
        temp->next = new Node<TKey,TValue>;
        (temp->next)->obj = obj;
        return;
    }

}


template <typename TKey,typename TValue>
void HashTable<TKey,TValue>::add(const TKey& key,const TValue& value)
{
    int index = hashFunc(key);

    if (ptr[index] == nullptr)
    {
        ptr[index] = new Node<TKey,TValue>;
        ptr[index]->obj.key = key;
        ptr[index]->obj.data = value;
        return;
    }
    else
    {
        Node<TKey,TValue>* temp = ptr[index];
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        
        temp->next = new Node<TKey,TValue>;
        ((temp->next)->obj).key = key;
        ((temp->next)->obj).data = value;

        return;
    }
}


template <typename TKey,typename TValue>
void HashTable<TKey,TValue>::print() const
{
    
   for (int i = 0; i < tableSize; ++i)
   {
        if (ptr[i] != nullptr)
        {
            std::cout<<"BUCKET INDEX     =      "<<i<<std::endl;

            int j = 0;

            std::cout<<"Node index = "<<j<<std::endl;
            std::cout<<"Key = "<<(ptr[i]->obj).key<<std::endl;
            std::cout<<"Data = "<<(ptr[i]->obj).data<<std::endl;

            Node<TKey,TValue>* temp = ptr[i]->next;
            while (temp != nullptr)
            {
                ++j;
                std::cout<<"Node index = "<<j<<std::endl;
                std::cout<<"Key = "<<(temp->obj).key<<std::endl;
                std::cout<<"Data = "<<(temp->obj).data<<std::endl;
                temp = temp->next;
            }
            
        }
        
   }
   
}

template <typename TKey,typename TValue>
bool HashTable<TKey,TValue>::empty() const
{
    for (int i = 0; i < tableSize; ++i)
    {
        if (ptr[i] != nullptr)
        {
            return false;
        }
        
    }
    
    return true;
}


template <typename TKey,typename TValue>
int HashTable<TKey,TValue>::bucket() const
{
    return tableSize;
}

template <typename TKey,typename TValue>
int HashTable<TKey,TValue>::bucket_count(const TKey& key) const
{
    int index = hashFunc(key);
    int count = 0;

    Node<TKey,TValue>* temp = ptr[index];

    while (temp != nullptr)
    {
        if (temp->obj.key == key)
        {
            ++count;
        }
        
        temp = temp->next;
    }

    return count;
}

template <typename TKey,typename TValue>
int HashTable<TKey,TValue>::size() const
{
    int count = 0;

    for (int i = 0; i < tableSize; ++i)
    {
        Node<TKey,TValue>* temp = ptr[i];

        while (temp != nullptr)
        {
            ++count;
            temp = temp->next;
        }
        
    }
    
    return count;
}