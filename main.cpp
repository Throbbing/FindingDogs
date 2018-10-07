#include "EditorApp.h"
#include "GameApp.h"
#include "GameSystem/YRScript.h"
#include <regex>
#include <fstream>
#include <unordered_map>
#include <vector>

class YRSMemNode
{
public:
	~YRSMemNode()
	{
		size = 0;
		delete[] data;
		data = 0;
	}
	YRSMemNode():YRSMemNode(4){}
	YRSMemNode(size_t size)
	{
		data = new unsigned char[size];
	}
	int size = -1;
	unsigned char* data = nullptr;
	YRSMemNode(const YRSMemNode&) = delete;
	YRSMemNode& operator=(const YRSMemNode&) = delete;
};

//std::unordered_map<std::string, YRSMemNode> global_env;
std::vector<YRSMemNode> function_stack;
std::unordered_map<std::string, int> string_id_map;

void term(int idx)
{

}

void parse(vector<YRSToken*>& le)
{

}

void interpret_directly(vector<YRSToken*>& le)
{

}

int main1()
{
	vector<YRSToken*> tokens;
	std::wifstream ifs("d:/test.yr",std::ios::in);
	std::wstring str((std::istreambuf_iterator<wchar_t>(ifs)),
		std::istreambuf_iterator<wchar_t>());
	ifs.close();
	//wstring str = L"\"lll\"==//fff\ndef fib(n) {\n    if n < 2 {\n        n\n    } else {\n        fib(n-1)+fib(n-2);\n    }\n}\nt = currentTime();//日你码码\"kkkkv达科为1.23|12\"\nfib 15\nprint\"iejfwiofj我出门11】！|@#——\" 12.3 1.2 -0.1 1+2\n\n";
	wsmatch result;
	wregex pattern(L"((//.*)|(\\s+)|-|([0-9]*\\.[0-9]+)|([1-9]\\d*|[0-9])|([A-Z_a-z][A-Z_a-z0-9]*)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")|==|<=|>=|&&|\\|\\||[\\\\*+\\-><()\"&.?!%,…:;/={}])?");

	wstring::const_iterator iterStart = str.begin();
	wstring::const_iterator iterEnd = str.end();
	wstring temp;

	

	while (regex_search(iterStart, iterEnd, result, pattern))
	{
		//0-comment|1-space|2-float|3-int|4-id|6-ref|other-operator
		int group = -1;
		for (int i = 2; i < result.size(); ++i)
		{
			wstring ll = result[i];
			if (ll != L"")
			{
				group = i - 2;
			}
		}
		temp = result[0];

		if (temp == L"")
			break;


		if (temp == L"\n" || temp[0] == L'\n')
		{
			tokens.push_back(new YRSToken(temp, TokenType::ENDL));
			iterStart = result[0].second;
			continue;
		}
		else if (temp != L" ")
			wcout << temp;
		wstring type_name = L"operator";
		switch (group)
		{
		case 0:
		{
			type_name = L"comment";

			break;
		}
		case 1:
		{
			type_name = L"space";

			break;
		}
		case 2:
		case 3:
		{
			type_name = group==2? L"float":L"integer";
			if (tokens.size() >= 1)
			{
				auto& s = tokens[tokens.size() - 1];
				if (s->get_type() == TokenType::OP&&s->get_str() == L"-")
				{
					if (tokens.size() >= 2)
					{
						auto& s1 = tokens[tokens.size() - 2];
						if (s1->get_type() != TokenType::INT && s1->get_type() != TokenType::REAL)
						{
							delete s;
							tokens.pop_back();
							temp = L"-" + temp;
						}
					}
					else
					{
						delete s;
						tokens.pop_back();
						temp = L"-" + temp;
					}
				}
			}
			tokens.push_back(new YRSToken(temp, group == 2?TokenType::REAL:TokenType::INT));
			
			break;
		}
		case 4:
		{
			type_name = L"id";
			tokens.push_back(new YRSToken(temp, TokenType::ID));
			
			break;
		}
		case 5:
		{
			type_name = L"|ref iner\n";
			break;
		}
		case 6:
		{
			type_name = L"|ref\n";
			tokens.push_back(new YRSToken(temp, TokenType::STR));

			break;
		}
		case -1:
		{
			tokens.push_back(new YRSToken(temp, TokenType::OP));
		}
		}
		wcout << type_name;
		iterStart = result[0].second;   //更新搜索起始位置,搜索剩下的字符串
	}

	std::ofstream ofs("d:/test_ans.txt", std::ios::out);
	for (auto i : tokens)
	{
		switch (i->get_type())
		{
		case TokenType::ENDL:ofs << "\\n\n";break;
		case TokenType::ID:ofs << "identity "; break;
		case TokenType::INT:ofs << "i "; break;
		case TokenType::REAL:ofs << "f "; break;
		case TokenType::STR:ofs << "string "; break;
		case TokenType::OP:ofs << "op "; break;
		default:
		{
			ofs << "unkown ";
			break;
		}
		}
	}
	ofs.close();
	return 0;
}

#if 1
//#define Editor
#ifdef Editor
MAKE_APP(FDGameEditor)
#else
MAKE_APP(FDGame)
#endif
#endif