// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

#ifndef MyMap_h
#define MyMap_h

#include "support.h"
#include <queue>
using namespace std;



template<typename KeyType, typename ValueType>
class MyMap
{
public:
	MyMap();
	~MyMap();
	void clear();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	MyMap(const MyMap&) = delete;
	MyMap& operator=(const MyMap&) = delete;

private:
    struct Node
    {
        Node* left;
        Node* right;
        ValueType value;
        KeyType key;
    };
    
    Node* root;
    int m_size;
};

template<typename KeyType, typename ValueType>
MyMap<KeyType,ValueType>::MyMap()
{
    root = nullptr;
    m_size = 0;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType,ValueType>::associate(const KeyType& key, const ValueType& value)
{
    if (nullptr == root)
    {
        root = new Node;
        root->left = nullptr;
        root->right = nullptr;
        root->key = key;
        root->value = value;
        m_size++;
        return;
    }
    
    Node* temp = root;
    
    while (nullptr != temp)
    {
        if (key == temp->key)
        {
            temp->value = value;
            return;
        }
        if (key > temp->key)
        {
            if (temp->right != nullptr)
            {
                temp = temp->right;
            }
            else
            {
                Node* node = new Node;
                node->key = key;
                node->value = value;
                node->left = nullptr;
                node->right = nullptr;
                temp->right = node;
                m_size++;
                return;
            }
        }
        if (key < temp->key)
        {
            if (temp->left != nullptr)
            {
                temp = temp->left;
            }
            else
            {
                Node* node = new Node;
                node->key = key;
                node->value = value;
                node->left = nullptr;
                node->right = nullptr;
                temp->left = node;
                m_size++;
                return;
            }
        }
    }
}

template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType,ValueType>::find(const KeyType& key) const
{
    Node* temp = root;
    
    while (nullptr != temp)
    {
        if (key == temp->key)
        {
            return (&temp->value);
        }
        if (key > temp->key)
        {
            if (temp->right != nullptr)
            {
                temp = temp->right;
            }
            else
                break;
        }
        if (key < temp->key)
        {
            if (temp->left != nullptr)
            {
                temp = temp->left;
            }
            else
                break;
        }
    }
    
    return nullptr;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType,ValueType>::clear()
{
    if (nullptr == root)
    {
        return;
    }
    
    queue<Node*> myQueue;
    
    myQueue.push(root);
    
    while (!myQueue.empty())
    {
        Node* cur = myQueue.front();
        myQueue.pop();
        
        if (nullptr != cur->left)
        {
            myQueue.push(cur->left);
        }
        
        if (nullptr != cur->right)
        {
            myQueue.push(cur->right);
        }
        
        delete cur;
    }
    
    root = nullptr;
    m_size = 0;
}

template<typename KeyType, typename ValueType>
int MyMap<KeyType,ValueType>::size() const
{
    return m_size;
}

template<typename KeyType, typename ValueType>
MyMap<KeyType,ValueType>::~MyMap()
{
    clear();
}


#endif 
