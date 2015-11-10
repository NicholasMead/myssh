target = myssh
source = ./source/
flags = -std=c++11 -l sqlite3

all: $(source)myssh.cpp clean
	g++ $(flags) $(source)myssh.cpp -o $(target)

clean:
	rm -f $(target)
