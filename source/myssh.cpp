#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class sshinfo
{
public:
  string info;
  string link;
  friend ostream & operator<<(ostream&, sshinfo);
};

ostream & operator<<(ostream& os, sshinfo output)
{
  os << output.link << " | " << output.info;
  return os;
}

vector<sshinfo> connections;
const string working_file("/Volumes/Mac_Storage/Nick/OSX_Macros/myssh/resources/save_ssh");

int main(int argc, char **argv)
{
  if(argc >1)
    {
      if (argv[1] == string("--help") || argv[1] == string("--h"))
	{
	  cout << "myssh: automated shh connector" << endl
	       << "(c) Nicholas Mead - Creative Commons License" << endl << endl
	       << "To add a new connection use command:" << endl
	       << "--a, --add <server> <info>" << endl << endl
	       << "To enter removal mode use:" << endl
	       << "--r, --remove" << endl << endl;

	  return 0;
	}
      else if (argv[1] == string("--add") || argv[1] == string("--a"))
	{
	  fstream save_file(working_file,fstream::out | fstream::app);
	  if (!save_file.is_open())
	    {
	      cout << "file did not open" << endl;
	      return 1;
	    }
	  save_file << endl << argv[2] << " " << argv[3];
	  save_file.close();
	  cout << "Adding to stored connections" << endl;
	  return -2;
	}
      else if (argv[1] == string("--remove") || argv[1] == string("--r"))
	{
	  fstream save_file(working_file,fstream::in);

	  if (!save_file.is_open())
	    {
	      cout << "file did not open" << endl;
	      return 1;
	    }
  
	  while (!save_file.eof())
	    {
	      cin.exceptions(iostream::badbit | iostream::failbit);
      
	      sshinfo input;
	  
	      save_file >> input.link;
	      save_file >> input.info;

	      if (input.link == "" || input.info == "") break;
      
	      connections.push_back(input);
	    }

	  for (int i(0); i<connections.size(); i++) cout << "[" << i << "] " << connections[i] << endl;
  
	  cout << "Remove: ";

	  int i;
	  cin >> i;

	  save_file.close();
	  save_file.open(working_file,fstream::out | fstream::trunc);

	  for (int j(0); j<connections.size(); j++)
	    if (j == i) break;
	    else save_file << connections[j].link << " " << connections[j].info << endl;
	  return -3;
	}
    }
  fstream save_file(working_file,fstream::in);

  if (!save_file.is_open())
    {
      cout << "file did not open" << endl;
      return 1;
    }
  
  while (!save_file.eof())
    {
      cin.exceptions(iostream::badbit | iostream::failbit);
      
      sshinfo input;
	  
      save_file >> input.link;
      save_file >> input.info;

      if (input.link == "" || input.info == "") break;
      
      connections.push_back(input);
    }

  for (int i(0); i<connections.size(); i++) cout << "[" << i << "] " << connections[i] << endl;
  
  cout << "Connect: ";

  int i;
  cin >> i;
  
  stringstream command;
  command << "ssh ";

  for (int j(1); j<argc; j++)
    command << argv[j] << " ";
  
  command << connections[i].link;

  stringstream echo;
  echo << "echo " << command.str();

  system(echo.str().c_str());  
  system(command.str().c_str());
  
  return 0;
}
