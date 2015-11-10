#ifndef __ssh_sql_h__
#define __ssh_sql_h__

#include <sqlite3.h>
#include <string>
#include <vector>

class Stored_connection
{
 protected:

  //Database
  static sqlite3 * db;
  static char * ErrMsg;
  static std::vector<char **> readout; //latest Query readout
  static int readout_col;
  static int readout_row;
  
  //Member Values
  std::string _user, _host, _info;
  int UID;
  
 public:

  //Constructor
  Stored_connection(){;}
  Stored_connection(int UID, std::string user, std::string host, std::string info):
  UID(UID), _user(user), _host(host), _info(info) {;}

  //Methods 
  bool AddToDatabase ();
  static bool AddToDatabase (std::string, std::string, std::string);
  static bool RemoveFromDatabase (int);
  void Connect(int argc,char ** argv);
  std::string Print();
  static std::vector<Stored_connection> ExtractFromDatabase();
  static void OpenDatabase(char *);
  static void CloseDatabase();
  static int callback(void *NotUsed, int argc, char **argv, char **azColName);
  
};

sqlite3 * Stored_connection::db = 0;
char * Stored_connection::ErrMsg = 0;
std::vector<char **> Stored_connection::readout; //latest Query readout
int Stored_connection::readout_col = 0;
int Stored_connection::readout_row = 0;

#endif
