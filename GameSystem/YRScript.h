#include <string>
#include <regex>
#include <vector>


//basic reflection https://github.com/preshing/FlexibleReflection/blob/part1/Main.cpp
//must implemente a scirpt language!
enum class TokenType
{
	NONE,
	ID,
	STR,
	INT,
	REAL,
	OP,
	ENDL,
	ENDF,
};

class YRSToken
{
	union ParsedData
	{
		float real;
		int integer;
	} _pdata;
	std::wstring _text = L"";
	TokenType _type = TokenType::NONE;
public:
	TokenType get_type() const { return _type; }
	const std::wstring& get_text() const { return _text; }
	const std::wstring& get_str() const { return _text; }
	int get_integer() const { return _pdata.integer; }
	float get_real() const { return _pdata.real; }
	YRSToken(const std::wstring& data, const TokenType& type) :_text(data), _type(type) {}
	YRSToken() = default;
	virtual ~YRSToken() {}
	YRSToken(YRSToken const&) = delete;
	YRSToken& operator=(YRSToken const&) = delete;
};

class YRSParser
{
	std::wstring _content = L"";
	int _line = 0;
	std::vector<YRSToken*> tokens;
public:

	YRSParser(int line_num):_line(line_num) {}
	void parse()
	{
		
	}
	virtual ~YRSParser() {}
	YRSParser(YRSParser const&) = delete;
	YRSParser& operator=(YRSParser const&) = delete;
};