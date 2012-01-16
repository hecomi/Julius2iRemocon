#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/regex.hpp>
#include "interpreter.hpp"

/* ------------------------------------------------------------------------- */
//  Constructor
/* ------------------------------------------------------------------------- */
Interpreter::Interpreter()
{
}

/* ------------------------------------------------------------------------- */
//  認識させる文章と対応して送信する IR の番号を書いた
//  XML を読み込んでマップに格納
/* ------------------------------------------------------------------------- */
bool Interpreter::learn_commands_from_xml(const std::string& file_name)
{
	using namespace boost::property_tree;

	ptree root;
	read_xml(file_name, root);

	for (const auto& pt : root.get_child("iRemocon")) {
		auto word = pt.second.get_optional<std::string>("<xmlattr>.word");
		auto num  = pt.second.get_optional<int>("<xmlattr>.num");
		if (!word || !num) return false;

		str_ir_map_.insert( std::make_pair(word.get(), num.get()) );
	}

	return true;
}

/* ------------------------------------------------------------------------- */
//  文章を引数にとって予め登録した言葉に合致するか調べる
//  合致した場合は送出する IR 信号の番号を返す
/* ------------------------------------------------------------------------- */
boost::optional<int> Interpreter::interpret(const std::string& sentence)
{
	using namespace std;

	for (const auto& str_ir : str_ir_map_) {
		std::string regex_str = str_ir.first;
		int ir_num            = str_ir.second;

		boost::regex r(regex_str);
		boost::smatch m;

		if ( boost::regex_search(sentence, m, r) ) {
			return ir_num;
		}
	}

	return boost::optional<int>();
}
