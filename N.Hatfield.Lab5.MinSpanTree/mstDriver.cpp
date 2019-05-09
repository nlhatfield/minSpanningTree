#include "MST_Smart.h"

using namespace std;

int main()
{
	smartMST test("test.txt");
	
	cout << "Number of vertices is " << test.getVerts() << '\n';
	cout << "Number of edges is " << test.getEdges() << '\n';
	cout << "Matrix is:\n";
	test.printGraph("out.txt");
	cout << "\n";

	cout << "Begin MST 1 starting at Vertex 0\n";
	test.prim(0);
	cout << '\n';
	test.printGraph("MST1.txt");
	cout << "End of MST 1\n\n";

	cout << "Begin MST 2 starting at Vertex 4\n";
	test.prim(4);
	cout << '\n';
	test.printGraph("MST2.txt");
	cout << "End of MST 2\n\n";

	cout << "Begin MST 3 starting at Vertex 2\n";
	test.prim(2);
	cout << '\n';
	test.printGraph("MST3.txt");
	cout << "End of MST 3\n\n";

	system("pause");
	return 0;
}