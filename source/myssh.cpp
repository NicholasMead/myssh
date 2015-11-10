#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <sqlite3.h> 
#include "ssh_sql.h"

using namespace std;

int main(int argc, char **argv)
{
  Stored_connection::OpenDatabase((char*)"/Users/NicholasMead/Mac_Storage/Nick/OSX_Macros/myssh-git/resources/saved_ssh.db");
  vector<Stored_connection> Database = Stored_connection::ExtractFromDatabase();

  if(argc > 1)
    {
      if (argv[1] == string("--help") || argv[1] == string("--h"))
	{
	  cout << "myssh: automated shh connector" << endl
	       << "(c) Nicholas Mead - Creative Commons License" << endl << endl
	       << "To add a new connection use command:" << endl
	       << "--a, --add <user> <host> <info>" << endl << endl
	       << "To enter removal mode use:" << endl
	       << "--r, --remove" << endl << endl;
	  return 0;
	}
      else if ((argv[1] == string("--add") || argv[1] == string("--a")) && argc >= 5)
	{
	  string info;
	  for (int i(4); i < argc; i++)
	    {
	      info += argv[i];
	      info += " ";
	    }
	  Stored_connection::AddToDatabase(argv[2], argv[3], info);
	  cout << "*** Connection Added ***" << endl;
	  return 0;
	}
      else if (argv[1] == string("--remove") || argv[1] == string("--r"))
	{
	  for (auto& conection: Database)
	    cout << conection.Print() << endl;

	  cout << "remove: ";
	  int UID;
	  cin >> UID;

	  Stored_connection::RemoveFromDatabase(UID);

	  cout << "*** Connection Removed ***" << endl;
	  return 0;
	}
      else
	{
	  for (auto& conection: Database)
	    cout << conection.Print() << endl;
	  
	  cout << "Connect: ";
	  
	  int UID;
	  cin >> UID;

	  string args;
	  for (int i(1); i < argc; i++)
	    {
	      args += argv[i];
	      args += " ";
	    }	  
	}
    }
  return 0;
}
