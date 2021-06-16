//乘客属性库
#include "simulation.h"
#include "state.h"
#ifndef CHARACTER_H
#define CHARACTER_H
using namespace simulationTianyu;
namespace characterTianyu {
	struct character;

	void create_character(character*, character*,int);
	void delete_character(character*, character*,character*);
}


#endif


#include "character.h"
namespace characterTianyu {

	struct character {
		character* next;//指向下个乘客
		character* last;//指向上个乘客
		int sum_weight;//乘客质量
		int aim_floor;//目标楼层
		//施工区
		int state;//状态
		int code;//the number used to identify.
		//施工区完毕
		//int token
	};
	
	void create_character(character* a, character* b,int h){
		b = new character;
		b->aim_floor = character_random_aim_floor(h);
		b->sum_weight = character_random_weight();
		b->next = nullptr;
		b->last = a;
		a->next = b;
	}

	void delete_character(character* aim, character* left, character* right) {
		left->next = aim->next;
		right->last = aim->last;
		delete aim;
	}

}
