/**
 * Defenition of class Address. It is used to store and retrieve 
 * information on Address such as home number, street, apt#, city,
 * state, and zip.
 *
 * Author: Yosef Alayev
 */


#include "Address.h"
#include <string>
#include <iostream>

using namespace std;

Address::Address() : home(""),
                     street(""),
                     apt("none"),
                     city(""),
                     state(""),
                     zip("")
{
   // empty
}

string Address::getHome() const
{
   return home;
}

string Address::getStreet() const
{
   return street;
}

string Address::getApt() const
{
   return apt;
}

string Address::getCity() const
{
   return city;
}

string Address::getState() const
{
   return state;
}

string Address::getZip() const
{
   return zip;
}

void Address::setHome(string homeInput)
{
    home=homeInput;
}
void Address::setStreet(string streetInput)
{
    street=streetInput;
}
void Address::setApt(string aptInput)
{
    apt=aptInput;
}
void Address::setCity(string cityInput)
{
    city=cityInput;
}
void Address::setState(string stateInput)
{
    state=stateInput;
}
void Address::setZip(string zipInput)
{
    zip=zipInput;
}

ostream& operator<<(ostream& out,const Address& add)
{
   out << add.home << " " << add.street;
   if (add.apt != "none")
      out << ", Apt# " << add.apt;
   out << endl;
   out << add.city << ", " << add.state << " " << add.zip << endl;
    return out;
}

istream& operator >>(istream& in, Address& add)
{
   char choice;
   cout << "Apartment or House (a/h):> ";
   cin >> choice;
   cout << endl;

   cin.ignore(10, '\n');
   cout << "Enter home number (EX: 141-92)___: ";
   getline(in, add.home);
   cout << "Enter street number (EX: 70th RD): ";
   getline(in, add.street);
 
   if (choice == 'a')
   {
      cout << "Enter Apartment Number: (EX: 1A)_: ";
      getline(in, add.apt);
   }
   else
      add.apt = "none";

   cout << "Enter city (Ex: Flushing)________: ";
   getline(in, add.city);

   cout << "Enter state (EX: NY)_____________: ";  
   getline(in, add.state);

   cout << "Enter zip code (EX: 11367)_______: ";
   getline(in, add.zip);
    
    return in;
}
