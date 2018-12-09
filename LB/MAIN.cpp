
//#pragma managed(push, off)

#include "CODE/Solver/Solver.h"
#include <ctime>
#include <iostream>

using namespace std;


int main() {
	cout << "!!!Hello World!!!" << endl;
	//omp_set_num_threads(2);

    {
        cout << "Testing openMP: START" << endl;
        int thread_id, thr_num, proc_num;
        proc_num = omp_get_num_procs();
        #pragma omp parallel private(thread_id) shared(thr_num, proc_num) default(none)
        //possible options: default private | shared | none, if not defined then shared, if default none - visibility of variable must be defined
        {
            //inside pragma - private variables
            thread_id = omp_get_thread_num(); //my thread_id  numer watku is private
            thr_num = omp_get_num_threads();
            printf("thread %d of %d, number of proc %d\n", thread_id, thr_num, proc_num);
        }
        cout << "Testing openMP: END" << endl;
    }

	std::clock_t start;
	double duration;

	start = std::clock();

	Solver solver;
	solver.Run();

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << " \n duration: " << duration << " [s] = " << duration / 60 << " min" << endl;


	cout << "-------------------------------------THE END---------------------------------\n" << endl;
//	system("PAUSE");
	return 0;
}
