/*//////////////////////////////////////////////////////////////////////////////

Carla Pastor  
COP4530. Project 5: Hash Tables and Its Applications        

Task 1: HashTable Class Template
File: Extra-credit part I (10 points) 
*///////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<utility>
#include<stdio.h>
#include<termios.h>
#include "passserver.h"
#include "hashtable.h"
using namespace std;
/*
Reference: 
http://programming59.blogspot.com/2011/07/getch-function-in-cc-language.html
the getch() function is used to catch a character from the keyboard. The getch()
function reads a single character from the keyboard but does not show on the screen. 
For this functionality, you can use the getch() function to hold the output window 
until hitting any key from the keyboard.
#include <termios.h>   --- int tcgetattr(int fildes, struct termios *termios_p);
*/

void jump();
void Menu();

int getch() 
{
	int r;
	struct termios term2, term1;
	tcgetattr(STDIN_FILENO, &term2);
	
	term1 = term2;
	term1.c_lflag &= ~(ICANON | ECHO);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &term1);
	
	r= getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &term2);
	return r;
}

int main()
{
	cout << "Enter preferred hash table capacity: ";
	int inputCty; cin >> inputCty;
	
	if(inputCty <= 0)
	{ 
		cout <<"**Input too large for prime_below()\nSet to default capacity\n11\n";
		inputCty = 11;
	}

	PassServer x(inputCty);
    char inp;
	do 
	{
		Menu();
		cin >> inp;

		if(inp == 'l') 
		{
			string filename;
			cout <<"Enter password file name to load from: "; jump();
			getline(cin, filename);
			
			if(!x.load(filename.c_str()))
			{
				cout << "Cannot open file " << filename << endl;
			}
		}

		else if(inp == 'a') 
		{
			string name, addu; char a, c=10;
			cout << "Enter user name: ";  jump();
			getline(cin, name);
			cout << "Enter password: \n";
		
			while((a= getch() ) !=c)
			{
				addu=addu+a;
			}
			
			pair<string, string> newPair(name, addu);
			
			if(x.addUser(newPair))
			{
				cout << "User " << name << " added.\n";
			}
			else
			{
				cout << "*****Error: User already exists. Could not add user.\n";
			}
		}

		else if(inp == 'r') 
		{
			string name;
			cout << "Enter username: "; jump();
			getline(cin, name);
			if(x.removeUser(name))
			{
				cout << "User " << name << " deleted.\n";
			}
			else
			{
				cout << "*****Error: User not found. Could not delete user.\n";
			}
		}

		else if(inp == 'c') 
		{
			string name, viejo, nuevo; char a, b, c=10;
			cout << "Enter username: ";    jump();
			getline(cin, name);  
			cout << "Enter password: \n";  
			
			while((a=getch())!= c)
			{
				viejo=viejo+a; 
			}
			
			cout << "Enter new password: ";
			
			while((b=getch()) !=c)
			{
				nuevo=nuevo+b;
			}
			
			pair<string, string> oldPair(name, viejo);
			
			if(x.changePassword(oldPair, nuevo))
			{
				cout << "Password changed for user " << name << '\n';
			}
			else
			{
				cout << "*****Error: Could not change user password." << endl;
			}
		}

		else if(inp == 'f') 
		{
			string name;
			cout << "Enter username: "; jump();
			getline(cin, name);
			
			if(x.find(name))
			{
				cout << "User " << "'" << name << "'" << " found.\n";
			}
			else
			{
				cout << "User " << "'" << name << "'" << " not found." << endl;
			}
		}

		else if(inp == 'd') 
		{
			x.dump();
		}

		else if(inp == 's') 
		{
			cout << "Size of hashtable: " << x.size();
			cout << '\n';
		}

		else if(inp == 'w')
		{
			string secName;
			cout << "Enter password file name to write to: "; jump();
			
			getline(cin, secName);
			x.write_to_file(secName.c_str());
		}

		else if(inp == 'x') 
		{
	//	  cout << "x - Exit program" << endl;
		}
		
		else
		{
			cout << "*****Error: Invalid entry.  Try again." << endl;
		}
	}
	while(inp != 'x');

	return 0;
}


void jump()
{
	char js;
	while(isspace(cin.peek()) && !cin.eof())
	{
		cin.get(js);
	}
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter inp : ";
}


//////////////////////////////////////////////////////////////////////////////
