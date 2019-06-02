#pragma once

#include <Geometry/Point.hpp>
#include <iosfwd>

namespace NCUtils::Geometry{
	
	template<size_t N, class REAL>	
	constexpr Point<N, REAL> constant(const REAL &val = 0){
		Point<N, REAL> ret;
		for(size_t i = 0; i < N; ++i) ret[i] = val;
		return ret;
	}
	
	template<size_t N, class REAL = double>
	constexpr Point<N, REAL> ZERO = constant<N, REAL>();

	template<size_t N, class REAL>
	Point<N, REAL> operator+(const Point<N, REAL> &P1, const Point<N, REAL> &P2){
		Point<N, REAL> ret;
		for(size_t i = 0; i < N; ++i) ret[i] = P1[i] + P2[i];
		return ret;
	}

	template<size_t N, class REAL>
	Point<N, REAL> operator-(const Point<N, REAL> &P1, const Point<N, REAL> &P2){
		Point<N, REAL> ret;
		for(size_t i = 0; i < N; ++i) ret[i] = P1[i] - P2[i];
		return ret;
	}

	template<size_t N, class REAL>
	Point<N, REAL> operator*(const REAL &a, const Point<N, REAL> &P){
		Point<N, REAL> ret;
		for(size_t i = 0; i < N; ++i) ret[i] = a*P[i];
		return ret;
	}




	template<size_t N, class REAL>
	std::ostream &operator<<(std::ostream &dest, const Point<N, REAL> &P){
		dest << "( ";
		for(size_t i = 0; i < N - 1; ++i)
			dest << P[i] << ", ";
		dest << P[N - 1] << " )";
		return dest;
	}
}
