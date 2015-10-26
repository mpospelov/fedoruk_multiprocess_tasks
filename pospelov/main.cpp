#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#define READ_END 0
#define WRITE_END 1

using namespace std;
const char EXAMPLE_USAGE[] = "Example usage of program: ./a.out file_name prototype";
char AR_COMMAND[] = "/bin/ar";

class ArFinder{

  void print_prototype_matches(char *prototype){
    // for (vector<string>::iterator it = archive_names.begin() ; it != archive_names.end(); ++it){
    //   if(regex_match(*it, prototype_regex)){
    //     cout << *it << endl;
    //   }
    // }
  }
public:
  ArFinder(char *file_name, char *prototype){
    char buff[1024];
    char *command = strcat(AR_COMMAND, file_name);
    int pid;
    int fds[2];
    regex prototype_regex = regex(prototype);
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
        while(1){
          cin >> buff;
          if(regex_match(buff, prototype_regex)){
            cout << buff << endl;
          }
      }
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
