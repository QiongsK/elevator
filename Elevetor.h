//������
//��һ�����ϵĺ�������һ���̺߳���
//SCAN-EDF
#include<iostream>
#include<string>
#include"building.h"
#ifndef EVELETOR_H
#define ECELETOR_H
using namespace characterTianyu;
namespace elevetorTianyu {
	using namespace std;
	//�����ͣ����ݡ�����˽�г�Ա�����ݱ�ţ����ݳ���,�ȴ�ʱ�䡣
	//���ݱ������ݳ���ֻ�ܳ�ʼ�����裬�������޸�
	//����ʹ��get����������ȡ��ֵ
	//TODO ˽�г�Ա �����ٶ�
	class base_elevator {
	public:
		base_elevator(int);
		~base_elevator();
		int get_code() const;
		int get_bearing() const;
		int get_waiting_time();
		//�������к���
		int  get_weightcnt();
		/*void set_weightcnt(PURCHARACTER);//���ϵ��ݵĳ˿�������ӵ�������
		void set_weightcnt(PDRCHARACTER);//���أ���¥��
		��������
		*/
		int  get_nowfloor();//��ȡ��ǰ����¥��
		void upload_aimfloorarray(character*);//����Ŀ��¥���б�
		int  get_characteraimfloor(character*);//���ڼ��ͻ�ȡ¥���г˿�Ŀ��¥��
		void set_nowfloor();//��������״̬�޸ĵ�������¥��



		//�ж���
		bool check_offelevator();//��⵱ǰ¥���Ƿ�����Ҫ��¥
		bool check_weightstate();//����Ƿ�������
		bool check_nowfloorstate(int []);//��ȡ¥��״̬����鵱ǰ¥���Ƿ�����Ҫ��¥��
		bool check_whetherhaveaimfloor();//��鵱ǰ��������Ŀ��¥��
		bool check_whetherhavewonderfloor(int []);//��鵱ǰ�����Ƿ�������¥��
		bool check_characterweight(PURCHARACTER);//��������Ƿ�����ϵ��ݣ���¥
		bool check_characterweight(PDRCHARACTER);//��������Ƿ�����ϵ��ݣ���¥


		//״̬��
		void STATE runstate_change(int[]);//����״̬�ı�
		void STATE fillstate_change();//�洢״̬�任
		void STATE state_comeback();//״̬�ص�,�������ʱ
		void STATE run_duty(PURCHARACTER*, PDRCHARACTER*, PBUF*,PBUF*);//��������

		//���ݽ�������
		void load_characterup(PURCHARACTER*, PBUF*,PBUF*);//װ����¥�ĳ˿�
		void load_characterdown(PDRCHARACTER*, PBUF*,PBUF*);//װ����¥�ĳ˿�
		void off_character();//�Ƴ��˿�,������¥
		//�ı�˿�״̬���������

		

	private:
		//number of elevators
		//every time create a new docker(elevator),this element will plus one.
		static int num;
		//always depend on the num.
		const int code;
		const int bearing=1500;//������λ��kg
		const int height = 20;
		int waiting_time;//�ȴ�ʱ��
		int defaultfloor = 0;//Ĭ��¥��
		int nowfloor;//��ǰ¥��߶�
		int weightcnt;//��������
		int* cnt;//������������
		int STATE lastrunstate;//��¼��һ��״̬
		int STATE runstate;//����ʱ״̬Ԫ��
		int STATE duty;//����״̬
		int STATE weightstate;//��������״̬Ԫ��
		bool aimfloorarray[20] = {false};//Ŀ��¥������
		//�ɸߵ���
		character*** characterinelevator;//��̬��ά����洢�˿ͣ������г�ʼ����
		//�ݶ�¥��߶�Ϊ20��

		
		/*protected:
			int initial_floor;*/
	};

	void elevatorthread(base_elevator* elevator,
		int floorstate[],
		PURCHARACTER pur[],
		PDRCHARACTER pdr[],
		PBUF* pbuf,
		PBUF* pend);//�߳�
	



}//elevetorTianyu






#endif
