#ifndef CRISTIAN_TRONCOSO_CHANNEL_H
#define CRISTIAN_TRONCOSO_CHANNEL_H

#include "KeyFrame.h"
#include "Span.h"
#include "Matrix44.h"
#include "string"
#include <vector>

class Channel
{

	std::vector<Span*> spans;               // List of key frames pairs.
	float tmin;								// Channel's starting time.
	float tmax;								// Channel's ending time.
    static const int LEFT  = 0;
    static const int RIGHT = 1;
    static const int ERROR = -10000000;
public:
    int id;
    std::vector<KeyFrame*> frames;	// List all key frames present in a channel.
    std::string extrapolate[2];		// Channel's extrapolation rules.
	Channel();
	~Channel();
	float evaluate(float time);
	/*!
	 * \Brief	:	Find which span (pair of key frames) a given time correspond to.
	 *					Or if the time hit exactly a key frame.
	 */
	bool findValue(Span * s, float time, float &value);
	/*!
	 * \Brief	:	Calculate Linear tangent
	 */
	void calculateLinearTangent(int i);
	/*!
	 * \Brief	:	Calculate smooth tangent.
	 */
	void calculateSmoothTangent(int i);
	/*!
	 * \Brief	:	Calculate tangents in and tangents out on each frame.
	 *					Calculate the cubic coefficients if a time is within two frames.
	 */
	void precompute();
	/*!
	 * \Brief	:	Create pairs of frames.
	 */
	void createSpans();
};

#endif //CRISTIAN_TRONCOSO_CHANNEL_H
