//电梯类
//差一个整合的函数，即一个线程函数
//SCAN-EDF
#include<iostream>
#include<string>
#include"building.h"
#ifndef EVELETOR_H
#define ECELETOR_H
using namespace characterTianyu;
namespace elevetorTianyu {
	using namespace std;
	//基类型，电梯。包含私有成员：电梯编号，电梯承重,等待时间。
	//电梯编号与电梯承重只能初始化给予，不允许修改
	//可以使用get（）函数获取数值
	//TODO 私有成员 运行速度
	class base_elevator {
	public:
		base_elevator(int);
		~base_elevator();
		int get_code() const;
		int get_bearing() const;
		int get_waiting_time();
		//其他运行函数
		int  get_weightcnt();
		/*void set_weightcnt(PURCHARACTER);//把上电梯的乘客质量添加到电梯上
		void set_weightcnt(PDRCHARACTER);//重载，下楼的
		出现问题
		*/
		int  get_nowfloor();//获取当前所在楼层
		void upload_aimfloorarray(character*);//更新目标楼层列表
		int  get_characteraimfloor(character*);//用于检查和获取楼层中乘客目标楼层
		void set_nowfloor();//根据运行状态修改电梯所在楼层



		//判断器
		bool check_offelevator();//检测当前楼层是否有人要下楼
		bool check_weightstate();//检查是否人满了
		bool check_nowfloorstate(int []);//获取楼层状态表，检查当前楼层是否有人要上楼。
		bool check_whetherhaveaimfloor();//检查当前方向有无目标楼层
		bool check_whetherhavewonderfloor(int []);//检查当前方向是否有需求楼层
		bool check_characterweight(PURCHARACTER);//检查体重是否可以上电梯，上楼
		bool check_characterweight(PDRCHARACTER);//检查体重是否可以上电梯，下楼


		//状态机
		void STATE runstate_change(int[]);//运行状态改变
		void STATE fillstate_change();//存储状态变换
		void STATE state_comeback();//状态回调,任务完成时
		void STATE run_duty(PURCHARACTER*, PDRCHARACTER*, PBUF*,PBUF*);//任务运行

		//数据交换函数
		void load_characterup(PURCHARACTER*, PBUF*,PBUF*);//装载上楼的乘客
		void load_characterdown(PDRCHARACTER*, PBUF*,PBUF*);//装载下楼的乘客
		void off_character();//移除乘客,就是下楼
		//改变乘客状态，清空数组

		

	private:
		//number of elevators
		//every time create a new docker(elevator),this element will plus one.
		static int num;
		//always depend on the num.
		const int code;
		const int bearing=1500;//重量单位：kg
		const int height = 20;
		int waiting_time;//等待时间
		int defaultfloor = 0;//默认楼层
		int nowfloor;//当前楼层高度
		int weightcnt;//计算重量
		int* cnt;//电梯人数数组
		int STATE lastrunstate;//记录上一个状态
		int STATE runstate;//运行时状态元素
		int STATE duty;//任务状态
		int STATE weightstate;//电梯载重状态元素
		bool aimfloorarray[20] = {false};//目标楼层数组
		//由高到低
		character*** characterinelevator;//动态二维数组存储乘客，函数中初始化。
		//暂定楼层高度为20层

		
		/*protected:
			int initial_floor;*/
	};

	void elevatorthread(base_elevator* elevator,
		int floorstate[],
		PURCHARACTER pur[],
		PDRCHARACTER pdr[],
		PBUF* pbuf,
		PBUF* pend);//线程
	



}//elevetorTianyu






#endif
