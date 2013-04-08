#include <iostream>
#include <tuple>
#include <string>

void example1()
{
    typedef std::tuple <int, double, long &, const char *> test_tuple;
    long lengthy = 12;
    test_tuple proof(18, 6.5, lengthy, "Ciao!");

    lengthy = std::get<0>(proof);
    std::get<3>(proof) = "Beautiful!";
    std::cout << lengthy << std::endl;
    std::cout << std::get<3>(proof) << std::endl;

    typedef std::tuple< int , double, std::string> tuple_1;
    tuple_1 t1;
    typedef std::tuple< char, short , const char *> tuple_2;
    tuple_2 t2 ('X', 2, "Hola!");
    t1 = t2;
    std::cout << std::get<2>(t1) << std::endl;
    std::cout << std::endl;
}

void example2()
{
    auto t = std::make_tuple("hello!", 10,  1.23);
    std::cout << " " << std::get<0>(t);
    std::cout << " " << std::get<1>(t);
    std::cout << " " << std::get<2>(t);
    std::cout << std::endl;
}

void example3()
{
    auto a = std::make_pair("Tom", 17);
    std::cout << a.first << " " << a.second << std::endl;
}


int main(int argc, char* argv[])
{
    example1();
    example2();
    example3();

    system("PAUSE");
}
