#include "contactbst.h"
#include "contact.h"
#include "myvector.h"
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

// variable to check for if update is calling remove
string check = "0";

// check if destructor is called
bool destruct = false;

// constructor
ContactBST::ContactBST()
{
	this->root = nullptr;
}

// destructor
ContactBST::~ContactBST()
{
	destruct = true;
	while (root)
	{
		remove(root, root->key);
	}
}

// get root
Node *ContactBST::getRoot()
{
	return root;
}

// add a contact to the bst
void ContactBST::add(Node *ptr, string key, Contact *data)
{
	Node *temp = new Node(key, data);

	if (root == nullptr)
	{
		root = temp;
	}

	// add to the bst according to the conditions given below
	else
	{
		if (key == ptr->key)
		{
			(ptr->contactVector).push_back(data);
		}
		else if (key < ptr->key && ptr->left == nullptr)
		{
			ptr->left = temp;
			ptr->left->parent = ptr;
		}
		else if (key > ptr->key && ptr->right == nullptr)
		{
			ptr->right = temp;
			ptr->right->parent = ptr;
		}
		else if (key < ptr->key && ptr->left != nullptr)
		{
			add(ptr->left, key, data);
		}
		else if (key > ptr->key && ptr->right != nullptr)
		{
			add(ptr->right, key, data);
		}
	}
}

// update the contact with the given key
void ContactBST::update(string key)
{
	Node *temp = searchFor(root, key);

	// vars for choices later
	string opt;
	string opt2;
	string opt3;
	if (temp == nullptr)
	{
		cout << "Contact not found";
	}

	else
	{
		// get inputs from user to update while validating the inputs
		do
		{
			temp->print();
			cout << "Please select the record you want to edit: ";
			getline(cin, opt);

		} while (stoi(opt) > temp->contactVector.size());

		Contact *ct = (temp->contactVector).at(stoi(opt) - 1);

		string new_fname = ct->fname;
		string new_lname = ct->lname;
		string new_email = ct->email;
		string new_phone = ct->phone;
		string new_city = ct->city;

		bool change;

		do
		{
			do
			{
				cout << "Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, 6) Country: ";
				getline(cin, opt2);
			} while (stoi(opt2) > 6);

			if (opt2 == "1")
			{
				string new_fname;
				cout << "Please enter the new first name: ";
				getline(cin, new_fname);
				new_fname[0] = toupper(new_fname[0]);
				ct->fname = new_fname;
				change = true;
			}
			else if (opt2 == "2")
			{
				string new_lname;
				cout << "Please enter the new last name: ";
				getline(cin, new_lname);
				new_lname[0] = toupper(new_lname[0]);
				ct->lname = new_lname;
				change = true;
			}
			else if (opt2 == "3")
			{
				string new_email;
				cout << "Please enter the new email: ";
				getline(cin, new_email);
				ct->email = new_email;
			}
			else if (opt2 == "4")
			{
				string new_phone;
				cout << "Please enter the new phone#: ";
				getline(cin, new_phone);
				ct->phone = new_phone;
			}
			else if (opt2 == "5")
			{
				string new_city;
				cout << "Please enter the new city: ";
				getline(cin, new_city);
				ct->city = new_city;
			}
			else if (opt2 == "6")
			{
				string new_country;
				cout << "Please enter the new country: ";
				getline(cin, new_country);
				ct->country = new_country;
			}

			cout << "Do you want to edit another field [y/n]? ";
			getline(cin, opt3);

		}

		while (opt3 == "Y" || opt3 == "y");

		if (change == true)
		{
			check = opt;

			string k = ct->fname + " " + ct->lname;
			add(root, k, ct);
			remove(root, temp->key);
		}

		cout << "The contact record has been successfully updated! " << endl;
	}
}

// remove a contact from the bst
void ContactBST::remove(Node *ptr, string key)
{
	Node *temp = searchFor(ptr, key);
	string output = temp->key;

	if (temp == nullptr && destruct == false)
	{
		cout << "Contact not found";
		return;
	}

	string choice;

	// only works when remove is not called by update and not called by destructor
	if (check == "0" && destruct == false)
	{
		// validating the input for records
		do
		{
			temp->print();
			cout << "Please select the record you want to delete: ";
			getline(cin, choice);
		} while (stoi(choice) > temp->contactVector.size());
	}

	else
	{
		choice = check;
	}

	// only remove one contact from vector and not the whole node
	if (destruct == false && temp->contactVector.size() > 1)
	{

		temp->contactVector.erase(stoi(choice) - 1);
	}

	else
	{
		// remove nodes with no children
		if (temp->right == nullptr && temp->left == nullptr)
		{
			if (temp == root)
			{
				root = nullptr;
				temp = nullptr;
			}
			else if (temp->parent->left == temp)
			{
				temp->parent->left = nullptr;
				temp = nullptr;
			}
			else
			{
				temp->parent->right = nullptr;
				temp = nullptr;
			}
		}

		// remove nodes with one children
		else if (temp->right == nullptr || temp->left == nullptr)
		{
			if (temp->right == nullptr)
			{
				Node *temp2 = temp->left;
				if (temp == root)
				{
					root = temp2;
					temp = nullptr;
				}
				else
				{
					if (temp->parent->right == temp)
					{
						temp->parent->right = temp2;
						temp2->parent = temp->parent;
						temp = nullptr;
					}
					else if (temp->parent->left == temp)
					{
						temp->parent->left = temp2;
						temp2->parent = temp->parent;
						temp = nullptr;
					}
				}
			}

			else
			{
				Node *temp2 = temp->right;
				if (temp == root)
				{
					root = temp2;
					temp = nullptr;
				}
				else
				{
					if (temp->parent->right == temp)
					{
						temp->parent->right = temp2;
						temp2->parent = temp->parent;
						temp = nullptr;
					}
					else if (temp->parent->left == temp)
					{
						temp->parent->left = temp2;
						temp2->parent = temp->parent;
						temp = nullptr;
					}
				}
			}
		}

		// remove nodes with both children
		else
		{
			Node *temp2 = findMin(temp->right);

			temp->key = temp2->key;
			temp->contactVector = temp2->contactVector;

			if (temp2->parent->right == temp2)
			{
				temp2->parent->right = nullptr;
			}

			else
			{
				temp2->parent->left = nullptr;
			}

			temp2 = nullptr;
		}
	}

	// only print when destructor is not called
	if (destruct == false)
	{
		cout << "The contact record " << output << " has been deleted" << endl;
	}

	check = "0";
}

// recursively search for the node in the bst
Node *ContactBST::searchFor(Node *ptr, string key)
{
	if (ptr == nullptr)
	{
		return nullptr;
	}
	else if (key > ptr->key)
	{
		return searchFor(ptr->right, key);
	}
	else if (key < ptr->key)
	{
		return searchFor(ptr->left, key);
	}
	else
	{
		return ptr;
	}
	// return ptr;
}

// mark the contact with the given key as favourite
bool ContactBST::markFav(string key)
{
	Node *temp = searchFor(root, key);
	string opt;
	if (temp == nullptr)
	{
		return false;
	}
	else
	{

		do
		{
			temp->print();
			cout << "Please select the record you want to mark as favourite: ";
			getline(cin, opt);
		} while (stoi(opt) > temp->contactVector.size());

		Contact *ct = temp->contactVector.at(stoi(opt) - 1);

		ct->isFav = true;

		cout << ct->fname << " " << ct->lname << " (" << ct->email << ") has been successfully marked as favourite! " << endl;

		return true;
	}
}

// unmark the given contact as favourite
bool ContactBST::unmarkFav(string key)
{
	Node *temp = searchFor(root, key);
	string opt;
	if (temp == nullptr)
	{
		return false;
	}
	else
	{
		do
		{
			temp->print();
			cout << "Please select the record you want to unmark as favourite: ";
			getline(cin, opt);
		} while (stoi(opt) > temp->contactVector.size());

		Contact *ct = temp->contactVector.at(stoi(opt) - 1);

		ct->isFav = false;

		cout << ct->fname << " " << ct->lname << " (" << ct->email << ") has been successfully unmarked as favourite! " << endl;

		return true;
	}
}

// print contacts in ascending order
void ContactBST::printASC(Node *ptr)
{
	if (ptr != nullptr)
	{
		printASC(ptr->left);
		for (int i = 0; i < ptr->contactVector.size(); i++)
		{
			Contact *ct = ptr->contactVector.at(i);
			cout << ct->fname << "," << ct->lname << "," << ct->email << "," << ct->phone << "," << ct->city << "," << ct->country << "," << ct->isFav << endl;
		}
		printASC(ptr->right);
	}
}

// print contacts in descending order
void ContactBST::printDES(Node *ptr)
{
	if (ptr != nullptr)
	{
		printDES(ptr->right);
		for (int i = 0; i < ptr->contactVector.size(); i++)
		{
			Contact *ct = ptr->contactVector.at(i);
			cout << ct->fname << "," << ct->lname << "," << ct->email << "," << ct->phone << "," << ct->city << "," << ct->country << "," << ct->isFav << endl;
		}
		printDES(ptr->left);
	}
}

// print all the favourite contacts
void ContactBST::printFav(Node *ptr)
{
	if (ptr != nullptr)
	{
		printFav(ptr->left);
		for (int i = 0; i < ptr->contactVector.size(); i++)
		{
			Contact *ct = ptr->contactVector.at(i);
			cout<<ct->isFav;
			if (ct->isFav)
			{
				cout << ct->fname << "," << ct->lname << "," << ct->email << "," << ct->phone << "," << ct->city << "," << ct->country << "," << ct->isFav << endl;
			}
		}
		printFav(ptr->right);
	}
}

// import the contacts from csv into the bst
int ContactBST::importCSV(string path)
{
	ifstream myFile(path);

	if (!myFile)
	{
		return -1;
	}
	string myText;
	int maincnt = 0;

	// parse the incoming text into the variables
	while (getline(myFile, myText))
	{
		string fname;
		string lname;
		string email;
		string phone;
		string city;
		string country;
		bool isFav;
		int cnt = 0;
		for (int i = 0; i < myText.length(); i++)
		{
			if (myText[i] == ',')
			{
				cnt += 1;
				continue;
			}
			if (cnt == 0)
			{
				fname += myText[i];
			}
			else if (cnt == 1)
			{
				lname += myText[i];
			}
			else if (cnt == 2)
			{
				email += myText[i];
			}
			else if (cnt == 3)
			{
				phone += myText[i];
			}
			else if (cnt == 4)
			{
				city += myText[i];
			}
			else if (cnt == 5)
			{
				country += myText[i];
			}
			else if (cnt == 6)
			{
				if (myText[i] == '1')
				{
					isFav = true;
				}
				else if (myText[i] == '0')
				{
					isFav = false;
				}
			}
		}
		string key = fname + " " + lname;

		// add the contacts to the bst
		Contact *temp = new Contact(fname, lname, email, phone, city, country, isFav);
		add(root, key, temp);
		maincnt++;
	}
	return maincnt;
}

// export the contacts onto a csv
int ContactBST::exportCSV(Node *ptr, string path)
{

	ofstream myFile(path, ios_base::app);
	int cnt = 0;

	if (ptr != nullptr)
	{
		ofstream myFile(path, ios_base::app);
		cnt += exportCSV(ptr->left, path);
		for (int i = 0; i < ptr->contactVector.size(); i++)
		{
			cnt += 1;
			Contact *ct = ptr->contactVector.at(i);
			myFile << ct->fname << "," << ct->lname << "," << ct->email << "," << ct->phone << "," << ct->city << "," << ct->country << "," << ct->isFav << endl;
		}
		cnt += exportCSV(ptr->right, path);
	}

	else
	{
		return 0;
	}

	myFile.close();
	return cnt;
}

// find the minimum from the binary tree
Node *ContactBST::findMin(Node *ptr)
{
	if (ptr->left == nullptr)
	{
		return ptr;
	}
	else
	{
		return findMin(ptr->left);
	}
}
