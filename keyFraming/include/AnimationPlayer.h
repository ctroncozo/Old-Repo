#ifndef CRISTIAN_TRONCOSO_ANIMATIONPLAYER_H
#define CRISTIAN_TRONCOSO_ANIMATIONPLAYER_H

#include "AnimationClip.h"
#include "Skeleton.h"
#include "Vector3D.h"

class AnimationPlayer
{

	static time_t START;
	Skeleton *skeleton;
	AnimationClip *anim;
	Vector3D pose;

public:
	AnimationPlayer(Skeleton *sk);
	~AnimationPlayer();
	void setClip(char *filename);
	void update();
};
#endif //CRISTIAN_TRONCOSO_ANIMATIONPLAYER_H
