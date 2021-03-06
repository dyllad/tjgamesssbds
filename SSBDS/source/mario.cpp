#include "mario.h"
#include <vector>
#include <PA9.h>
#include "display.h"
#include "projectiles.h"
#include "fighter.h"
#include "gfx/all_sounds.c"
using std:: vector;

// constructor
Mario::Mario(int xpos, int ypos, int num, vector<Fighter*> listplayers, Display *disp, bool AI) : Fighter(xpos,ypos,num,listplayers,disp,"mario",AI) {
	shieldstr = 64;
	runspeed = 3.75;
	handx = 29;
	handy = 19;
	fluddcharge = 0;
	MYCHAR = MARIO;
	topside = 17;
	bottomside = 47;
	rightside = 39;
	leftside = 24;
	gravity = 3;
	jumpmax = 2;
} // initializes all of the variables
// initializers
void Mario::playsound(int sndnum) {
	if(sndnum == JUMP) AS_SoundQuickPlay(mariojump);
	if(sndnum == DOUBLEJUMP) AS_SoundQuickPlay(mariodoublejump);
	if(sndnum == UTILT) AS_SoundQuickPlay(marioutilt);
	if(sndnum == DASHATTACK) AS_SoundQuickPlay(mariodashattack);
	if(sndnum == SMASHDOWN) AS_SoundQuickPlay(mariodsmash);
	if(sndnum == SMASHUP) AS_SoundQuickPlay(mariousmash);
}
void Mario::initFrames() {
	// LAND
	startframes.push_back(0);
	endframes.push_back(0);
	framespeeds.push_back(10);

	// SHIELD
	startframes.push_back(31);
	endframes.push_back(31);
	framespeeds.push_back(20);

	// ROLL
	startframes.push_back(25);
	endframes.push_back(30);
	framespeeds.push_back(15);

	// DODGE
	startframes.push_back(84);
	endframes.push_back(86);
	framespeeds.push_back(3);
	// should be updown. fix in sprite

	// AIRDODGE
	startframes.push_back(128);
	endframes.push_back(131);
	framespeeds.push_back(12);

	// CROUCH
	startframes.push_back(0);
	endframes.push_back(0);
	framespeeds.push_back(20);

	// FALL
	startframes.push_back(14);
	endframes.push_back(14);
	framespeeds.push_back(20);

	// IDLE
	startframes.push_back(1);
	endframes.push_back(4);
	framespeeds.push_back(10);

	// RUN
	startframes.push_back(5);
	endframes.push_back(8);
	framespeeds.push_back(15);

	// SHORTHOP
	startframes.push_back(10);
	endframes.push_back(14);
	framespeeds.push_back(12);

	// JUMP
	startframes.push_back(10);
	endframes.push_back(14);
	framespeeds.push_back(12);

	// DOUBLEJUMP
	startframes.push_back(16);
	endframes.push_back(23);
	framespeeds.push_back(20);

	// JAB
	startframes.push_back(35);
	endframes.push_back(46);
	framespeeds.push_back(12);

	// DASHATTACK
	startframes.push_back(64);
	endframes.push_back(64);
	framespeeds.push_back(4);

	// FTILT
	startframes.push_back(47);
	endframes.push_back(51);
	framespeeds.push_back(10);

	// UTILT
	startframes.push_back(58);
	endframes.push_back(62);
	framespeeds.push_back(10);

	// DTILT
	startframes.push_back(52);
	endframes.push_back(57);
	framespeeds.push_back(10);

	// CHARGELEFT
	startframes.push_back(94);
	endframes.push_back(95);
	framespeeds.push_back(20);

	// CHARGERIGHT
	startframes.push_back(94);
	endframes.push_back(95);
	framespeeds.push_back(20);

	// CHARGEUP
	startframes.push_back(102);
	endframes.push_back(102);
	framespeeds.push_back(20);

	// CHARGEDOWN
	startframes.push_back(111);
	endframes.push_back(112);
	framespeeds.push_back(20);

	// SMASHLEFT
	startframes.push_back(96);
	endframes.push_back(101);
	framespeeds.push_back(15);

	// SMASHRIGHT
	startframes.push_back(96);
	endframes.push_back(101);
	framespeeds.push_back(15);

	// SMASHUP
	startframes.push_back(104);
	endframes.push_back(110);
	framespeeds.push_back(15);

	// SMASHDOWN
	startframes.push_back(113);
	endframes.push_back(120);
	framespeeds.push_back(15);

	// FAIR
	startframes.push_back(75);
	endframes.push_back(83);
	framespeeds.push_back(10);

	// BAIR
	startframes.push_back(71);
	endframes.push_back(75);
	framespeeds.push_back(12);

	// UAIR
	startframes.push_back(67);
	endframes.push_back(71);
	framespeeds.push_back(15);

	// DAIR
	startframes.push_back(84);
	endframes.push_back(93);
	framespeeds.push_back(15);

	// NAIR
	startframes.push_back(66);
	endframes.push_back(66);
	framespeeds.push_back(4);

	// STUN
	startframes.push_back(121);
	endframes.push_back(126);
	framespeeds.push_back(20);

	// SLIDE
	startframes.push_back(10);
	endframes.push_back(10);
	framespeeds.push_back(20);

	// HANG
	startframes.push_back(24);
	endframes.push_back(24);
	framespeeds.push_back(20);

	// GRABBED
	startframes.push_back(121);
	endframes.push_back(121);
	framespeeds.push_back(20);

	// GRAB
	startframes.push_back(151);
	endframes.push_back(152);
	framespeeds.push_back(10);

	// GRABATK
	startframes.push_back(155);
	endframes.push_back(155);
	framespeeds.push_back(10);

	// DEAD
	startframes.push_back(169);
	endframes.push_back(169);
	framespeeds.push_back(20);
}
// actions
void Mario::bside() {
	if(action != BSIDE) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 143, 148, 10, ANIM_ONESHOT);
		delay = 60/10 * 6;
		setDirection();
		dx = 0;
		action = BSIDE;
		CAPE = true;
	}
	else {
		if(delay == 1) {
			if(checkFloorCollision()) idle();
			else fall();
			CAPE = false;
		}
	}
}
void Mario::bup() {
	if(action != BUP) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 137, 142, 20, ANIM_ONESHOT);
		aerial = true;
		delay = 60/20 * 6;
		dy = -7;
		dx = 0;
		fastfall = 0;
		DI = 0;
		setDirection();
		action = BUP;
		AS_SoundQuickPlay(mariobup);
	}
	else {
		if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 142) {
			if(!checkFloorCollision()) {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 142, 142, 20, ANIM_LOOP, -1);
				delay = 60/20 * 1;
				dy = 0;
			}
			else {
				idle();
			}
		}
	}
}
void Mario::bdown() {
	if(action != BDOWN) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 149, 149, 20, ANIM_LOOP, -1);
		delay = 60/20 * 1;
		fluddcharge = 0;
		dx = 0;
		if(aerial) dy = -gravity/2;
		else dy = 0;
		action = BDOWN;
	}
	else if(custom_action(ACTION_SPECIAL, PAD_RELEASED) && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 149) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 150, 150, 12, ANIM_LOOP, -1);
		delay = 60/12 * 1;
		int directionmodifier = 1;
		if(direction == RIGHT) directionmodifier = -1;
		Hitbox tempbox;
		tempbox.addCircle(createAtkbox(58, 32, 5, Knockback((-1*directionmodifier), -.5, 6), 60));
		((vector<Projectile>*)getProj())->push_back(Projectile(x, y-16, -5*directionmodifier, 0, 2*fluddcharge, FLUDDWATER, charnum, tempbox, stage, display));
		fluddcharge = 0;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 150) {
		if(delay == 1) {
			if(checkFloorCollision()) idle();
			else fall();
		}
	}
	else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 149) {
		delay = 60/20 * 1;
		fluddcharge++;
	}
	else if(aerial && checkFloorCollision()) {
		dy = 0;
	}
	else {
		fluddcharge++;
		if(fluddcharge > 30) fluddcharge = 30;
	}
}
void Mario::bneut() {
	if(action != BNEUT) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 132, 133, 12, ANIM_LOOP, -1);
		delay = 60/12 * 2;
		dx = 0;
		action = BNEUT;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 133 && delay == 1) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 134, 134, 10, ANIM_LOOP, -1);
		delay = 60/10 * 1;
		AS_SoundQuickPlay(mariobneut);
		int directionmodifier = 1;
		if(direction == RIGHT) directionmodifier = -1;
		Hitbox tempbox;
		tempbox.addCircle(createAtkbox(32, 32, 6, Knockback(-.25*directionmodifier, 0, 6), 10));
		Projectile p = Projectile(x, y, -3*directionmodifier, 1.5, 90, FIREBALL, charnum, tempbox, stage, display);
		p.miny = stage->getFloors()[0].y-32;
		p.maxy = y;
		((vector<Projectile>*)getProj())->push_back(p);
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 134 && delay == 1) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 135, 136, 12, ANIM_LOOP, -1);
		delay = 60/12 * 2;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 136 && delay == 1) {
		if(checkFloorCollision()) idle();
		else fall();
	}
	else if(aerial && checkFloorCollision()) dy = 0;
	else {}
}
void Mario::fthrow() {
	if(action != FTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 153, 155, 12, ANIM_LOOP, -1);
		playsound(FTHROW);
		delay = 60/12 * (155-153+1);
		action = FTHROW;		
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 153) {
		if(direction == LEFT) grabbedenemy -> dx = 8;
		else grabbedenemy -> dx = -8;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 154 or PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 155) {
		if(direction == LEFT) grabbedenemy -> dx = -8;
		else grabbedenemy -> dx = 8;
	}
	if(delay <= 0) {
		int mult = -1;
		grabbedenemy -> k = Knockback(2, -2, 7);
		if(direction == RIGHT) {
			mult = 1;
		}
		grabbedenemy -> hitstun = (int) (grabbedenemy -> k.length * 3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 7;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;	
		idle();
	}
}
void Mario::bthrow() {
	if(action != BTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 156, 162, 12, ANIM_LOOP, -1);
		playsound(BTHROW);
		delay = 60/12 * (162-156+1);
		action = BTHROW;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 156 or PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 157) {
		if(direction == LEFT) grabbedenemy -> dx = 4;
		else grabbedenemy -> dx = -4;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 158) {
		grabbedenemy -> dx = 0;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 159 or PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 160) {
		if(direction == LEFT) grabbedenemy -> dx = -4;
		else grabbedenemy -> dx = 4;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 161) {
		grabbedenemy -> dx = 0;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 162) {
		if(direction == LEFT) grabbedenemy -> dx = 8;
		else grabbedenemy -> dx = -8;
	}
	if(delay <= 0) {
		int mult = 1;
		grabbedenemy -> k = Knockback(2.5, -2, 7);
		if(direction == RIGHT) {
			mult = -1;
		}
		grabbedenemy -> hitstun = (int)(grabbedenemy -> k.length*3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 9;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		idle();
	}
}
void Mario::uthrow() {
	if(action != UTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 163, 165, 12, ANIM_LOOP, -1);
		playsound(UTHROW);
		delay = 60/12 * (165-163+1);
		action = UTHROW;
		if(direction == LEFT) grabbedenemy -> dx = 2;
		else grabbedenemy -> dx = -2;
	}
	if(delay <= 0) {
		int mult = -1;
		grabbedenemy -> k = Knockback(0, -3, 5);
		if(direction == RIGHT) {
			mult = 1;
		}
		grabbedenemy -> hitstun = (int)(grabbedenemy -> k.length*3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 6;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		idle();		
	}
}
void Mario::dthrow() {
	if(action != DTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 165, 168, 12, ANIM_LOOP, -1);
		playsound(DTHROW);
		delay = 60/12 * (168-165+1);
		action = DTHROW;
		if(direction == LEFT) grabbedenemy -> dx = 2;
		else grabbedenemy -> dx = -2;
		grabbedenemy -> dy = .5;
	}
	if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 167) {
		grabbedenemy -> dx = 0;
	}
	if(delay <= 0) {
		int mult = -1;
		grabbedenemy -> k = Knockback(1, -2.5, 7);
		if(direction == RIGHT) {
			mult = 1;
		}
		grabbedenemy -> hitstun = (int)(grabbedenemy -> k.length*3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 6;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		idle();
	}
}
void Mario::jaywalk() {}
Mario::~Mario() {
	allatkbox.clear();
	alldefbox.clear();
	PA_DeleteSprite(MAIN_SCREEN, SPRITENUM);
	PA_FatFreeSprite(MYCHAR);		
}
