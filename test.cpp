#include <iostream>
#include <set>

#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
  cout << "Test para greedy\n" << endl;

  srand(time(NULL));

  for(int i=0; i<15; i++){
      cout << rand()%10 << endl;
  }

  return 0;
}
