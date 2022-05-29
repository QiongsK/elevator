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
			cout << "乘客头文件的乘客装载到准备区函数出现问题";
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
			cout << "乘客头文件的乘客装载到准备区函数出现问题";
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
				//这里说明正在等待随机分配，或者已经随机分配等待装载。
				//这是线程任务了。
				cha->direction = DEFAULT;
				cha->readystate = DEFAULT;//等待随机分配和装载
				break;
			}

		}
	}
	

//等待整合为线程了。
}
