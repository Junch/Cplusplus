/*
http://blog.csdn.net/zwvista/article/details/5151059
http://blog.smartbear.com/software-quality/bid/167271/The-Biggest-Changes-in-C-11-and-Why-You-Should-Care
*/

#include <array>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;


template <typename Container>
void print(const Container& c)
{
    for_each(begin(c), end(c), [](const typename Container::value_type& e) {
        cout << e << " ";
    });

    cout << endl;
}

template<class _Ty, size_t _Size> inline void
print(_Ty (&_Array)[_Size])
{
    for(auto e: _Array)
        cout << e << " ";
    
    cout << endl;
}

/////////////////////////////////////
void example1() {
    array<int, 20> a;
    int n = 0;
    for (auto i=begin(a); i != end(a); i++)
        *i = n++;
}

int gn = 0;
int next_int() {
    return gn++;
}

void example2() {
    array<int, 20> a;
    generate(begin(a), end(a), next_int);
}

class generator  
{  
public:  
    explicit generator(int& n) : n_(n) {}  
    int operator()() const { return n_++; }  
private:  
    int& n_;  
};

void example3() {
    array<int, 20> a;  
  
    int n = 0;  
    generate(a.begin(), a.end(), generator(n));  
}

void exmaple4() {
    array<int, 20> a;

    int n = 0;
    generate(a.begin(), a.end(), [&]{return n++;});
    //generate(a.begin(), a.end(), [&n]{return n++;});
    //for_each(begin(a), end(a), [&](int&v){v = n++;});
    //for_each(begin(a), end(a), [&n](int&v){v = n++;});
}

void example5() {
    vector<int> a(20);

    int n = 1;
    generate(a.begin(), a.end(), [&n]{return n++;});

    auto prime = [] (const int n) -> bool {
        if (n < 2)
            return false;

        for (int i=2; i<=n/i; ++i)
            if (n % i == 0)
                return false;
        return true;
    };

    auto notprime = [=](const int n) -> bool {
        return !prime(n);
    };

    auto iter = remove_if(begin(a), end(a), notprime);
    // To change the sequence size, use erase
    a.erase(iter, end(a));

    print(a);
}

void example6() {
    int my_array[5] = {1, 2, 3, 4, 5};
    for(auto &x : my_array)
        x *= 2;

    bool alleven = all_of(begin(my_array), end(my_array), [](int e){
        return e % 2 == 0;
    });

    bool anyeven = any_of(begin(my_array), end(my_array), [](int e){
        return e % 2 == 0;
    });

    bool noneven = none_of(begin(my_array), end(my_array), [](int e){
        return e % 2 == 0;
    });

    for(auto x : my_array)
        cout << x << " ";
    cout << endl;

    cout << "alleven=" << alleven << endl;
    cout << "anyeven=" << alleven << endl;
    cout << "noneven=" << noneven << endl;
}

#include <numeric>
void example7() {
    int a[5] = {0};
    char c[3] ={0};

    iota(begin(a), end(a), 10);  //changes a to {10,11,12,13,14}
    iota(begin(c), end(c), 'a'); //{'a','b','c'} 

    print(a);
    print(c);
}


int main(int argc, char* argv[])
{
    example1();
    example2();
    example3();
    exmaple4();
    example5();// remove_if
    example6();// new for loop, any_of, none_of, all_of
    example7();// iota

    system("PAUSE");
}