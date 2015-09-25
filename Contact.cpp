/**Contact.cpp
 * Definition of class Contact. Stores and retrieves
 * Contact information such as last and first name, address, phone number and email.
 *
 * Author: Alison Cheu
 */
#include "Contact.h"
#include "Address.h"
#include <iostream>
#include <regex>
using namespace std;

//DEFAULT CONSTRUCTOR OF CONTACT
Contact::Contact()
    :lastName(""),firstName(""),address(),phoneNum(""),email("")
{
}

//Overrides the default constructor
Contact::Contact(string lastName, string firstName, Address address, string phoneNum, string email)
{
    this->lastName=lastName;
    this->firstName=firstName;
    this->address=address;
    this->phoneNum=phoneNum;
    this->email=email;
}

//Input function that assigns user-input to appropriate member variables
//Also contains check functions to check validity of user input.
istream& operator>>(istream& in, Contact& a)
{
    cout<<"Give me your last name\n";
    in>>a.lastName;
    cout<<"Give me your first name\n";
    in>>a.firstName;
    cout<<"Give me your address\n";
    in>>a.address;
    cout<<"Give me your phone number\n";//10 digits (123)-456-7890
    in>>a.phoneNum;
    a.setPhone(a.phoneNum);
    cout<<"Give me your email address\n";
    in>>a.email;
    a.setEmail(a.email);
    return in;
}

//Output function displaying Contact Information
ostream& operator<<(ostream& out, const Contact& a)
{
	out<<"Last Name "<<a.lastName<<endl;
	out<<"First Name: "<<a.firstName<<endl;
	out<<"Address: "<<a.address;
	out<<endl;
	out<<"Phone Number: "<<a.phoneNum<<endl;
	out<<"Email: "<<a.email<<endl<<endl;
    return out;
}


//Accessor function for last name
string Contact::getLastName() const
{
   return lastName;
}

//Mutator function for last name
void Contact::setLastName(string tempLast)
{
    lastName=tempLast;
}

//Accessor function for first name
string Contact::getFirstName() const
{
    return firstName;
}

//Mutator function for first name
void Contact::setFirstName(string tempFirst)
{
    firstName=tempFirst;
}

//Accessor function for address
Address Contact::getAddress() const
{
    return address;
}

//Mutator function for address
void Contact::setAddress( Address other)
{
	address=other;
}
//Accessor function for phone number
string Contact::getPhone() const
{
    return phoneNum;
}

//Mutator function for phone number
void Contact::setPhone(string pNum)
{
    phoneNum=checkPhone();
}

//Check function to determine whether user input is a valid phone number
string Contact::checkPhone()
{
    for (int i=0; i<phoneNum.length();i++)
    {
	//while loop if string is not 10 length or string elements are not digits
	while (phoneNum.length()!=10 || !isdigit(phoneNum[i]))
	{
        //condition if phone number length is not 10 digits long
		if(phoneNum.length()!=10)
		{
			cout<<"Whoops! It appears you did not enter 10 digits. You gave me "<<phoneNum.length()<<" digits. Please try again.\n";
			cin>>phoneNum;
		}
        //condition if phone number contains value besdies digit
		if(!isdigit(phoneNum[i]))
		{
			cout<<"Uhoh! Looks like there may be letters in your phone number. Try again.\n";
			cin>>phoneNum;
			i=0;
	        }
	}
     }
    return phoneNum;
}

//Accessor function to retrieve email
string Contact::getEmail() const
{
	return email;
}

//Mutator function that checks for proper email address using regex
void Contact::setEmail(string toCheck)
{

    string checkMail=toCheck;
	regex fullEmail("[[:w:]]+@[[:w:]]+.[[:w:]]+");
	bool match=regex_match(checkMail,fullEmail);

	while(match==false)
	{
		cout<<"Uhoh! Are you sure that's your email address? Please try again\n";
		cin>>checkMail;
		match=regex_match(checkMail, fullEmail);
	}
	
	email=checkMail;
}

//COMPARES ONE CONTACT TO ANOTHER
bool Contact::operator ==(const Contact& other) const
{
    return(   lastName==other.lastName
           && firstName==other.firstName
           );
}

//Determines whether calling object is less than other Contact
bool Contact::operator <  (const Contact& other) const
{
    return(   lastName<other.lastName
           && firstName<other.firstName
           );
}

//Determines whether calling object is greater than other Contact
bool Contact::operator >  (const Contact& other) const
{
    return(   lastName>other.lastName
           && firstName>other.firstName
           );
}

//Determines whether calling object is not equal to other Contact
bool Contact::operator != (const Contact& other) const
{
    return(   lastName!=other.lastName
           && firstName!=other.firstName
           );
}

//Determines whether calling object is less than or equal to other Contact
bool Contact::operator <= (const Contact& other) const
{
    return(   lastName<=other.lastName || (lastName<other.lastName
           && firstName<=other.firstName)
           );
}

//Determines whether calling object is greater than or equal to other Contact
bool Contact::operator >= (const Contact& other) const
{
    return(   lastName>=other.lastName || (lastName>other.lastName
         && firstName>=other.firstName)
           );
}