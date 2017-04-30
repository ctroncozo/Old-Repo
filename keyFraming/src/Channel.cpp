#include "Channel.h"
#include <math.h>
Channel::Channel(){}

Channel::~Channel(){}

float Channel::evaluate(float time)
{
	float dof = 0;
    float t = 0;
    float cIndex = 0;
    float start = 0;
    
    if(time < tmin || time > tmax)
    {
        if(extrapolate[0] == "constant")
        {
            if (time < tmin)
                return frames.front()->getValue();
            else
                return frames.back()->getValue();
        }
        else if(extrapolate[0] == "cycle")
        {
            cIndex = floor((time - tmin)/(tmax - tmin));
            start = cIndex * (tmax - tmin) + tmin;
            t = time - start + tmin;
            
            for(std::vector<Span*>::iterator it = spans.begin(); it != spans.end(); ++it)
                if(findValue((*it), t, dof))
                    return dof;
        }
        else if(extrapolate[0] == "cycle_offset")
        {
            cIndex = fabs((time - tmin)/(tmax - tmin));
            start = cIndex * (tmax - tmin) + tmin;
            t = time - start + tmin;
            float offset = frames.back()->getValue() - frames.front()->getValue();
            
            for(std::vector<Span*>::iterator it = spans.begin(); it != spans.end(); ++it)
                if(findValue((*it), t, dof))
                    return (dof + (cIndex * offset));
        }
    }
    else
    {
        for(std::vector<Span*>::iterator it = spans.begin(); it != spans.end(); ++it)
            if(findValue((*it), time, dof))
                return dof;
    }
    return ERROR;
}

bool Channel::findValue(Span * s, float time, float &value)
{
	int r = s->findTime(time);
	if (r == 0) // within thi span.
    {
        float u = s->getU();
        Vector4D coef = s->getCoef();
        float a = coef.x;
        float b = coef.y;
        float c = coef.z;
        float d = coef.w;
        value = d + u * (c + u * (b + u * (a)));
        return true;
    }
	else if(r == 1)                   // hit first key of this span.
    {
        value = s->first->getValue();
        return true;
    }
    else if(r == 2)                   // hit second key of this span.
    {
        value = s->second->getValue();
    }
    else if(r == -1)
    {
        value = ERROR;
        return false;
    }
    return false;
}

void Channel::calculateLinearTangent(int i)
{
	float v0_out = 0;
	float v1_in = 0;
	float p0 = 0;
	float p1 = 0;
	float t0 = 0;
	float t1 = 0;

	// last key frame exeption
	if(i == (signed int)(frames.size() - 1))
	{
		// Tangent In for the last frame would be set when
		// calculating the value at (frames.size() - 2). Therefore
		// we just need to set Tangent Out sames at the previous frame.
		frames.at(i)->setTanOut(frames.at(i-1)->getTanOut());
	}
	else
	{
		p0 = frames.at(i)->getValue();
		p1 = frames.at(i+1)->getValue();
		t0 = frames.at(i)->getTime();
		t1 = frames.at(i+1)->getTime();

		v0_out = v1_in = (p1 - p0) / (t1 -t0);
			
		frames.at(i)->setTanOut(v0_out);
		frames.at(i+1)->setTanIn(v1_in);

		// first key frame exeption
		if(i == 0)
		{
			// set tangent in for p0 sames as tangent in for p1
			frames.at(i)->setTanIn(v1_in);		
		}
	}
}

void Channel::calculateSmoothTangent(int i)
{
	float v1_in = 0;
	float v1_out= 0;
	float p2 = frames.at(i+1)->getValue();
	float p0 = frames.at(i-1)->getValue();
	float t2 = frames.at(i+1)->getTime();
	float t0 = frames.at(i-1)->getTime();

	v1_in = v1_out = (p2 - p0) / (t2 - t0);

	frames.at(i)->setTanIn(v1_in);
	frames.at(i)->setTanOut(v1_out);
}

void Channel::precompute()
{
	for(int i = 0; i < (signed int)frames.size(); i++)
	{
		// if there is only one frame no need to caculate tangent
		if(frames.size() == 1)
			continue;

		// if rules are flat return tanIn and tanOut = 0
		if(frames.at(i)->getRuleIn() == "flat")
		{
			frames.at(i)->setTanIn(0.0f);
			frames.at(i)->setTanOut(0.0f);
		}
		else if(frames.at(i)->getRuleIn() == "linear")
		{
			calculateLinearTangent(i);
		}
		else if(frames.at(i)->getRuleIn() == "smooth")
		{	
			// if frames.size() == 2, degenerate to linear
			// or if size is more that 2 but the index is in the first 
			//or last frame, degenerate to linear
			
			if(frames.size() == 2 || i == 0 || i == (signed int)(frames.size() - 1))
			{
				calculateLinearTangent(i);
			}
			else
			{
				calculateSmoothTangent(i);			
			}
		}
	}
	tmin = frames.front()->getTime();
	tmax = frames.back()->getTime();
	createSpans();
}
				
void Channel::createSpans()
{
	if(frames.size() == 1)
	{
		Span *s = new Span(frames.at(0), frames.at(0));
		spans.push_back(s);
	}
	else
	{
		for(int i = 0; i < (signed int)(frames.size() - 1); i++)
		{
			Span *s = new Span(frames.at(i), frames.at(i+1));
			spans.push_back(s);
		}
	}
}

				
				
		
			
	
