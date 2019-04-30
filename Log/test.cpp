#include <Log/Log.h>
#include <iostream>

int main(){
	using namespace NCUtils::Log;
	SharedFileBuffer sbuf("test.log");

	std::ostream log(&sbuf);

	//std::ofstream log("test.log", std::ios::app);

	log << "=======================================================\n";
	for(size_t n = 1; n < 10000; ++n){
		log << "block No. " << n << "\n";
	log << 1 << " st. : The quick brown fox jumps over the lazy dog, ";
	log << 2 << " nd. : The quick brown fox jumps over the lazy dog, ";
	log << 3 << " rd. : The quick brown fox jumps over the lazy dog, ";
	for(size_t i = 4; i < 10; ++i)
		log << i << " th. : The quick brown fox jumps over the lazy dog, ";
	log << "\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	log << "=======================================================\n";

	return 0;
}
