#pragma once


#include <vector>
#include <list>
#include <functional>
using std::hash;
using std::vector;
using std::list;

template <typename K, typename V>
class Hashtable
{
private:
struct Entry
{
    K key;
    V value;
    Entry(const K& k, const V& v) : key(k), value(v) {}
};
vector<list<Entry>> table;
size_t capacity;
size_t num_elements;

const double load_factor = 0.75;

size_t hashFunction(const K& key) const
{
    hash<K> hasher;
    return hasher(key) % capacity;
}

void rehash()
{
    
    capacity *= 2;

    vector<list<Entry>> old_table = table;
    table.clear();
    table.resize(capacity);
    num_elements = 0;

    for(const auto& bucket : old_table)
    {
        for(const auto& entry : bucket)
        {
            insert(entry.key, entry.value);
        }
    }
}

public:
Hashtable(size_t initial_capacity = 10007) : capacity(initial_capacity), num_elements(0)
{
    table.resize(capacity);
}

void insert(const K& key, const V& value)
{
    //when at or above load factor rehash
    if ((double)num_elements / capacity >= load_factor)
    {
        rehash();
    }

    size_t index = hashFunction(key);
    for (auto& entry : table[index])
    {
        if (entry.key == key)
        {
            entry.value = value;
            return;
        }
    }
    table[index].push_back(Entry(key, value));
    num_elements++;
}

bool find(const K& key, V& value) const
{
    size_t index = hashFunction(key);

    for (const auto& entry : table[index])
    {
        if (entry.key == key)
        {
            value = entry.value;
            return true;
        }
    }
    return false;

}

bool exists(const K& key) const
{
    size_t index = hashFunction(key);

    for (const auto& entry : table[index])
    {
        if (entry.key == key)
        {
            return true;
        }
    }
    return false;
}

void remove(const K& key)
{
    size_t index = hashFunction(key);

    auto& bucket = table[index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->key == key)
        {
            bucket.erase(it);
            num_elements--;
            return;
        }
    }

}

size_t size() const{
    return num_elements;
}

bool empty() const{
    return num_elements == 0;
}

void clear(){
    table.clear();
    table.resize(capacity);
    num_elements = 0;
}

vector<V> getAllValues() const{
    vector<V> values;
    
    for(const auto& bucket : table){
        for(const auto& entry : bucket){
            values.push_back(entry.value);
        }
    }
    return values;
}
};