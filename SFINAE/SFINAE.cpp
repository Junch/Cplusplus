// http://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
// http://blog.think-async.com/2009/07/user-friendly-compile-errors-for.html
// http://www.martinecker.com/wiki/index.php?title=SFINAE_Principle
//
// SFINAE = Substitution Failure Is Not An Error
// with SFINAE you can check if a given class does provide a certain method
// The point is that SFINAE only applies to template functions.
//
// To summarize, the essence of the SFINAE principle is this: If an invalid argument or
// return type is formed when a function template is instantiated during overload resolution,
// the function template instantiation is removed from the overload resolution set and does
// not result in a compilation error.

#include <iostream>

/////////////////////////////////////////////////////////////
// example 1
struct Test  {  
    typedef int type;  
};  
  
template<typename T>  
void f(T)  
{     
    std::cout<< "two" <<std::endl;  
}

template <typename T>  
void f(typename T::type) {  
    std::cout<< "one" <<std::endl;  
}  

void example1()
{
    f<Test>(10);
    f<int>(10);
}

///////////////////////////////////////////////////////////////
// example 2
// http://blog.olivierlanglois.net/index.php/2007/09/01/what_is_the_c_sfinae_principle
// 
template<typename T>
class IsClassT {
  private:
    typedef char One;
    typedef struct { char a[2]; } Two;
    template<typename C> static One test(int C::*);
    // Will be chosen if T is anything except a class.
    template<typename C> static Two test(...);
  public:
    enum { Yes = sizeof(test<T>(0)) == 1 };
    enum { No = !Yes };
};

void example2()
{
    std::cout << "int is class? = " << IsClassT<int>::Yes << std::endl;
    std::cout << "Test is class? = " << IsClassT<Test>::Yes << std::endl;
}

  
int main(int argc, char* argv[])  
{  
    example1();
    example2();

    system("PAUSE"); //std::cin.get();
} 
