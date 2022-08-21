3.6指向DataMember的指针
这一章节建议参考CSDN上面的博客，因为这本书的时间写的较早，所以虽然原理都是相通，但是其内部已经经过了改进。

4 The semantics of Functions
class 支持三种类型的function: virtual, static, nonstatic

一个例子：
class Point3d{
	int _x;
	int _y;
	int _z;
	Point3d normalize() const;
	float magnitude() const;
};
Point3d Point3d::normalize() const{
	register float mag = magnitude();
	Point3d normal;

	normal._x = _x/mag;
	normal._y = _y/mag;
	normal._z = _z/mag;
	return normal;
}
float Point3d::magnitude() const{
	return sqrt(_x*_x+_y*_y+_z*_z);
}

nonstatic member function 

一个原则： nonstatic member function要和一般的nonmember function 有相同的效率
一般编译器将member 函数实体，转换为对等的nonmember 函数实体 

一个Point3d::magnitude()定义:
float Point3d::magnitude() const{
	return sqrt(_x*_x + _y*_y + _z*_z);
}

magnitude的一个nonmember定义：
float Point3d::magnitude(const Point3d* _this) {
	return sqrt(_this->_x*_this->_x + 
				_this->_y*_this->_y + 
				_this->_z*_this->_z);
}

扩张过程：
1-改写函数原型，以安插一个指针，被称为this指针
Point3d Point3d::magnitude(Point3d* const this)
如果member function为const，则变成
Point3d Point3d::magnitude(const Point3d* const this)

2-对每一个nonstatic data member的存取操作改为经过this指针的存取
{
	return sqrt(_this->_x*_this->_x + 
				_this->_y*_this->_y + 
				_this->_z*_this->_z);
}

3-function名称重写，进行mangling(重新命名)
	magnitude_7point3dFv(register Point3d* const this)

那么后面的调用也会发生转换：
Point3d obj;
Point3d* ptr = &obj;
obj.magnitude()
ptr->magnitude()
会变为：
magnitude_7point3dFv(&obj)
magnitude_7point3dFv(ptr)

normalization函数:
Point3d Point3d::normalize() const
{
	register float mag = magnitude();
	Point3d normal;
	normal._x = _x/mag;
	normal._y = _y/mag;
	normal._z = _z/mag;
	return normal;
}

在已经设置了copy constructor和使用了Name Returned Value的时候，其会被构造为这样：
void Point3d::normalize(const Point3d* const this, Point3d& __result) 
{
	register float mag = magnitude();
	__result.Point3d::Point3d();
	__result._x = this->_x/mag;
	__result._y = this->/mag;
	__result._z = this->/mag;
	return;
}

一个有效率的做法是直接构建normal的值
Point3d Point3d::normalize() const
{
	register float mag = magnitude();
	return Point3d(_x/mag, _y/mag, _z/mag);
}
它会被编译器修改为如下形式：
void Point3d::normalize(const Point3d* const this, Point3d& __result) 
{
	register float mag = magnitude();
	__result.Point3d::Point3d(this->_x/mag, this->_y/mag, this->_z/mag); //这里触发的是拷贝构造函数？那些情况使用的是拷贝构造，和初始
	//化有什么区别
	return;
}
这样节省了初始化引起的负担

name mangling

	function一般会经过mangling，形成独一无二的名称。
	为什么？

	主要是为了区别继承中，两个data member以及同名的function
	比如：
	class Base{
		int ival;
	};
	class Derived: public Base{
		int ival;
	}
	那么实际上在Derived的object实体中，存在两个ival，他们会经过name mangling拥有两个不同的名称，从而容易区分
	对于function来说也是这样的, name mangling主要是为了区分重载函数的区别。
	一般来说这种name mangling的方式主要是，把类名，参数链表，都加入到function名称中。
	函数标记signature : 函数名称+参数数目+参数类型

	编译器可以区分函数声明和调用时的函数标记错误，但是没有办法区分返回值错误。


virtual member function

	如果normalize()是一个virtual member function ，那么以下的调用：
	ptr->normalize()

	会被编译器内部转换为：
	(* ptr->vptr[1])(ptr);
	这个感觉可以这样理解：
		ptr 是一个class pointer
		vptr是object内部的一个pointer，并且它是一个地址，指向一个virtual function table
		所以ptr->vptr[1]
		指向了virtual function table中normalize()函数的地址
		经过这个函数的地址，前面加上*，就可以对这个函数产生调用，这就是：
		(* ptr->vptr[1])
		其输入就是(ptr), ptr表示this指针

	如果magnitude()是一个virtual function，那么它在normalize之中的调用将会被进行如下的转换：
	register float mag = (*this->vptr[2])(this);
	因为matnitude()是在Point3d::normalize()被调用，而后者已经由虚拟机制resolved，所以明确调用
	Point3d实体会比较有效率，以压制由于虚拟机制产生的不必要的重复调用操作。

	register float mag = Point3d::magnitude();

	magnitude()声明为inline函数会更有效率
	使用class scope operator明确调用virtual function ，其resolved方式会和nonstatic member function一样

Static Member Functions 
	
