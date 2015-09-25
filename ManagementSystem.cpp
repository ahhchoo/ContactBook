//
//  ManagementSystem.cpp
//  Project1
//
/**
 * Declaration of class ManagementSystem. It is used to access and manipulate
 * at most 5 Contact Books. Contains ability to add, delete, modify and display all 
 * Contact Books. 
 **/
//  Created by Alison Cheu
//

#include "ManagementSystem.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

//DEFAULT CONSTRUCTOR
ManagementSystem::ManagementSystem(){
    capacity=5;
    size=0;
    ContactBook** array=new ContactBook*[capacity];
}

//COPY CONSTURCTOR
ManagementSystem::ManagementSystem(const ManagementSystem& other): capacity(other.capacity),size(other.size)
{
    array= new ContactBook*[capacity];
    
    for(int i=0;i<size;i++)
    {
        array[i]=new ContactBook(*other.array[i]);
    }
}

//DESTRUCTOR
ManagementSystem::~ManagementSystem()
{
    for (int i=0;i<size;i++)//delete only removes dynamic variables to free up heap
    {
        delete array[i];
    }
}

//ASSIGNMENT OPERATOR
ManagementSystem& ManagementSystem::operator=(const ManagementSystem& other)//assignment operator, by reference to access member functions
{
    cout<<"Assignment operator called\n";
    if(this == &other)//if addresses are the same
    {
        return *this;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            delete array[i];
        }
        
        capacity=other.capacity;
        size=other.size;
        
        for(int i=0;i<size;i++)
        {
            array[i]=new ContactBook(*other.array[i]);

        }
    }
    return *this;
}

//IS FULL
bool ManagementSystem::isFull()
{
    return (size==capacity);
}

//CHECK IF CB IS EMPTY
bool ManagementSystem::isEmpty()
{
    return (size<0);
}

//GET AND SET FUNCTIONS FOR CAPACITY AND SIZE
int ManagementSystem::getCapacity() const
{
    return capacity;
}
int ManagementSystem::getSize() const
{
    return size;
}
void ManagementSystem::setCapacity(int otherCap)
{
    capacity=otherCap;
}
void ManagementSystem::setSize(int otherSize)
{
    size=otherSize;
}

//GET ARRAY FUNCTION
ContactBook** ManagementSystem::getArray()
{
    return array;
}
    
//MAKE NEW CONTACT BOOK
bool ManagementSystem::makeNewCB()
{
    ContactBook* toAdd=new ContactBook();
    cin>>*toAdd;
    array[size]=toAdd;
    size++;
    return true;
}

//SEARCH FUNCTION
ContactBook* ManagementSystem::search()
{
    int index;
	string lastName,firstName;
	cout<<"Please give me the owner's LAST NAME\n";
	cin>>lastName;
	cout<<"Please give me the owner's FIRST NAME\n";
	cin>>firstName;
    
    string otherLast, otherFirst;

    //For loop traverses array and searches for appropriate ContactBook based on given first and last name.
    for(index=0;index<size;index++)
    {
        otherLast=array[index]->getOwnLastName();
        if( lastName==otherLast)
        {
            cout<<"Search successful\n";
            return array[index];
        }
    }
    cout<<"Search unsuccessful\n";
    return NULL;

}

//REMOVE CONTACTBOOK
bool ManagementSystem::remove(ContactBook* toRemove)
{
    for(int i=0;i<size;i++)
    {
        if(array[i]==toRemove)//Once pointer is found in array by comparing addresses...
        {
            for(int j=i;j<=size-1;j++)//for loop traverses to the rest of the array until size-1, where...
            {
                if(j==size-1)//if j reaches the new last pointer...
                {
                    array[j]=NULL;//last pointer assigned NULL.
                }
                array[j]=array[j+1];//Meanwhile if not at size-1 pointer, assigns pointer to next pointer, therefore pointing to next Contact
            }
            size-=1;
            return true;
        }
        else;
    }
    return false;
    
}

//DISPLAY ALL
void ManagementSystem::displayAll() const
{
    for(int i=0;i<size;i++)
    {
        cout<<"Contents of Contact Book "<<i+1<<endl;
        cout<<*array[i];
    }

}

//Selection Menu to modify ContactBook contents
void ManagementSystem::select(ContactBook* chosenOne)
{
    bool valid=true;
    do{
    int num;
    cout<<"\t\t\t\t\tCONTACT BOOK MENU\n";
    cout<<"\t\t\t Please choose from the following options: \n";
    cout<<"\t\t\t 1. Add New Contact \n";
    cout<<"\t\t\t 2. Delete Old Contact \n";
    cout<<"\t\t\t 3. Display Contact Info \n";
    cout<<"\t\t\t 4. Update Contact Info \n";
    cout<<"\t\t\t 5. Display Entire Contact Book \n";
    cout<<"\t\t\t 6. Return to Main Menu \n";
    cin>>num;
    valid=check(num,*chosenOne);
    }while(valid);
}

//Check function to determine which appropriate function to call
bool ManagementSystem::check(int answer, ContactBook& chosen)
{
    switch(answer){
        case 1://Add New Contact
        {
            chosen.addNew();
            break;
        }
        case 2://Delete Old Contac
        {
            Contact* toRemove=chosen.search();
            chosen.deleteOld(toRemove);
            break;
        }
        case 3://Display Particular Contact
        {
            Contact* findOne=chosen.search();
            chosen.displayOne(findOne);
            break;
        }
        case 4://Update Contact
        {
            Contact* toUpdate=chosen.search();
            chosen.updateInfo(toUpdate);
            break;
        }
        case 5://Display All Contact
        {
            chosen.displayAll();
            break;
        }
        case 6://Escape Contact Menu
        {
            return false;
        }
        default:
        {
            cout<<"Value of answer is unknown.Goodbye.\n";
            return false;
        }
    }
    return true;
}
