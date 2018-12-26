#include <iostream>
#include <boost/array.hpp>

using namespace std;
int main(){
  boost::array<int, 4> arr = {{1,2,3,4}};
  for (int i = 0; i < 4; ++i)
  {
    cout << "hi" << arr[i] << endl;
  }

  return 0;
}