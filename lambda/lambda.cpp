/****************************************************

     [captures] (params) -> ret {Statments;} 

*****************************************************/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <array>
#include <memory>
using namespace std;

void add1()
{
    int x = 1, y = 2;
    auto f1 = [](int x, int y)->int{return x + y;};
    cout << "add1: " << f1(1,2) << endl; // return 5
}

void add2()
{
    int x = 1, y = 2;
    auto f1 = [x, &y]{return x + y;};
    x = 3, y = 4;
    cout << "add2: " << f1() << endl; // return 5
}

void add3()
{
    //The line below could not be compiled in vs2012
    //vector<int> nums={1,3,5,9,10}; 
    int nums[]={1,3,5,9,10};
    int sum = 0;
    for_each(begin(nums), end(nums), [&sum](int n){
        sum += n;
    });
    cout << "add3: " << sum << endl;
}

int foo(function<int (int, int)> f)
{
    return f(7,8);
}

void add4()
{
    auto add = [](int x, int y){
        return x + y;};

    cout << "add4: " << foo(add) << endl;
}

void upper()
{
    char s[]="Hello World!";
    int Uppercase = 0; // modified by the lambda
    for_each(begin(s), end(s), [&Uppercase](char c){
        if (isupper(c))
            Uppercase++;
    });
    cout << Uppercase <<" uppercase letters in: " << s << endl;
}

void gen1()
{
    int step = 2;
    int i = -step;
    vector<int> seq(10);
    generate(begin(seq),end(seq), 
        [&i, step]
        {
            return (i += step);
        });

    cout << "gen1: ";
    for_each(begin(seq), end(seq), [](int i){
        cout << i << ",";
    });

    cout << endl;
}

void gen2()
{
    class Functor
    {
    public:
        Functor(int i, int step)
            :_i(i), _step(step)
        {}

        int operator()()
        {
            return (_i += _step);
        }
    private:
        int _i;
        int _step;
    };

    int step = 2;
    int i = -step;
    vector<int> seq(10);
    generate(begin(seq),end(seq), Functor(i, step));

    cout << "gen2: ";
    for_each(begin(seq), end(seq), [](int i){
        cout << i << ",";
    });

    cout << endl;
}


void printInt(int i)
{
    cout << i << endl;
}

void other()
{
    int a[5] = {1,2,3,4,5};
    vector<int> la(begin(a), end(a));
    for_each(begin(la),end(la),ptr_fun(printInt));
}

void arr()
{
    array<int, 4> a = {9,10,11};
    cout << "arr: " << endl;
    for_each(begin(a),end(a),[](int n) {
        cout << n << endl;
    });
}

int main()
{
    add1();
    add2();
    add3();
    add4();
    upper();
    gen1();
    gen2();
    other();
    arr();
}