#include "Span.h"

Span::Span(){}

Span::Span(KeyFrame *f, KeyFrame *s):first(f),second(s)
{
	hermite.set( 2, -2,  1, 1,
                -3,  3, -2,-1,
                 0,  0,  1, 0,
                 1,  0,  0, 0
				  );		
		
	float p0 = first->getValue();
	float p1 = second->getValue();
	float t0 = first->getTime();
	float t1 = second->getTime();
	float v0 = first->getTanOut();
	float v1 = second->getTanIn();
		
	Vector4D vars(p0, p1, (t1 - t0)*v0, (t1 - t0)*v1); 
	
	coef = hermite * vars;

	if((t1 - t0) != 0.0)	
		k = 1 / (t1 - t0);
	else
		k = 0; 
	u = 0;
}

Span::~Span(){}

int Span::findTime(float t)
{
	if(t == first->getTime()) return 1;
	if(t == second->getTime()) return 2;
	else if(t > first->getTime() && t < second->getTime())
	{
		float t0 = first->getTime();
		u = (t - t0) * k;
        return 0;
	}
	
    return -1;
}

float Span::getU()
{
	return u;
}

Vector4D Span::getCoef()
{
	return coef;
}


