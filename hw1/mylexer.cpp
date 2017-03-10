/// William Thurman        2/7/17
/// CS3500                 lexicalAnalysis.cpp


#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool integer(const string s);
bool dec(const string s);
bool sci(const string s);
bool hex(const string s);
bool key(const string s);
bool id(const string s);
bool email(const string s);

int main()
{
  string input;
  int runs;
	vector<string> lexemes;
  
  cin >> runs;
  
	for( int i = 0; i < runs; i++ )
	{
		cin >> input;
		lexemes.push_back(input);
	}
	
	for(int i = 1; i <= runs; i++)
	{
		cout << i << ": ";
		
		if(integer(lexemes[i-1]))
			cout << "Integer." << endl;
		else if(dec(lexemes[i-1]))
			cout << "Decimal." << endl;
		else if(hex(lexemes[i-1]))
			cout << "Hexadecimal." << endl;
		else if(key(lexemes[i-1]))
			cout << "Keyword." << endl;
		else if(sci(lexemes[i-1]))
			cout << "Scientific." << endl;
		else if(id(lexemes[i-1]))
			cout << "Identifier." << endl;
		else if(email(lexemes[i-1]))
			cout << "Email." << endl;
		else
			cout << "INVALID!" << endl;
	}
  return 0;
}

bool integer(const string s)
{
  int state = 0;
  for( int i = 0; i < s.length(); i++ )
  {
    if( (s[i] == '+' || s[i] == '-') && state == 0 )
    {
      state = 1;
    }
		else if( state == 1 && isdigit(s[i]) )
		{
			state = 2;
		}
    else if( isdigit(s[i]) && state == 0 )
    {
      state = 2;
    }
		else if ( state == 2 && isdigit(s[i]) )
		{
			//no transition
		}
    else 
    {
      state = -1;
    }
  }
  if(state == 2)
    return true;
  return false;    
}

bool dec(const string s)
{
	int state = 0;
	for(int i = 0; i < s.length(); i++)
	{
	  if(state == 0 && s[i] == '.' )
		{
			if(integer(s.substr(0, i)))
			{
				state = 1;
			}
			else 
			{
				state = -1;
			}
		}
		else if(state == 1 && isdigit(s[i]) )
		{
			state = 2;
		}
		else if(state == 2 && isdigit(s[i]) )
		{
			
		}
		else if(state == 2 && !isdigit(s[i]) )
		{
			state = -1;
		}
	}
	if(state == 2)
		return true;
	return false;
}

bool sci(const string s)
{
	int state = 0;
	for( int i = 0; i < s.length(); i++)
	{
		if(state == 0 && s[i] == 'E' )
		{
			if(dec(s.substr(0, i)))
			{
				state = 1;
			}
			else
			{
				state = -1;
			}
		}
		else if(state == 1 && (s[i] == '+' || s[i] == '-') )
		{
			state = 2;
		}
		else if(state == 1 && (isdigit(s[i]) && s[i] != '0') )
		{
			state = 3;
		}
		else if(state == 2 && (isdigit(s[i]) && s[i] != '0') )
		{
			state = 3;
		}
		else if(state == 3 && isdigit(s[i]) )
		{
			
		}
		else if(state == 3 && !isdigit(s[i]) )
		{
			state = -1;
		}
	}
	if( state == 3 )
		return true;
	return false;
}

bool hex(const string s)
{
	int state = 0;
	for( int i = 0; i < s.length(); i++ )
	{
		if(  ( isdigit(s[i]) || (s[i] >= 'A' && s[i] <= 'F') ) && state == 0 )
		{
			state = 1;
		}
		else if(state == 1 && (isdigit(s[i]) || (s[i] >= 'A' && s[i] <= 'F')) )
		{
			//no transtion
		}
		else if ( state == 1 && s[i] == 'H' )
		{
			state = 2;
		}
		else 
		{
			state = -1;
		}
	}
	if(state == 2)
		return true;
	return false;
}

bool key(const string s)
{
	if(s == "while" || s == "if" || s == "else")
		return true;
	return false;
}

bool id(const string s)
{
	int state = 0;
	if(!hex(s))
	{
		for(int i = 0; i < s.length(); i++)
		{
			if( state == 0 && isalpha(s[i]) )
			{
				state = 1;
			}
			else if( state == 1 && (isalnum(s[i]) || s[i] == '_') )
			{
				
			}
			else
			{
				state = -1;
			}
		}
	}
	if( state == 1 )
		return true;
	return false;
}

bool email(const string s)
{
	int state = 0;
	int start = 0;
	for( int i = 0; i < s.length(); i++)
	{
		if( state == 0 && s[i] == '.' )
		{
			if (id(s.substr(start, i-start)))
			{
				state = 1;
				start = i+1;
			}
			else
			{
				state = -1;
			}
		}
		else if( state == 0 && s[i] == '@' )
		{
			if (id(s.substr(start, i-start)))
			{
				state = 2;
				start = i+1;
			}
			else
			{
				state = -1;
			}
		}
		else if( state == 1 && s[i] == '@' )
		{
			if (id(s.substr(start, i-start)))
			{
				state = 2;
				start = i+1;
			}
			else
			{
				state = -1;
			}
		}
		else if( state == 1 && s[i] == '.' )
		{
			if (id(s.substr(start, i-start)))
			{
				start = i+1;
			}
			else
			{
				state = -1;
			}
		}
		else if( state == 2 && s[i] == '.' )
		{
			if (id(s.substr(start, i-start)))
			{
				state = 3;
				start = i+1;
			}
			else
			{
				state = -1;
			}
		}
		else if( state == 3 && s[i] == '.' )
		{
			if (id(s.substr(start, i-start)))
			{
				start = i+1;
			}
			else
			{
				state = -1;
			}
		}
	}
	if(state == 3 )
		if( s.substr(s.length()-3, 3) == "com" || s.substr(s.length()-3, 3) == "edu" || s.substr(s.length()-3, 3) == "net")
			state = 4;
		
	if(state == 4)
		return true;
	return false;
}