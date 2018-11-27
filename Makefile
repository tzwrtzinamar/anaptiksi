all: main

main: project.cpp functions.cpp
	g++ -g3  project.cpp functions.cpp -o project