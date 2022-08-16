#include <iostream>
#include <vector>
#include <list>
#include <cmath>
template <typename Key, typename Value>
class hash_table {
public: // constructors and destructo
	hash_table();
	hash_table(const hash_table<Key, Value>&);
	hash_table(hash_table<Key, Value>&&); 
	hash_table(size_t);
	hash_table(const std::initializer_list<std::pair<Key, Value>>&);
	~hash_table();

public: // overloaded operators
	hash_table<Key, Value>& operator=(const hash_table<Key, Value>&); 
	hash_table<Key, Value>& operator=(hash_table<Key, Value>&&);
	hash_table<Key, Value> operator+(const hash_table<Key, Value>&);
	const hash_table<Key, Value> operator+=(const hash_table<Key, Value>& ht);
	const Value& operator[](const Key&) const;
	Value& operator[](const Key&);

	friend bool operator==(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		if (t1.m_table.size() != t2.m_table.size()) {
			return false;
		}
		for (int i = 0; i < t1.m_table.size(); ++i) {
			if (t1.m_table[i] != t2.m_table[i]) {
				return false;
			}
		}
		return true;
	}
	
	friend bool operator!=(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		return !(t1 == t2);
	}

	friend bool operator<(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		if (t1.m_table.size() >= t2.m_table.size()) {
			return false;
		}
		for (int i = 0; i < t1.m_table.size(); ++i) {
			if (t1.m_table[i] >= t2.m_table[i]) {
				return false;
			}
		}
		return true;
	}

	friend bool operator<=(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		return (t1 < t2) || (t1 == t2);
	}

	friend bool operator>(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		if (t1.m_table.size() <= t2.m_table.size()) {
			return false;
		}
		for (int i = 0; i < t1.m_table.size(); ++i) {
			if (t1.m_table[i] <= t2.m_table[i]) {
				return false;
			}
		}
		return true;
	}

	friend bool operator>=(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		return (t1 > t2) || (t1 == t2);
	}

	friend std::ostream& operator<<(std::ostream& os, const hash_table<Key, Value>& table) {
		for (const auto& list : table.m_table) {
			for (const auto& pair : list) {
				os << "Key : " << pair.first << " Value : " << pair.second << std::endl;
			}
		}
		return os;
	}

public: // main functionnality

	bool empty() const; 
	bool contains(const Key&) const; 
	size_t size() const; 
	void clear();
	void insert(const std::pair<Key, Value>&);
	void emplace(const std::pair<Key, Value>&);
	void erase(const Key&);
	void swap(hash_table<Key, Value>&);
	std::pair<Key, Value> extract(const Key&); 
	void merge(const hash_table<Key, Value>&);
	size_t count(const Key&); 
	Value* find(const Key&); 
	size_t hash_function(const Key&);
	double load_factor() const; 
	void rehash(size_t); 

private:
	std::vector<std::list<std::pair<Key, Value>>> m_table;
};
