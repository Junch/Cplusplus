#include <iostream>
#include <algorithm>
using namespace std;

struct PrintInt {
    PrintInt(int a):a_(a){}

    void operator()(int elem) {
        cout << elem + a_<< " ";
    }

    int a_;
};

int main(int argc, char* argv[])
{
    int a[] = {3,1,4,1,5,9,2,6};

    for_each(begin(a), end(a), PrintInt(2));
    cout << endl;

    for_each(begin(a), end(a), [](int elem){
        cout << elem + 1<< " ";
    });
    cout << endl;

    system("PAUSE");
}
