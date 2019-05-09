#pragma once
constexpr auto INF = 999999;
#include <iostream>
#include <fstream>
#include <string>

class smartMST {
private:
	std::unique_ptr<std::unique_ptr<int[]>[]> graph;		//2D array to store provided undirected graph -- smart pointer, can handle a graph of any size
	std::unique_ptr<std::unique_ptr<int[]>[]> graph2;		//2D array to store final undirected graph for printing and writing to file
	int numVerts = 0;
public:
	smartMST(std::string inFile)  //Default constructor, passes in name of file which has undirected graph
	{
		int weight;
		std::string line;
		std::fstream input;
		input.open(inFile);

		while (std::getline(input, line))		//Number of vertices will equal number of rows in provided file
			numVerts++;
		input.clear();
		input.seekg(0, std::ios::beg);			//Return to beginning of file so values may be read

		graph = std::make_unique<std::unique_ptr<int[]>[], 0>(getVerts());		//Initializes 2D array row values
		graph2 = std::make_unique<std::unique_ptr<int[]>[], 0>(getVerts());		//Initializes 2D array row values
		for (int i = 0; i < getVerts(); i++)									//Makes 2D arrays two-dimensional by storing more pointer arrays within
		{
			std::unique_ptr<int[]> graphCol = std::make_unique<int[], 0>(getVerts());
			std::unique_ptr<int[]> graph2Col = std::make_unique<int[], 0>(getVerts());
			graph[i] = move(graphCol);
			graph2[i] = move(graph2Col);
		}

		for (int i = 0; i < numVerts; i++) {		//Fills both graph arrays with data from undirected graph in file
			for (int j = 0; j < numVerts; j++)
			{
				input >> weight;
				graph[i][j] = weight;
				graph2[i][j] = weight;
			}
		}
		input.close();
	}
	~smartMST() {}		//Since smart pointers are used, no memory management or deletions for garbage collection are necessary in destructor

	int getVerts()const { return numVerts; }		//Returns number of vertices
	int getEdges()const { return numVerts - 1; }	//Returns number of edges (always verts - 1)

	void prim(int startVert)		//Minimum tree function based on Prim's algorithm -- passes in the start vertex
	{
		int x, y, min;
		std::unique_ptr<bool[]> selected = std::make_unique<bool[], false>(getVerts());		//Array to indicate which vertices have been checked -- false by default
		for (int i = 0; i < getVerts(); i++)
		{
			for (int j = 0; j < getVerts(); j++)		//Ensures graph2 array values are reset to zero so it can be populated with only minimum edges
				graph2[i][j] = 0;
		}
		selected[startVert] = true;
		for (int e = 0; e < getEdges(); e++)	//Ensures the correct number of edges are added
		{
			x = 0; y = 0; min = INF;
			for (int i = 0; i < getVerts(); i++)
			{
				for (int j = 0; (j < getVerts()) && selected[i]; j++)
				{
					if (!selected[j] && graph[i][j] && min > graph[i][j]) //Ensures min edge has not been found already, is not zero, and passes sanity check
					{
							min = graph[i][j];		//Stores found min edge
							x = i; y = j;			//Stores array location of min edge
					}
				}
			}
			graph2[x][y] = graph[x][y];		//Adds the min edge to graph2 (row)
			graph2[y][x] = graph[x][y];		//Adds the min edge to graph2 (column)
			std::cout << "Add edge " << x << " to " << y << '\n';
			selected[y] = true;		//Indicates vertex has been searched
		}
	}

	void printGraph(std::string outFile)		//Print and write graph to file (desired filename passed in)
	{
		std::ofstream output;
		output.open(outFile);
		for (int i = 0; i < getVerts(); i++) {
			for (int j = 0; j < getVerts(); j++)
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