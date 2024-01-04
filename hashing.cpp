#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

// the const keyword is used to indicate that a variable 
// or a function parameter should not be modified after 
// its initial assignment or declaration.

//  the static keyword has several different uses, depending on 
//  where it is applied. It can be used with variables, functions, 
//  classes, and member functions. Like when you declare a variable
//  as static within a function, it retains its value between function calls. 

// The static_cast is a C++ casting operator that allows
// you to perform type conversions between related types
// in a controlled and explicit manner.

// static_cast<int> refers to using the 
// static_cast operator to convert a value 
// or expression of one type to an int type.

// size_t is a data type in C and C++ that is used to represent 
// the size of objects in memory, typically in terms of the number of bytes. 
// It's an unsigned integral type, meaning it can only represent non-negative
// values, making it suitable for representing sizes and indices in memory-related operations.

size_t sampleHash(const std::string& s) {

  static const int hashPrime = 997;

   int sum = 0;
  for (char c : s) {
    sum += static_cast<int>(c);     // summing over ASCII Values of the all the characters in the string
    // why this is bad?  - As for a string of given length, the sum of ASCII values of all the characters
    //                     will lie in a particular range                                                    
  }
  return sum % hashPrime;

}

class HashFunctionTester {
private:
    std::vector<std::string> randomStrings;
    size_t (*hashFunc)(const std::string&);     // HashFunction* hashFunc

public:

   HashFunctionTester(size_t (*func)(const std::string&), int numStrings = 1000) : hashFunc(func) {
        // Generate random strings                                             
        for (int i = 0; i < numStrings; ++i) {
            randomStrings.push_back(generateRandomString());
	}
    }

  
  std::string generateRandomString(int length = 10) {
        const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::string result;

        for (int i = 0; i < length; ++i) {
            result += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return result;
    }

  void testUniformity() {
        std::unordered_map<size_t, int> hashCounts;

        for (const auto& s : randomStrings) {
            size_t hashValue = hashFunc(s);
            hashCounts[hashValue]++;
        }

        double averageCount = static_cast<double>(randomStrings.size()) / hashCounts.size();
        std::cout << "Average count per bucket: " << averageCount << std::endl;
  }

  void testCollisionRate(){
    //TODO
  }

  void timeTaken(){
    //TODO
  }

  void avalancheEffect(){
    //TODO
  }
  
};

int main() {

    HashFunctionTester tester(sampleHash);

    std::cout << "Testing Uniformity..." << std::endl;
    tester.testUniformity();

    std::cout << "\nTime taken..." << std::endl;
    tester.timeTaken();

    std::cout << "\nTesting Collision Rate..." << std::endl;
    tester.testCollisionRate();

    std::cout << "\nTesting Avalanche Effect..." << std::endl;
    tester.avalancheEffect();
    
    return 0;
}

