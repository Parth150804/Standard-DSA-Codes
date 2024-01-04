#include <iostream>
#include <list>
#include <vector>
#include <string>

// std::list is a doubly linked list in c++ (inbuilt)

class HashTable {
private:
    static const int hashPrime = 13;
    std::list<std::pair<std::string, std::string> > table[hashPrime];

    int hash(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % hashPrime;
    }

public:
    bool isEmpty() const {
        int sum = 0;
        for (int i = 0; i < hashPrime; i++) {
            sum += table[i].size();
        }
        return (sum == 0);
    }

    void insertItem(std::string key, std::string value) {
        int hashValue = hash(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;

        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr->second = value;
                break;
            }
        }

        if (!keyExists) {
            cell.emplace_back(key, value);
        }
    }

    void removeItem(std::string key) {
        int hashValue = hash(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;

        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr = cell.erase(bItr);
                break;
            }
        }

        if (!keyExists) {
            std::cout << "Key not found. Pair not removed." << std::endl;
        }
    }

    std::string searchItem(std::string key) {
        int hashValue = hash(key);
        auto& cell = table[hashValue];
        auto bItr = begin(cell);
        bool keyExists = false;

        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                return bItr->second;
            }
        }

        return {};
    }

    void printTable() {
        for (int i = 0; i < hashPrime; i++) {
            if (!table[i].empty()) {
                auto bItr = table[i].begin();
                for (; bItr != table[i].end(); bItr++) {
                    std::cout << "[" << bItr->first << ": " << bItr->second << "] ";
                }
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    HashTable HT;
    
    if (HT.isEmpty()) {
        std::cout << "HT is EMPTY!" << std::endl;
    } 

    HT.insertItem("SVS", "col106");
    HT.insertItem("RAHUL", "Garg");


    HT.printTable();

    HT.removeItem("SVS");
    HT.removeItem("RAHUL");

    HT.printTable();

    return 0;
}
