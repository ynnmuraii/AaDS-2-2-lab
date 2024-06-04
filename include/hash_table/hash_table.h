#pragma once
#include<iostream>
#include<string>
#include<random>
#include<vector>

using namespace std;

namespace hash_table {
    template<typename K, typename T>
    struct Pair {
        K _key;
        T _value;
        Pair(K key, T value) : _key(key), _value(value) {}
        Pair() : _key(K()), _value(T()) {}
    };

    template<typename K, typename T>
    struct Node {
        Pair<K, T> _pair;
        Node<K, T>* _next;
        Node(const Pair<K, T>& data) : _pair(data), _next(nullptr) {}
        Node() : _pair(Pair<K, T>()), _next(nullptr) {}
    };

    template<typename K, typename T>
    class HashTable {
    private:
        size_t _size;
        std::vector<Node<K, T>*> _data;

        size_t hash(const K& key) {
            long long int result = (long long int)key * 2654435761;
            result = result % (long long int)(pow(2, 32));
            result = result >> (32 - power_of_two(_size));
            return result;
        }

        size_t power_of_two(size_t n) {
            size_t power = 0;
            while (n > 1) {
                n = n >> 1;
                power++;
            }
            return power;
        }

        static int pearson(std::string str) {
            static const unsigned char T[256] = {
              98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
              61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
              90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
             237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
             123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
              59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
             197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
              39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
             154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
             133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
             189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
             183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
             221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
               3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
             238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
              43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239
            };
            unsigned char hash = 0;
            for (char c : str) {
                hash = T[hash ^ static_cast<unsigned char>(c)];
            }
            return hash;
        }

    public:

        template<typename U = int, typename V = int>
        friend  bool hash_comparison(const std::string& s1, const std::string& s2);

        HashTable(size_t size) : _data(std::vector<Node<K, T>*>(size, nullptr)), _size(size) {}

        HashTable(size_t size, size_t str_length) : _data(size, nullptr), _size(size) {
            const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<int> charDistribution(0, alphabet.size() - 1);

            for (size_t i = 0; i < _data.size(); ++i) {
                if (_data[i] == nullptr) {
                    std::string randomString = "";
                    for (size_t j = 0; j < str_length; j++) {
                        randomString += alphabet[charDistribution(generator)];
                    }
                    insert(i, randomString);
                }
            }
        }

        ~HashTable() {
            clear();
        }

        void clear() {
            for (size_t i = 0; i < _data.size(); i++) {
                Node<K, T>* head = _data[i];
                while (head != nullptr) {
                    Node<K, T>* temp = head;
                    head = head->_next;
                    delete temp;
                }
            }
            _data.clear();
            _size = 0;
        }

        HashTable(const HashTable<K, T>& other) : _data(other._data.size(), nullptr), _size(other._size) {
            for (size_t i = 0; i < other._data.size(); ++i) {
                Node<K, T>* current = other._data[i];
                while (current != nullptr) {
                    insert(current->_pair._key, current->_pair._value);
                    current = current->_next;
                }
            }
        }

        HashTable<K, T>& operator=(const HashTable<K, T>& other) {
            if (this != &other) {
                clear();
                _size = other._size;
                _data.resize(other._data.size(), nullptr);
                for (size_t i = 0; i < other._data.size(); ++i) {
                    Node<K, T>* current = other._data[i];
                    while (current != nullptr) {
                        insert(current->_pair._key, current->_pair._value);
                        current = current->_next;
                    }
                }
            }
            return *this;
        }

        void print() const {
            for (size_t i = 0; i < _data.size(); i++) {
                if (_data[i] != nullptr) {
                    Node<K, T>* ptr = _data[i];
                    while (ptr != nullptr) {
                        std::cout << "(" << ptr->_pair._key << ", '" << ptr->_pair._value << "') ";
                        ptr = ptr->_next;
                    }
                }
            }
            std::cout << std::endl;
        }

        size_t count(K key) {
            size_t index = hash(key);
            int count = 0;
            Node<K, T>* node = _data[index];
            while (node != nullptr) {
                if (node->_pair._key == key) {
                    count++;
                }
                node = node->_next;
            }
            return count;
        }

        bool contains(K key) {
            size_t index = hash(key);
            Node<K, T>* node = _data[index];
            while (node != nullptr) {
                if (node->_pair._key == key) {
                    return true;
                }
                node = node->_next;
            }
            return false;
        }

        void insert(K key, T value) {
            size_t index = hash(key);
            if (contains(key)) {
                return;
            }

            if (_data[index] == nullptr) {
                _data[index] = new Node<K, T>(Pair<K, T>(key, value));
            }
            else {
                Node<K, T>* newNode = new Node<K, T>(Pair<K, T>(key, value));
                newNode->_next = _data[index];
                _data[index] = newNode;
            }
        }

        void insert_or_assign(const K& key, const T& value) {
            size_t index = hash(key);
            Node<K, T>* node = _data[index];
            while (node != nullptr && node->_pair._key != key) {
                node = node->_next;
            }
            if (node != nullptr) {
                node->_pair._value = value;
            }
            else {
                Node<K, T>* newNode = new Node<K, T>(Pair<K, T>(key, value));
                newNode->_next = _data[index];
                _data[index] = newNode;
            }
        }

        T* search(const K& key) {
            size_t index = hash(key);
            Node<K, T>* node = _data[index];
            while (node != nullptr && node->_pair._key != key) {
                node = node->_next;
            }
            if (node != nullptr) {
                return &node->_pair._value;
            }
            return nullptr;
        }

        bool erase(const K& key) {
            size_t index = hash(key);
            Node<K, T>* prev = nullptr;
            Node<K, T>* current = _data[index];
            while (current != nullptr && current->_pair._key != key) {
                prev = current;
                current = current->_next;
            }
            if (current != nullptr) {
                if (prev == nullptr) {
                    _data[index] = current->_next;
                }
                else {
                    prev->_next = current->_next;
                }
                delete current;
                return true;
            }
            return false;
        }
    };

    template<typename U = int, typename V = int>
    bool hash_comparison(const std::string& s1, const std::string& s2) {
        if (HashTable<U, V>::pearson(s1) == HashTable<U, V>::pearson(s2)) {
            return true;
        }
        return false;
    }
}
