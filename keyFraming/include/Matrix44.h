//
// Matrix44.h
// Cristian Troncoso 2/15/2016
//
#ifndef Matrix44_h
#define Matrix44_h

#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Vector4D.h"



class Matrix44
{
private:
    double data[16];
    
public:
    /*!
     * \Brief    : Constructor, Initializes the matrix to zero.
     */
    Matrix44();
	
    /*!
     * \Brief		: Constructor, Initializes the matrix to a constant.
     */
    Matrix44(double c);
    /*!
     * \Brief    : Constructor, Initializes from another matrix.
     */
    Matrix44(Matrix44& m);
    /*!
     * \Brief   : Destructor.
     */
    ~Matrix44();
	 /*!
	 * \Brief	   : Set user entered values
	 */
	 void set(float m0, float m1, float m2, float m3,
	 			 float m4, float m5, float m6, float m7,
				 float m8, float m9, float m10, float m11,
                 float m12, float m13, float m14, float m15);
    /*!
    * \Brief    : Returns the data of this matrix.
    */
    double* get();
    /*!
    * \Brief    : Negation.
    */
    inline Matrix44 operator-( void ) const
    {
        Matrix44 m;
        for(int i = 0; i < 16; i++)
        {
            m.data[i] = (-1 * data[i]);
        }
        return m;
    }
    /*!
    * \Brief    : Matrix Addition.
    */
    inline Matrix44 operator+(const Matrix44& m)
    {
        Matrix44 ret;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                ret.data[i * 4 + j] = data[i * 4 + j] + m.data[i * 4 + j];
            }
        }
        return ret;
    }
    /*!
    * \Brief    : Matrix Subtraction.
    */
    inline Matrix44 operator-(const Matrix44& m)
    {
        Matrix44 ret;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                ret.data[i * 4 + j] = data[i * 4 + j] - m.data[i * 4 + j];
            }
        }
        return ret;
    }
    /*!
     *\Brief     : Scalar multiplication.
     */
    inline Matrix44 operator*( const double& c ) const
    {
        Matrix44 ret;
        for(int i = 0; i < 16; i++)
        {
            ret.data[i] = c * data[i];
        }
        return ret;
    }
    /*!
     * \Brief   : Addition / assignment.
     */
    inline void operator+=(const Matrix44& m)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                data[i * 4 + j] = data[i * 4 + j] + m.data[i * 4 + j];
            }
        }
    }
    /*!
     * \Brief   : Vector4D matrix multiplication.
     */
    inline Vector4D operator*(const Vector4D& v) const
    {
        Vector4D ret;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                ret[i] += v[j] * data[i * 4 + j];
            }
        }
        return ret;
    }

    /*!
     * \Brief   : Returns the transpose.
     */
    Matrix44 transpose(void);
    /*!
     * \Brief   : Inverse.
     */
    Matrix44 inverse(void);
    /*!
     * \Brief   : Calculates the inverse of this matrix with the assumption that it is ortho-normal.
     */
    Matrix44 orthoNormalInverse(void);
    /*!
     * \Brief   : Return the value a location j.
     */
    inline double operator[]( int j ) const
    {
        return data[j];
    }
    /*!
     * \Brief   : Print out data.
     */
    void print(std::string comment);
};
#endif // End Matrix44_h
