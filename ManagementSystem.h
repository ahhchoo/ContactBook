//
//  ManagementSystem.h
//  Project1
//
/**
 * Definition of class ManagementSystem. It is used to access and manipulate
 * at most 5 Contact Books. Contains ability to add, delete, modify and display all
 * Contact Books.
 **/
//  Created by Alison Cheu


#ifndef __Project1__ManagementSystem__
#define __Project1__ManagementSystem__

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "ContactBook.h"
class ManagementSystem{
private:
    int capacity;
    int size;
    ContactBook** array;
public:
    ManagementSystem();
    
    ManagementSystem(const ManagementSystem& other);//copy constructor
    ~ManagementSystem();//destructor
    ManagementSystem& operator=(const ManagementSystem&);//assignment operator, by reference to access member functions
    
    bool isFull();
    bool isEmpty();
    
    int getCapacity() const;
    int getSize() const;
    void setCapacity(int);
    void setSize(int);
    
    ContactBook** getArray();
    bool makeNewCB();
    ContactBook* search();
    bool remove(ContactBook*);
    void displayAll() const;
    
    void select(ContactBook*);
    bool check(int , ContactBook& );
};

#endif /* defined(__Project1__ManagementSystem__) */
