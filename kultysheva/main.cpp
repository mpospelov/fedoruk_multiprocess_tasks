#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

bool func(bool x1, bool x2, bool x3)
{
	//return (x1 || x2) && (!x2 || x3);
	//return !x1 && !x2 && !x3;
	return (x1 || !x2) && x3;
}

int main()
{
	int x[3];
	int ppid = getpid();
	std::cout << "PARENT PID: " << getpid() << std::endl;

	for(int i = 0; i < 3; ++i){
		x[i] = fork();
	}
	printf(
		"Input in PID %d: expression(%d%d%d) = %d\n",
	  getpid(),
	  (bool)x[0], (bool)x[1], (bool)x[2],
	  func(x[0], x[1], x[2])
	);

	sleep(60);

	return 0;
}


