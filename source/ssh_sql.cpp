#include "ssh_sql.h"

#include <sstream>
#include <cstdlib>
#include <sqlite3.h>
#include <iostream>

using std::string;
using std::stringstream;
using std::vector;
using std::endl;
using std::cout;

bool Stored_connection::AddToDatabase ()
{
  return Stored_connection::AddToDatabase(_user,_host,_info);
}

bool Stored_connection::AddToDatabase (string user, string host, string info)
{
  //create sql command as ss and convert to char*
  stringstream sql_ss;
  sql_ss << "INSERT INTO Stored_connection (USER, HOST, INFO) "
	 << "VAlUES (\"" << user << "\",\"" << host << "\",\"" << info << "\");";
  char * sql = (char *)sql_ss.str().c_str();
  
  //exec sql command
  int check = sqlite3_exec(db, sql, Stored_connection::callback, 0, &Stored_connection::ErrMsg);

  //return result
  return check == SQLITE_OK;
}

bool Stored_connection::RemoveFromDatabase(int UID)
{
  //create sql command as ss and convert to char*
  stringstream sql_ss;
  sql_ss << "DELETE from Stored_connection where UID = " << UID << ";";
  char * sql = (char *)sql_ss.str().c_str();
  
  //exec sql command
  int check = sqlite3_exec(db, sql, Stored_connection::callback, 0, &ErrMsg);

  //return result
  return check == SQLITE_OK;
}

void Stored_connection::Connect(int argc, char ** argv)
{
  //command line argument
  stringstream cmd;
  cmd << "ssh ";
  
  for (int i(0); i < argc; i++)
    cmd << argv[i] << " ";

  cmd << _user << "@" << _host;

  //echo command
  stringstream echo;
  echo << "echo " << cmd.str();

  system(echo.str().c_str());
  system(cmd.str().c_str());
}

string Stored_connection::Print()
{
  stringstream os;
  os << "[" << UID << "] " << _user << "@" << _host << " | " << _info;
  return os.str();
}

vector<Stored_connection> Stored_connection::ExtractFromDatabase()
{
  char sql[] = "SELECT * from Stored_conection;";
  readout_row = readout_col = 0; readout.clear();
  int check = sqlite3_exec(db, sql, Stored_connection::callback, 0, &ErrMsg);

  if(check != SQLITE_OK || readout_col != 4)
    cout << "Check: " << check << endl
	 << "readout_col: " << readout_col << endl;

  vector<Stored_connection> array;
  
  for (int row(0); row < readout_row; row++)
    array.push_back( Stored_connection(atoi(readout[row][0]),readout[row][1],readout[row][2],readout[row][3]));

  return array;
}

void Stored_connection::OpenDatabase(char * Database)
{
  sqlite3_open(Database, &db);
}

void Stored_connection::CloseDatabase()
{
  sqlite3_close(db);
}

int Stored_connection::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  readout_col = argc;
  readout_row++;

  readout.push_back(argv);

  return 0;
}  
