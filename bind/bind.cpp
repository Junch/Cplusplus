//
// http://www.radmangames.com/programming/how-to-use-boost-bind
//

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// example one
///////////////////////////////////////////////////////////////////////////////
void square(double x) {
    cout << x << "^2 == " << x * x << endl;
}

void product(double x, double y) {
    cout << x << "*" << y << " == " << x * y << endl;
}

void example1() {
    double arg[]={1, 2, 3};
    for_each(begin(arg), end(arg), square);
    cout << endl;

    for_each(begin(arg), end(arg), bind(product, placeholders::_1, 2));
    cout << endl;

    for_each(begin(arg), end(arg), bind(square, placeholders::_1));

    cout << endl;
    for_each(begin(arg), end(arg), [](double x){
        cout << x << "^3 == " << x * x * x << endl;
    });
}

///////////////////////////////////////////////////////////////////////////////
// example two
///////////////////////////////////////////////////////////////////////////////
void func(int number, float floatation, string s) {
    cout << "Int: \"" << number << "\" Float: \"" << floatation
            << "\" String: \"" << s << "\"" << endl;
}

void example2() {
    using namespace std::placeholders;

    std::function<void(string, float, int)> shuffleFunction;
    std::function<void(void)> voidFunction;
    std::function<void(float)> reducedFunction;

    shuffleFunction = bind(&func, _3, _2, _1);
    voidFunction = bind(&func, 5, 5.f, "five");
    reducedFunction = bind(&func, 13, _1, "empty");

    shuffleFunction("String", 0.f, 0);
    voidFunction();
    reducedFunction(13.f);
}

///////////////////////////////////////////////////////////////////////////////
// example three - about function
///////////////////////////////////////////////////////////////////////////////
void example3() {
    using namespace std::placeholders;

    int number = 0; 
    string aString("text"); 
    float aFloat = 0.f; 

    // some function pointers 
    function<void()> voidFunction; 
    function<int(std::string)> stringAndIntFunction; 
    function<void(float, int)> floatAndIntFunction; 

    if (stringAndIntFunction._Empty())
        cout << "Does not contain valid method" << endl;

    floatAndIntFunction = bind(func, _2, _1, "example3");
    if (floatAndIntFunction)
        floatAndIntFunction(10.0, 7);
}

int main()
{
    example1();
    cout << endl;
    example2();
    cout << endl;
    example3();
    system("PAUSE");
}
