#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <controller.hpp>

using namespace std;


int main(int argc, char *argv[]){
	CONTROLLER *controller = new CONTROLLER();
	controller->run();
	return 0;
}
