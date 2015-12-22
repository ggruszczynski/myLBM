
#include "headers/Node.h"
#include "headers/Solver.h"
#include <ctime>

using namespace std;

//#include <Eigen/Dense>
//using namespace Eigen;



int main() {
	cout << "!!!Hello World!!!" << endl;
	std::clock_t start;
	double duration;

	start = std::clock();

	const unsigned x = 300; //width x
	const unsigned y = 60; //height y
	const unsigned totalTime = 1000;
	const unsigned timeSave = 10;


	Solver solver(x, y, totalTime, timeSave);
	//auto solver = new Solver(n_rows, n_col);
	solver.Run();


	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "duration: " << duration << endl;

    cout <<"-------------------------------------THE END---------------------------------\n"<<endl;
	system("PAUSE");
	return 0;
}
