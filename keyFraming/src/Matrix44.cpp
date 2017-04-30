//
// Matrix44.h
// Cristian Troncoso 2/15/2016
//

#include "Matrix44.h"



Matrix44::Matrix44()
{
    data[0]     = 0.0; data[1]  = 0.0; data[2]  = 0.0; data[3]  = 0.0;
    data[4]     = 0.0; data[5]  = 0.0; data[6]  = 0.0; data[7]  = 0.0;
    data[8]     = 0.0; data[9]  = 0.0; data[10] = 0.0; data[11] = 0.0;
    data[12]    = 0.0; data[13] = 0.0; data[14] = 0.0; data[15] = 0.0;
}

Matrix44::Matrix44(double c)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            data[i * 4 + j] = c;
        }
    }
}

Matrix44::Matrix44(Matrix44& m)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            data[i * 4 + j] = m.data[i * 4 + j];
        }
    }
}

Matrix44::~Matrix44(){}

void Matrix44::set(float m0, float m1, float m2, float m3,
                   float m4, float m5, float m6, float m7,
                   float m8, float m9, float m10, float m11,
                   float m12, float m13, float m14, float m15)
{
    data[0]     = m0 ; data[1]  = m1 ; data[2]  = m2 ; data[3]  = m3;
    data[4]     = m4 ; data[5]  = m5 ; data[6]  = m6 ; data[7]  = m7 ;
    data[8]     = m8 ; data[9]  = m9 ; data[10] = m10; data[11] = m11;
    data[12]    = m12; data[13] = m13; data[14] = m14; data[15] = m15;
}

double* Matrix44::get()
{
    return data;
}

Matrix44 Matrix44::transpose(void)
{
    Matrix44 transpose;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            transpose.data[j*4+i] = data[i*4+j];
        }
    }
    return transpose;
}

Matrix44 Matrix44::inverse(void)
{
    Matrix44 b;
    //TODO
    //Calculate the inverse of this matrix
    
    return b;
}

Matrix44 Matrix44::orthoNormalInverse(void)
{
    Matrix44 b;
    //This will be useful when implementing cameras!
    //TODO
    return b;
}

void Matrix44::print(std::string comment)
{
    //Width constants and variables
    static const int pointWidth = 1;
    static const int precisionWidth = 4;
    int integerWidth = 1;
    
    //Determine the necessary width to the left of the decimal point
    float* elementPtr = (float*)data;
    float maxValue = fabsf(*(elementPtr++));
    while(elementPtr++ < ((float*)data+16))
        if(fabsf(*elementPtr) > maxValue)
            maxValue = fabsf(*elementPtr);
    
    while(maxValue >= 10.0) { ++integerWidth; maxValue /= 10.0; }
    
    //Sum up the widths to determine the cell width needed
    int cellWidth = integerWidth + pointWidth + precisionWidth;
    
    //Set the stream parameters for fixed number of digits after the decimal point
    //and a set number of precision digits
    std::cout << std::fixed;
    std::cout << std::setprecision(precisionWidth);
    
    //Print the comment
    std::cout << comment << std::endl;
    
    //Loop through the matrix elements, format each, and print them to screen
    float cellValue;
    for(int element = 0; element < 4; element++)
    {
        std::cout << std::setw(1) << (element == 0 ? "[" : " ");
        for(int vector = 0; vector < 4; vector++)
        {
            cellValue =  data[element * 4 + vector];
            std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
            std::cout << std::setw(0) << (vector < 3 ? " " : "");
        }
        std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
    }
}
