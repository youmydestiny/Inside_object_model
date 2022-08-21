/*
This template illustrate that mem occur first.
2022-8-9
fantl
*/
#include<iostream>
#include<string>
using namespace std;
class A{
public:
	int mem;
	int b;
};
//template<class class_type,
//		class data_type1,
//		class data_type2>
string access_order(int*mem1, int*mem2){
	if( mem1 < mem2) 
		return "member 1 occurs first.";
	else
		return "member 2 occurs first";
}
int main(void){
	A* a=new A();
	a->mem = 1;
	a->b = 2;
	cout<<sizeof(a)<<endl;
	cout<<access_order(& A::mem, & A::b)<<endl;
	return 0;
}