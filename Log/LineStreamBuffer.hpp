#pragma once

#include <streambuf>
#include <string>

namespace NCUtils::Log{

	template<class CharT, class Traits = std::char_traits<CharT>>
	class LineBuffer : public std::basic_streambuf<CharT, Traits>{
		
	};

}
