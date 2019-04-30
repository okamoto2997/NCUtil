#pragma once

#include <streambuf>
#include <filesystem>
#include <string>
#include <fstream>
#include <mutex>
#include <fcntl.h>
#include <thread>
#include <iostream>

namespace NCUtils::Log{
	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_SharedFileBuffer
		 : public std::basic_streambuf<CharT, Traits>
	{
		std::mutex file_access;
		std::filesystem::path abs_path, lock_path;
		std::basic_filebuf<CharT, Traits> file;
		std::basic_string<CharT, Traits> buffer;
	public:
		basic_SharedFileBuffer(const std::basic_string<CharT, Traits> &file_name)
			: abs_path(std::filesystem::current_path() / file_name),
				lock_path(std::filesystem::current_path() / ("." + file_name + ".lock")){}
		~basic_SharedFileBuffer(){
			sync();
		}
	protected:
		std::streamsize xsputn(const typename Traits::char_type *s, std::streamsize count) override{
			buffer.append(s, s + count);
			return count;
		}
		/*! output and clear buffer */
		typename Traits::int_type overflow([[maybe_unused]]typename Traits::int_type c = Traits::eof()) override{
			std::lock_guard<std::mutex> lock(file_access);
			int fd = -1;
			while((fd = open(lock_path.c_str(), O_CREAT | O_EXCL, 0)) == -1){
				//std::cerr << "failed to create lock file : " << lock_path << "\n";
				std::this_thread::yield();
				//std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			if(file.open(abs_path, std::ios::app) == nullptr){
				std::cerr << "failed to open file : " << abs_path << "\n";
				throw std::filesystem::filesystem_error(std::string("failed to open file"), abs_path, std::error_code());
			}

			file.sputn(buffer.c_str(), buffer.size());
			file.close();
			close(fd);
			unlink(lock_path.c_str());
			return !Traits::eof();
		}
		int sync() override{
			if(buffer.empty()) return 0;
			overflow();
			return 0;
	 	}
	};

	using SharedFileBuffer = basic_SharedFileBuffer<char>;
}
