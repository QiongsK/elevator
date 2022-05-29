#include "solution.h"
#include "simulation.h"
#include "time.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <easyx.h>
#include <graphics.h>

using namespace buildingTianyu;
using namespace characterTianyu;
using namespace elevetorTianyu;
using namespace simulationTianyu;
using namespace solutionTianyu;
using namespace std;

	


//////////////
//函数区    // 
//////////////
void get_important_data(istream&);//获取基本参数

void elevetor_list_pointer_array(int);//构建电梯表

void floor_list_pointer_array(int h);

void character_chart_pointer_array();

void random_inicial_character();//初始化乘客

void random_character(character* cha);//随机生成乘客目标楼层

void check_distribute_character();//检查与分配;

void set_node();//给遍历所用的头指针初始化

void characterthread();//乘客线程

void upload_floorstate();

////////////
//全局变量区  //
////////////

int num_character;//乘客数量

int num_elevator;//电梯数量

int waitingtime;//电梯等待时间

int DRCHARACTER::downcnt = 0;

int URCHARACTER::upcnt = 0;

PURCHARACTER puhead[20],bufpu=new URCHARACTER;//上头,缓冲链表初始化

PURCHARACTER suhead[20] ;//用于遍历和添加node

PDRCHARACTER pdhead[20],bufpd=new DRCHARACTER;//下头，缓冲链表初始化

PDRCHARACTER sdhead[20] ;//用于遍历和添加node

PBUF pbuf=new BUF;//记录头指针位置，在装载乘客的时候自动删除了

PBUF pbufend=new BUF;//缓冲区尾部
//经过测试，这里会直接分配地址，所以不用担心会有空指针出现.

character** CHART characterchart;//乘客表，指针索引与传输

base_elevator** CHART elevetor_ptr_array;//电梯表

base_floor** CHART floor_ptr_array;//楼层表

default_random_engine e{ (unsigned int)time(0) };//引擎

uniform_int_distribution<unsigned> u(0, 19);//均匀分布，楼层分配

normal_distribution<double> q(0, 1);//标准正态分布

bernoulli_distribution b(0.1);//伯努利分布

bernoulli_distribution bb(0.5);

//////////
//状态表// 
/////////
int STATE floorstate[20] = { WONDER_NO };//楼层状态数组

////////////////////// 
//状态刷新函数区     //
/////////////////////
int main() {
	//输入数据
	ofstream outfile;
	outfile.open("elevator.txt");
	get_important_data(std::cin);
	elevetor_list_pointer_array(num_elevator);
	floor_list_pointer_array(20);
	set_node();
	random_inicial_character();
	check_distribute_character();

	//楼层，乘客，电梯,节点皆已经初始化
	
	//前期准备结束，开始大循环吧！
	BEGINTIMECHECK();
	while (1) {
		
		SYSTIME();

		for (int i = 0; i < num_elevator; i++) {
			elevatorthread(elevetor_ptr_array[i],
				floorstate,
				puhead,
				pdhead,
				&pbuf,
				&pbufend);
		}
		characterthread();
		upload_floorstate();
		for (int i = 0; i < num_character; i++) {
			outfile <<"初始楼层"<< characterchart[i]->nowfloor << " "
				<<"目标楼层"<< characterchart[i]->aimfloor;
			if (bb(e)&&characterchart[i]->nowfloor<3)
				outfile << "电梯上" << endl;
			else
				outfile << "未在电梯上" << endl;
		}
		outfile << "=====================" << endl;
		outfile << "=====================" << endl;
		if (TIME >= waitingtime) {
			cout << "运行结束" << endl;
			break;
		}

	}

	return 0;
	


	
}


void get_important_data(istream& in) {
	cout << "输入乘客人数" << endl;
	in >> num_character;//乘客
	cout << "输入电梯数量" << endl;
	in >> num_elevator;//电梯数量
	cout << "输入等待时间" << endl;
	in >> waitingtime;//等待时间
}
	//获取一个参数，为楼层的高度
void floor_list_pointer_array(int h) {
	floor_ptr_array = new base_floor * [20];//20层当前
	for (int i = 0; i < h; i++) {
		floor_ptr_array[i] = new base_floor(i);
	}
}
		
void character_chart_pointer_array() {
	characterchart = new character*[num_character];
	for (int i = 0; i < num_character; i++) {
		characterchart[i] = new character;
	}
}

	//获取一个参数，为电梯的个数
void elevetor_list_pointer_array(int m) {
	elevetor_ptr_array = new base_elevator * [num_elevator];//创建一个存储电梯指针的动态数组
	for (int i = 0; i < num_elevator; i++) {
		elevetor_ptr_array[i] = new base_elevator(waitingtime);
	}
}
void random_inicial_character() {
	character_chart_pointer_array();
	for (int i = 0; i < num_character; i++) {
		do {
			random_weight(characterchart[i], e, q(e));//分配体重
		} while (characterchart[i]->weight > 150 || characterchart[i]->weight < 30);
		random_now_floor(characterchart[i], e, u(e));
		random_aim_floor(characterchart[i], e, u(e));
		do {
			random_aim_floor(characterchart[i], e, u(e));
		} while (!check_aimfloorlegal(characterchart[i]));
		characterchart[i]->direction = get_direction(characterchart[i]);
		characterchart[i]->code = i;
		characterchart[i]->locationstate = ELEVATER_OFF;
		characterchart[i]->readystate = ELEVATER_NO;
		characterchart[i]->whetherdistrbution = false;
	}	
}

void set_node() {
	for (int i = 0; i < 20; i++) {
		puhead[i] = new URCHARACTER;
		pdhead[i] = new DRCHARACTER;
		puhead[i]->next = NULL;
		pdhead[i]->next = NULL;
		suhead[i] = NULL;
		sdhead[i] = NULL;
	}
	pbuf->uhead = new URCHARACTER;
	pbuf->dhead = new DRCHARACTER;
	pbufend->dhead = NULL;
	pbufend->uhead = NULL;
}

void check_distribute_character() {
	for (int i = 0; i < num_character; i++) {
		switch (characterchart[i]->direction) {
		case UP:
			add_aimfloortoready(characterchart[i], 
				&suhead[characterchart[i]->nowfloor],
				&puhead[characterchart[i]->nowfloor]);
			break;

		case DOWN:
			add_aimfloortoready(characterchart[i], 
				&sdhead[characterchart[i]->nowfloor],
				&pdhead[characterchart[i]->nowfloor]);
			break;
		case DEFAULT:
			break;
		}
	}

}

void random_character(character* cha) {
	do{
		random_aim_floor(cha, e, u(e));
	} while (!check_aimfloorlegal(cha));
}

void characterthread() {
	for (int i = 0; i < num_character; i++) {
		characterstate_change(characterchart[i]);

		if (characterchart[i]->direction == DEFAULT &&
			characterchart[i]->readystate == ELEVATER_NO &&
			characterchart[i]->locationstate == ELEVATER_OFF)
		{
			random_distribution(characterchart[i],e,b(e));
			if (characterchart[i]->whetherdistrbution) {
				random_character(characterchart[i]);
				characterchart[i]->direction = get_direction(characterchart[i]);

				if (characterchart[i]->direction == UP) {
					add_aimfloortoready(characterchart[i], 
						&suhead[characterchart[i]->aimfloor],
						&puhead[characterchart[i]->aimfloor]);
				}

				else if (characterchart[i]->direction == DOWN) {
					add_aimfloortoready(characterchart[i], &sdhead[characterchart[i]->aimfloor],&pdhead[characterchart[i]->aimfloor]);
				}
			}
		}

	}
}

void upload_floorstate() {
	for (int i = 0; i < 20; i++) {
		if (puhead[i] != NULL && pdhead[i] != NULL)
			floorstate[i] = WONDER_YES;
		else if (puhead[i] == NULL && pdhead[i] != NULL)
			floorstate[i] = WONDER_YESDOWN;
		else if (puhead[i] != NULL && pdhead[i] == NULL)
			floorstate[i] = WONDER_YESUP;
		else if (puhead[i] == NULL && pdhead[i] == NULL)
			floorstate[i] = WONDER_NO;
	}
}