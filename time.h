#pragma once
#ifndef TIME_H
#define TIME_H

#include<windows.h>
#include<time.h>


clock_t BEGIN;//�洢��Ϸ��ʽ��ʼʱ��ʱ��
clock_t NOW;//�洢���ڵ�ʱ��
clock_t STOPTIME;//��Ϸ��;�����¼�ʱ���Զ�����ʱ��

//ʱ��ϵͳ����״̬
#define NOTBEGIN 0
#define TIMEBLOCK 1
#define TIMEUNBLOCK 2
#define TIMEBEGIN 3

//ʱ�����б���
#define NORMAL 1
#define DOUBLE 2

INT TIMESTATE;//�����ж�ʱ��״̬
INT TIMERECORDSTATE = NOTBEGIN;
INT TIMES = 1;//���ڵ���ʱ������

INT TIME = 0;//ʵ���ϵ���Ϸ�ڽ���ʱ��
INT BTIME = 0;//���ڼ�¼����ʱ��

INT MINUTE;
INT HOUR;
INT DAY = 1;
INT YEAR = 1;


void BEGINTIMECHECK() {
	BEGIN = clock() / CLOCKS_PER_SEC;
	TIMESTATE = TIMEUNBLOCK;
	TIMERECORDSTATE = TIMEBEGIN;
}//��Ϸ��ʽ��ʼ����֮����Ϊʱ��Ļ���ֵ,�趨ʱ��״̬Ϊ��������״̬

void TIMECHECK() {
	NOW = clock() / CLOCKS_PER_SEC;
}//��ȡ��ǰϵͳʱ��

void BLOCKTIME() {
	STOPTIME = NOW / CLOCKS_PER_SEC;
	TIMESTATE = TIMEBLOCK;
}//��������ʱ�䣬�趨ʱ������״̬Ϊʱ������״̬

void STOPOVER() {
	TIMESTATE = TIMEUNBLOCK;
}//ʱ����������,״̬�ص�(�¼��������ʱ����)



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
}//ʱ������ϵͳ,ѭ����ϵ����ѭ��

void TRANSLATETIME() {
	MINUTE = TIME % 60;
	HOUR = ((TIME / 60) + 8) % 24;//��һ��Ӱ˵㿪ʼ,24Сʱ��
	DAY = 1 + (((TIME / 60) + 8) / 24) % 4;
	YEAR = 1 + (((TIME / 60) + 8) / 24) / 4;
}//ʱ�任��
#endif