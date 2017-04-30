/**
 ** \name grid.cpp
 ** \brief Label a set of points with their Columns and Rows
 ** \author Cristian Troncoso
 ** \date April 29, 2017
 **/
#include <iostream>
#include <vector>
#include <math.h>
#include "Point2D.h"
#include "Data.h"
#include "ColRow.h"

/*
 * @brief  Rotate  the  grid  to align it  with the xy-axis.It
 * finds  the right-most  and left-most  points  and  rotate 
 * accordingly. Clockwise  if left-most is positive, otherwise
 * rotate counter-clockwise.
 * @condition The left-most point previously translated to origin.
 * @param<out> vector of points with new position aligned 
 * to the xy-axis
 */
 void rotateGrid(vector<Point2D> &v, float &theta){
  // First,Find right and left most Points.
  // Since the vector is sorted by x just get first and last
  bool clockwise = true; 
  Point2D rightMost;
  Point2D leftMost;

  rightMost.assign(v.at(v.size()-1));
  leftMost.assign(v.at(0));
  
  float vec2[2];
  if(leftMost.getX() < 0.0f){
    vec2[0]= leftMost.getNewX();
    vec2[1]= leftMost.getNewY();
    clockwise = false;
  }else{
    vec2[0] = rightMost.getNewX();
    vec2[1] = rightMost.getNewY();
  } 
  
  float unitVec2[2];
  float norm = sqrt(pow(vec2[0],2) + pow(vec2[1],2));
  
  unitVec2[0] = vec2[0] / norm;
  unitVec2[1] = vec2[0] / norm;

  if((unitVec2[0] == 1.0f || unitVec2[0] == -1.0f) && unitVec2[1] == 0.0){
    // the grid need no rotation
    return;
  }else{
    // Rotate grid
    float dist = sqrt(pow(vec2[0],2) + pow(vec2[1],2));
    theta = asin(vec2[1] / dist);
    // Start rotation
    for(size_t i=0; i<v.size(); i++){
      Point2D p(v.at(i).getNewX(), v.at(i).getNewY());
      float newX;
      float newY;
      if(clockwise){
        newX = p.getX()*cos(theta) + p.getY()*sin(theta);
        newY = -1*p.getX()*sin(theta) + p.getY()*cos(theta);
      }else{
        newX = p.getX()*cos(theta) - p.getY()*sin(theta);
        newY = p.getX()*sin(theta) + p.getY()*cos(theta);
      }
      v.at(i).updateNewPos(newX, newY); 
    }
  }
}

/*
 * @brief Translate the grid to the origin such that the
 * point with smallest y-value is set as the (0,0) coords.
 * When the grid is aligned with the x-axis, the algorithm 
 * will choose the leftmost x because the grid is sorted by 
 * x values
 */
void translateGrid(vector<Point2D> &v){
  // Find smallest y-value.
  Point2D minY(v.at(0).getX(), v.at(0).getY());
  for(size_t i=0; i<v.size(); i++){
    Point2D p(v.at(i).getX(), v.at(i).getY());
    if(p.getY() < minY.getY())
      minY.assign(p);
  }
  // Translate grid
  float translateX = minY.getX();
  float translateY = minY.getY();
  for(size_t i=0; i<v.size(); i++){
    Point2D p(v.at(i).getX(), v.at(i).getY());
    // align min-y with origin
    float newX = p.getX() - translateX;
    float newY = p.getY() - translateY;
    v.at(i).updateNewPos(newX, newY); 
  }
} 

int main(int argc, char **argv){
 
  if(argc < 2){
    cerr<<" Usage: "<< argv[0]<< " File name"<<endl;
    exit(1);
  }
  
  // Vector containing the final labeled Points
  vector<Point2D> grid;  
  float angle; 
  // Pull the data out from the data handler   
  Data *d = new Data(string(argv[1]),1);
  vector<pair<float, float>> pairData = d->getData();
  int n = d->getLength();

  // Create 2D Point objects and keep them in a vector pv. 
  Point2DFactory *pf = new Point2DFactory(pairData,n);
  // get data as 2D points
  vector<Point2D> pv = pf->getPoints();  
  
  // To find the lowest Y value, first sort about x. Then, when 
  // finding lowest Point check if it's the left or right-most 
  // point
  sort(pv.begin(), pv.end(), sortByIncreasingX);
  translateGrid(pv);
  rotateGrid(pv, angle);
  
  // Sort data by their y-value to organize them by rows
  sort(pv.begin(), pv.end(), sortByNewY);
 
  // Label the points with its respective Cols and Rows 
  int rowLen = sqrt(n); // length of a row
  vector<Col> cols(rowLen);
  for (int idx=0; idx<n; idx+=rowLen){
    vector<Point2D> row;
    for(int j=idx; j< (idx+rowLen); j++){
      row.push_back(pv.at(j));
    }
    sort(row.begin(), row.end(), sortByNewX);
    Row R;
    for(int r=0; r<rowLen; r++){  
      R.push(row.at(r));
      cols.at(r).push(row.at(r));
    }
    R.toString(); 
  }
  for(int i=0; i<rowLen; i++)
    cols.at(i).toString();
  
  cout<<"Alpha="<<angle * 180.0 / M_PI<<" degrees"<<endl;
  return 0;
} 

