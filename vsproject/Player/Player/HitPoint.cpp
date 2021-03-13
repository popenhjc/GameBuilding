#include "HitPoint.h"
#include "limits.h"

/*
* baseHP
* The natural hitpoints with no alterations.
*/
int baseHP;
/*
* totalHP
* The total number of hitpoints with all alterations.
*/
int totalHP;
/*
* buffedHP
* Any hitpoints to be added to baseHP temporarily.
*/
int buffedHP;
/*
* debuffedHP
* Any hitpoints to be subtracted from baseHP temporarily.
*/
int debuffedHP;
/*
* currentHP
* The current number of hitpoints.
*/
int currentHP;

/*
* currentHPTrackMode
* No Tracking
*	currentHP will not track a any other HP modification.
* Modifier Tracking
*	When baseHP or buffHP change, currentHP will change by the same ammount or be set to 0, whichever is higher.
*	When debuffHP changes, currentHP will stay the same or track totalHP, whichever is lower.
* "Level Up" Tracking
*	When baseHP increases currentHP becomes totalHP.
*	When baseHP decreases, currentHP will stay the same or track totalHP, whichever is lower.
* Modifier and "Level Up" Tracking
*	When baseHP increases currentHP becomes totalHP.
*	When baseHP decreases, currentHP will stay the same or track totalHP, whichever is lower.
*	When buffHP changes, current HP will change by the same ammount or be set to 0, whichever is higher. 
*	When debuffHP changes, currentHP will stay the same or track totalHP, whichever is lower.
* TotalHP Tracking
*	When currentHP is higher than TotalHP, currentHP becomes TotalHP.
*/
int currentHPTrackMode;

int increaseTotalHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((totalHP + ammount) < 0) throw GTMAXINTERROR;

		totalHP += ammount;
		return totalHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int decreaseTotalHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((totalHP - ammount) <= 0) throw LTMININTERROR;

		totalHP -= ammount;
		if ((currentHPTrackMode != 0) && (currentHP > totalHP)) currentHP = totalHP;
		return totalHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

void HitPoint::init()
{
	currentHPTrackMode = DEFAULTTRACKER;
	baseHP = DEFAULTHP;
	totalHP = baseHP;
	buffedHP = 0;
	debuffedHP = 0;
	currentHP = baseHP;
	return;
}

int HitPoint::getBaseHP()
{
	return baseHP;
}

int HitPoint::increaseBaseHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((baseHP + ammount) < 0) throw GTMAXINTERROR;
		
		int ret = increaseTotalHP(ammount);
		if (ret < 0) throw ret;

		if ((currentHPTrackMode & LEVTRACKER) != 0) currentHP = totalHP;
		else if (currentHPTrackMode == MODTRACKER)
		{
			if ((currentHP + ammount) < 0) throw GTMAXINTERROR;
			currentHP += ammount;
		}

		baseHP += ammount;
		return baseHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::decreaseBaseHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((baseHP - ammount) <= 0) throw LTMININTERROR;

		int ret = decreaseTotalHP(ammount);
		if (ret < 0) throw ret;

		if (currentHPTrackMode == MODTRACKER)
		{
			if ((currentHP -= ammount) < 0) currentHP = 0;
		}

		baseHP -= ammount;
		return baseHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::getBuffedHP()
{
	return buffedHP;
}

int HitPoint::increaseBuffedHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((buffedHP + ammount) < 0) throw GTMAXINTERROR;

		int ret = increaseTotalHP(ammount);
		if (ret < 0) throw ret;

		if ((currentHPTrackMode & MODTRACKER) != 0)
		{
			if ((currentHP + ammount) < 0) throw GTMAXINTERROR;
			currentHP += ammount;
		}

		buffedHP += ammount;
		return buffedHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::decreaseBuffedHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((buffedHP - ammount) < 0) throw LTMININTERROR;

		int ret = decreaseTotalHP(ammount);
		if (ret < 0) throw ret;

		if ((currentHPTrackMode & MODTRACKER) != 0)
		{
			if ((currentHP -= ammount) < 0) currentHP = 0;
		}

		buffedHP -= ammount;
		return buffedHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::getDebuffedHP()
{
	return debuffedHP;
}

int HitPoint::increaseDebuffedHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((debuffedHP + ammount) < 0) throw GTMAXINTERROR;

		int ret = decreaseTotalHP(ammount);
		if (ret < 0) throw ret;

		debuffedHP += ammount;
		return debuffedHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::decreaseDebuffedHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((debuffedHP - ammount) < 0) throw LTMININTERROR;

		int ret = increaseTotalHP(ammount);
		if (ret < 0) throw ret;

		debuffedHP -= ammount;
		return debuffedHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::getCurrentHP()
{
	return currentHP;
}

int HitPoint::increaseCurrentHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((currentHP + ammount) < 0) throw GTMAXINTERROR;

		currentHP += ammount;
		return currentHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::decreaseCurrentHP(int ammount)
{
	try
	{
		if (ammount < 0) throw NEGAMMOUNTERROR;
		if ((currentHP -= ammount) < 0) currentHP = 0;
		return currentHP;
	}
	catch (int error) { return error; }
	catch (...) { return UNKNOWNERROR; }
}

int HitPoint::getTotalHP()
{
	return totalHP;
}
