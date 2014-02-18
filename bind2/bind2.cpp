/* http://www.rritw.com/a/caozuoxitong/OS/20120727/151346.html
*/

#include <iostream>
#include <algorithm>
using namespace std;

template<typename _Arg1, typename _Arg2, typename _Result>
struct binary_function2 {
	typedef _Arg1 first_argument_type;
	typedef _Arg2 second_argument_type;
	typedef _Result result_type;
};

template<typename _Tp>
struct equal_to2: public binary_function2<_Tp, _Tp, bool> {
	bool operator()(const _Tp& __x, const _Tp& __y) const {
		return __x == __y;
	}
};

template<typename _Arg, typename _Result>
struct unary_function2 {
	typedef _Arg argument_type;
	typedef _Result result_type;
};

template<typename _Operation>
class binder1st2: public unary_function2<
		typename _Operation::second_argument_type,
		typename _Operation::result_type> {
protected:
	_Operation op;
	typename _Operation::first_argument_type value;

public:
	binder1st2(const _Operation& __x,
			const typename _Operation::first_argument_type& __y) :
			op(__x), value(__y) {
	}

	typename _Operation::result_type operator()(
			const typename _Operation::second_argument_type& __x) const {
		return op(value, __x);
	}

	typename _Operation::result_type operator()(
			typename _Operation::second_argument_type& __x) const {
		return op(value, __x);
	}
};

template<typename _Operation, typename _Tp>
inline binder1st2<_Operation> bind1st2(const _Operation& __fn, const _Tp& __x) {
	typedef typename _Operation::first_argument_type _Arg1_type;
	return binder1st2<_Operation>(__fn, _Arg1_type(__x));
}

int main() {
	binder1st2<equal_to2<int> > equal_to_10(equal_to2<int>(), 10);
	int numbers[] = { 10, 20, 30, 40, 50, 10 };
	int cx;
	cx = std::count_if(numbers, numbers + 6, bind1st2(equal_to2<int>(), 10));
	cout << "There are " << cx << " elements that are equal to 10.\n";

    system("pause");
}
