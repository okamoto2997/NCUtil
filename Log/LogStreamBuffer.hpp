/**
 * @file   LogStreamBuffer.hpp
 * @brief  Implement of basic_LogStreamBuffer
 * @author Mamoru OKAMOTO
 * @date   2019/4/17
 */


#pragma once

#include <Log/LineStreamBuffer.hpp>
#include <chrono>
#include <iomanip>
#include <unistd.h>

namespace NCUtils::Log{

	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_LogStreamBuffer : public basic_LineStreamBuffer<CharT, Traits>{
		using Base = basic_LineStreamBuffer<CharT, Traits>;
		using string = std::basic_string<CharT, Traits>;
		string prefix;
		size_t current_line = 1;
	public:
		basic_LogStreamBuffer(std::ostream &dest ) : 
			basic_LogStreamBuffer(std::to_string(getpid()) + "/" + std::to_string(getppid()) + " : ", dest){}
		basic_LogStreamBuffer(const string &prefix, std::ostream &dest ) : 
			basic_LineStreamBuffer<CharT, Traits>(dest), prefix(prefix){

				using system_clock = std::chrono::system_clock;                                                           
				time_t current_time = system_clock::to_time_t(system_clock::now());                                       
				this->dest << "# log started at " << std::put_time(std::localtime(&current_time), "%F %T") << "\n";   
				this->dest << "# format -> prefix : [line, ellapsed time] : detail " << "\n";
				this->dest.flush();
				start_time = std::chrono::steady_clock::now();

		}

	protected:
		std::chrono::steady_clock::time_point start_time; 
		/*! output and clear buffer */
		typename Traits::int_type overflow([[maybe_unused]]typename Traits::int_type c = Traits::eof()) override{
			auto current_time = std::chrono::steady_clock::now();
			auto ellapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);
			char buf[128];
			sprintf(buf, "[%09zu, %014.6f]", current_line++, ellapsed_time.count()*1e-6);

			this->dest << prefix << buf << " : ";
			Base::overflow(c);
			return !Traits::eof();
		}
	};

	using LogStreamBuffer = basic_LogStreamBuffer<char>;
}
