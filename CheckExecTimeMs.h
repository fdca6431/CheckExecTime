#include <iostream>
#include <vector>
using namespace std;

//时间数据默认输出位置
#define TIME_LOG cout

//获取当前ms时间戳
#ifdef WIN32
#include "windows.h"
long getCurrentMS(){
  return GetTickCount();
}
#else
#include <sys/time.h>
#include <stdio.h>
long getCurrentMS(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (long)1000 + tv.tv_usec/1000;
}
#endif

class CheckExecTimeMs
{
public:
    CheckExecTimeMs(string name="") :res(name){
        start = getCurrentMS();
    }
    ~CheckExecTimeMs(){
        checkPoint(" End:");
        print();
    }
    void checkPoint(string desc = ""){
        char tStr[40];
        long gap = getCurrentMS() - start;
        sprintf(tStr, ":%ld, ", gap);
        res += desc + tStr;
    }
    void checkPoint(int desc){
        char tStr[40];
        long gap = getCurrentMS() - start;
        sprintf(tStr, " %d:%ld, ", desc, gap);
        res += tStr;
    }
    void print(string desc = ""){
        if(desc.size()==0)
            TIME_LOG << res.c_str() << endl;
        else
            TIME_LOG << (desc+res).c_str() << endl;
    }
    long getPeriod(){
        return getCurrentMS() - start;
    }
    void reset(string desc = ""){
        if(desc.size()==0)
            checkPoint("Reset");
        else
            checkPoint(desc);
        start = getCurrentMS();
    }
private:
    long start;
    string res;
};
