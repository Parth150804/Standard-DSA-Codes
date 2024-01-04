#include<iostream>

using namespace std;

class Base {
public:
  virtual  void foo() { std::cout << "Base::foo()\n"; }
  //void foo() { std::cout << "Base::foo()\n"; }                                                                    
};

class Derived : public Base {
public:
    void foo() { std::cout << "Derived::foo()\n"; }
    void bar() { Base::foo(); }
};


int main(){
  
  Base *b;
  Derived d;
  // d.foo();
  b = &d;
  b->foo();
  
//   int x = 10;
  
//   int *p;
//   p = &x;

//   cout << "Value of x =" << x << endl;
//   cout << "Value of p =" << p << endl;
//   cout << "Value pointed to by p = " << *p << endl;

//   int y = *p;
//   *p = 20;
//   cout << "Value of x =" << x << endl;
//   cout << "Value of y =" << y << endl;

//   int **dp;
//   dp = &p ; 

//   cout << "Value of  dp = " << dp << endl;
//   cout << "Address of dp = " << &dp << endl;
//   cout << "Value pointed by dp (i.e. *dp) = " << *dp << endl;
//   cout << "Value pointed by **dp = " << **dp << endl;
//   return 0;
// }


  return 0;
}
