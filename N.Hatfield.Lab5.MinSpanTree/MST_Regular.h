#pragma once
#define INF 999999
#include <iostream>
#include <fstream>
#include <string>

class MST {
private:
	int** graph = NULL;
	int** graph2 = NULL;
	bool* selected = NULL;
	int numVerts = 0;
public:
	MST(std::string inFile)
	{
		int weight;
		std::string line;
		std::fstream input;
		input.open(inFile);

		while (std::getline(input, line))
			numVerts++;
		input.clear();
		input.seekg(0, std::ios::beg);

		graph = new int*[numVerts];
		graph2 = new int*[numVerts];
		selected = new bool[numVerts];
		for (int i = 0; i < numVerts; i++)
		{
			graph[i] = new int[numVerts];
			graph2[i] = new int[numVerts];
		}

		for (int i = 0; i < numVerts; i++) {
			for (int j = 0; j < numVerts; j++)
			{
				input >> weight;
				graph[i][j] = weight;
				graph2[i][j] = weight;
			}
		}
		input.close();
	}
	~MST()
	{
		for (int i = 0; i < numVerts; i++) {
			delete[] graph[i];
			delete[] graph2[i];
		}
		delete[] graph2;
		delete[] selected;
	}

	void prim(int startVert)
	{
		int x, y, min;
		for (int i = 0; i < getVerts(); i++) {
			for (int j = 0; j < getVerts(); j++)
			{
				selected[i] = false;
				graph2[i][j] = 0;
			}
		}
		selected[startVert] = true;
		for (int e = 0; e < getEdges(); e++)
		{
			x = 0; y = 0; min = INF;
			for (int i = 0; i < getVerts(); i++)
			{
				for (int j = 0; (j < getVerts()) && selected[i]; j++)
				{
					if (!selected[j] && graph[i][j] && min > graph[i][j])
					{
							min = graph[i][j];
							x = i; y = j;
					}
				}
			}
			graph2[x][y] = graph[x][y];
			graph2[y][x] = graph[x][y];
			std::cout << "Add edge " << x << " to " << y << '\n';
			selected[y] = true;
		}
	}

	int getVerts()const { return numVerts; }
	int getEdges()const { return numVerts - 1; }

	void printGraph(std::string outFile)
	{
		std::ofstream output;
		output.open(outFile);

		for (int i = 0; i < numVerts; i++) {
			for (int j = 0; j < numVerts; j++)
			{
				output << graph2[i][j] << ' ';
				std::cout << graph2[i][j] << ' ';
			}
			output << '\n';
			std::cout << '\n';
		}
		output.close();
	}
};