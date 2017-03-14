#pragma once

#include <iostream>
#include <fstream>
using namespace std;

class PlaneCreator
{
public:
	PlaneCreator(int r, int c);
	~PlaneCreator();

	void create();

	int rows;
	int columns;

	float* vertices;  // array.
	float* normals;   // array.
	int* faces; // array.
};

