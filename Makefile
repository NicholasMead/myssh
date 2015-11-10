target = myssh
source = ./source/
flags = -std=c++11
SQL = -l sqlite3

all: ssh_sql.o myssh.o
	g++ -o $(target) $(SQL) ssh_sql.o myssh.o 

ssh_sql.o: $(source)ssh_sql.h $(source)ssh_sql.cpp
	g++ -c $(flags) $(source)ssh_sql.cpp

myssh.o: $(source)myssh.cpp
	g++ -c $(flags) $(source)myssh.cpp

clean:
	rm -f $(target) *.o
