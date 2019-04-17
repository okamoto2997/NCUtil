#include "LogStreamBuffer.hpp"

namespace NCUtils::Log{
	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_PrefixedBlockStreamBuffer : public basic_LineStreamBuffer<CharT, Traits>{
		std::basic_string<CharT, Traits> prefix, blank;
		bool is_flushed = true;
	public:
		basic_PrefixedBlockStreamBuffer(const std::basic_string<CharT, Traits> &prefix, std::ostream &dest) : basic_LineStreamBuffer<CharT, Traits>(dest), prefix(prefix), blank(prefix.length(), dest.widen(' ')){}
		~basic_PrefixedBlockStreamBuffer(){ if(!this->buffer.empty()) sync(); }

	protected:
		typename Traits::int_type overflow([[maybe_unused]]typename Traits::int_type c = Traits::eof()) override{
			if(!Traits::eq(c, Traits::eof())) this->buffer.push_back(c);
			this->dest << (is_flushed ? prefix : blank) << this->buffer;
			this->buffer.clear();
			is_flushed = false;
			return !Traits::eof();
		}

		int sync() override{
			auto ret = basic_LineStreamBuffer<CharT, Traits>::sync();
			is_flushed = true;
			return ret;
		}

	};
	using PrefixedBlockStreamBuffer = basic_PrefixedBlockStreamBuffer<char>;
}

