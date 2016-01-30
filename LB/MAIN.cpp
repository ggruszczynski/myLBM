
//#pragma managed(push, off)

//#include "headers/Node.h"
#include "CODE/Solver/Solver.h"
#include <ctime>
#include <iostream>

using namespace std;


int main() {
	cout << "!!!Hello World!!!" << endl;

	//omp_set_num_threads(1);

	std::clock_t start;
	double duration;

	start = std::clock();

	//int* p1;
	//int* p2;

	//int a1 = 4;

	//*p1 = a1;
	//p2 = &a1;

	//cout << "p1" << *p1;
	//cout << "p2" << *p2;


	LidMeshBuilder lid_mesh_builder;
	lid_mesh_builder.ReadCase();


	Solver solver;
	solver.Run();

	/*XMLParser reader;
	auto czytanka =	reader.ReadXMLCase("LidDrivenCavity.xml");
	reader.WriteCaseInfoXML("output","testZapisu");*/

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << " \n duration: " << duration << " [s] = " << duration / 60 << " min" << endl;
	//cout << " omp_get_num_threads(): " << omp_get_num_threads() << endl;

	cout << "-------------------------------------THE END---------------------------------\n" << endl;
	system("PAUSE");
	return 0;
}
