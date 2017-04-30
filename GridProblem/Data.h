/**
 ** \name Data.h
 ** \brief It handles Data input
 ** \author Cristian Troncoso
 ** \date April 29, 2017
 **/

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "Point2D.h"
#include "fstream"
#include <sstream>
using namespace std;

/*
 * @brief A class to store test data
 */
class StoreData {
  public:
        static const int dataSize = 9;
        static const float dummyData[9][2];
        static const float test[9][2];
};

float const StoreData::dummyData[9][2] = {
        {1.5, 2.5},
        {2.0, 2.0},
        {2.5, 1.5},
        {1.0, 2.0},
        {1.5, 1.5},
        {2.0, 1.0},
        {1.5, 0.5},
        {0.5, 1.5},
        {1.0, 1.0} 
};

float const StoreData::test[9][2] = {
        {10.0000, 10.000},
        {9.9000 , 12.000},
        {9.7000 , 14.000},
        {12.0000, 10.100},
        {11.8000, 12.100},
        {11.7000, 14.100},
        {14.0000, 10.300},
        {13.8000, 12.300},
        {13.7000, 14.300}
};

/*
 * @brief data handler, read from file or memory
 */
class Data{
private:
  vector<pair<float, float>>pairData;
  int length;
public:
  /*
   * @brief Constructor
   */
  Data(string name, int type=1){
    length = StoreData::dataSize;
    if(type == 0){
      for(int i=0; i<length; i++){
        pair<float, float> p(StoreData::test[i][0],StoreData::test[i][1]); 
        pairData.push_back(p);
      }
    }else{
      ifstream ifile(name, ios::in);
      if(!ifile){
        cerr<<"File cannot be open"<<endl;
        exit(1);
      }
      while(ifile){
        string str;
        vector<float> coord;
        ifile >> str;
        if(0 == str.length())
          break;
        split(str, coord);
        pair<float, float> p(coord.at(0),coord.at(1)); 
        pairData.push_back(p);
      }
    }
  };
 
  /*
   * @brief parse each entry pair from input file
   *
   * @param<in> One pair - a line at the time from input file
   * @param<out> the pair of coordinates as float
   */ 
  void split(const string& str, std::vector<float>& coord)
  {
    char delim = ',';
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) 
    {
      float x = stof(token);
      coord.push_back(x);
    }
  };
  
  /*
   * @brief getter for the parsed numeric representation of the 
   * pairs of coordinates
   *
   * @return  vector with all coordinates pairs.
   */
  vector<pair<float, float>>& getData()
  {
    return pairData;
  };
  int getLength(){
    return length;
  }
  ~Data(){};
};


#endif
