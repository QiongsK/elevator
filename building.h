//����¥��Ŀ�
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
		int  STATE get_state();//����״̬�����ڸ���¥��״̬����
		void STATE set_state(int);

	protected://�޸�Ϊ�м�ȼ�����������̳к͵����������
		int hight;//�����¥���ǵڼ���

		//character** rest;//һ��ָ�����飬�洢����Ϣ���ĳ˿͵Ľṹ���ָ��
		//�����Ҫ��Ҫ��Ӵ�����������

		int STATE state;//״̬

	};

	enum function{workspace,rastaurant,null};//�ݶ����������
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
		base_floor* floor);//״̬��,�ı�¥��״̬.

}








#endif