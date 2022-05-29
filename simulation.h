//用于模拟环境的接口文件
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
	//第一版，返回一个随机的一批乘客重量。

	int character_random_aim_floor(int);
	//传入楼层高度

	void random_now_floor(character* cha, 
		default_random_engine e,
		unsigned u);

	void random_aim_floor(character* cha,
		default_random_engine e,
		unsigned u);
	//随机分配楼层，服从均匀分布；

	void random_weight(character* cha,
		default_random_engine e,
		unsigned q);
	//随机分配体重，服从正态分布

	void random_distribution(character* cha,
		default_random_engine e,
		bool b);
	//随机分配是否重置状态.





}//simulationTianyu
//正态分布测试代码
/*		double max1 = 0;
		double min1 = 1;
		int min2 = 150;
		int max2 = 30;
		int X = 120 * (q(e) / 10 + 0.5) + 30;//服从正态分布的体重,得不断变化
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
