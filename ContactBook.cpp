/**ContactBook.cpp
 *
 * Declaration of ContactBook Class.
 * ContactBook class contains functions that allows user to manipulate Contacts in ContactBook class.
 * Contains functions such as add, delete, update, display and exit.
 *
 * Author: Alison Cheu
 */

#include "Contact.h"
#include "ContactBook.h"
#include <ctype.h>
#include <string.h>
#include <iostream>
using namespace std;

//Assigns owner's name from user input
void ContactBook::ownerName()
{
    cout<<"Please give me this ContactBook owner's LAST NAME.\n";
    cin>>lName;
    cout<<"Please give me this ContactBook owner's FIRST NAME\n";
    cin>>fName;
}

//Default Constructor
ContactBook::ContactBook()
:capacity(5), size(0)
{
    ownerName();
    list= new Contact*[capacity];
}

//2nd Defacult Constructor
ContactBook::ContactBook(string ownerLast, string ownerFirst):lName(ownerLast),fName(ownerFirst),capacity(5),size(0)
{
    list= new Contact*[capacity];
}

//COPY CONSTRUCTOR
ContactBook::ContactBook(const ContactBook& other): capacity(other.capacity),size(other.size)//take by const reference to avoid infinite loop
{
    //why other.capacity and not getCapacity?
    list= new Contact*[capacity];
    
    for(int i=0;i<size;i++)
    {
       list[i]=new Contact(*other.list[i]);
    }
}

//DESTRUCTOR
ContactBook::~ContactBook()
{
    for (int i=0;i<size;i++)//delete only removes dynamic variables to free up heap
    {
        delete list[i];
    }
    
    delete[] list;
}

//OVERLOADING ASSIGNMENT OPERATOR
ContactBook& ContactBook::operator=(const ContactBook& rightSide)
{
    if(this == &rightSide)//if addresses are the same
    {
        return *this;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            delete list[i];
        }
      
        capacity=rightSide.capacity;
        size=rightSide.size;
        
        for(int i=0;i<size;i++)
            list[i]=new Contact(*rightSide.list[i]);
    }
    return *this;
}

//Increase the capacity to twice the original size plus one.
void ContactBook::grow()
{
    capacity=capacity*2+1;
    
    Contact** temp= new Contact*[capacity];//pointer to pointer of arrays
    
    //or loop passes list pointers into temp array so now 2 pointers pointing to same address of type Cotact
    for(int i=0;i<size;i++)
    {
        temp[i]= list[i];
    }
    
    delete[]list;
    
    list=new Contact*[capacity];
    for(int i=0;i<size;i++)
    {
        list[i]=temp[i];
    }
    
    cout<<"Capacity of your Contact Book is now "<<capacity<<" \n";
    
}

//ADDING NEW CONTACT
void ContactBook::addNew()
{
    if(isFull())
    {
        grow();
        list[size]=new Contact();
        cin>>*list[size];
        size+=1;
        sort();
        
        cout<<"You have created a new contact. You now have "<< size <<" contact(s) in your Contact Book.\n";
    }
    else
    {
        list[size]=new Contact();
        cin>>*list[size];
        size+=1;
        sort();
        cout<<"You have created a new contact. You now have "<< size <<" contact(s) in your Contact Book.\n";
    }
}

//Selection Sort
void ContactBook::sort()
{

    for (int i = 0; i < size - 1; i++)
    {
        int indexLowest = i;
        for (int j = i + 1; j < size; j++)
        {
            if (*list[indexLowest]>*list[j])
                indexLowest = j;
        }
        //swap
        Contact* temp= list[i];
        list[i]=list[indexLowest];
        list[indexLowest]=temp;

    }
}

//DELETING OLD CONTACT
void ContactBook::deleteOld(Contact* remove)
{
    if(remove==NULL)//if pointer is pointing to NULL
    {
        cout<<"Sorry Contact could not be deleted\n";
    }
    else{
        //outer for loop traverses pointer array until size of array
        for(int i=0;i<size;i++)
        {
            if(*list[i]==*remove) //Once pointer is found in array by comparing addresses...
            {
                for(int a=i;a<=size-1;a++) //for loop traverses to the rest of the array until size-1, where...
                {
                    if(a==size-1)//if a reaches the new last pointer...
                    {
                        list[a]=NULL;//last pointer is assigned NULL
                    }
                    //Meanwhile if not at size-1 pointer, assigns pointer to next pointer, therefore pointing to next Contact
                    list[a]=list[a+1];

                }
                size=size-1;
                cout<<"Successfully deleted contact.\n";
            }
        }

    }
}

//DISPLAYING ONE CONTACT INFO
void ContactBook::displayOne(Contact* display) const
{
    if(display==NULL)
    {
        cout<<"Empty Contact\n";
    }
    else cout<<*display;
}

//UPDATING ONE CONTACT INFO
void ContactBook::updateInfo(Contact* toUpdate)
{
    bool test=true;
    if(toUpdate==NULL)
    {
        cout<<"Sorry Contact is not valid.\n";
    }
    else
    {
        do{
        int choice;
        cout<<"\t\t\t\t\tCONTACT MENU BELONGING TO "<<toUpdate->getFirstName()<<" "<<toUpdate->getLastName()<<endl;
        cout<<"\t\t\t Please choose from the following to update: \n";
        cout<<"\t\t\t 1. Entire Contact \n";
        cout<<"\t\t\t 2. Name \n";
        cout<<"\t\t\t 3. Address\n";
        cout<<"\t\t\t 4. Phone Number \n";
        cout<<"\t\t\t 5. Email \n";
        cout<<"\t\t\t 6. Return to Contact Book Menu\n";
        cin>>choice;
        test=checkUpdate(choice, toUpdate);
        }while(test);
    }
}

//PARTICULAR CONTACT INFO UPDATE
bool ContactBook::checkUpdate(int answer, Contact* toChange)
{
    switch(answer)
    {
        case 1://Entire Contact
        {
            cout<<"You are about to update the entire contact belonging to "<<toChange->getFirstName()<<" "<<toChange->getLastName()<<endl;
            cin>>*toChange;
            cout<<"Contact Update Complete\n";
            break;
        }
        case 2://Update Name
        {
            string first,last;
            cout<<"New First Name: \n";
            cin>>first;
            cout<<"New Last Name: \n";
            cin>>last;
            toChange->setFirstName(first);
            toChange->setLastName(last);
            cout<<"Name Update Complete\n";
            break;
        }
        case 3://Update Address
        {
            char choice;
            cout << "Apartment or House (a/h):> ";
            cin >> choice;
            cout << endl;
            
            string general;
            cin.ignore(10, '\n');
            cout << "Enter home number (EX: 141-92)___: ";
            getline(cin,general);
            toChange->getAddress().setHome(general);
            cout << "Enter street number (EX: 70th RD): ";
            getline(cin,general);
            toChange->getAddress().setStreet(general);
            
            if (choice == 'a')
            {
                cout << "Enter Apartment Number: (EX: 1A)_: ";
                getline(cin,general);
                toChange->getAddress().setApt(general);
            }
            else
            {
                toChange->getAddress().setApt("none");
            }
            
            cout << "Enter city (Ex: Flushing)________: ";
            getline(cin,general);
            toChange->getAddress().setCity(general);
            
            cout << "Enter state (EX: NY)_____________: ";  
            getline(cin,general);
            toChange->getAddress().setState(general);
            
            cout << "Enter zip code (EX: 11367)_______: ";
            getline(cin,general);
            toChange->getAddress().setZip(general);
            break;
        }
        case 4://Update Phone Number
        {
            string num;
            cout<<"New Phone Number:\n ";
            cin>>num;
            toChange->setPhone(num);
            cout<<"Number Update Complete\n";
            break;
        }
        case 5://Update Email
        {
            string email;
            cout<<"New Email : \n";
            cin>>email;
            toChange->setEmail(email);
            cout<<"Email Update Complete\n";
            break;
        }
        case 6://Escape
        {
            return false;
            break;
        }
        default:
        {
            cout<<"Value of answer is unknown.Goodbye.\n";
            return false;
        }

    }
    return true;
}
void ContactBook::displayAll() const
{
    for(int i=0; i<size;i++)
	{
		cout<<"Contact "<<i+1<<endl;
        cout<<*list[i];
		cout<<"\n";
	}
	cout<<"\n";
}

//EXIT PROGRAM
void ContactBook::endProgram() const
{
    cout<<"Goodbye\n";
    exit(1);
}

//SEARCH FOR POINTER
Contact* ContactBook::search()
{
    int index;
	string lastName,firstName;
	cout<<"Please give me the person's LAST NAME\n";
	cin>>lastName;
	cout<<"Please give me the person's FIRST NAME\n";
	cin>>firstName;
    
    //For loop traverses array and searches for appropriate Contact based on given first and last name.
        for(index=0;index<size;index++)
        {
            if( lastName==list[index]->getLastName() && firstName==list[index]->getFirstName() )
            {
                cout<<"Search successful\n";
                return list[index];
            }
        }
    cout<<"Search unsuccessful\n";
    return NULL;
}

//Print Contact at Particular Index
void ContactBook::printIndex() const
{
    int index;
    cout<<"Give me the index of the contact you would like to print.";
    cin>>index;
    
    if(index < 0 || index >= size) cout<<"I'm sorry this is not a valid index number.\n";
    else cout<<*list[index];
}

//Get Owner Last Name
string ContactBook::getOwnLastName() const
{
    return lName;
}

//Set Owner Last Name
void ContactBook::setOwnLastName(string last)
{
    lName=last;
}

//Get Owner First Name
string ContactBook::getOwnFirstName() const
{
    return fName;
}

//Set Owner First Name
void ContactBook::setOwnFirstName(string first)
{
    fName=first;
}

//Get Size of List Function
int ContactBook::getSize() const
{
    return size;
}

//Get Capacity of Function
int ContactBook::getCapacity() const
{
    return capacity;
}
//Set Function for Size
void ContactBook::setSize(int otherS)
{
    size=otherS;
}
//Checks if ContactBook is Empty
bool ContactBook::isEmpty(){
    if(size==0)
        return true;
    else return false;
}

//Checks if Contact Book is Full
bool ContactBook::isFull(){
    if(size==capacity)
        return true;
    else return false;
}

//Get List Function
Contact**& ContactBook::getList()
{
    return list;
}

//MERGE FUNCTION
ContactBook& ContactBook::merge(ContactBook& other)
{
    int newSize=this->size+other.getSize();
    Contact** temp=new Contact*[newSize];
    
    for(int i=0;i<size;i++)
    {
           temp[i]=list[i];
    }
    
    int otherStart=0;
    for(int i=size;i<newSize;i++)
    {
        temp[size]=other.list[otherStart++];
    }
    
    delete[]list;
    delete[]other.list;
    
    list=new Contact*[newSize];
    
    for(int i=0;i<newSize;i++)
    {
        list[i]=temp[i];
    }
    size=newSize;
    sort();
    return *this;
    
}

//OUTPUT FUNCTION FOR CONTACTBOOK
ostream& operator<<(ostream& out, const ContactBook& a){
    
    out<<"Contact Book Owner's Name: "<<a.fName <<" "<<a.lName<<endl;
    
    for(int i=0;i<a.size;i++)
    {
        out<<"Contact Number: "<<i+1<<endl;
        out<<*a.list[i]<<endl;
    }
    return out;
}

//INPUT FUNCTION FOR CONTACTBOOK- inputting Contacts
istream& operator>>(istream& in, ContactBook& a){
    
    int numChoice;
    cout<<"How many Contacts would you like to input?"<<endl;
    cin>>numChoice;
    if(numChoice<=0)
        cout<<"Invalid Answer.";
    else{
        
        while(a.size<numChoice)
        {
            a.addNew();

        }
    }
    return in;
}