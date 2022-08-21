/*Notion:
3.3 Data member 的存取
*/
class Point3d{
	int _x;
};
Point3d origin, *ptr=&origin
上面两种存取data member的方式有区别吗？
1.static data member的情况
存取的始终是一个指针，跟object无关，可以看作一个global的变量，不会带来额外的负担。
两个class如果定义同一个名称的static data member，那么会造成冲突，所以编译器会进行编码
2.non static data member的情况
如果没有虚拟继承，无论_x是一个struct member, class member, 单一继承，多重继承，都是一样的。
nonstatic data member的偏移量在编译期就已经知道了。
其地址一般为：clas object 地址  +  data member 的偏移量offset - 1
指向data member的指针，其offset总会+1，主要是为了区分指向data member的指针有没有指向一个data member 
3.如果存在虚拟继承，则会导致间接性
所以上面问题的答案：
Point3d是一个derived class，并且上面的_x是其virtual base class 的 data member的时候会存在差异。
因为一个比较好的编译器会经过origin解决掉对_x的存储
->对ptr，只能运行的时候间接访问_x
->对origin, 可以通过编译器解决这种间接性

3.4继承与Data member 
1.单一继承没有virtual function
只是数据的扩充，但是可能因为继承中的data alignment，导致空间的膨胀.
比如:
class Point2d{
	int a;
	char b;
	char c;
	char d;
};
原本是占据8个字节。
但是如果变成：
class Point2d{
	int a;
	char b;
}
class Point2d_1: public Point2d{
	char c;
}
class Point2d_2: public Point2d_1{
	char d;
}
最后的Point2d_2因为alignment，会有12个字节
2.单一继承带有virtual function
简单来说就是如果存在virtual function，会导入一个virtual function table，存储virtual function，一般数目为virtual function的数目加上两个slots
object中会导入一个vfptr.
microsoft将其中的virtual function pointer放在开头处
cfront的编译器将其中的vfptr放在结尾处
3.多重继承
按照声明顺序每个base class object进行排列。
4.多重虚拟继承
分为不变局部和共享局部
不变局部：derived class subobject部分，这个部分的offset不变
共享局部：base class subobject部分，这部分的offset在每次继承以后不断变化 
cfront编译器：在derived class object中，为其每一个virtual base class安插一个指针，指向其virtual base class subobject部分
缺点：
1-不是固定负担，因为virtual base class多了以后，指针也多了
2-继承长了以后，间接储存的次数增加了，存取时间增加
MetaWare : 拷贝所有指向virtual base class的指针，这样解决了第二个问题 
对第一个问题
Microsoft 使用了virtual base table，储存其virtual base class 的指针
Bjarne: 使用了virtual function table中，相对于table起始偏移负数的部分，防止每个virtual base class table 的偏移量offset(<0)

notation: 实际上在后面我看到，microsoft 仍然使用了virtual base class,但是其中已经开始记录offset，而非地址.

