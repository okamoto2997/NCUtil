#include <iostream>
#include <Geometry/Geometry.h>

using namespace NCUtils::Geometry;

int main(){
	Point<5> p1, p2;
	Point<5> p3(p1);
	for(size_t i = 0; i < 5; ++i) p1[i] = i + 1;
	for(size_t i = 0; i < 5; ++i) p2[i] = p1[i]*p1[i];
	std::cout << p1 << "\n";
	std::cout << p2 << "\n";
	std::cout << p3 << "\n";
	std::cout << p1 + p2 << "\n";
	return 0;
}
