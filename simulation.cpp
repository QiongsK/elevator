//����ģ��ʵ���ļ�
#include "simulation.h"
namespace simulationTianyu {

	int character_random_mumber() {
		int i=1;
		while (i) {
			srand((int)time(0));
			i= rand();
			if(i>20)
				return i;
		}
	}

	void random_now_floor(character* cha,
		default_random_engine e,
		unsigned u) {
		cha->nowfloor=u;
		return;
	}

	void random_aim_floor(character* cha,
		default_random_engine e,
		unsigned u) {
		cha->aimfloor = u;
		return;
	}

	void random_weight(character* cha,
		default_random_engine e,
		unsigned q) {
		double p = q / 10 + 0.5;
		cha->weight= 120 * p + 30;
	}

	//����������أ����Ӿ��ȷֲ�

	int character_random_aim_floor(int h) {
		int i = 1;
		while (i) {
			srand((int)time(0));
			i = rand() % h + 1;
			if (i != h)
				return i;
		}
		
	}

	void random_distribution(character* cha,
		default_random_engine e,
		bool b) {
		cha->whetherdistrbution = b;
	}


}//simulationTianyu
