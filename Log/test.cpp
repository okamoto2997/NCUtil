#include <Log/Log.h>
#include <iostream>

int main(){
	using namespace NCUtils::Log;
	LineStreamBuffer log1(std::cout);
	PrefixedLineStreamBuffer log2("[prefix : ]", std::cout);
	LogStreamBuffer log3(std::cout);
	std::ostream dest1(&log1);
	std::ostream dest2(&log2);
	std::ostream dest3(&log3);
	PrefixedBlockStreamBuffer log4("[block prefix]", dest3);
	std::ostream dest4(&log4);
	dest1 << "test  !!!\n";
	dest1 << "test  !!!";
	dest1 << "test  !!!\n";
	dest1 << "ujyfg";
 	dest1 << std::flush;
	dest1 << "ujyfpppg";
	dest1 << std::endl;
	dest2 << "test  !!!\n";
	dest2 << "test  !!!";
	dest2 << "test  !!!\n";
	dest2 << "ujyfg";
 	dest2 << std::flush;
	dest2 << "ujyfpppg";
	dest2 << std::endl;
	dest3 << "test  !!!\n";
	dest3 << "test  !!!";
	dest3 << "test  !!!\n";
	dest3 << "ujyfg";
 	dest3 << std::flush;
	dest3 << "ujyfpppg";
	dest3 << std::endl;
	dest4 << "test  !!!\n";
	dest4 << "test  !!!";
	dest4 << "test  !!!\n";
	dest4 << "ujyfg";
	dest4 << "std::flush";
 	dest4 << std::flush;
	dest4 << "ujyfpppg\n";
	dest4 << "flush by std::endl";
	dest4 << std::endl;
	dest4 << "new block\n";
	dest4 << "new block^\n";
	dest4 << "new block-\n";
	dest4 << "new block*";
	return 0;
}
