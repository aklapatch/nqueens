all:
	g++ -g -Og nqueens.cpp -o nqueens.exe

profile:
	g++ -fprofile-arcs -ftest-coverage -Og nqueens.cpp -o nqueens.exe