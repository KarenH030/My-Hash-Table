#include "MyHash_table"

// Implementation of constructors

template <typename Key, typename Value> 
hash_table<Key, Value>::hash_table() = default;


template <typename Key, typename Value>
hash_table<Key, Value>::hash_table(const hash_table<Key, Value>& table) {
    m_table = table.m_table;
}


template <typename Key, typename Value>
hash_table<Key, Value>::hash_table(hash_table<Key, Value>&& table) {
    m_table = std::move(table.m_table);
}



template <typename Key, typename Value>
hash_table<Key, Value>::hash_table(const std::initializer_list<std::pair<Key, Value>>& init) {
    m_table.resize(init.size());
    for (auto it = init.begin(); it != init.end(); ++it) {
        m_table[hash_function(it->first)].push_back(*it);
    }
}


template <typename Key, typename Value> 
hash_table<Key, Value>::hash_table(size_t count) : m_table(count) {}


template <typename Key, typename Value>
hash_table<Key, Value>::~hash_table() = default;


template <typename Key, typename Value>
size_t hash_table<Key, Value>::hash_function(const Key& key) {
    size_t hash_idx = 0;
    return hash_idx;
}

template <typename Key, typename Value>
bool hash_table<Key, Value>::empty() const {
    return m_table.size() == 0;
}

template <typename Key, typename Value>
size_t hash_table<Key, Value>::size() const {
    return m_table.size();
}

template <typename Key, typename Value>
void hash_table<Key, Value>::clear() {
    m_table.clear();
}

template <typename Key, typename Value>
bool hash_table<Key, Value>::contains(const Key& key) const {
    for (const auto& list : m_table) {
        for (const auto& pair : list) {
            if (pair.first == key) {
                return true;
            }
        }
    }
    return false;
}


template <typename Key, typename Value>
void hash_table<Key, Value>::swap(hash_table<Key, Value>& ht) {
    auto toSwap = this->m_table;
    this->m_table = ht.m_table;
    ht.m_table = toSwap;
}

template <typename Key, typename Value>
void hash_table<Key, Value>::erase(const Key& key) {
    size_t hash_idx = hash_function(key);
    m_table.erase(m_table.begin() + hash_idx);
}

template <typename Key, typename Value>
void hash_table<Key, Value>::insert(const std::pair<Key, Value>& pair) {
    this->rehash(1);
    size_t hash_idx = hash_function(pair.first);
    m_table[hash_idx].push_back(pair);
}

template <typename Key, typename Value>
void hash_table<Key, Value>::rehash(size_t count) {
    std::vector<std::list<std::pair<Key, Value>>> new_table(count + m_table.size());
    for (int i = 0; i < m_table.size(); ++i) {
        auto begIt = m_table[i].begin();
        auto endIt = m_table[i].end();
        for (; begIt != endIt; ++begIt) {
            size_t hash_idx = hash_function(begIt->first);
            new_table[hash_idx].push_back(*begIt);
        }
    }
    m_table = std::move(new_table);
}

template <typename Key, typename Value>
Value* hash_table<Key, Value>::find(const Key& key) {
    for (int i = 0; i < m_table.size(); ++i) {
        auto begit = m_table[i].begin();
        auto endit = m_table[i].end();
        for (; begit != endit; ++begit) {
            if (begit->first == key) {
                return &begit->second;
            } 
        }
    }
    return nullptr;
}

template <typename Key, typename Value> 
void hash_table<Key, Value>::emplace(const std::pair<Key, Value>& pair) {
    this->rehash(1);
    size_t hash_idx = hash_function(pair.first);
    m_table[hash_idx].push_back(pair);
}

template <typename Key, typename Value>
std::pair<Key, Value> hash_table<Key, Value>::extract(const Key& key) {
    size_t hash_idx = hash_function(key);
    std::pair<Key, Value> pair;
    for (auto it = m_table[hash_idx].begin(); it != m_table[hash_idx].end(); ++it) {
        if (key == it ->first) {
            pair = *it;
        }
    }
    return pair;
}

template <typename Key, typename Value>
size_t hash_table<Key, Value>::count(const Key& key) {
    size_t matches = 0;
    size_t hash_idx = hash_function(key);
    for (auto it = m_table[hash_idx].begin(); it != m_table[hash_idx].end(); ++it) {
        if (it->first == key) {
            ++matches;
        }
    }
    return matches;
}

template <typename Key, typename Value>
void hash_table<Key, Value>::merge(const hash_table<Key, Value>& ht) {
    this->operator+=(ht);
}

template <typename Key, typename Value>
double hash_table<Key, Value>::load_factor() const {
    size_t max = m_table[0].size();
    for (int i = 1; i < m_table.size(); ++i) {
        if (max < m_table[i].size()) {
            max = m_table[i].size();
        }
    }
    return m_table.size() % max;
}

// Implementation of operators

template <typename Key, typename Value> 
hash_table<Key, Value>& hash_table<Key, Value>::operator=(const hash_table<Key, Value>& table) {
    m_table = table.m_table;
    return *this;
}

template <typename Key, typename Value>
hash_table<Key, Value>& hash_table<Key, Value>::operator=(hash_table<Key, Value>&& table) {
    m_table = std::move(table.m_table);
    return *this;
}

template <typename Key, typename Value>
Value& hash_table<Key, Value>::operator[](const Key& key) {
    size_t hash_idx = hash_function(key);
    auto begIt = m_table[hash_idx].begin();
    auto endIt = m_table[hash_idx].end();
    for (; begIt != endIt; ++begIt) {
        if (begIt->first != key) {
            continue;
        }
    }
    return begIt->second;
}

template <typename Key, typename Value> 
const Value& hash_table<Key, Value>::operator[](const Key& key) const {
    size_t hash_idx = hash_function(key);
    auto begIt = m_table[hash_idx].begin();
    auto endIt = m_table[hash_idx].end();
    for (; begIt != endIt; ++begIt) {
        if (begIt->first != key) {
            continue;
        }
    }
    return const_cast<Value&>(begIt->second);   
}

template <typename Key, typename Value> 
const hash_table<Key, Value> hash_table<Key, Value>::operator+=(const hash_table<Key, Value>& ht) {
    hash_table<Key, Value> tmp(*this);
    this->operator=(tmp + ht);
    return *this;
}

template <typename Key, typename Value> 
hash_table<Key, Value> hash_table<Key, Value>::operator+(const hash_table<Key, Value>& ht) {
    hash_table<Key, Value> tmp(this->size() + ht.size());
    size_t hash_idx = 0;
    for (int i = 0; i < m_table.size(); ++i) {
        auto begIt = m_table[i].begin();
        auto endIt = m_table[i].end();
        for (; begIt != endIt; ++begIt) {
            hash_idx = hash_function(begIt->first);
            tmp.m_table[hash_idx].push_back(*begIt);
        }   
    }
    for (int i = 0; i < m_table.size(); ++i) {
        auto begIt = ht.m_table[i].begin();
        auto endIt = ht.m_table[i].end();
        for (; begIt != endIt; ++begIt) {
            hash_idx = hash_function(begIt->first);
            tmp.m_table[hash_idx].push_back(*begIt);
        }   
    }
    return tmp;
}

int main() {

}
