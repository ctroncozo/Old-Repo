#ifndef CRISTIAN_TRONCOSO_ANIMATIONCLIP_H
#define CRISTIAN_TRONCOSO_ANIMATIONCLIP_H

#include <vector>
#include "Channel.h"
#include "Vector3D.h"
#include "token.h"

class AnimationClip
{
	float range[2];
	std::vector<Channel*> channels;
	int nunOfchannels;

public:
	AnimationClip();
	~AnimationClip();
	int getNumOfChannels();
	void load(char *filename);
  void evaluateTranslation(int idx, float time, Vector3D &pose);
	void evaluate(int idx, float time, Vector3D &pose);
};
#endif // CRISTIAN_TRONCOSO_ANIMATIONCLIP_H
