//
//  main.cpp
//  Project 2
//
//  Created by Caroline Quigg on 10/8/15.
//  Copyright © 2015 Caroline Quigg. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
bool run = true;

int main()
{
    //prompt user for input
    //if input is invalid print an error message and end program
    
    cout << "Units sent: ";
    int units;
    cin >> units;
    cin.ignore(10000,'\n');
    
    if(units<0)
    {
        cout << "---" << endl;
        cout << "The number of units sent must be nonnegative." << endl;
        return 1;
        
    }
    
    cout << "Title: ";
    string title;
    getline(cin,title);
    
    if(title == "")
    {
        cout << "---" << endl;
        cout << "You must enter a title." << endl;
        return 1;
    }
    
    cout << "Base price: ";
    double basePrice;
    cin >> basePrice;
    cin.ignore(100000,'\n');
    
    
    if(basePrice < 0)
    {
        cout << "---" << endl;
        cout << "The base price must be nonnegative." << endl;
        return 1;
    }
    
    cout << "Premium item? (y/n): ";
    string premium;
    getline(cin,premium);
    
    
    if( (premium != "y" ) && (premium != "n"))
    {
        cout << "---" << endl;
        cout << " You must enter y or n." << endl;
        return 1;
    }
    
    cout << "---" <<endl;
    
    //formatting
    cout.setf(ios::fixed);
    cout.precision(2);

    
    //calculate royalties for first 400 units using a royalty rate of 9%
    double royalties;
    int unitsInRange;
    double royaltyRate = 0.09;
    
    //if units is less than or equal to 400, unitsInRange is the same as units
    //otherwise unitsInRange is equal to 400
    if(units <=400)
        unitsInRange = units;
    else
        unitsInRange = 400;
    
    //royalties is calculated using 9% for unitsInRange
    royalties = unitsInRange * basePrice * royaltyRate;
    
    //400 is subtracted from unitsInRange to signify the remaining amount of units
    units -= 400;
    
    
    //if remaining units is >0, continue to next range, else print results and exit the program
    if(units<=0)
    {
        cout << title << " earned $" << royalties << " in royalties." << endl;
        return 0;
    }
    
    //continue to next range, (400,1200] royalty rate dependent on premium
    
    //if units is less than or equal to 800, unitsInRange is the same as units
    //otherwise unitsInRange is equal to 800
    if(units<=800)
        unitsInRange = units;
    else
        unitsInRange = 800;
    
    //if premium, rate = 16%
    //if not premium, rate = 13%
    if(premium== "y")
    {
        //calculate royalties for this range, using 16%
        royaltyRate = 0.16;
    }
    else
    {
        //calculate royalties for this range, using 13%
        royaltyRate = 0.13;
    }
    
    //calculate royalties in range, and add to current royalty value
    royalties = royalties + (unitsInRange * basePrice * royaltyRate);
    
    //800 is subtracted from units to signify the remaining units
    units -= 800;
    
    //if remaining units is >0, continue to next range, else print results and exit the program
    if(units<=0)
    {
        cout << title << " earned $" << royalties << " in royalties." << endl;
        return 0;
    }
    
    //for remaining units 1200+ , use royalty rate 14%
    //therefore there is no need for unitsInRange, just use units
    royaltyRate = 0.14;
    
    //royalties is calculated using 9% for units
    royalties = royalties + (units * basePrice * royaltyRate);
    
    //print out results and exit program
    cout << title << " earned $" << royalties << " in royalties." << endl;
    return 0;
    
}
