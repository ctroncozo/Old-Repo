/**
 ** \name Point2D.h
 ** \brief Handles Cartesian points information
 ** \author Cristian Troncoso
 ** \date April 29, 2017
 **/
#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
/**
 * @brief Very Basic and simple class to manage 
 * 2D points in a Cartesian plane
 */
class Point2D{
private:
  float m_x;
  float m_y;
  int   m_row;
  int   m_col;
  Point2D *newPos;  
public:
  /*
   * @brief Constructors
   */
  Point2D(){
    m_col = 0;
    m_row = 0;
    newPos = (Point2D*)malloc(sizeof(Point2D));
  };
  Point2D(float x, float y):m_x(x), m_y(y){
    m_col = 0;
    m_row = 0;
    newPos = (Point2D*)malloc(sizeof(Point2D));
  };
  Point2D(float x, float y, int row, int col):
  m_x(x), m_y(y), m_row(row), m_col(col){
    newPos = (Point2D*)malloc(sizeof(Point2D));
  };
  
  /*
   * @brief Getters
   */ 
  float getY() const{
    return m_y;
  };
  float getX() const {
    return m_x;
  };
  float getNewY() const{
    return newPos->getY();
  };
  float getNewX() const{
    return newPos->getX();
  }
  
  /*
   * brief  Setters
   */
  void setX(float x){
    m_x = x;
  };

  void setY(float y){
   m_y = y;
  }; 

  /*
   * brief  Set new points position after transformation
   */
  void updateNewPos(float x, float y)
  {
     newPos->setX(x);
     newPos->setY(y);
  }; 

  /*
   * @brief print class summary
   */ 
  void toString(){
    cout<<"("<<getX()<<" , "<<getY()<<")"<<"-><Row :"<<m_row<<",Col :"<<m_col<<">"<<endl;
  };

  /*
   * brief assignment operation
   */
  void assign(const Point2D &p ) { 
    this->m_x = p.m_x;
    this->m_y = p.m_y;
    this->m_row = p.m_row;
    this->m_col = p.m_col;
    newPos->m_x = p.newPos->getX();
    newPos->m_y = p.newPos->getY();
  }

  /*
   * @brief Destructor
   */  
  ~Point2D(){};
  
};

/*
 * @brief Sorting logic
 */
bool sortByIncreasingX(const Point2D &l, const Point2D &r){
  return l.getX() < r.getX();
}

bool sortByNewY(const Point2D &l, const Point2D &r){
  return l.getNewY() > r.getNewY();
}

bool sortByNewX(const Point2D &l, const Point2D &r){
  return l.getNewX() < r.getNewX();
}


/*
 * @brief A factory class to create 2D points objects out
 * of raw data coming in from a file or dist
 */
class Point2DFactory{
private:
  vector<Point2D> points;
public:
  /*
   * @brief Constructor
   * @param<in> A reference to a vector with pairs of floats
   */
  Point2DFactory(vector<pair<float, float>> &pairs, int n){
    vector<pair<float,float>>::iterator it;
    for(it=pairs.begin(); it!=pairs.end(); ++it){
      Point2D p((*it).first, (*it).second);
      points.push_back(p);
    }
  };

  /*
   * @brief It returns the data in the form of 2D points objects
   */
  vector<Point2D>& getPoints(){
    return points;
  }
  ~Point2DFactory(){};
};


#endif
  

