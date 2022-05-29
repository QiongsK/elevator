#pragma once
#ifndef STATE_H
#define STATE_H

//乘客
#define  ELEVATER_YES  1//想上电梯
#define  ELEVATER_NO   0//不想上电梯
#define  ELEVATER_ON   1//在电梯上
#define  ELEVATER_OFF  0//不在电梯上
//楼层
#define  WONDER_YES    1
#define  WONDER_NO     0
#define  WONDER_YESUP  2
#define  WONDER_YESDOWN 3
//电梯
#define  FULLFILL_YES  1
#define  FULLFILL_NO   2
#define  UP            4
#define  DOWN          5
#define  DUTY          6//有上有下
#define  DUTYON        7//只上人
#define  DUTYOFF       8//只下人
#define  DEFAULT       9//回到默认地址




#endif

#ifndef STATE
#define STATE//扩展宏，标记该数据类型用于存储状态，或者该函数用于修改状态
			
#endif

#ifndef CHART
#define CHART//扩展宏，用于标记数据为表

#endif
