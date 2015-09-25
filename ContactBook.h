/**
 * Definition of ContactBook Class.
 * ContactBook class contains functions that allows user to manipulate Contacts in ContactBook class. 
 * Contains functions such as add, delete, update, display and exit. 
 *
 * Author: Alison Cheu
 */
#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H
#include <iostream>
#include "Contact.h"

class ContactBook{
private:
    string fName;
    string lName;
    int size;
    int capacity;
    Contact** list;
    void grow();
    void sort();

public:
    ContactBook();
    ContactBook(string, string);
    ContactBook(const ContactBook& other);//copy constructor
    ~ContactBook();//destructor
    ContactBook& operator=(const ContactBook&);//assignment operator, by reference to access member functions

    void ownerName();
    
    void addNew();
    void deleteOld(Contact*);
    void displayOne(Contact*) const;
    void displayAll()const;
    void updateInfo(Contact*);
    bool checkUpdate(int, Contact*);
    void endProgram() const;
    
    Contact* search();
    void printIndex()const;
    
    string getOwnLastName() const;
    void setOwnLastName(string last);
    
    string getOwnFirstName() const;
    void setOwnFirstName(string first);
    
    Contact**& getList();
    int getSize() const;
    int getCapacity() const;
    void setSize(int);
    
    bool isEmpty();
    bool isFull();
    
    ContactBook& merge(ContactBook& other);
    friend ostream& operator<<(ostream& out, const ContactBook& a);
    friend istream& operator>>(istream& in, ContactBook& a);
};

#endif /* defined(CONTACTBOOK_H) */
