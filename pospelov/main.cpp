#include <iostream>
#define READ_END 0
#define WRITE_END 1

using namespace std;
const char EXAMPLE_USAGE[] = "Example usage of program: ./a.out file_name prototype";

class ArFinder{

public:
  ArFinder(char *file_name, char *prototype){
    char buff[1024];
    int pid;
    int fds[2];
    pipe(fds);

    switch(pid = fork()){
      case -1:
        perror("Can't fork");
        exit(1);
      case 0:
        dup2(fds[1], 1);
        execl("/usr/bin/ar", "ar", "-t", file_name, NULL);
        exit(1);
      default:
        dup2(fds[0], 0);
        execl("/usr/bin/grep", "grep", prototype, NULL);
    }
  }

};

int main(int argc, char **argv){
  // ARGV parsing
  char *file_name = argv[1];
  char *prototype = argv[2];
  if(!file_name){
    cout << "file_name parameter is missing!\n";
    cout << EXAMPLE_USAGE;
    return 1;
  }

  if(!prototype){
    cout << "prototype parameter is missing!\n";
    cout << EXAMPLE_USAGE << endl;
    cout << "prototype: \n1. * - any char\n2. a - 'a' char\n3. a* - usage of both(files start with 'a' char)";
    return 1;
  }
  // END ARGV parsing

  ArFinder *m = new ArFinder(file_name, prototype);
  return 0;
}
