#include <iostream>
using namespace std;

void memory_dump(void *ptr, int len) {
    int i;
    printf("%p\n", ptr);
    for (i = 0; i < len; i++) {
        if (i % 8 == 0 && i != 0)
            printf(" ");
        if (i % 16 == 0 && i != 0)
            printf("\n");
        printf("%02x ", *((uint8_t *)ptr + i));
    }
    printf("\n");
}
class A {
};
class B : public virtual A 
{
};
class C : public virtual A
{
	//void virtual foo2(void){}
 };
class D : public B, public C
{ };
int main(void){
	A cur_A1, cur_A2;
	std::cout<<"the size of class A object: "<<sizeof(cur_A1)<<endl;
	//cout<<"whether A1 == A2 : "<< (&cur_A1==&cur_A2) << endl;

	B cur_B1;
	C cur_C1;
	cout<<"size of class B object : "<<sizeof(cur_B1)<<endl;
	cout<<"size of class C object : "<<sizeof(cur_C1)<<endl;

	D cur_D1;
	cout<<"size of class D object : "<<sizeof(cur_D1)<<endl;

	memory_dump(&cur_A1, sizeof(cur_A1));
	memory_dump(&cur_B1, sizeof(cur_B1));

	memory_dump(&cur_C1, sizeof(cur_C1));
	memory_dump(&cur_D1, sizeof(cur_D1));
	return 0;  
}