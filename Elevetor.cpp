#include "Elevetor.h"
#include <iostream>
#include <cstdlib>
namespace elevetorTianyu{
	int base_elevator::num = 1;//静态参数初始化

	base_elevator::base_elevator(int WAITTIME):
	waiting_time(WAITTIME),code(num)
	{
		nowfloor = 0;
		weightcnt = 0;
		runstate = UP;
		weightstate = FULLFILL_NO;
		duty = DEFAULT;
		characterinelevator = new character**[height];
		cnt = new int[height];
		for (int i = 0; i < height; i++) {
			cnt[i] = 0;
			characterinelevator[i] = new character*[1];//真正存储的地方乘客的地方
		}
		num++;	
	}
	
	base_elevator::~base_elevator() {
		for (int i = 0; i < height; i++) {
			delete[] characterinelevator[i];
		}
		delete[] characterinelevator;
	}

	int base_elevator::get_code() const {
		return code;
	}

	int base_elevator::get_bearing() const {
		return bearing;
	}

	int base_elevator::get_waiting_time() {
		return waiting_time;
	}

	int base_elevator::get_weightcnt(){
		return weightcnt;
	}

	/*void base_elevator::set_weightcnt(PURCHARACTER PRCHA){
		weightcnt += PRCHA->cha->weight;
	}//修改体重

	void base_elevator::set_weightcnt(PDRCHARACTER PRCHA) {
		weightcnt += PRCHA->cha->weight;
	}修改
	*/

	int base_elevator::get_nowfloor(){
		return nowfloor;
	}

	void base_elevator::set_nowfloor(){
		switch (runstate) {
		case UP:
			nowfloor++;
			break;
		case DOWN:
			nowfloor--;
			break;
		case DUTY:
		case DUTYON:
		case DUTYOFF:
			break;
		case DEFAULT:
			if (nowfloor != 0&&nowfloor>0) {
				nowfloor--;
			}
			break;
		}
		return;
	}


	void base_elevator::upload_aimfloorarray(character* cha){
		aimfloorarray[get_characteraimfloor(cha)-1] = true;
		return;
	}

	int base_elevator::get_characteraimfloor(character* cha) {
		return cha->aimfloor;
	}



	bool base_elevator::check_offelevator() {
		if (aimfloorarray[nowfloor])
			return true;
		else
			return false;
	}

	bool base_elevator::check_weightstate() {
		switch (weightstate) {
		case FULLFILL_YES:
			return true;
			break;
		case FULLFILL_NO:
			return false;
			break;
		}
	}


	bool base_elevator::check_nowfloorstate(int floor []) {
		if (floor[nowfloor] == WONDER_YES)
			return true;
		else if (floor[nowfloor] == WONDER_YESUP && runstate == UP)
			return true;
		else if (floor[nowfloor] == WONDER_YESDOWN && runstate == DOWN)
			return true;
		else
			return false;
	}
	
	bool base_elevator::check_whetherhaveaimfloor() {
		switch (runstate) {
		case UP:
			for (int i = nowfloor+1; i < height; i++) {
				if (aimfloorarray[i])
					return aimfloorarray[i];
			}
			return false;
			break;
		case DOWN:
			for (int i = nowfloor - 1; i >= 0; i--) {
				if (aimfloorarray[i])
					return aimfloorarray[i];
			}
			return false;
			break;
		case DEFAULT:
			return false;
			break;
		}
	}

	bool base_elevator::check_whetherhavewonderfloor(int floor[]) {
		switch (runstate) {
		case UP:
			for (int i = nowfloor + 1; i < height; i++) {
				if (floor[i]==WONDER_YES)
					return true;
			}
			return false;
			break;
		case DOWN:
			for (int i = nowfloor - 1; i >= 0; i--) {
				if (floor[i])
					return true;
			}
			return false;
			break;
		case DEFAULT:
			return false;
			break;
		}
	}



	void base_elevator::fillstate_change() {
		if (weightcnt == bearing) {
			weightstate = FULLFILL_YES;
		}
		else{
			weightstate = FULLFILL_NO;
		}
		return;
	}

	void base_elevator::state_comeback() {
		if (runstate == DUTY) {
			runstate = lastrunstate;
			duty = DEFAULT;
		}
		else if (runstate == DEFAULT)
			return;
		return;
	}

	bool base_elevator::check_characterweight(PURCHARACTER pur) {
		int nowweight = weightcnt;
		if (pur->cha->weight + nowweight > bearing) {

			return false;
		}
		else if (pur->cha->weight + nowweight <= bearing) {
			return true;
		}
		else {
			cout << "wrong state" << endl;
			system("pause");
			exit(1);
		}
	}

	bool base_elevator::check_characterweight(PDRCHARACTER pur) {
		int nowweight = weightcnt;
		if (pur->cha->weight + nowweight > bearing) {

			return false;
		}
		else if (pur->cha->weight + nowweight <= bearing) {
			return true;
		}
		else {
			cout << "wrong state" << endl;
			system("pause");
			exit(1);
		}
	}

	void base_elevator::runstate_change(int floorstate[]) {
		//传入楼层数组
		if (check_offelevator()) {
			//有人下电梯
			//存储原本运行方向，改变当前运行状态
			lastrunstate = runstate;
			duty = DUTYOFF;
			if (check_nowfloorstate(floorstate)) {
				//有人上，存储状态，修改运行状态
				duty = DUTY;	
			}
		}
		else {
			//没人下电梯
			if (check_weightstate()) {
				//人满，状态不变
				lastrunstate = runstate;
				return;
			}
			else {
				//人不满，检查有无人上电梯
				if (check_nowfloorstate(floorstate)) {
					//有人上，存储状态，修改运行状态
					lastrunstate = runstate;
					duty = DUTYON;
				}
				else {
					//没人上电梯,检查当前方向有无目标楼层
					if (check_whetherhaveaimfloor()) {
						return;
					}
					else {
						//当前方向没有目标楼层，检查当前方向是否有需求
						if (check_whetherhavewonderfloor(floorstate)) {
							//有，方向不变，状态不变
							return;
						}
						else {
							//没有，改方向吧
							switch (runstate) {
							case UP:
								runstate = DOWN;
								return;
								break;
							case DOWN:
								runstate = UP;
								return;
								break;
							}
							if (check_whetherhaveaimfloor())
								return;
							else
								if (check_whetherhavewonderfloor(floorstate))
									return;
								else
									runstate = DEFAULT;
						}
					}
				}
			}
		}
		
		
	}

	void base_elevator::load_characterup(PURCHARACTER* head,PBUF* buf,PBUF* pend){
		//cnt=0时，无法分配正确长度的old数组，因此要分为两部分组成
		if (cnt[nowfloor] >= 0) {
			character** old = new character * [cnt[nowfloor]];

			(*buf)->uhead->next = NULL;
			if (*head == NULL) {
				cout << "装载乘客（up）函数指针出现问题" << endl;
				system("pause");
				exit(1);
			}
			for (int i = 0; i < cnt[nowfloor]; i++) {
				old[i] = characterinelevator[nowfloor][i];
			}
			while ((*head)->next != NULL) {
				if (check_characterweight((*head)->next)) {
					(*head)->next->cha->locationstate;
					(*head)->upcnt--;
					if ((*buf)->uhead == NULL) {
						(*buf)->uhead = (*head)->next;
						(*buf)->uhead->cha = (*head)->next->cha;
					}
					else {
						(*pend)->uhead = (*head)->next;
						(*pend)->uhead->cha = (*head)->next->cha;
					}
					(*pend)->uhead = (*head)->next;
					(*buf)->bufferlength++;
					cnt[nowfloor]++;
					
					weightcnt+=(*head)->next->cha->weight;
					(*head) = (*head)->next;//乘客组删除首节点
				}
				else
				{
					(*pend)->uhead->next = NULL;//到头了,刚好就重置了，又变空了
					break;//目前只实现超重了就走，没实现越位检查
				}
			}

			

			characterinelevator[nowfloor] = new character * [cnt[nowfloor]];
			for (int i = 0; i < cnt[nowfloor]; i++) {
				characterinelevator[nowfloor][i] = old[i];
			}

			for (int i = cnt[nowfloor]; (*buf)->uhead->next != NULL; i++) {
				characterinelevator[nowfloor][i] = (*buf)->uhead->cha;
				characterinelevator[nowfloor][i]->locationstate = ELEVATER_ON;
				upload_aimfloorarray((*buf)->uhead->cha);
				(*buf)->uhead = (*buf)->uhead->next;
				
			}
			(*buf)->bufferlength = 0;//重置
			delete[] old;
		}
		else if (cnt[nowfloor] == 0) {
			(*buf)->uhead->next = NULL;
			if (*head == NULL) {
				cout << "装载乘客（up）函数指针出现问题" << endl;
				system("pause");
				exit(1);
			}
			while ((*head)->next != NULL) {
				if (check_characterweight((*head)->next)) {
					(*head)->upcnt--;
					if ((*buf)->uhead == NULL) {
						(*buf)->uhead = (*head)->next;
						(*buf)->uhead->cha = (*head)->next->cha;
					}
					else {
						(*pend)->uhead = (*head)->next;
						(*pend)->uhead->cha = (*head)->next->cha;
					}
					(*pend)->uhead = (*head)->next;
					(*buf)->bufferlength++;
					cnt[nowfloor]++;
					//
					weightcnt += (*head)->next->cha->weight;
					(*head) = (*head)->next;//乘客组删除首节点
				}
				else
				{
					(*pend)->uhead->next = NULL;//到头了,刚好就重置了，又变空了
					break;//目前只实现超重了就走，没实现越位检查
				}
			}
			for (int i = cnt[nowfloor]; (*buf)->uhead->next != NULL; i++) {
				characterinelevator[nowfloor][i] = (*buf)->uhead->cha;
				characterinelevator[nowfloor][i]->locationstate = ELEVATER_ON;
				upload_aimfloorarray((*buf)->uhead->cha);
				(*buf)->uhead = (*buf)->uhead->next;
			}
		
			(*buf)->bufferlength = 0;//重置
		}
	}

	void base_elevator::load_characterdown(PDRCHARACTER* head, PBUF* buf,PBUF *pend) {
		//cnt=0时，无法分配正确长度的old数组，因此要分为两部分组成
		if (cnt[nowfloor] >= 0) {
			character** old = new character * [cnt[nowfloor]];

			(*buf)->dhead->next = NULL;
			if (*head == NULL) {
				cout << "装载乘客（up）函数指针出现问题" << endl;
				system("pause");
				exit(1);
			}

			for (int i = 0; i < cnt[nowfloor]; i++) {
				old[i] = characterinelevator[nowfloor][i];
			}

			while ((*head)->next != NULL) {
				if (check_characterweight((*head)->next)) {
					(*head)->downcnt--;
					if ((*buf)->dhead == NULL) {
						(*buf)->dhead = (*head)->next;
						(*buf)->dhead->cha = (*head)->next->cha;
					}
					else {
						(*pend)->dhead = (*head)->next;
						(*pend)->dhead->cha = (*head)->next->cha;
					}
					(*pend)->dhead = (*head)->next;
					(*buf)->bufferlength++;
					//
					weightcnt += (*head)->next->cha->weight;
					(*head) = (*head)->next;//乘客组删除首节点
				}
				else
				{
					(*pend)->dhead->next = NULL;//到头了,刚好就重置了，又变空了
					break;//目前只实现超重了就走，没实现越位检查
				}
			}

			

			characterinelevator[nowfloor] = new character * [(*buf)->bufferlength + cnt[nowfloor]];
			for (int i = 0; i < cnt[nowfloor]; i++) {
				characterinelevator[nowfloor][i] = old[i];
			}

			for (int i = cnt[nowfloor]; (*buf)->dhead->next != NULL; i++) {
				characterinelevator[nowfloor][i] = (*buf)->dhead->cha;
				characterinelevator[nowfloor][i]->locationstate = ELEVATER_ON;
				upload_aimfloorarray((*buf)->dhead->cha);
				(*buf)->dhead = (*buf)->dhead->next;
			}
			(*buf)->bufferlength = 0;//重置
			delete[] old;
		}
		else if (cnt[nowfloor] == 0) {
			(*buf)->dhead->next = NULL;
			if (*head == NULL) {
				cout << "装载乘客（up）函数指针出现问题" << endl;
				system("pause");
				exit(1);
			}
			while ((*head)->next != NULL) {
				if (check_characterweight((*head)->next)) {
					(*head)->downcnt--;
					if ((*buf)->dhead == NULL) {
						(*buf)->dhead = (*head)->next;
						(*buf)->dhead->cha = (*head)->next->cha;
					}
					else {
						(*pend)->dhead = (*head)->next;
						(*pend)->dhead->cha = (*head)->next->cha;
					}
					(*pend)->dhead = (*head)->next;
					(*buf)->bufferlength++;
					cnt[nowfloor]++;
					//
					weightcnt += (*head)->next->cha->weight;
					(*head) = (*head)->next;//乘客组删除首节点
				}
				else
				{
					(*pend)->dhead->next = NULL;//到头了,刚好就重置了，又变空了
					break;//目前只实现超重了就走，没实现越位检查
				}
			}
			for (int i = cnt[nowfloor]; (i < cnt[nowfloor] + (*buf)->bufferlength) && (*buf)->dhead->next != NULL; i++) {
				characterinelevator[nowfloor][i] = (*buf)->dhead->cha;
				characterinelevator[nowfloor][i]->locationstate = ELEVATER_ON;
				upload_aimfloorarray((*buf)->dhead->cha);
				(*buf)->dhead = (*buf)->dhead->next;
			}
			(*buf)->bufferlength = 0;//重置
		}
	}

	void base_elevator::off_character() {
		for (int i = 0; i < cnt[nowfloor]; i++) {
			characterinelevator[nowfloor][i]->readystate = ELEVATER_NO;
			characterinelevator[nowfloor][i]->locationstate = ELEVATER_OFF;
			characterinelevator[nowfloor][i]->nowfloor = nowfloor;
			//更新状态，更新楼层
		}
		characterinelevator[nowfloor] = new character * [1];//删除数据，重新分配空间
		cnt[nowfloor] = 0;//重置
		
	}

	void base_elevator::run_duty(PURCHARACTER *pur, PDRCHARACTER *pdr, PBUF *pbuf,PBUF* pend) {
		switch (duty) {
		case DUTY:
			switch (lastrunstate) {
			case UP:
				off_character();
				load_characterup(pur, pbuf,pend);
				duty = DEFAULT;
				break;
			case DOWN:
				off_character();
				load_characterdown(pdr, pbuf,pend);
				duty = DEFAULT;
				break;
			case DEFAULT:
				if ((*pur)->next!=NULL) {
					lastrunstate = UP;
					load_characterup(pur, pbuf, pend);
				}
				else if ((*pdr)->next != NULL) {
					lastrunstate = DOWN;
					load_characterdown(pdr, pbuf, pend);
				}
				duty = DEFAULT;
			}break;
		case DUTYON:
			switch (lastrunstate) {
			case UP:
				load_characterup(pur, pbuf,pend);
				duty = DEFAULT;
				break;
			case DOWN:
				load_characterdown(pdr, pbuf, pend);
				duty = DEFAULT;
				break;
			case DEFAULT:
				if ((*pur)->next!=NULL) {
					lastrunstate = UP;
					load_characterup(pur, pbuf,pend);
					duty = DEFAULT;
				}
				else if ((*pdr)->next != NULL) {
					lastrunstate = DOWN;
					load_characterdown(pdr, pbuf, pend);
					duty = DEFAULT;
				}
				break;
			}break;
		case DUTYOFF:
			lastrunstate = runstate;
			off_character();
			duty = DEFAULT;
			break;
		case DEFAULT:
			runstate = DEFAULT;
			break;
		}

	}
	void elevatorthread(base_elevator* elevator, 
		int floorstate[], 
		PURCHARACTER pur[], 
		PDRCHARACTER pdr[], 
		PBUF* pbuf,
		PBUF* pend) {
		elevator->runstate_change(floorstate);
		elevator->set_nowfloor();
		elevator->fillstate_change();
		elevator->run_duty(&(pur[elevator->get_nowfloor()]), &(pdr[elevator->get_nowfloor()]), pbuf,pend);
		elevator->state_comeback();
		
	}
}