#ifndef CRISTIAN_TRONCOSO_KEYFRAME_H
#define CRISTIAN_TRONCOSO_KEYFRAME_H

#include "Vector4D.h"
#include <string>

class Channel;
/*!
 * \Brief	:	The KeyFrame class store time and value of each key frame.
 *					It also stores some aditional information, such as tangent in,
 *					tangent out, and tangent rules. The first key frame of each
 *					span will also sore the coefficient for the cubic equation.
 */
class KeyFrame
{
	float time;
	float value;
	float tanIn;
	float tanOut;
	std::string ruleIn;
	std::string ruleOut;
public:
    Channel *ch;
	/*!
	 * \Brief	:	Default constructor
	 */
	KeyFrame();
	/*
	 * \Brief	:	Construcor
	 */
    KeyFrame(float t, float v, std::string ri, std::string ro);
    /*
     *  \Brief  :   Destructor.
     */
    ~KeyFrame();
	/*!
	 * \Brief	:	Setter
	 */
	void setTime(float t);
	/*!
	 * \Brief	:	Setter
	 */
	void setValue(float v);
	/*!
	 * \Brief	:	Setter
	 */
	void setTanIn(float ti);
	/*!
	 * \Brief	:	Setter
	 */
	void setTanOut(float to);
	/*!
	 * \Brief	:	Setter
	 */
	void setRuleIn(std::string ri);
	/*!
	 * \Brief	:	Setter
	 */
	void setRuleOut(std::string ro);
	
	/*!
	 * \Brief	:	getter
	 */
	float getTime();
	/*!
	 * \Brief	:	getter
	 */
	float getValue();
	/*!
	 * \Brief	:	getter
	 */
	float getTanIn();
	/*!
	 * \Brief	:	getter
	 */
	float getTanOut();
	/*!
	 * \Brief	:	getter
	 */
	std::string getRuleIn();
	/*!
	 * \Brief	:	getter
	 */
	std::string getRuleOut();
};
#endif //CRISTIAN_TRONCOSO_KEYFRAME_H
