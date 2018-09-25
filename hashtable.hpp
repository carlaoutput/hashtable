/*//////////////////////////////////////////////////////////////////////////////

Carla Pastor
COP4530. Project 5: Hash Tables and Its Applications        

Task 1: HashTable Class Template
File: hashtable.hpp (containing the implementation of member functions).
*///////////////////////////////////////////////////////////////////////////////
//The algorithm for the crypt() method is MD5-based.
//The salt are character stream "$1$########".

//(K and V are the template parameters, represent the key and value types, respectively)


template<typename K, typename V>
HashTable<K,V>::HashTable(size_t size) 
{
	myTupper.resize(prime_below(size)); 	numPairs = 0;
}

template<typename K, typename V>
void HashTable<K,V>::properSz(size_t size)
{
	if(sizee()!= size) 
	{
		myTupper.resize(prime_below(size));	 numPairs = 0;
	}
}

template<typename K, typename V>
int HashTable<K,V>::sizee() const
{
	return numPairs;
}

template<typename K, typename V>
bool HashTable<K,V>::contains(const K & k) const
{
	for(auto i= myTupper[myhash(k)].begin(); i!=myTupper[myhash(k)].end(); ++i)
	{  
		if(i->first == k)
		{
			return true;  
		}
	} return false; //key is not the same 
}

template<typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> & kv) const
{
	auto &checkKeys = myTupper[myhash(kv.first)];

	return std::find(checkKeys.begin(),checkKeys.end(),kv)!=checkKeys.end();
}

template<typename K, typename V> //add the key-value pair kv into the hash table
bool HashTable<K,V>::insert(const std::pair<K,V> & kv) 
////http://www.cplusplus.com/reference 
{
	if(contains(kv.first))
	{
		auto &checkKeys = myTupper[myhash(kv.first)];
		for(auto i=checkKeys.begin(); i !=checkKeys.end(); ++i) 
		{
				if(i->first == kv.first) 
				{
					auto replace = checkKeys.erase(i);
					checkKeys.insert(replace, kv); //insert la new correct one
				}
		}return true;
	}
	else if(match(kv)) //ya got it  ...just in case
	{
			return false;
	}
	else 
	{
			myTupper[myhash(kv.first)].push_back(kv); //add more space as needed
			if(++numPairs > myTupper.size())
			{
				rehash();
		  }
			return true;
	}	
}
//////////////////////////////////////////////////////////////////////////////1
template<typename K, typename V>
bool HashTable<K,V>::insert(std::pair<K,V> && kv) //its proper move
{
		const std::pair<K,V> Pair = std::move(kv);	return insert(Pair);  
}
////////
template<typename K, typename V>
bool HashTable<K,V>::remove(const K&k)  
{
	auto &checkKeys=myTupper[myhash(k)];	bool r = false;
	for(auto i=checkKeys.begin(); i !=checkKeys.end(); ++i)
	{  
			if(i->first == k) //so, ..delete node if it is in the hash table
			{
				i = checkKeys.erase(i);	--numPairs; //to update size
				r = true;
			}
	} return r;
}
//////////////
template<typename K, typename V> 
void HashTable<K,V>::makeEmpty() //private HashTable interfaces
{
	for(auto &elements:myTupper) 
	{
			myTupper.clear(); //public interface clear() will call this function
	}
	numPairs = 0;
}

////////////////////////////////////////////////////////////////////////////////0
template<typename K, typename V>
bool HashTable<K,V>::load(const char* filename) 
{
	char c;
	std::pair<K,V> Pair;
	std::ifstream inFile;  //typedef basic_ifstream<..> ifstream;
	
	inFile.open(filename, std::ifstream::in);  // ifstream::in); 
	if(!inFile)
	{
		cout << filename << " is invalid!" << endl;
		return false;
	}
	
	while(inFile)  //<string> getline (string)
	{
			std::getline(inFile, Pair.first, ' '); //delimited; end of my obj file 
			
	   //<cctype> isspace, check if character is a white-space
	   //and extracts the space "character" from the stream
			while(isspace(inFile.peek()))  inFile.get(c); std::getline(inFile, Pair.second,'\n');
			while(isspace(inFile.peek()))  inFile.get(c); 
			
			insert(Pair);
	}
	inFile.close();	return true;
}

template<typename K, typename V>
void HashTable<K,V>::dump() const
{
	for(int in = 0; in < myTupper.size(); in++) 
	{ //If an entry contains multiple key-value pairs, separate them by a
		//semicolon character (:)
		cout << "v[" << in << "]:";

    if(!myTupper[in].empty()) 
		for(auto i = myTupper[in].begin(); i != myTupper[in].end(); ++i)
		{
			if(i != myTupper[in].begin())
				cout << ':'; //If an entry contains multiple key-value pairs

			cout << i->first << ' ' << i->second;
		}
		cout << endl;
	}
}

template<typename K, typename V>
bool HashTable<K,V>::write_to_file(const char* filename) const
{ 
	std::ofstream os;   // or ofstream os(filename); 
	os.open(filename);
	
	if(!os)
	{
		return false;
	}

	for(int in=0; in<myTupper.size();in++)
	{
		for(auto i = myTupper[in].begin();i!=myTupper[in].end();++i)
		{
			os << i->first << ' ' << i->second << '\n';
		}
	}
	os.close(); 
	return true;
}

////////////////////////////////////////
template<typename K, typename V>
void HashTable<K,V>::clear()
{
	makeEmpty();  
}

template<typename K, typename V>
void HashTable<K,V>::rehash() 
{
	auto tempOld=myTupper;
	myTupper.resize(prime_below(2 * myTupper.size()));

	for(auto & elements: myTupper) 	elements.clear();	
	numPairs = 0;
	
	for(auto & elements: tempOld)
	{
		for(auto & Pair:elements) insert(move(Pair));
	}
}
/////////////////
template<typename K, typename V>
size_t HashTable<K,V>::myhash(const K & k) const
{
	static std::hash<K> tempHs;  
	return tempHs(k) % myTupper.size();
}

////***********************************************************************/
// Function provided in class, (FSU)
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below(unsigned long n)
{
	  if(n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
	  if(n == max_prime)
    {
      return max_prime;
    }
	  if(n <= 1)
    {
      std::cerr << "** input too small \n";
      return 0;
    }

	  // now: 2 <= n < max_prime
  std::vector <unsigned long> v(n+1);
  setPrimes(v);
  while(n > 2)
    {
      if(v[n] == 1)
        return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K,V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for(i = 2; i < n; ++i)
    vprimes[i] = 1;

  for(i = 2; i*i < n; ++i)
    {
      if(vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template<typename K, typename V>  
HashTable<K,V>::~HashTable()  //destructor
{
	clear();  //bye bye all
}
//////////////////////////////////////////////////////////////////////////////

