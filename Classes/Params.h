#ifndef _PARAMS_
#define  _PARAMS_

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "cocos2d.h"
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8  ||  CC_TARGET_PLATFORM == CC_PLATFORM_IOS )

#define SCALE_FACTOR   0.3

#else

// this value is multiplied by the size of the sprite
// our platform is win32, we conserv same size but on
// other platform, we change this value
#define SCALE_FACTOR   1

#endif

// KEYBOARD
//const CCEventKeyboard::KeyCode ENTER = CCEventKeyboard::KeyCode::KEY_KP_ENTER;
//const CCEventKeyboard::KeyCode UP_ARROW = CCEventKeyboard::KeyCode::KEY_UP_ARROW;
//const CCEventKeyboard::KeyCode DOWN_ARROW = CCEventKeyboard::KeyCode::KEY_DOWN_ARROW;
//const CCEventKeyboard::KeyCode LEFT_ARROW = CCEventKeyboard::KeyCode::KEY_LEFT_ARROW;
//const CCEventKeyboard::KeyCode RIGHT_ARROW = CCEventKeyboard::KeyCode::KEY_RIGHT_ARROW;

#endif


#if (  CC_TARGET_PLATFORM == CC_PLATFORM_WINRT )

#define SPEEDREDUCTION  0.3


#else

#define SPEEDREDUCTION  0.3


#endif





static const char Arrow1_enabled[] = "Arrow/b1.png";
static const char Arrow1_disabled[] = "Arrow/b2.png";


// ship general declaration
static Vec2 Ship1_Pos(500, 240);
static const int Ship_Level = 0;
static const int Ship_MaxLevel = 25;


// ship fireball declaration
static const int ShipWar_NumExplosion = 17;
static const float ShipWar_ExplosionDuration = 3.4f;
static const float ShipWar_ExplosionScale = 1.25f;
static const float ShipWar_Scale = 0.35f;
static const char ShipWar_Sprite[] = "Ship/ship1.png";
static const char ShipWar_SpriteDead[] = "Ship/ship1.png";
static const int ShipWar_MaxHealth = 1000;
static const int ShipWar_Health = 1000;
static const int ShipWar_MaxEnergy = 200;
static const int ShipWar_Energy = 800;
static const double ShipWar_MaxSpeed = 0.0;
static const double ShipWar_Speed = 60;
static const double ShipWar_MaxTurnRate = 0.5;
static const double ShipWar_MaxForce = 0.8;



// ship war

// ship freeze

// ship electrile


// Mini Ship

static const int Mini_NumExplosion = 17;
static const float Mini_ExplosionDuration = 3.4f;
static const float Mini_ExplosionScale = 1.25f;
static const float Mini_Scale = 0.3f;
static const char Mini_Sprite[] = "Ship/ship3.png";
static const char Mini_SpriteDead[] = "Ship/ship1.png";
static const int Mini_MaxHealth = 10;
static const int Mini_Health = 20;
static const int Mini_MaxEnergy = 20;
static const int Mini_Energy = 800;
static const double Mini_MaxSpeed = 0.0;
static const double Mini_Speed = 180;
static const double Mini_MaxTurnRate = 0.5;
static const double Mini_MaxForce = 0.8;

// ship alien 1
static const char ShipAlien1_Name[] = "ShipAlien1";
static const char ShipAlien1_Sprite[] = "Ship/Alien/ship1_001.png";
static const float ShipAlien1_Scale = 0.5f;
static const int ShipAlien1_Health = 140;
static const int ShipAlien1_armor = 2;
static const int ShipAlien1_TimerSpawn = 2;
static const int ShipAlien1_MineralCost = 125;

// ship alien 2
static const char ShipAlien2_Name[] = "ShipAlien2";
static const char ShipAlien2_Sprite[] = "Ship/Alien/ship2_001.png";
static const float ShipAlien2_Scale = 0.7f;
static const int ShipAlien2_Health = 200;
static const int ShipAlien2_armor = 1;
static const int ShipAlien2_TimerSpawn = 3;
static const int ShipAlien2_MineralCost = 175;

// ship alien 3
static const char ShipAlien3_Name[] = "ShipAlien3";
static const char ShipAlien3_Sprite[] = "Ship/Alien/ship3_001.png";
static const float ShipAlien3_Scale = 0.7f;
static const int ShipAlien3_Health = 35;
static const int ShipAlien3_armor = 0;
static const int ShipAlien3_TimerSpawn = 1;
static const int ShipAlien3_MineralCost = 35;

// ship alien 4
static const char ShipAlien4_Name[] = "ShipAlien4";
static const char ShipAlien4_Sprite[] = "Ship/Alien/ship4_001.png";
static const float ShipAlien4_Scale = 0.9f;
static const int ShipAlien4_Health = 80;
static const int ShipAlien4_armor = 0;
static const int ShipAlien4_TimerSpawn = 2;
static const int ShipAlien4_MineralCost = 100;

// ship alien 5
static const char ShipAlien5_Name[] = "ShipAlien5";
static const char ShipAlien5_Sprite[] = "Ship/Alien/ship5_001.png";
static const float ShipAlien5_Scale = 0.2f;
static const int ShipAlien5_Health = 225;
static const int ShipAlien5_armor = 2;
static const int ShipAlien5_TimerSpawn = 5;
static const int ShipAlien5_MineralCost = 350;

// ship alien 6 (UltraLisk)
static const char ShipAlien6_Name[] = "ShipAlien6";
static const char ShipAlien6_Sprite[] = "Ship/Alien/ship6_001.png";
static const float ShipAlien6_Scale = 0.3f;
static const int ShipAlien6_Health = 500;
static const int ShipAlien6_armor = 2;
static const int ShipAlien6_TimerSpawn = 5;
static const int ShipAlien6_MineralCost = 350;


// weapon torpedo 1
static const int Weapon1_Damage = 40;
static const int Weapon1_BonusVs_Light = 0;
static const int Weapon1_BonusVs_Armored = 0;
static const float Weapon1_Rate = 2;
static const int Weapon1_Range = 125;



// weapon torpedo 2    // for tower
static const int Weapon2_Damage = 6;
static const int Weapon2_BonusVs_Light = 0;
static const int Weapon2_BonusVs_Armored = 0;
static const float Weapon2_Rate = 2.5;
static const int Weapon2_Range = 125;


// weapon alien 1
static const int Weapon3_Damage = 16;
static const int Weapon3_BonusVs_Light = 0;
static  const int Weapon3_BonusVs_Armored = 0;
static const float Weapon3_Rate = 1.2f;
static const int Weapon3_Range = 50;

// weapon alien 2
static const int Weapon4_Damage = 20;
static const int Weapon4_BonusVs_Light = 0;
static const int Weapon4_BonusVs_Armored = 20;
static const float Weapon4_Rate = 1.0f;
static const int Weapon4_Range = 150;


// weapon alien 3
static const int Weapon5_Damage = 7;
static const int Weapon5_BonusVs_Light = 0;
static const int Weapon5_BonusVs_Armored = 0;
static const float Weapon5_Rate = 3.5f;
static const int Weapon5_Range = 15;


// weapon alien 4
static const int Weapon6_Damage = 12;
static const int Weapon6_BonusVs_Light = 0;
static const int Weapon6_BonusVs_Armored = 0;
static const float Weapon6_Rate = 2.8f;
static const int Weapon6_Range = 135;


// weapon alien 5
static const int Weapon7_Damage = 75;
static const int Weapon7_BonusVs_Light = 0;
static const int Weapon7_BonusVs_Armored = 0;
static const float Weapon7_Rate = 0.6f;
static const int Weapon7_Range = 225;



// weapon fireball
static const int Weapon8_Damage = 10;
static const int Weapon8_BonusVs_Light = 6;
static const int Weapon8_BonusVs_Armored = 0;
static const float Weapon8_Rate = 1.0f;
static const int Weapon8_Range = 25;



// pROJECTILE general declaration
static Vec2 Projectile_Pos(370, 240);
static Vec2 Projectile_Target(670, 240);

// projectile torpdedo
static const char Projectile1_Sprite[] = "Projectile/Torpedo/torpedo_001.png";
static const double Projectile1_MaxSpeed = 200;
static const double Projectile1_Speed = 20;
static const double Projectile1_RangeDead = 400;


// projectile toredo2
static const char Projectile2_Sprite[] = "Projectile/Tower/p_01.png";

// projectile alien1
static const char Projectile3_Sprite[] = "Projectile/Alien/alien_001.png";

// projectile alien1
static const char Projectile4_Sprite[] = "Projectile/Alien/alien1_001.png";

// projectile alien1
static const char Projectile5_Sprite[] = "Projectile/Alien/alien2_001.png";

// projectile alien1
static const char Projectile6_Sprite[] = "Projectile/Alien/alien3_001.png";

// projectile alien1
static const char Projectile7_Sprite[] = "Projectile/Alien/alien4_001.png";

// wall declaration
static int Wall_Health = 500;

// tower Marine
static int Tower1_Health = 350;
static const int Tower1_Defense = 0;
static int Tower1_Cost = 150;
static float Tower1_BuildTime = 4;

// tower marauder
static int Tower2_Health = 350;
static int Tower2_Cost = 250;
static const int Tower2_Defense = 1;
static float Tower2_BuildTime = 6;


// tower firebat

static int Tower3_Cost = 300;
static int Tower3_Health = 350;
static const int Tower3_Defense = 1;
static float Tower3_BuildTime = 6;


// tower tank

static int Tower4_Cost = 350;
static int Tower4_Health = 200;
static const int Tower4_Defense = 1;
static float Tower4_BuildTime = 10;


// tower thor

static int Tower5_Cost = 700;
static int Tower5_Health = 400;
static const int Tower5_Defense = 1;
static float Tower5_BuildTime = 18;

// ai game mode

// NOVICE MODE
#define NOVICE_TOWER_COST_FACTORDMG     0.2f ;
#define NOVICE_TOWER_COST_FACTORHP      0.4f ;
#define NOVICE_MONSTER_FACTOR_MINERAL_COST	 	    0.5f ;

// advanced mode
#define ADVANCED_TOWER_COST_FACTORDMG     0.3f ;
#define ADVANCED_TOWER_COST_FACTORHP      0.6f ;
#define ADVANCED_MONSTER_FACTOR_MINERAL_COST	 	    0.3f ;

// EXPERT MODE
#define EXPERT_TOWER_COST_FACTORDMG     0.5f ;
#define EXPERT_TOWER_COST_FACTORHP      1.0f ;
#define EXPERT_MONSTER_FACTOR_MINERAL_COST	 	    0.15f ;


#endif