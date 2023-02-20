
//=================================================================================
// Name         : DS Assignment#2
// Author       :
// Version      : 1.0
// Date Created : 05-Nov-2022
// Date Modified:
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
#include <sstream>
//=================================================================================
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <regex>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
	cout << "----------------------------------" << endl;
	cout << "import <path>      :Import contacts from a CSV file" << endl
		 << "export <path>      :Export contacts to a CSV file" << endl
		 << "add                :Add a new contact" << endl
		 << "update <key>       :Update a contact's details" << endl
		 << "remove <key>       :Delete a contact" << endl
		 << "searchFor <key>    :Search for a contact" << endl
		 << "markFav <key>      :Mark as favourite" << endl
		 << "unmarkFav <key>    :Unmark as favourite" << endl
		 << "printASC           :Print contacts in ascending order" << endl
		 << "printDES           :Print contacts in descending order" << endl
		 << "printFav           :Print all favourite contacts" << endl
		 << "help               :Display the available commands" << endl
		 << "exit               :Exit the program" << endl;
}
//==========================================================

// to be completed with ALL the necessary method definitions

// validate lname, fname, city, country
bool name_validator(string name)
{
	for (int i = 0; i < name.length(); i++)
	{
		if (!isalpha(name[i]) && name[i] != ' ')
		{
			return false;
		}
	}
	return true;
}

// validate email
bool email_validator(string email)
{
	return regex_match(email, regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
}

// validate phone
bool phone_validator(string phone)
{
	return regex_match(phone, regex("\\+[0-9]+"));
}

// validate favourite
bool fav_validator(string fav)
{
	if (fav == "y" || fav == "Y")
	{
		return true;
	}
	return false;
}
//==========================================================
int main(void)
{
	ContactBST contactbst;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout << ">";
		getline(cin, user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter);

		Node *root = contactbst.getRoot();

		if (command == "import")
		{
			int num = contactbst.importCSV(parameter);

			if (num != -1)
			{
				cout << num << " records have been imported" << endl;
			}

			else
			{
				cout << "Please enter a valid file name" << endl;
			}
		}
		else if (command == "export")
		{
			int val = contactbst.exportCSV(root, parameter);
			cout << val << " records have been exported" << endl;
		}
		// take inputs, validate and add
		else if (command == "add")
		{
			string fname;
			string lname;
			string email;
			string phone;
			string city;
			string country;
			string fav;
			bool isFav;

			cout << "Please enter the details of the contact:" << endl;

			do
			{
				cout << "First Name: ";
				getline(cin, fname);
			} while (!name_validator(fname));

			do
			{
				cout << "Last Name: ";
				getline(cin, lname);
			} while (!name_validator(lname));

			do
			{
				cout << "Email: ";
				getline(cin, email);
			} while (!email_validator(email));

			do
			{
				cout << "Phone#: ";
				getline(cin, phone);
			} while (!phone_validator(phone));

			do
			{
				cout << "City: ";
				getline(cin, city);
			} while (!name_validator(city));

			do
			{
				cout << "Country: ";
				getline(cin, country);
			} while (!name_validator(country));

			cout << "Do you want to add the contact in your favourites (y/n): ";
			getline(cin, fav);

			isFav = fav_validator(fav);

			string key;
			key = fname + " " + lname;

			fname[0] = toupper(fname[0]);
			lname[0] = toupper(lname[0]);

			Contact *data = new Contact(fname, lname, email, phone, city, country, isFav);

			contactbst.add(root, key, data);
		}

		else if (command == "update")
		{
			contactbst.update(parameter);
		}
		else if (command == "remove")
		{
			contactbst.remove(contactbst.getRoot(), parameter);
		}
		else if (command == "searchFor")
		{
			Node *ans = contactbst.searchFor(contactbst.getRoot(), parameter);
			if (ans == nullptr)
			{
				cout << "No record found" << endl;
			}
			else
			{
				ans->print();
			}
		}
		else if (command == "markFav")
		{
			bool check = contactbst.markFav(parameter);

			if (check == false)
			{
				cout << "Contact not found";
			}
		}
		else if (command == "unmarkFav")
		{
			bool check = contactbst.unmarkFav(parameter);

			if (check == false)
			{
				cout << "Contact not found";
			}
		}
		else if (command == "printASC")
		{
			contactbst.printASC(root);
		}
		else if (command == "printDES")
		{
			contactbst.printDES(root);
		}
		else if (command == "printFav")
		{
			contactbst.printFav(root);
		}
		else if (command == "help")
		{
			listCommands();
		}
		else if (command == "exit" or command == "quit")
		{
			break;
		}
		else
		{
			cout << "Invalid Command!!!" << endl;
		}
		fflush(stdin);
	} while (true);
	return 0;
}