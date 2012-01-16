#include <boost/regex.hpp>
#include <boost/format.hpp>
#include "julius_client.hpp"

/* ------------------------------------------------------------------------- */
//  引数からエンドポイントを作成
/* ------------------------------------------------------------------------- */
JuliusClient::JuliusClient(const std::string& ip, const int port)
	: ep_(boost::asio::ip::address::from_string(ip), port)
{
}

/* ------------------------------------------------------------------------- */
//  Julius へ接続して Interpreter に音声認識結果を渡す（ループ）
/* ------------------------------------------------------------------------- */
void JuliusClient::connect(Interpreter& ip, iRemoconClient& ir)
{
	using namespace std;

	// Julius へ接続
	boost::asio::ip::tcp::iostream s(ep_);

	// Julius サーバ 起動
	s << "STATUS\n" << std::flush;

	// 応答を解析する正規表現
	boost::regex r("WORD=\"([^\"]+)\"");
	boost::smatch m;

	// Julius からの応答を解析して dest.construes へ送信
	string line, sentence;
	while (getline(s, line)) {
		if (boost::regex_search(line, m, r))
			sentence += m.str(1);
		else if (line.find("<RECOGOUT>") != string::npos)
			sentence = "";
		else if (line.find("</RECOGOUT>") != string::npos) {
			cout << boost::format("認識結果: %1%\n") % sentence;
			// 音声認識結果に該当する IR 番号を調べて送信
			auto ir_num = ip.interpret(sentence);
			if (ir_num) {
				ir.ir_send(ir_num.get());
			}
		}
	}
}

