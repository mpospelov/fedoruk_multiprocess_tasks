#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;
const char EXAMPLE_USAGE[] = "Example usage of program: ./a.out file_name prototype";
char AR_COMMAND[] = "ar -t ";

class ArFinder{

  vector<string> archive_names;

public:
  ArFinder(char *file_name){
    char buff[1024];
    char *command = strcat(AR_COMMAND, file_name);
    FILE *in = popen(command, "r");
    while(fgets(buff, sizeof(buff), in) != NULL){
      string str(buff);
      str = str.substr(0, str.length()-1);
      archive_names.push_back(str);
    }
  }

  void print_prototype_matches(char *prototype){
    regex prototype_regex = regex(prototype);
    for (vector<string>::iterator it = archive_names.begin() ; it != archive_names.end(); ++it){
      if(regex_match(*it, prototype_regex)){
        cout << *it << endl;
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

  ArFinder *m = new ArFinder(file_name);
  m -> print_prototype_matches(prototype);

  return 0;
}
