#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

namespace {
  class placeholder {};
  placeholder _1;
}

template <typename R,typename T, typename Arg>
class simple_bind_t {
    typedef R (T::*fn)(Arg);
    fn fn_;
    T t_;
public:
    simple_bind_t(fn f,const T& t):fn_(f),t_(t) {}

    R operator()(Arg& a) {
        return (t_.*fn_)(a);
    }
};

template <typename R, typename T, typename Arg>
simple_bind_t<R,T,Arg> simple_bind(
    R (T::*fn)(Arg),
    const T& t,
    const placeholder&) {
        return simple_bind_t<R,T,Arg>(fn,t);
}

class Test {
public:
    void do_stuff(const std::vector<int>& v) {
        std::copy(v.begin(),v.end(),
            std::ostream_iterator<int>(std::cout," "));
    }
};

int main() {
    Test t;
    std::vector<int> vec;
    vec.push_back(42);
    vec.push_back(21);
    simple_bind(&Test::do_stuff,t,_1)(vec);

    system("pause");
}

