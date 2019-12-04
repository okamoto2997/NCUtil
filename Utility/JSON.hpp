#pragma once
#include <optional>
#include <string>
#include <vector>
#include <map>

//
// See Also:
//   https://www.json.org/json-en.html
//

namespace NCUtils::Utility::JSON {

	struct Value{
		enum class TypeID{
			Object,
			Array,
			String,
			Number,
			True,
			False,
			Null
		};
		constexpr virtual TypeID type_id() const = 0;
		virtual ~Value(){};
	};

	struct Element;

	class Object : public Value{
		std::map<std::string, Element> val;
	public:
		template<class... Args>
		Object(Args&&... args) : val(args...){}
		constexpr TypeID type_id() const { return TypeID::Object; };
		operator const std::map<std::string, Element> &() const { return val; }
		operator std::map<std::string, Element> &() { return val; }

		const std::map<std::string, Element> &value() const { return val; }
		std::map<std::string, Element> &value() { return val; }
	};

	class Array : public Value{
		std::vector<Element> val;
	public:
		template<class... Args>
		Array(Args&&... args) : val(args...){}
		Array(const Element &elem) : 
			val(elem.type_id() == Value::TypeID::Array ? elem.as<Array>.value() : elem)
		{}
		constexpr TypeID type_id() const { return TypeID::Array; };
		operator const std::vector<Element> &() const { return val; }
		operator std::vector<Element> &() { return val; }

		const std::vector<Element> &value() const { return val; }
		std::vector<Element> &value() { return val; }
	};

	std::ostream &operator<<(std::ostream &dest, const Array &A){
		dest << "[";
		dest << A.value()[0] << "\n";
		//for(const auto & a : A.value())
		//	dest << a << "\n";
		dest << "]";
		return dest;

	}

	class String : public Value{
		std::string val;
	public:
		template<class... Args>
		String(Args&&... args) : val(args...){}
		String(const String &s) : val(s.val){}
		constexpr TypeID type_id() const { return TypeID::String; };
		operator const std::string &() const { return val; }
		operator std::string &() { return val; }
		const std::string &value() const { return val; }
		std::string &value() { return val; }
	};

	std::ostream &operator<<(std::ostream &dest, const String &s){
		return dest << s.value();
	}

	class Number : public Value{
		double val;
	public:
		constexpr Number(double val = 0) : val(val){}
		constexpr TypeID type_id() const { return TypeID::Number; };
		constexpr operator double() const { return val; }
		constexpr operator double &() { return val; }
		constexpr double value() const { return val; }
		constexpr double &value() { return val; }
	};

	std::ostream &operator<<(std::ostream &dest, const Number &n){
		return dest << n.value();
	}

	class True : public Value{
	public:
		constexpr TypeID type_id() const { return TypeID::True; };
		constexpr operator bool() const { return true; }
		constexpr bool value() const { return true; }
	};

	std::ostream &operator<<(std::ostream &dest, const True &){
		return dest << "true";
	}

	class False : public Value{
	public:
		constexpr TypeID type_id() const { return TypeID::False; };
		constexpr operator bool() const { return false; }
		constexpr bool value() const { return false; }
	};

	std::ostream &operator<<(std::ostream &dest, const False &){
		return dest << "false";
	}

	class Null : public Value{
	public:
		constexpr TypeID type_id() const { return TypeID::Null; };
	};

	std::ostream &operator<<(std::ostream &dest, const Null &){
		return dest << "null";
	}

	struct Element{
		Value *p_v;
		Element(Value *p_v = nullptr) : p_v(p_v){}
		Element(const Element &e) : p_v(copy(e)){}
		~Element(){ delete p_v; }
		Element &operator=(const Element &e){
			delete p_v; p_v = copy(e);
			return *this;
		}

		template<class ObjectType, class... Args>
		static Value *create(Args&&... args){ return new ObjectType(args...);}

		operator Value*() {return p_v;}
		operator const Value*() const {return p_v;}

		constexpr Value::TypeID type_id() const { return p_v->type_id(); };
		template<class ObjectType>
		ObjectType &as(){return *dynamic_cast<ObjectType*>(p_v); }
		template<class ObjectType>
		const ObjectType &as() const {return *dynamic_cast<ObjectType*>(p_v); }

	private:
		Value* copy(const Element &e){
			switch(e.type_id()){
			case Value::TypeID::Object:
				return create<Object>(e.as<Object>().value());
			case Value::TypeID::Array:
				return create<Array>(e.as<Array>().value());
			case Value::TypeID::String:
				return create<String>(e.as<String>().value());
			case Value::TypeID::Number:
				return create<Number>(e.as<Number>().value());
			case Value::TypeID::True:
				return create<True>();
			case Value::TypeID::False:
				return create<False>();
			case Value::TypeID::Null:
				return create<Null>();
			}
			return nullptr;
		}
	};

	std::ostream &operator<<(std::ostream &dest, const Element &e){
		
			switch(e.type_id()){
			case Value::TypeID::Object:
				//return dest << e.as<Object>().value();
				return dest;
			case Value::TypeID::Array:
				return dest << e.as<Array>();
			case Value::TypeID::String:
				return dest << e.as<String>();
			case Value::TypeID::Number:
				return dest << e.as<Number>();
			case Value::TypeID::True:
				return dest << e.as<True>();
			case Value::TypeID::False:
				return dest << e.as<False>();
			case Value::TypeID::Null:
				return dest << e.as<Null>();
			}
			
		return dest;	
	}

	template<class charT>
	class Parser{
	public:
		constexpr static std::optional<size_t> value(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin; 
			index += whitespace(input, index).value();
			if(auto ret = string(input, index); ret){index += ret.value(); }
			else if(auto ret = number(input, index); ret){index += ret.value(); }
			else if(auto ret = array(input, index); ret){index += ret.value(); }
			else if(auto ret = object(input, index); ret){index += ret.value(); }
			else if(auto ret = keyword("true", input, index); ret){index += ret.value(); }
			else if(auto ret = keyword("false", input, index); ret){index += ret.value(); }
			else if(auto ret = keyword("null", input, index); ret){index += ret.value(); }
			else return std::nullopt;
			index += whitespace(input, index).value();
			return index - begin;
		}
		static constexpr std::optional<size_t> object(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin; 
			if(index < input.size() && input[index] == '{') ++index;
			if(auto len = whitespace(input, index).value(); index + len < input.size() && input[index] == '}') return index - begin;
			while(1){
				index += whitespace(input, index).value();
				if(auto ret = string(input, index); !ret) return std::nullopt;
				else index += ret.value();
				index += whitespace(input, index).value();
				if(index < input.size() && input[index] == ':') ++index;
				if(auto ret = value(input, index); ret){
					index += ret.value();
					if(index < input.size()){
						if(input[index] == '}') return ++index - begin;
						if(input[index] != ',') return std::nullopt;
						else ++index;
					}
				}else return std::nullopt;
			}
		}
		static constexpr std::optional<size_t> array(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin; 
			if(index < input.size() && input[index] == '[') ++index;
			else return std::nullopt;
			
			if(auto len = whitespace(input, index).value(); index + len < input.size() && input[index + len] == ']') return ++index + len - begin;
			else while(1)
				if(auto ret = value(input, index); ret){
				 	index += ret.value();
					if(index < input.size()){
						if(input[index] == ',') ++index;
						else if (input[index] == ']') return ++index - begin;
					}
					else break;
				}else break;
			return std::nullopt;
		}
		static constexpr std::optional<size_t> string(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin;
			if (input.size() <= index)
				return std::nullopt;
			if (input[index] != '"')
				return std::nullopt;
			++index;
			for (; index < input.size(); ++index)
				if (input[index] == '"')
					return ++index - begin;
			return std::nullopt;
		}
		static constexpr std::optional<size_t> hex_digit(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin;
			if (index < input.size()) {
				if (('0' <= input[index] && input[index] <= '9')
						|| ('a' <= input[index] && input[index] <= 'f')
						|| ('A' <= input[index] && input[index] <= 'F'))
					return 1;
				else
					return std::nullopt;
			}
			return std::nullopt;
		}
		static constexpr std::optional<size_t> escape(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin;
			if (input.size() <= index)
				return std::nullopt;
			if (input[index] != "\\")
				return std::nullopt;
			++index;
			if (input.size() <= index)
				return std::nullopt;
			switch (input[index]) {
			case '\"':
			case '\\':
			case '/':
			case '\b':
			case '\f':
			case '\n':
			case '\r':
			case '\t':
				++index;
				return index - begin;
			case 'u':
				++index;
				if (input.size() - 4 <= index)
					return std::nullopt;
				for (size_t i = 0; i < 4; ++i) {
					++index;
					if (!hex_digit(input, index))
						return std::nullopt;
				}
			}
		}
		static constexpr std::optional<size_t> one_nine(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin;
			if (index < input.size()) {
				if ('1' <= input[index] && input[index] <= '9')
					return 1;
				else
					return std::nullopt;
			}
			return std::nullopt;
		}
		static constexpr std::optional<size_t> digit(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin;
			while (index < input.size())
				if ('0' <= input[index] && input[index] <= '9')
					index++;
				else if (index > begin)
					return index - begin;
				else
					return std::nullopt;
			return std::nullopt;
		}
		static constexpr std::optional<size_t> number(const std::basic_string<charT>& input, size_t begin) {
			//std::cerr << "enter number\n";
			size_t index = begin;
			if (input.size() <= index)
				return std::nullopt;
			if (input[index] == '-')
				++index;

			if (input.size() <= index)
				return index - begin;
			if (input[index] == '0')
				++index;
			else if (one_nine(input, index)) {
				++index;
				if (auto ret = digit(input, index); ret)
					index += ret.value();
			} else
				return std::nullopt;
			if (input.size() <= index)
				return index - begin;
			if (input[index] == '.') {
				++index;
				if (auto ret = digit(input, index); ret)
					index += ret.value();
			}
			if (input.size() <= index)
				return index - begin;
			if (auto c = input[index]; c == 'E' || c == 'e') {
				++index;
				if (input.size() <= index)
					return index - begin;
				if (auto c = input[index]; c == '+' || c == '-')
					++index;
				if (auto ret = digit(input, index); ret)
					index += ret.value();
				else
					return std::nullopt;
			}
			return index - begin;
		}
		static constexpr std::optional<size_t> whitespace(const std::basic_string<charT>& input, size_t begin) {
			size_t index = begin;
			while (index < input.size())
				switch (input[index]) {
				case ' ':
				case '\n':
				case '\r':
				case '\t':
					++index;
					continue;
				default:
					return index - begin;
				}
			return index - begin;
		}
		static constexpr std::optional<size_t> keyword(const std::string &keyword, const std::basic_string<charT>& input, size_t begin) {
			if(auto len = keyword.size(); begin + len < input.size() && input.substr(begin, len) == keyword)
				return len;
			else
				return std::nullopt;
		}
	};
} // namespace NCUtils::Utility::JSON
