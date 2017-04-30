/**
 ** \name ColRow.h
 ** \brief Stores Rows and Columns information
 ** \author Cristian Troncoso
 ** \date April 29, 2017
 **/
#ifndef COLROW_H
#define COLROW_H

#include <vector>
#include <iostream>
#include "Point2D.h"
/*
 * @brief Stores information for each Row
 */
using namespace std;
class Row{
public:
  Row(){
    id = ROWCOUNTER++;
  };
  void push(Point2D p){
    row.push_back(p);
  };
  void toString(){
    vector<Point2D>::iterator it;
    cout<<"Row "<<id<<": ";
    for(it = row.begin(); it != row.end(); ++it)
    {
      cout<<(*it).getX()<<","<<(*it).getY();
      if(it + 1 == row.end())
          break;
      cout<<" - ";
    }
    cout<<"\n";
  };
  ~Row(){};
private:
  size_t id;
  vector<Point2D> row;
  static size_t ROWCOUNTER;
};

/*
 * @brief Store information for each col
 */
class Col{
public:
  Col(){
    id = COLCOUNTER++;
  };
  void push(Point2D p){
    col.push_back(p);
  };
  void toString(){
    vector<Point2D>::iterator it;
    cout<<"Col "<<id<<": ";
    for(it = col.begin(); it != col.end(); ++it)
    {
      cout<<(*it).getX()<<","<<(*it).getY();
      if(it + 1 == col.end())
          break;
      cout<<" - ";
    }
    cout<<"\n";
  };
  ~Col(){};
private:
  size_t id;
  vector<Point2D> col;
  static size_t COLCOUNTER;
};
size_t Row::ROWCOUNTER = 0;
size_t Col::COLCOUNTER = 0;
#endif
