#include <iostream>
#include "math.h"
#include <signal.h>
using namespace std;

const int ARITY = 3;
bool expression(bool *x){
  return x[0] || x[1] && x[2];
}

void print_input(bool *input){
  for(int i = 0; i < ARITY; ++i){
    cout << input[i];
  }
}

int main() {
  int inputs_count = pow(2, ARITY);
  bool **inputs = new bool*[inputs_count];


  for(int i = 0; i < inputs_count; ++i){
    inputs[i] = new bool[ARITY];
    for(int j = 0; j < ARITY; ++j){
      inputs[i][j] = i & (int)pow(2, ARITY - j - 1);
    }
  }
  for (int i = 0; i < inputs_count; ++i)
  {
    if(fork() == 0){
      if(expression(inputs[i])){
        cout << "Truthy input in PID " << getpid() << ": ";
        print_input(inputs[i]);
        cout << endl;
      } else {
        cout << "False input in PID " << getpid() << ": ";
        print_input(inputs[i]);
        cout << endl;
      }
      kill(getpid(), SIGTERM);
    }
  }
  return 0;
}
