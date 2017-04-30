#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(Skeleton *sk):skeleton(sk) {}

AnimationPlayer::~AnimationPlayer(){}

void AnimationPlayer::setClip(char *filename)
{
	anim = new AnimationClip();
    //anim->load("./animation/wasp/wasp_walk.anim");
	anim->load(filename);
}

void AnimationPlayer::update()
{
	int size = anim->getNumOfChannels();
    size = (size / 3) ;     // total of 24 3-tuple
	time_t current = clock();
	float time = current - START;
    time = time /CLOCKS_PER_SEC;
    
    // First evaluate the root
    anim->evaluateTranslation(0, time, pose); // trasnlation
    skeleton->jointsArr.at(0)->setOffset(pose);
    
    // Loop through the 23 joints
	for(int i = 0; i < size -1 ; i += 1)
	{
		anim->evaluate(i, time, pose);
        skeleton->jointsArr.at(i)->setPose(pose);
        //std::cout<<time<<" "<<skeleton->jointsArr.at(i)->jname<<" "<<pose.x<<std::endl;
        //std::cout<<time<<" "<<skeleton->jointsArr.at(i)->jname<<" "<<pose.y<<std::endl;
        //std::cout<<time<<" "<<skeleton->jointsArr.at(i)->jname<<" "<<pose.z<<std::endl;
	}
}
		
