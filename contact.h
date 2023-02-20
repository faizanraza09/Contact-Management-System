#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
//class ContactBST;  //Forward declaration of ContactBST class
using namespace std;

class Contact
{
	private:
		string fname;
		string lname;
		string email;
		string phone;
		string city;
		string country;
		bool isFav;

	public:
		Contact(string fname, string lname, string email, string phone, string city, string country, bool isFav);
		friend class Node;
		friend class ContactBST;	
};

#endif