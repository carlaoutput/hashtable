/*//////////////////////////////////////////////////////////////////////////////

Carla Pastor  
COP4530. Project 5: Hash Tables and Its Applications       
Task 2: Requirement of the Password Server Class (PassServer)
** Implementationfile**
*///////////////////////////////////////////////////////////////////////////////

#include "passserver.h"
#include "hashtable.h"
using namespace std;
using namespace cop4530;

PassServer::PassServer(size_t size) //constructor, create a hash table of the specified size
{
	htable.properSz(size);  //initialization
}

bool PassServer::load(const char* filename)
{
	return htable.load(filename);
}

bool PassServer::addUser(std::pair<string, string>&kv)
{
	string a = encrypt(kv.second);
	
	pair<string, string> dp2(kv.first,a);

	return htable.insert(dp2);
}

bool PassServer::addUser(std::pair<string, string> && kv) 
{
	pair<string, string> up2(std::move(kv));
	return addUser(up2);
}

bool PassServer::removeUser(const string & k) 
{
	htable.remove(k);
}

bool PassServer::changePassword(const pair<string, string> & p, const string & newpassword) 
{
	if(p.second == newpassword)
	{
		return false;
	}
	else if(!htable.contains(p.first))
	{
		return false;
	}
	else 
	{
		string oldPassword = encrypt(p.second);
		string newPassword = encrypt(newpassword);
		
		pair<string, string> vp(p.first, oldPassword);
		if(!htable.match(vp))
		{
			return false;  
		}
		else
		{
			pair<string, string> np(p.first, newPassword);
			htable.insert(np); return true;
		}
	}
}

bool PassServer::find(const string & user) const 
{
	return htable.contains(user);
}

void PassServer::dump() const 
{
	htable.dump();
}

size_t PassServer::size() const 
{
	htable.sizee();
}

bool PassServer::write_to_file(const char* filename) const 
{
	htable.write_to_file(filename);
}

PassServer::~PassServer()
{
	htable.clear();
}
//**************** Private interfaces: 

string PassServer::encrypt(const string & str) 
{
	char arrsalt[] = "$1$########";
	string encryptedstring= crypt(str.c_str(), arrsalt);
	encryptedstring.replace(0, 12, "");
	return encryptedstring;
}
/////////////////////////////////////////////////////////////////////////////
