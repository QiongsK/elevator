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
//������    // 
//////////////
void get_important_data(istream&);//��ȡ��������

void elevetor_list_pointer_array(int);//�������ݱ�

void floor_list_pointer_array(int h);

void character_chart_pointer_array();

void random_inicial_character();//��ʼ���˿�

void random_character(character* cha);//������ɳ˿�Ŀ��¥��

void check_distribute_character();//��������;

void set_node();//���������õ�ͷָ���ʼ��

void characterthread();//�˿��߳�

void upload_floorstate();

////////////
//ȫ�ֱ�����  //
////////////

int num_character;//�˿�����

int num_elevator;//��������

int waitingtime;//���ݵȴ�ʱ��

int DRCHARACTER::downcnt = 0;

int URCHARACTER::upcnt = 0;

PURCHARACTER puhead[20],bufpu=new URCHARACTER;//��ͷ,���������ʼ��

PURCHARACTER suhead[20] ;//���ڱ��������node

PDRCHARACTER pdhead[20],bufpd=new DRCHARACTER;//��ͷ�����������ʼ��

PDRCHARACTER sdhead[20] ;//���ڱ��������node

PBUF pbuf=new BUF;//��¼ͷָ��λ�ã���װ�س˿͵�ʱ���Զ�ɾ����

PBUF pbufend=new BUF;//������β��
//�������ԣ������ֱ�ӷ����ַ�����Բ��õ��Ļ��п�ָ�����.

character** CHART characterchart;//�˿ͱ�ָ�������봫��

base_elevator** CHART elevetor_ptr_array;//���ݱ�

base_floor** CHART floor_ptr_array;//¥���

default_random_engine e{ (unsigned int)time(0) };//����

uniform_int_distribution<unsigned> u(0, 19);//���ȷֲ���¥�����

normal_distribution<double> q(0, 1);//��׼��̬�ֲ�

bernoulli_distribution b(0.1);//��Ŭ���ֲ�

bernoulli_distribution bb(0.5);

//////////
//״̬��// 
/////////
int STATE floorstate[20] = { WONDER_NO };//¥��״̬����

////////////////////// 
//״̬ˢ�º�����     //
/////////////////////
int main() {
	//��������
	ofstream outfile;
	outfile.open("elevator.txt");
	get_important_data(std::cin);
	elevetor_list_pointer_array(num_elevator);
	floor_list_pointer_array(20);
	set_node();
	random_inicial_character();
	check_distribute_character();

	//¥�㣬�˿ͣ�����,�ڵ���Ѿ���ʼ��
	
	//ǰ��׼����������ʼ��ѭ���ɣ�
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
			outfile <<"��ʼ¥��"<< characterchart[i]->nowfloor << " "
				<<"Ŀ��¥��"<< characterchart[i]->aimfloor;
			if (bb(e)&&characterchart[i]->nowfloor<3)
				outfile << "������" << endl;
			else
				outfile << "δ�ڵ�����" << endl;
		}
		outfile << "=====================" << endl;
		outfile << "=====================" << endl;
		if (TIME >= waitingtime) {
			cout << "���н���" << endl;
			break;
		}

	}

	return 0;
	


	
}


void get_important_data(istream& in) {
	cout << "����˿�����" << endl;
	in >> num_character;//�˿�
	cout << "�����������" << endl;
	in >> num_elevator;//��������
	cout << "����ȴ�ʱ��" << endl;
	in >> waitingtime;//�ȴ�ʱ��
}
	//��ȡһ��������Ϊ¥��ĸ߶�
void floor_list_pointer_array(int h) {
	floor_ptr_array = new base_floor * [20];//20�㵱ǰ
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

	//��ȡһ��������Ϊ���ݵĸ���
void elevetor_list_pointer_array(int m) {
	elevetor_ptr_array = new base_elevator * [num_elevator];//����һ���洢����ָ��Ķ�̬����
	for (int i = 0; i < num_elevator; i++) {
		elevetor_ptr_array[i] = new base_elevator(waitingtime);
	}
}
void random_inicial_character() {
	character_chart_pointer_array();
	for (int i = 0; i < num_character; i++) {
		do {
			random_weight(characterchart[i], e, q(e));//��������
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