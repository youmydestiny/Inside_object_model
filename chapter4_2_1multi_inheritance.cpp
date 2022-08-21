#include<iostream>
#include<vector>
using namespace std;
class Base1{
public:
    Base1(){};
    virtual ~Base1(){};
    virtual void speakClearly(){};
    virtual Base1 *clone() const{return new Base1();};
protected:
    float data_Base1;
};
class Base2{
public:
    Base2(){};
    virtual ~Base2(){};
    virtual void mumble(){};
    virtual Base2 *clone() const{ return new Base2();};
protected:
    float data_Base2;
};
class Derived: public Base1, Base2{
public:
    Derived(){};
    virtual ~Derived(){};
    virtual Derived *clone() const{return new Derived();};
protected:
    float data_Derived;
};
int main(void){
    Derived cur_Derived;
}