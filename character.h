//乘客属性库
//等待被整合为线程
#include "state.h"
#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H
using namespace std;
namespace characterTianyu {
	struct character {
		int  weight;//乘客质量
		int  nowfloor;//当前位置
		int  aimfloor;//目标楼层
		//施工区
		int  STATE direction;//方向
		int  STATE readystate;//是否ready状态
		int  STATE locationstate;//所处位置状态
		bool STATE whetherdistrbution;//是否随机分配,开局初始化为真，之后随机分配
		int  code;//the number used to identify.
		//施工区完毕
		//int token
	};

	//向上乘客组
	typedef struct UPreadycharacter {
		UPreadycharacter* next;//指向下个乘客
		UPreadycharacter* last;//指向上个乘客
		static int upcnt;//计数器
		struct character* cha;

	}URCHARACTER, *PURCHARACTER;



	//向下乘客组
	typedef struct DOWNreadycharacter {
		DOWNreadycharacter* next;//指向下个乘客
		DOWNreadycharacter* last;//指向上个乘客
		static int downcnt;//计数器
		struct character* cha;

	}DRCHARACTER, *PDRCHARACTER;
	
	

	//乘客数据缓冲区
	typedef struct buffer {
		PURCHARACTER uhead;
		PDRCHARACTER dhead;
		int bufferlength;//缓冲长度，记得初始化
	}BUF,*PBUF;


	bool check_aimfloorlegal(character* );//检测目标楼层是否合法，并没有做到同时分配到相应队列。

	int  get_direction(character* );//获取和返回方向

	void add_aimfloortoready(character* cha, PURCHARACTER* shead, PURCHARACTER* head);//上楼乘客组

	void add_aimfloortoready(character* cha, PDRCHARACTER* shead,PDRCHARACTER* head);//下楼乘客组

	void STATE characterstate_change(character* cha);//用于乘客表状态转换

	


		//该状态函数仅仅只是修改部分状态。在每一次进程运行的时候启动。
		//部分状态修改实在上电梯的时候分配的。

}


#endif