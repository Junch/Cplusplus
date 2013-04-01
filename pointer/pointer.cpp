/*
http://stackoverflow.com/questions/569775/smart-pointers-boost-explained
http://www.drdobbs.com/weak-pointers/184402026
http://stackoverflow.com/questions/712279/what-is-the-usefulness-of-enable-shared-from-this
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
using namespace std;


///////////// unique_ptr /////////////////////
void ptr1()
{
    //unique_ptr<int[]> ptr(new int[3]);
    unique_ptr<int[]> ptr;
    ptr.reset(new int[3]);
    ptr[0] = 1;
    ptr[1] = 2;
    ptr[2] = 3;
    cout << "ptr1: " << endl;
    for_each(&ptr[0],&ptr[3],[](int n){
        cout << n << endl;
    });
}

void ptr2()
{
    unique_ptr<int> a(new int(3));
    //The line below cannot pass the compiler
    //unique_ptr<int> b(a);
    unique_ptr<int> b(std::move(a));
}

void ptr3()
{
    vector<unique_ptr<int>> values;
    values.push_back(unique_ptr<int>(new int(0)));
    unique_ptr<int> two(new int(2));
    values.push_back(std::move(two));

    cout << "ptr3: " << endl;
    for_each(begin(values),end(values),[](const unique_ptr<int> &item){
        cout << *item << endl;
    });
}

struct Foo
{
void print(){
    cout << "Foo::print" << endl;
}
~Foo(){
    cout << "Foo::destruction" << endl;
}
};

void ptr4()
{
    shared_ptr<Foo> sp1(new Foo);
    sp1->print();
    shared_ptr<Foo> sp2(sp1);
    sp2->print();
    cout << "ptr4:" << endl;
    cout << "sp1 pointer:" << sp1.get() << endl;
    cout << "sp2 pointer:" << sp2.get() << endl;
    cout << "counter sp1:" << sp1.use_count() << endl;
    cout << "counter sp2:" << sp2.use_count() << endl;
}

void ptr5()
{
    cout << "ptr5:" << endl;
    shared_ptr<Foo> sp1(new Foo);
    cout << "counter sp1:" << sp1.use_count() << endl;
    shared_ptr<Foo> sp2(sp1);
    shared_ptr<Foo> sp3(sp2);
    cout << "counter sp1:" << sp1.use_count() << endl;
    cout << "counter sp2:" << sp2.use_count() << endl;
    cout << "counter sp3:" << sp3.use_count() << endl;
    sp1.reset();
    cout << "counter sp1:" << sp1.use_count() << endl;
    cout << "counter sp2:" << sp2.use_count() << endl;
    cout << "counter sp3:" << sp3.use_count() << endl;
    sp2.reset();
    cout << "counter sp1:" << sp1.use_count() << endl;
    cout << "counter sp2:" << sp2.use_count() << endl;
    cout << "counter sp3:" << sp3.use_count() << endl;
}

/*
The major weakness of shared_ptr is that it cannot detect cyclic dependencies. In
this case, the reference counter is incremented more than it should actually be, so
that the resources are no longer released when the shared pointer objects go out of scope.

To fix this problem, a second smart pointer was created, weak_ptr, that points to
a resource owned by a shared_ptr but does not affect the reference counter;
it is a "weak reference." When the last shared_ptr that owns the resource referred
by a weak_ptr, the resource is released and the weak pointer is marked as invalid.
To check whether a weak_ptr is valid or not, you can use function expired() that
returns true if the pointer was marked as invalid.
*/
void show(const weak_ptr<int>& wp)
{
    //The following line is illegal
    //cout << *wp << endl;
    shared_ptr<int> sp = wp.lock();
    cout << *sp << endl;
}

void ptr6()
{
    weak_ptr<int> wp;
    {
        shared_ptr<int> sp(new int(44));
        wp = sp;
        show(wp);
    }
    cout << "expired: " << boolalpha << wp.expired() << endl;
}

void ptr7()
{
    shared_ptr<Foo> sp1(new Foo);
    shared_ptr<Foo> sp2(sp1);
    Foo* p = sp1.get();
    cout << "counter sp1:" << sp1.use_count() << endl;
    cout << "counter sp2:" << sp2.use_count() << endl;
    //This line will cause crash
    shared_ptr<Foo> sp3(p);
}


/* enable_shared_from_this template
  It enables you to get a valid shared_ptr instance to this, when all you have is this.
  Without it, you would have no way of getting a shared_ptr to this, unless you had
  already one as a member. 
*/

class A: public enable_shared_from_this<A>
{
public:
    shared_ptr<A> child_;
    //The following line will cause the memory leak
    //shared_ptr<A> parent_;
    weak_ptr<A> parent_;

    void add(shared_ptr<A> child) {
        child_ = child;
        child_->set(shared_from_this());
    }

    void set(shared_ptr<A> parent) {
        parent_ = parent;
    }

    ~A() {
        cout << "A::~A()" << endl;
    }
};

void ptr8()
{
    shared_ptr<A> sp1(new A);
    shared_ptr<A> sp2(new A);
    shared_ptr<A> sp3(new A);
    sp1->add(sp2);
    sp2->add(sp3);
    cout << "ptr8:" << endl;
    cout << "counter sp1:" << sp1.use_count() << endl;
    cout << "counter sp2:" << sp2.use_count() << endl;
    cout << "counter sp3:" << sp3.use_count() << endl;
}


int main()
{
    ptr1();
    ptr3();
    ptr4();
    ptr5();
    ptr6();
    //ptr7();
    ptr8();

    system("Pause");
}