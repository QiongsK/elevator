#include "building.h"
namespace buildingTianyu{
	base_floor::base_floor(int h) :hight(h) {
		state = WONDER_NO;
	}
	base_floor::~base_floor() {

	}

	int base_floor::get_hight(){
		return hight;
	}

	void base_floor::set_hight(int h) {
		hight = h;
	}

	int base_floor::get_state() {
		return state;
	}

	void base_floor::set_state(int floorstate) {
		state = floorstate;
	}

	derive_floor::derive_floor(int h,function fun):base_floor(h),func(fun) {
		
	}

	function derive_floor::getfunc() {
		return func;
	}

	void state_change(PURCHARACTER upready,
		PDRCHARACTER downready,
		base_floor* floor) {
		if (upready->next == NULL && downready == NULL) {
			floor->set_state(WONDER_NO);
		}
		else if (upready->next != NULL && downready != NULL) {
			floor->set_state(WONDER_YES);
		}
		else if (upready->next != NULL && downready == NULL) {
			floor->set_state(WONDER_YESUP);
		}
		else if (upready->next == NULL && downready != NULL) {
			floor->set_state(WONDER_YESDOWN);
		}
	}
}//buildingTianyu