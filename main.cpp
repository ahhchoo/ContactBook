//Project 1

//Note: Not Completely Finished.
//1. When I try to close the input stream calling .close(), or initialize ofstream to file,
//   linking error is created on
//   line 107 of main.cpp (book.getArray()[sizeCB]=new ContactBook(OwnerLast,OwnerFirst);)
//   so I've been unable to read data back into file.


/*Driver Program first reads in contactbooks.txt containing Contact Books.
 *After organizing the Contact Books read in, displays the interface from which the user
 *interacts with to access and modify contents of user defined Contact Book.
 *
 * Author: Alison Cheu
 */
#include <iostream>
#include <fstream> //Stream class to both read and write from/to files.
#include "ManagementSystem.h"
using namespace std;

void getFileData(ifstream&, ManagementSystem&);//Input from File Method
void toFileData(ostream&,ManagementSystem&);//Output to File Method

bool menuMain(int, ManagementSystem&);//Menu Interface

void properAssign(Contact*,string,string,int);//Assignment Method for Data

bool done=true;//Global variable Boolean to ensure loop for Menu

//Driver function
int main(int argc, const char * argv[])
{
    ManagementSystem system;
    
    string fileName = argv[1];
    ifstream fromFile(argv[1]); //("contactbooks.txt") same as .open
    
    getFileData(fromFile,system);//retrieves Contact Books from file
    
    cout<<"After File Input, you read in "<<system.getSize()<<" Contact Books.\n";
    
    //Main Menu
    do
    {
        int choice;
        cout<<"\t\t\t\t\tMAIN MENU\n";
        cout<<"\t\t\t Please choose from the following options: \n";
        cout<<"\t\t\t 1. Create a New Contact Book \n";
        cout<<"\t\t\t 2. Remove a Contact Book \n";//owner's name
        cout<<"\t\t\t 3. Display All Contact Books \n";
        cout<<"\t\t\t 4. Merge Two Contact Books\n";//owner's name
        cout<<"\t\t\t 5. Select a Contact Book \n";//owner's name
        cout<<"\t\t\t 6. Exit \n";
        cin>>choice;
        done=menuMain(choice,system);
    }while(done);
    
    cout<<"Goodbye\n";
    fromFile.close();
    //
    //fromFile.close(); //automatically invokes flush fxn
    /*  ofstream giveBack ("contactbooks.txt");
     if(giveBack.fail())
     cout<<"Output to File failed.\n";
     toFileData(giveBack,system);
     giveBack.close();//flush fxn
     */
    
    return 0;
}

//Retrieving Contents of contactbooks.txt

void getFileData(ifstream& readIn, ManagementSystem& book)
{
    string data1;
    string data2;
    string readyForNextBook="endofbook";
    int sizeCB=0;//int value for Contact Book Position
    int listPos=-1;//int value for Contact List Position
    
   while(true)
    {
        //Retrieving Contact Book Owner's Name & initializing it with constructor
        readIn>>data1;
        if(readIn.eof())//if file reaches eof escapes while loop
        {
            break;
        }
        
        
        if(sizeCB==5)
        {
            cout<<"Capacity of Contact Book System has been reached. Only first five Contact Books have been read in.\n";
            break;
        }
        
        long cutOffBook=data1.find("|");
        string OwnerFirst=data1.substr(0,cutOffBook);
        string OwnerLast=data1.substr(cutOffBook+1);

        book.getArray()[sizeCB]= new ContactBook(OwnerLast,OwnerFirst);
        
        //For loop traverses Contact values in pairs using data1 and data2. Assigns it to the corresponding variable
        //Example:
        //Pairs        1                    2            3            4             5
        //    FirstName|LastName  | phoneNum|email  |home|street  |apt|city|   state|zip
       
        for(int pair=1,choice=1;pair<=5;pair++)
        {

            getline(readIn, data1,'|');
            if(data1.compare(readyForNextBook)==0)//if value read in equals "endofbook", escapes for loop to initialize new Contact Book
            {
                book.getArray()[sizeCB]->setSize(listPos+1);
                sizeCB+=1;
                listPos=-1;
                break;
            }
            
            //creates a new Contact in beginning of for loop
            if(pair==1)
            {
                
                listPos+=1;
                book.getArray()[sizeCB]->getList()[listPos]=new Contact();
                choice=1;
            }
            
            if(pair==5)//if reaches last pair, data2 searches til end of newline
            {
                getline(readIn,data2,'\n');
                pair=0;
                
                //assigns data to appropriate case
                properAssign(book.getArray()[sizeCB]->getList()[listPos],data1,data2,choice);
                
            }
            else
            {
                getline(readIn,data2,'|');
                properAssign(book.getArray()[sizeCB]->getList()[listPos],data1,data2,choice);
            }
            
            //increments switch case
            choice+=1;
        }
    }
     book.setSize(sizeCB);
     cout<<"File successfully read into Contact Book System\n";

}

//Coressponding Case Assignment:
//        1                  2               3          4            5
//FirstName|LastName|1231231234|a@gma.com| home|street|apt|city|state|zip

//SWITCHCASE FOR FILE
    
void properAssign(Contact* datum,string first,string second,int section)
{
    switch(section){
        case 1://set Contact's first and last name
        {
            datum->setFirstName(first);
            datum->setLastName(second);
            break;
        }
        case 2://assign phone number and email
        {
            datum->setPhone(first);
            datum->setEmail(second);
            break;
        }
        case 3://set home and street
        {
            datum->getAddress().setHome(first);
            datum->getAddress().setStreet(second);
            break;
        }
        case 4://set apartment and city
        {
            datum->getAddress().setApt(first);
            datum->getAddress().setCity(second);
            break;
        }
        case 5://set state and zipcode
        {
            datum->getAddress().setState(first);
            datum->getAddress().setZip(second);
            break;
        }
    }

}

//Main Menu Switchcase
bool menuMain(int answer,ManagementSystem& load)
{
    switch(answer){
        case 1://Create Contact Book
        {
            if(load.isFull())
                cout<<"Error: Capacity Reached\n";
            else{
                if(load.makeNewCB())
                    cout<<"Successfully added Contact Book\n";
                else cout<<"Failure to add Contact Book\n";
            }
            break;
        }
        case 2://Remove ContactBook
        {
            if(load.isEmpty())
                cout<<"Error: System Empty\n";
            else{
               ContactBook* toRemove=load.search();
               if(load.remove(toRemove))
                   cout<<"Successfully removed Contact Book\n";
               else cout<<"Remove Unsuccessful\n";
            }

            break;
        }
        case 3://Display All Contacts
        {
            if(load.isEmpty())
                cout<<"Error: System Empty\n";
            else
                load.displayAll();
                cout<<"Displayed All Contact Books\n";
            break;
        }
            
        case 4://Merge Two Contact Books
        {
            ContactBook* firstCB= load.search();
            ContactBook* secondCB= load.search();
            if(firstCB==NULL || secondCB==NULL ){
                cout<<"Could not merge Contact Books\n";
            }
            else{
                firstCB=&firstCB->merge(*secondCB);
                load.remove(secondCB);//removes secondCB from Contact Book array
                cout<<"Merge successful\n";
            }
            break;
        }
        case 5://Select Contact Book
        {
            ContactBook* toSelect=load.search();
            if(toSelect== NULL)
            {
                cout<<"Unknown Contact\n";
                break;
            }
            load.select(toSelect);
            break;
        }
        case 6://Exit
        {
            cout<<"You've selected the Exit Option\n";
            done=false;
            break;
        }
        default:
        {
            cout<<"Value of answer is unknown.Please try again.\n";
        }
    }
    return done;
}
//Returns Data back to file
void toFileData(ostream& out,ManagementSystem data)
{
    for(int i=0;i<data.getSize();i++)//for loop traversing Contact Book Array
    {
        //OUTPUT OF OWNER NAME
        out<<data.getArray()[i]->getOwnFirstName();
        out<<'|';
        out<<data.getArray()[i]->getOwnLastName();
        out<<endl;
        
        int numOfContacts=data.getArray()[i]->getSize();
        for(int j=0;j<numOfContacts;j++)
        {
            
            //OUTPUT OF CONTACT LIST NAME
            out<<data.getArray()[i]->getList()[j]->getFirstName();
            out<<'|';
            out<<data.getArray()[i]->getList()[j]->getLastName();
            
            //OUTPUT OF CONTACT PHONE
            out<<data.getArray()[i]->getList()[j]->getPhone();
            out<<'|';

            //OUTPUT OF CONTACT EMAIL
            out<<data.getArray()[i]->getList()[j]->getEmail();
            out<<'|';
            
            //OUTPUT OF HOME
            out<<data.getArray()[i]->getList()[j]->getAddress().getHome();
            out<<'|';
            
            //OUTPUT OF STREET
            out<<data.getArray()[i]->getList()[j]->getAddress().getStreet();
            out<<'|';
            
            //OUTPUT OF APT
            out<<data.getArray()[i]->getList()[j]->getAddress().getApt();
            out<<'|';
            
            //OUTPUT OF CITY
            out<<data.getArray()[i]->getList()[j]->getAddress().getCity();
            out<<'|';
            
            //OUTPUT OF STATE
            out<<data.getArray()[i]->getList()[j]->getAddress().getState();
            out<<'|';
            
            //OUTPUT OF ZIP
            out<<data.getArray()[i]->getList()[j]->getAddress().getZip();
        }
        //OUTPUT ENDOFBOOK
        out<<"endofbook|\n";
    }
}

