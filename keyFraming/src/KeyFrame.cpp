#include "KeyFrame.h"

KeyFrame::KeyFrame(){}

KeyFrame::KeyFrame(float t, float v, std::string ri, std::string ro): 
						 time(t), value(v), ruleIn(ri), ruleOut(ro){}

KeyFrame::~KeyFrame(){};

			// Setters //
void KeyFrame::setTime(float t)
{
	time = t;
}

void KeyFrame::setValue(float v)
{
	value = v;
}

void KeyFrame::setTanIn(float ti)
{
	tanIn = ti;
}	

void KeyFrame::setTanOut(float to)
{
	tanOut = to;
}

void KeyFrame::setRuleIn(std::string ri)
{
	ruleIn = ri;
}

void KeyFrame::setRuleOut(std::string ro)
{
	ruleOut = ro;
}

		// Getters //
float KeyFrame::getTime()
{
	return time;
}

float KeyFrame::getValue()
{
	return value;
}

float KeyFrame::getTanIn()
{
	return tanIn;
}

float KeyFrame::getTanOut()
{
	return tanOut;
}

std::string KeyFrame::getRuleIn()
{
	return ruleIn;
}

std::string KeyFrame::getRuleOut()
{
	return ruleOut;
}

