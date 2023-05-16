CC = g++


all: 
	g++ $(pkg-config --cflags Qt5Widgets) -fPIC main.cpp -o main $(pkg-config --libs Qt5Widgets)