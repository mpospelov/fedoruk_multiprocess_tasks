#include <iostream>
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

void print_if_truthy(bool *input, int setted_values = 0) {
  if(setted_values == ARITY - 1){
    bool *input0 = new bool[ARITY];
    bool *input1 = new bool[ARITY];
    memcpy(input0, input, ARITY * sizeof(bool));
    memcpy(input1, input, ARITY * sizeof(bool));
    input0[setted_values] = false;
    input1[setted_values] = true;

    if(expression(input0)){
      cout << "Truthy input: ";
      print_input(input0);
      cout << endl;
    }
    if(expression(input1)){
      cout << "Truthy input: ";
      print_input(input1);
      cout << endl;
    }
  } else {
    int parent_pid = getpid();
    pid_t pid = fork();
    if(pid == 0){
      // cout << getpid() << endl;
      // cout << setted_values << "|";
      // print_input(input);
      // cout << endl;
      bool *input0 = new bool[ARITY];
      bool *input1 = new bool[ARITY];
      memcpy(input0, input, ARITY * sizeof(bool));
      memcpy(input1, input, ARITY * sizeof(bool));

      input0[setted_values] = false;
      input1[setted_values] = true;
      cout << "Generated 2 childs for solving\n";
      print_input(input0);
      cout << "|" << setted_values << endl;
      print_input(input1);
      cout << "|" << setted_values << endl;

      setted_values++;
      print_if_truthy(input0, setted_values);
      print_if_truthy(input1, setted_values);
    } else if(pid > 0){
      // cout << "\nParent process stoped. PID:" << parent_pid << "\n#######\n";
    }
  }
}

int main() {
  bool *input = new bool[ARITY];
  print_if_truthy(input);
  return 0;
}
