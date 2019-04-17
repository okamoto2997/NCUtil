#pragma once

#include <streambuf>
#include <string>
#include <vector>
#include <iostream>

namespace NCUtils::Log{

	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_LineStreamBuffer : public std::basic_streambuf<CharT, Traits>{
		std::basic_string<CharT, Traits> buffer;
		std::basic_ostream<CharT, Traits> &dest;
	public:
		basic_LineStreamBuffer(std::basic_ostream<CharT, Traits> &dest) : dest(dest){}
		~basic_LineStreamBuffer(){ if(!buffer.empty()) sync(); }

	protected:
		std::streamsize xsputn(const typename Traits::char_type*s, std::streamsize count){
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
		typename Traits::int_type overflow([[maybe_unused]]typename Traits::int_type c = Traits::eof()) override{
			dest << buffer;
			buffer.clear();
			return !Traits::eof();
		}
		int sync() override{ dest << buffer << std::endl; return 0; }
	};

	using LineStreamBuffer = basic_LineStreamBuffer<char>;

}
