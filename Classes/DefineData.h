#pragma once

#define offset		-100

// player
#define SCOPEMODE1 0	// 기본 배율
#define SCOPEMODE2 1	// 2배율 
#define SCOPEMODE3 2	// 4배율
#define SCOPEMODE4 3	// 8배율

#define SCOPEX1					1.0
#define SCOPEX2					0.8
#define SCOPEX4					0.6
#define SCOPEX8					0.4

#define FirstAidKit				0
#define BandAge					1
#define EnergyDrink				2

#define Player_Max_Health		100

#define weight_max1				125
#define weight_max2				300

#define Shiled_HP_MAX			250

// zombie
#define MAX_ZOMBIE				99
#define ZOMBIE_SPEED_RANDOM		700		// 클수록 빠름 랜덤에 사용
#define ZOMBIE_SPEED_STANDARD	100		// 클수록 빠름 랜덤에 더해지는 기본 속도
#define ZOMBIE_SPEED_BLOCK		500		// 작을 수록 빠름, 액션 시간을 거리 대비 나눠주는 값


#define ZOMBIE_DETECTIVE_1		1.0f
#define ZOMBIE_DETECTIVE_3		3.0f
#define ZOMBIE_DETECTIVE_RANGE	6.0f
#define ZOMBIE_DETECTIVE_FULL	13.0f

// item
#define SG_weight		 1.25
#define AR_weight		 0.5
#define SR_weight		 1

#define FisrtKit_weight		10
#define Bandage_weight		2
#define Drink_weight		4

#define FisrtKit_Delay		6
#define Bandage_Delay		4
#define Drink_Delay			6
#define Drink_Duration		40

#define GUN					100
#define SCOPE				200
#define HP_ITEM				300
#define DRINK_ITEM			400
#define BACKPACK			500
#define SHIELD				600
#define SMOKE				700

// bullet
#define PI					0
#define SG					1
#define AR					2
#define SR					3

#define PI_load				7
#define SG_load				8
#define AR_load				40
#define SR_load				10

#define DelayReloadTime		1

#define max_bullet			60
#define dam_P				50
#define dam_SG				25
#define dam_AR				50
#define dam_SR				200
#define dam_Zombie			5			// 원거리 좀비 데미지


// Map
#define MapSize				20000
#define MiniSize			2500

// UI
#define show_minimap_size	300
#define real_minimap_size	2500

// virus
#define virus_range			200
#define Virus_Speed			300			// 작을수록 빠름

// sound 
#define id_Reload			4
#define id_Melee_Attack		5
#define id_Range_Attack		6
#define id_mZombie_Death	7
#define id_rZombie_Death	8
#define id_Player_Death		9


// map
#define MAP_ZONE			25
#define	MAP_BLOCKS			16