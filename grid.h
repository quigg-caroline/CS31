//
//  grid.h
//  Project 3
//
//  Created by Caroline Quigg on 10/24/15.
//  Copyright © 2015 Caroline Quigg. All rights reserved.
//

#ifndef grid_h
#define grid_h

// Grid library interface

const int MAXROWS = 20;
const int MAXCOLS = 20;

void setSize(int nr, int nc);
int getRows();
int getCols();
void setWall(int r, int c);
bool isWall(int r, int c);
void draw(int rStart, int cStart, int rEnd, int cEnd);
void draw(int rStart, int cStart, int rEnd, int cEnd, int rRobot, int cRobot);

#endif /* grid_h */
