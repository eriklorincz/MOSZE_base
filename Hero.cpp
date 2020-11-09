#include "Hero.h"
#include "Exceptions.h"
#include "JSON.h"
#include <math.h>
#include <algorithm>
#include <fstream>



Hero::Hero(const std::string & nm, int hp, int dmg,double cd, int xpgap, int hpbonus, int dmgbonus, double cdMulti) 
		: Monster(nm, hp, dmg, cd), XPgap(xpgap), HPbonus(hpbonus), DMGbonus(dmgbonus), CDMultiplier(cdMulti), XP(0)
{
}

void Hero::levelUp()
{
	while (XP >= XPgap)
	{
		maxHP = std::lround(maxHP + HPbonus);
		DMG = std::lround(DMG + DMGbonus);
		HP = maxHP;
		CD = CD * CDMultiplier;
		Lvl++;
		XP = XP - XPgap;
	}


}

Hero Hero::parse(const std::string &file_nam)
{
	std::string file_name = "./units/" + file_nam;
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		throw(JSON::ParseException());
	}


	std::string nm = "";
	int hp = -1;
	int dm = -1;
	double cd = -1.0;
	int xp = -1;
	int hpb = -1;
	int dmb = -1;
	double cdm = -0.1;


	try
	{
		JSON attributes = JSON::parseFromIstream(infile);
		nm = attributes.get<std::string>("name");
		hp = attributes.get<int>("base_health_points");
		dm = attributes.get<int>("base_damage");
		cd = attributes.get<double>("base_attack_cooldown");
		xp = attributes.get<int>("experience_per_level");
		hpb = attributes.get<int>("health_point_bonus_per_level");
		dmb = attributes.get<int>("damage_bonus_per_level");
		cdm = attributes.get<double>("cooldown_multiplier_per_level");
	}
	catch(const std::out_of_range&)
	{
		throw(JSON::ParseException());
	}
	catch (const InputFormatException&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	catch (const std::invalid_argument&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	catch (const std::bad_variant_access&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	infile.close();

	return Hero(nm, hp, dm, cd, xp, hpb, dmb, cdm);

}

void Hero::causeDamage(Monster* enemy)
{
	XP += std::min(DMG, enemy->getHealthPoints());
	enemy->gotHit(*this);
	levelUp();
}
std::string Hero::showStats() const {

	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG)
		+ " EXP: " + std::to_string(XP) + " LVL: " + std::to_string(Lvl);
}
