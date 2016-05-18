
/*
 I am using s.at(k) to get the character in string s at position k
 instead of s[k] because xcode checks to see if s.at(k) is out of range
 */


#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include "grid.h"
using namespace std;


bool isRouteWellFormed(string route);
bool isValidLet(char check);
bool isValidPosition(int r, int c);
int  navigateSegment(int r, int c , char dir , int maxSteps);
int  navigateRoute (int sr, int sc, int er, int ec, string route, int& nsteps);
string processRoute( string route, int& position);
void updatePosition(int& row,int& col, char dir, int steps);

const char ZERO_CHARACTER = '0';
const char NORTH = 'n';
const char SOUTH = 's';
const char EAST = 'e';
const char WEST = 'w';

int main()
{
    //int n = -12;

    setSize(5,5);      // make a 3 by 4 grid
    setWall(1,4);      // put a wall at (1,4)
    setWall(2,2);      // put a wall at (2,2)
    if (!isWall(3,2))  // if there's no wall at (3,2)  [there isn't]
        setWall(3,2);  //    put a wall at (3,2)
    draw(3,1, 3,4);
    int len=-234;
    assert(navigateRoute(-1,3,2,3,"n2s3",len)==2 && len == -234);
    assert(navigateRoute(1,4,2,3,"n2s3",len)==2 && len == -234);
    assert(navigateRoute(1,3,-2,3,"n2s3",len)==2 && len ==-234 );
    assert(navigateRoute(1,3,1,4,"n2s3",len)==2 && len ==-234 );
    assert(navigateRoute(4,1,2,3,"s3", len) == 3 && len == 1);
    cout << "All tests succeeded" << endl;

    
}

//checks to see if a route is valid
//a valid route is....
bool isRouteWellFormed(string route)
{
    //if the string isn't empty, check to see if the first letter is valid
    if( route.size()!=0 && !isValidLet(route.at(0)) )
        return false;
    
    int index =1;
    while ( index < route.size() )
    {
        //every character must either be a digit or a validLet
        if (!isValidLet(route.at(index)) && !isdigit(route.at(index)) )
            return false;
        
        //make sure there isn't more than two digits in a row
        if ( isdigit(route.at(index)) )
        {
            int digit_index = index;
            
            //add up the number of digits in a row
            while (digit_index<route.size() && isdigit( route[digit_index] ) )
            {
                
                digit_index++;
            }
            
            //more than two digits in a row, return false
            if (digit_index >= index+3)
                return false;
            
            //else update index
            else
                index = digit_index;
        }
        
        else
            index++;
    }
    
    return true;
}

int navigateSegment(int r, int c , char dir , int maxSteps)
{
    int direction;
    int steps=0;
    //if the argument values are not valid, return -1
    //invalid arguments are:
    //    (r,c) is a not valid empty position
    //    dir is a not valid cardinal direction
    //    maxSteps is negative
    if (!isValidPosition(r,c) || !isValidLet(dir) || maxSteps<0)
        return -1;
    // account for upper or lower case input
    dir = tolower(dir);
    if (dir == SOUTH || dir == EAST)
        // you will be increasing r or c by moving south or east respectively
        direction = 1;
    else
        //you will be decreasing r or c by moving north or west respectively
        direction = -1;
    
    if (dir == NORTH || dir == SOUTH)
        // while the next position is a valid position, then take a step in that direction until maxSteps is reached or an invalid position is reached
        // only r is affected
        while (steps !=maxSteps && isValidPosition(r + (steps + 1)* direction , c))
               steps++;
    else
        // while the next position is a valid position, then take a step in that direction until maxSteps is reached or an invalid position is reached
        // only c is affected
        while (steps !=maxSteps && isValidPosition(r,c + (steps+1)*direction))
               steps ++;
    return steps;
}

int  navigateRoute (int sr, int sc, int er, int ec, string route, int& nsteps)
{
    //check to see if the arguments are valid
    //valid arugments are:
    //    (sr,sc) and (er,ec) are valid, empty positions
    //    route is syntactically correct
    if (!isValidPosition(sr,sc) || !isValidPosition(er,ec) || !isRouteWellFormed(route) )
        return 2;
    //only reset nsteps if arguments are valid
    nsteps=0;
    int i=0;
    int row =sr;
    int col = sc;
    while (i < route.size() )
    {
        // get the route segment starting at position i
        string segment  = processRoute(route, i);
        char dir = segment[0];
        int stepsToTake=0;
        // convert the number characters in the route segment to integers
        for (int i=1; i<segment.size() ; i++)
        {
            stepsToTake = stepsToTake*10 + (segment[i] - ZERO_CHARACTER);
        }
        //if the size is 1 (i.e. segment is only a direction) then take 1 step
        if (segment.size() ==1)
            stepsToTake =1;
        //naviagte the route segment
        int stepsTaken = navigateSegment( row, col , dir, stepsToTake);
        nsteps += stepsTaken;
        //if the route was not fully navigable then stop and return the maximum amount of steps
        if (stepsTaken != stepsToTake)
        {
            return 3;
        }
        //update row and col
        updatePosition(row,col, dir, stepsTaken);
    }
    // check to see if the ending position is what the argument claims
    if (row==er && col==ec) return 0;
    else return 1;
    
}

//checks to see if a letter is valid (i.e. a cardinal direction)
bool isValidLet(char check)
{
    //letter can be upper or lower case
    check = tolower(check);
    return (check== EAST|| check == WEST || check == SOUTH || check == NORTH);
}

//checks to see if (r,c) is a valid and empty position
bool isValidPosition (int r, int c)
{
    // to be on grid, r and c must be on interval [1, # of rows] and [1, # of cols] respectively
    // to be empty (r,c) must not be occupied by a wall
    
    return (r>0 && c>0 && r <= getRows() && c <= getCols() && !isWall(r,c) );
}

// takes route and returns the route segment starting at a certain position
string processRoute( string route, int& position)
{
    // if the route is syntactically correct, position will initially be a letter
    string seg = "";
    do{
        seg += route[position];
        position++;
    }while (position != route.size() && isdigit(route.at(position)) );
    
    
    return seg;
}

//update the position (row, col) with the number of steps taken in a certain direction
void updatePosition(int& row,int& col, char dir, int steps)
{
    int direction;
    //can be either upper or lower case
    dir=tolower(dir);
    if (dir == EAST || dir == SOUTH)
        // if east or south, col and row will be increasing
        direction = 1;
    else
        //if north or west, row and col will be decreasing
        direction = -1;
    // if moving north or south, only row is affected
    if (dir == NORTH || dir == SOUTH) row += (steps * direction);
    //if moving east or west, only col is affected
    else col += (steps * direction);
}

