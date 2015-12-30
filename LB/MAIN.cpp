
#include "headers/Node.h"
#include "headers/Solver.h"
#include <ctime>

using namespace std;

//#define BOOST_ALL_NO_LIB 

#include <iostream>



int main() {
	cout << "!!!Hello World!!!" << endl;
	std::clock_t start;
	double duration;

	start = std::clock();

	Solver solver;
	solver.Run();

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "duration: " << duration << " [s] = "<< duration/60 << " min" << endl;
    cout <<"-------------------------------------THE END---------------------------------\n"<<endl;
	system("PAUSE");
	return 0;
}
