//����ģ�⻷���Ľӿ��ļ�
#include <ctime>
#include <cstdlib>
#include <random>
#include "Elevetor.h"
#ifndef SIMULATION_H
#define SIMULATION_H
using namespace elevetorTianyu;
using namespace std;
namespace simulationTianyu {

	int character_random_weight();
	//��һ�棬����һ�������һ���˿�������

	int character_random_aim_floor(int);
	//����¥��߶�

	void random_now_floor(character* cha, 
		default_random_engine e,
		unsigned u);

	void random_aim_floor(character* cha,
		default_random_engine e,
		unsigned u);
	//�������¥�㣬���Ӿ��ȷֲ���

	void random_weight(character* cha,
		default_random_engine e,
		unsigned q);
	//����������أ�������̬�ֲ�

	void random_distribution(character* cha,
		default_random_engine e,
		bool b);
	//��������Ƿ�����״̬.





}//simulationTianyu
//��̬�ֲ����Դ���
/*		double max1 = 0;
		double min1 = 1;
		int min2 = 150;
		int max2 = 30;
		int X = 120 * (q(e) / 10 + 0.5) + 30;//������̬�ֲ�������,�ò��ϱ仯
		cout << pbuf->dhead << endl;
		cout << pbuf->uhead << endl;
		cout << pbuf->bufferlength << endl;
		
		for (int i = 0; i < 1000000; i++) {
			double p = q(e) / 10 + 0.5;
			max1 = max(p, max1);
			min1 = min(p, min1);
			int X = 120 * p + 30;
			min2 = min(X, min2);
			max2 = max(X, max2);
			//cout << X<<endl;

		}
		cout << max1 << endl;
		cout << min1 << endl;
		cout << max2 << endl << min2 << endl;
		return 0;*/

#endif 
