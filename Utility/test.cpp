#include <iostream>
#include <Utility/JSON.hpp>

int main(){
	using namespace std;
	using namespace NCUtils::Utility::JSON;
	string tmp;
	getline(cin, tmp, (char)char_traits<char>::eof());
	cout << tmp << endl;
	Parser<char> parser;
	auto ret = parser.array(tmp, 0);
	/*if(!ret)
		cout << "error\n";
	else{
		size_t pos = ret.value();
		cout << pos << "\n";
		//cout << tmp.substr(0, pos) << "\n";
		//cout << stof(tmp.substr(0, pos)) << "\n";
		//cout << tmp.substr(pos) << "\n";
	}*/
	Element e0 = Element::create<True>();
	Element e1 = Element::create<Number>(3.14);
	Element e2 = Element::create<String>("test message");
	Element e3 = Element::create<Array>();
	Element e4 = Element::create<Object>();
	e3.as<Array>().value().push_back(e0);
	e3.as<Array>().value().push_back(e1);
	e3.as<Array>().value().push_back(e2);
	
	for(const auto & v: e3.as<Array>().value()){
		cout << (int)v.type_id() << " " << v << "\n";
		e4.as<Object>().value()["key_type" + to_string((int)v.type_id())] = v;
	}
	e4.as<Object>().value()[to_string((int)e3.type_id())] = e3;
	for(const auto & [k, v] : e4.as<Object>().value())
		cout << k << "\n";
	return 0;
}
