#pragma once
#ifndef TIME_H
#define TIME_H

#include<windows.h>
#include<time.h>


clock_t BEGIN;//存储游戏正式开始时的时间
clock_t NOW;//存储现在的时间
clock_t STOPTIME;//游戏中途触发事件时，自动阻塞时间

//时间系统运行状态
#define NOTBEGIN 0
#define TIMEBLOCK 1
#define TIMEUNBLOCK 2
#define TIMEBEGIN 3

//时间运行倍速
#define NORMAL 1
#define DOUBLE 2

INT TIMESTATE;//用于判断时间状态
INT TIMERECORDSTATE = NOTBEGIN;
INT TIMES = 1;//用于调整时间流速

INT TIME = 0;//实际上的游戏内进行时间
INT BTIME = 0;//用于记录阻塞时间

INT MINUTE;
INT HOUR;
INT DAY = 1;
INT YEAR = 1;


void BEGINTIMECHECK() {
	BEGIN = clock() / CLOCKS_PER_SEC;
	TIMESTATE = TIMEUNBLOCK;
	TIMERECORDSTATE = TIMEBEGIN;
}//游戏正式开始运行之后，作为时间的基础值,设定时间状态为正常运行状态

void TIMECHECK() {
	NOW = clock() / CLOCKS_PER_SEC;
}//获取当前系统时间

void BLOCKTIME() {
	STOPTIME = NOW / CLOCKS_PER_SEC;
	TIMESTATE = TIMEBLOCK;
}//进程阻塞时间，设定时间运行状态为时间阻塞状态

void STOPOVER() {
	TIMESTATE = TIMEUNBLOCK;
}//时间阻塞结束,状态回弹(事件触发完毕时调用)



void SYSTIME() {
	if (TIMERECORDSTATE == TIMEBEGIN) {
		TIMECHECK();
		switch (TIMESTATE) {
		case TIMEBLOCK:

			BTIME = NOW - STOPTIME;
			break;

		case TIMEUNBLOCK:
			TIME = (NOW - BEGIN - BTIME) * TIMES;
			break;

		}
	}
	else
		return;
}//时间运行系统,循环体系无限循环

void TRANSLATETIME() {
	MINUTE = TIME % 60;
	HOUR = ((TIME / 60) + 8) % 24;//第一天从八点开始,24小时制
	DAY = 1 + (((TIME / 60) + 8) / 24) % 4;
	YEAR = 1 + (((TIME / 60) + 8) / 24) / 4;
}//时间换算
#endif