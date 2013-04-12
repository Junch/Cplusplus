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

    shuffleFunction = bind(func, _3, _2, _1);
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

///////////////////////////////////////////////////////////////////////////////
// example four - about function
///////////////////////////////////////////////////////////////////////////////
void funcA(int& errorcode)
{
    cout << "Hello World" << endl;
    errorcode = 1;
}

void funcB(int& errorcode, string str)
{
    cout << "Hello World" << endl;
    cout << str << endl;
    errorcode = 2;
}

//int caller(void (*funca)(int&))
//{
//    int errorcode = 0;
//    funca(errorcode);
//    return errorcode;
//}

template<class _Func>
int caller(_Func _func)
{
    int errorcode = 0;
    _func(errorcode);
    return errorcode;
}

void example4()
{
    using namespace std::placeholders;

    // normal call
    caller(funcA);

    // use bind to change the signature of the funcB
    caller(bind(funcB, _1, "ABC"));
 }

void example5()
{
    //If the expression is nonzero (true), the static_assert declaration has no effect.
    //This following code is assuring that only 32-bit code could be compiled.
    static_assert(sizeof(void *) == 4, "64-bit code generation is not supported.");
}






int main()
{
    example1();
    cout << endl;
    example2();
    cout << endl;
    example3();
    cout << endl;
    example4();
    system("PAUSE");
}
