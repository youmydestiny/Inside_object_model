#include<iostream>
using namespace std;
class Point{
public:
    virtual ~Point(){return;};
    virtual float z(){return 0.0;};
    float x(){return 0.0;};
    float y(){return 0.0;};
    
};

int main(void){
    Point point = Point();     //纯虚函数不能实例化，如果转换为虚函数，定义一个函数体，里面存在内容，就可以
    printf("%d\n", &Point::z); //这里的结果是9，跟书上说的不一样
    printf("%d\n", &Point::x); //地址值4211020
    printf("%d\n", &Point::y); //地址值4211036
    return 0;
}