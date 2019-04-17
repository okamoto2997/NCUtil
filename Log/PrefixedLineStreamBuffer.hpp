/**
 * @file   PrefixedLineStreamBuffer.hpp
 * @brief  Implement of basic_PrefixedLineStreamBuffer
 * @author Mamoru OKAMOTO
 * @date   2019/4/17
 */

#pragma once

#include <Log/LineStreamBuffer.hpp>

namespace NCUtils::Log{
	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_PrefixedLineStreamBuffer : public basic_LineStreamBuffer<CharT, Traits>{
		std::basic_string<CharT, Traits> prefix;
	public:
		basic_PrefixedLineStreamBuffer(const std::basic_string<CharT, Traits> &prefix, std::ostream &dest) : basic_LineStreamBuffer<CharT, Traits>(dest), prefix(prefix){}

	protected:
		typename Traits::int_type overflow([[maybe_unused]]typename Traits::int_type c = Traits::eof()) override{
			if(!Traits::eq(c, Traits::eof())) this->buffer.push_back(c);
			this->dest << prefix << this->buffer;
			this->buffer.clear();
			return !Traits::eof();
		}

	};
	using PrefixedLineStreamBuffer = basic_PrefixedLineStreamBuffer<char>;
}
