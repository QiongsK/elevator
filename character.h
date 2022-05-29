//�˿����Կ�
//�ȴ�������Ϊ�߳�
#include "state.h"
#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H
using namespace std;
namespace characterTianyu {
	struct character {
		int  weight;//�˿�����
		int  nowfloor;//��ǰλ��
		int  aimfloor;//Ŀ��¥��
		//ʩ����
		int  STATE direction;//����
		int  STATE readystate;//�Ƿ�ready״̬
		int  STATE locationstate;//����λ��״̬
		bool STATE whetherdistrbution;//�Ƿ��������,���ֳ�ʼ��Ϊ�棬֮���������
		int  code;//the number used to identify.
		//ʩ�������
		//int token
	};

	//���ϳ˿���
	typedef struct UPreadycharacter {
		UPreadycharacter* next;//ָ���¸��˿�
		UPreadycharacter* last;//ָ���ϸ��˿�
		static int upcnt;//������
		struct character* cha;

	}URCHARACTER, *PURCHARACTER;



	//���³˿���
	typedef struct DOWNreadycharacter {
		DOWNreadycharacter* next;//ָ���¸��˿�
		DOWNreadycharacter* last;//ָ���ϸ��˿�
		static int downcnt;//������
		struct character* cha;

	}DRCHARACTER, *PDRCHARACTER;
	
	

	//�˿����ݻ�����
	typedef struct buffer {
		PURCHARACTER uhead;
		PDRCHARACTER dhead;
		int bufferlength;//���峤�ȣ��ǵó�ʼ��
	}BUF,*PBUF;


	bool check_aimfloorlegal(character* );//���Ŀ��¥���Ƿ�Ϸ�����û������ͬʱ���䵽��Ӧ���С�

	int  get_direction(character* );//��ȡ�ͷ��ط���

	void add_aimfloortoready(character* cha, PURCHARACTER* shead, PURCHARACTER* head);//��¥�˿���

	void add_aimfloortoready(character* cha, PDRCHARACTER* shead,PDRCHARACTER* head);//��¥�˿���

	void STATE characterstate_change(character* cha);//���ڳ˿ͱ�״̬ת��

	


		//��״̬��������ֻ���޸Ĳ���״̬����ÿһ�ν������е�ʱ��������
		//����״̬�޸�ʵ���ϵ��ݵ�ʱ�����ġ�

}


#endif