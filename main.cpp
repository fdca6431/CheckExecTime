#include "CheckExecTimeMs.h"
using namespace std;
#ifndef WIN
#include <unistd.h>
void Sleep(int ms){usleep(ms*1000);}
#endif

class TestAutoCheck :CheckExecTimeMs{
public:
    TestAutoCheck(string desc) :CheckExecTimeMs(desc){}
    TestAutoCheck(){}
};

class TestAutoCheck2{
public:
    TestAutoCheck2(string desc) :ck(desc){}
    TestAutoCheck2(){}
private:
    CheckExecTimeMs ck;
};

void funcB(CheckExecTimeMs& p){
    p.print("Check ");
    p.checkPoint("Breset:");
}

void funcA(){
    CheckExecTimeMs p1(__FUNCTION__);
    Sleep(200);
    p1.checkPoint();
    p1.reset();
    funcB(p1);
    Sleep(200);
}
void test(){
    TestAutoCheck ck1("ck1");//先构造，入栈，后析构
    TestAutoCheck ck3;
    TestAutoCheck2 ck2("ck2");//先析构
    TestAutoCheck2 ck4;
    funcA();
}
int main(){
    test();
    return 0;
}
