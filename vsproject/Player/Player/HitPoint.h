#pragma once
//Trackers
#define NOTRACKER 0
#define MODTRACKER 1
#define LEVTRACKER 2
#define MODLEVTRACKER 3
#define TOTALTRACKER 4

//Defaults
#define DEFAULTHP 10
#define DEFAULTTRACKER NOTRACKER

//ERRORS
#define GTMAXINTERROR -1
#define LTMININTERROR -2
#define NEGAMMOUNTERROR -3
#define UNKNOWNERROR -5

class HitPoint
{
private:
	void init();
public:
	HitPoint() {
		init();
	}
	//int setBaseHP(int bHP);
	int getBaseHP();
	int increaseBaseHP(int ammount);
	int decreaseBaseHP(int ammount);
	//int setBuffedHP(int bufHP);
	int getBuffedHP();
	int increaseBuffedHP(int ammount);
	int decreaseBuffedHP(int ammount);
	//int setDebuffedHP(int debHP);
	int getDebuffedHP();
	int increaseDebuffedHP(int ammount);
	int decreaseDebuffedHP(int ammount);
	//in setCurrentHP();
	int getCurrentHP();
	int increaseCurrentHP(int ammount);
	int decreaseCurrentHP(int ammount);
	int getTotalHP();
};

