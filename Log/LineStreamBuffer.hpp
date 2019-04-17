/**
 * @file   LineStreamBuffer.hpp
 * @brief  Implement of basic_LineStreamBuffer, which is generalization of LineStreamBuffer
 * @author Mamoru OKAMOTO
 * @date   2019/4/17
 */


#pragma once

#include <streambuf>
#include <string>
#include <vector>
#include <iostream>

namespace NCUtils::Log{

	/*! @class basic_LineStreamBuffer
	 *  @brief stream buffer for line buffering inheriting std::basic_streambuf
	 */
	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_LineStreamBuffer : public std::basic_streambuf<CharT, Traits>{
	public:
		basic_LineStreamBuffer(std::basic_ostream<CharT, Traits> &dest) : dest(dest){}
		~basic_LineStreamBuffer(){ if(!buffer.empty()) sync(); }

	protected:
		/*! line buffer */
		std::basic_string<CharT, Traits> buffer;
		/*! destination of buffered data */
		std::basic_ostream<CharT, Traits> &dest;
		/*! for each new line character, overflow will be called */
		std::streamsize xsputn(const typename Traits::char_type *s, std::streamsize count) override{
			const typename Traits::char_type *b = s, *i = s, *e = s + count;
			while(i != e){
				if(Traits::eq(*i, dest.widen('\n'))){ 
					 buffer.append(b, ++i), overflow();
					 if(i == e) return count;
					 b = i;
				}
				++i;
			}
			buffer.append(b, i);
			return count;
		}
		/*! output and clear buffer */
		typename Traits::int_type overflow([[maybe_unused]]typename Traits::int_type c = Traits::eof()) override{
			if(!Traits::eq(c, Traits::eof())) buffer.push_back(c);
			dest << buffer;
			buffer.clear();
			return !Traits::eof();
		}
		int sync() override{
			if(buffer.empty()) return 0;
			if(!Traits::eq(buffer.back(), dest.widen('\n'))) buffer.push_back(dest.widen('\n'));
			overflow();
			dest.flush();
			return 0; }
	};

	using LineStreamBuffer = basic_LineStreamBuffer<char>;

}
