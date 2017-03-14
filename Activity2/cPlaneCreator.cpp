#include "cPlaneCreator.h"

PlaneCreator::PlaneCreator(int r, int c)
{
	rows = r;
	columns = c;
	vertices = new float[rows*columns*3];
	normals = new float[rows*columns*3];
	//faces = new int[???];
}

PlaneCreator::~PlaneCreator()
{
	delete vertices;
	delete normals;
	delete faces;
}

void PlaneCreator::create()
{
	ofstream myfile("assets/plane.obj");
	if( myfile.is_open() )
	{
		myfile << "#PLANE.\n";
		int vCounter = 0;
		int nCounter = 0;
		
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < columns; c++)
			{
				vertices[vCounter++] = (float)r;
				vertices[vCounter++] = 0.0f;
				vertices[vCounter++] = (float)c;				

				normals[nCounter++] = 0.0f;
				normals[nCounter++] = 1.0f;
				normals[nCounter++] = 0.0f;
			}
		}

		// FILL FACES HERE
		

		for (int v = 0; v < rows * columns; v++)
		{
			myfile << "v " << vertices[v * 3 + 0] << " " << vertices[v * 3 + 1] << " " << vertices[v * 3 + 2] << "\n";
		}

		myfile << "\n";

		for (int n = 0; n < rows * columns; n++)
		{
			myfile << "vn " << normals[n * 3 + 0] << " " << normals[n * 3 + 1] << " " << normals[n * 3 + 2] << "\n";
		}

		myfile << "\n";

		// WRITE TO FILE HERE
		

		myfile.close();
	}
	else cout << "Unable to open file";
}
