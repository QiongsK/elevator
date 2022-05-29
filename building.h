//关于楼层的库
#include "character.h"
#include <iostream>
#ifndef BUILDING_H
#define BUILDING_H
using namespace std;
using namespace characterTianyu;
namespace buildingTianyu {

	class base_floor {
	public:
		base_floor(int);
		~base_floor();
		int  get_hight();
		void set_hight(int);
		int  STATE get_state();//返回状态，用于更新楼层状态数组
		void STATE set_state(int);

	protected://修改为中间等级，用于子类继承和调用相关数据
		int hight;//这个是楼层是第几层

		//character** rest;//一个指针数组，存储在休息区的乘客的结构体的指针
		//这个看要不要添加凑行数。。。

		int STATE state;//状态

	};

	enum function{workspace,rastaurant,null};//暂定这三种情况
	//TODO

	class derive_floor:public base_floor {
	public:

		derive_floor(int,function);

		function getfunc();

	private:
		const function func;
	};
	void STATE state_change(PURCHARACTER upready, 
		PDRCHARACTER downready,
		base_floor* floor);//状态机,改变楼层状态.

}








#endif