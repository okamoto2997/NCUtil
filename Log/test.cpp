#include <Log/Log.h>
#include <iostream>

int main(){
	using namespace NCUtils::Log;
	LineStreamBuffer bf(std::cout);
	std::ostream dest(&bf);
	dest << "test  !!!\n";
	dest << "test  !!!";
	dest << "test  !!!\n";
	dest << "ujyfg";
 	dest << std::flush;
	dest << "ujyfpppg";
	dest << std::endl;
	return 0;
}
