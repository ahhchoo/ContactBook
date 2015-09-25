/**
 Contact.h
 * Declaration of class Contact. Stores and retrieves 
 * Contact information such as last and first name, address, phone number and email. 
 *
 * Author: Alison Cheu
 */
#ifndef CONTACT_H
#define CONTACT_H
#include "Address.h"
class Contact
{
private:
    string lastName;
    string firstName;
    Address address;
    string phoneNum;
    string email;
    
public:
    Contact();//default constructor
    Contact(string lastName, string firstName, Address address, string phoneNum, string email);
    
    string getLastName() const;
    void setLastName(string tempLast);
    
    string getFirstName() const;
    void setFirstName(string tempFirst);
    
    Address getAddress() const;
    void setAddress(Address);
    
    string getPhone() const;
    void setPhone(string phone);
    string checkPhone();
    
    string getEmail() const;
    void setEmail(string email);
    
    friend ostream& operator<<(ostream& out, const Contact& a);
    friend istream& operator>>(istream& in, Contact& a);
    
    bool operator == (const Contact& other) const;
    bool operator <  (const Contact& other) const;
    bool operator >  (const Contact& other) const;
    bool operator != (const Contact& other) const;
    bool operator <= (const Contact& other) const;
    bool operator >= (const Contact& other) const;

};
#endif
