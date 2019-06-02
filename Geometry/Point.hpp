#pragma once

#include <cstddef>

namespace NCUtils::Geometry{
	
	template<size_t N, class REAL = double>
	class Point{
		REAL buf[N] = {};
		static_assert(N > 0, "N must be larger than 0.");
	public:

		constexpr Point(){ };
		constexpr Point(const Point &) = default;

		constexpr Point &operator=(const Point &P){ for(size_t i = 0; i < N; ++i) buf[i] = P[i]; return *this; }

		constexpr REAL &operator[](size_t i){ return buf[i]; }
		constexpr const REAL &operator[](size_t i) const { return buf[i]; }
	};
}
