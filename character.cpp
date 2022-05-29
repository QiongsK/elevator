#include "character.h"
namespace characterTianyu {
	bool check_aimfloorlegal(character* pcha) {
		if (pcha->aimfloor != pcha->nowfloor)
			return true;
		else
			return false;
	}

	int  get_direction(character* pcha) {
		if (pcha->aimfloor > pcha->nowfloor)
			return UP;
		else if (pcha->aimfloor < pcha->nowfloor)
			return DOWN;
	}

	void add_aimfloortoready(character* cha, PURCHARACTER* shead, PURCHARACTER* head) {
		PURCHARACTER next = new URCHARACTER;
		if (next) {
			next->cha = cha;
			if ((*head)->next == NULL) {
				(*head)->next = next;
			}
			else {
				(*shead)->next = next;
			}
			(*shead) = next;
			(*shead)->next = NULL;
			//salute
			(*head)->upcnt++;
			cha->readystate = ELEVATER_YES;
		}
		else {
			cout << "�˿�ͷ�ļ��ĳ˿�װ�ص�׼����������������";
			system("pause");
			exit(1);
		}
	}
	
	void add_aimfloortoready(character* cha, PDRCHARACTER* shead, PDRCHARACTER* head) {
		PDRCHARACTER next = new DRCHARACTER;
		if (next) {
			next->cha = cha;
			if ((*head)->next == NULL) {
				(*head)->next = next;
			}
			else {
				(*shead)->next = next;
			}
			(*shead) = next;
			(*shead)->next = NULL;
			//salute
			(*head)->downcnt++;
			cha->readystate = ELEVATER_YES;
		}
		else {
			cout << "�˿�ͷ�ļ��ĳ˿�װ�ص�׼����������������";
			system("pause");
			exit(1);
		}

	}

	void characterstate_change(character* cha) {
		switch (cha->locationstate) {
		case ELEVATER_ON:
			cha->readystate = DEFAULT;
			cha->whetherdistrbution = false;
			break;
		case ELEVATER_OFF:
			switch (cha->readystate) {
			case ELEVATER_YES:
				cha->whetherdistrbution = false;
				break;
			case ELEVATER_NO:
				//����˵�����ڵȴ�������䣬�����Ѿ��������ȴ�װ�ء�
				//�����߳������ˡ�
				cha->direction = DEFAULT;
				cha->readystate = DEFAULT;//�ȴ���������װ��
				break;
			}

		}
	}
	

//�ȴ�����Ϊ�߳��ˡ�
}
