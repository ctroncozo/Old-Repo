#ifndef CRISTIAN_TRONCOSO_SPAN_H
#define CRISTIAN_TRONCOSO_SPAN_H

#include "KeyFrame.h"
#include "Matrix44.h"
#include "Vector4D.h"
/*!
 * \Brief	:	Span class keep the information regarding a time span between two frames.
 *					The span is defined by the value of the two keyframes and the OUTGOING tangent
 *					of the FIRST and INCOMING tangent of the SECOND.
 */
class Span
{
	
public:
	KeyFrame *first;    // first key frame.
	KeyFrame *second;   // second key frame.

	/*!
	 * \Brief	:	Default constructor.
	 */
	Span();
	/*!
	 * \Brief	:	Constructor 
	 * \Params	:	start and edn frame.
	 */
	Span(KeyFrame *f, KeyFrame *s);
	/*! 
	 * \Brief	:	Destructor.
	 */
    ~Span();
	/*!
	 * \Brief	:	Check if time value belong to this span.
	 *	\Return	:  0 within this span.
	 *					1 hit first frame of this span.
	 *					2 hit second frame of this span.
	 */
	int findTime(float time);
	/*!
	 * \Brief	: Return parameter u calculated by the Inv Lerp
	 */
	float getU();
	/*!
	 * \Brief	: Return the cubic coefficients
	 */
	Vector4D getCoef();

protected:
	float k; // k= 1 / (t1 - t0)
	float u;
	Vector4D coef;
	Matrix44 hermite;
};	
#endif //CRISTIAN_TRONCOSO_SPAN_H
