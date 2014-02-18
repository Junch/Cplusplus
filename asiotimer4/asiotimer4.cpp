#include <iostream>
#include <functional>

template<typename WaitHandler>
int async_wait(WaitHandler handler)
{
    int errorcode = 0;
    handler(errorcode);
    return errorcode;
}

//////////////// example 1 ///////////////////////
void funcA(int& errorcode)
{
    std::cout << "funcA: Hello World" << std::endl;
    errorcode = 1;
}

void example1()
{
    async_wait(funcA);
}

//////////////// example 2 ///////////////////////
//void funcB()
//{
//    std::cout << "funcB: Hello" << std::endl;
//}
//
//void example2()
//{
//    async_wait(funcB);
//}

//////////////// example 3 ///////////////////////
class printer
{
public:
    void test()
    {
        std::function<void(int&)> a = std::bind(&printer::print, this);
        async_wait(a);

        async_wait(std::bind(&printer::print, this));
        async_wait(std::bind(&printer::print2, this, std::placeholders::_1));
        async_wait(std::bind(&printer::print2, this, 100));
    }

    void print()
    {
        std::cout << "printer::print" << std::endl;
    }

    void print2(int para)
    {
         std::cout << "printer::print2 para=" << para << std::endl;
    }
};

void example3()
{
    printer a;
    a.test();

    (std::bind(&printer::print, std::placeholders::_1))(a);
    (std::bind(&printer::print, printer()))();
    (std::bind(&printer::print, &a))();

    (std::bind(&printer::print2, std::placeholders::_1, std::placeholders::_2))(a, 300);
    (std::bind(&printer::print2, &a, std::placeholders::_1))(400);
    (std::bind(&printer::print2, &a, 500))();
    (std::bind(&printer::print2, printer(), 600))();
}

int main(int argc, char* argv[])
{
    example1();
    //example2();
    example3();

    system("PAUSE");
}
