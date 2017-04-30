/**
 * @file Color.h
 * @author  Cristian Troncoso <troncoso.cristian.e@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The color Class handle OpenGL color settings.
 */

#ifndef CRISTIAN_TRONCOSO_COLOR_H
#define CRISTIAN_TRONCOSO_COLOR_H

#include <string>
#include <assert.h>
#include <iostream>
#define clampf(min,max,num) (num < min ? min : num > max ? max : num)

class Color
{
	protected:
	float r,g,b,a;

	public:
	Color();
	Color(float ir, float ig, float ib);
	Color(float ir, float ig, float ib, float ia);
	Color(float ptr[4]);
	~Color();
	float *ptr();
	float& operator[](const int& idx);
	const float& operator[](const int& idx) const;
	Color interpolate(Color& c1, float t);
	void print(std::string comments); 
	
	static Color LightYellow() ;		
	static Color Violet()		;	
	static Color Lime()			;	
	static Color Green()			;	
	static Color Cyan()			;	
	static Color SkyBlue()		;	
	static Color Blue()			;	
	static Color Brown()			;	
	static Color White()			;	
	static Color Gray()			;	
	static Color Black()			;	
	static Color Red()			;
	static void Mat(int ID, float *param);
	static void Light(int ID, float *param);
};
#endif //CRISTIAN_TRONCOSO_COLOR.H
