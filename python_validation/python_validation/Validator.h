#pragma once
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <sstream>
#include <list>
#include <utility>
#include <iterator>


using namespace std;

struct SLiteral
{
	string first;
	string second;
	bool comment;

	SLiteral(string first, string second, bool comment)
		: first(first), second(second), comment(comment)
	{
	}
};


class CValidator
{
public:
	CValidator();
	~CValidator();
	bool ProcessCode(const string & code);

private:
	// TODO: add # comments support
	// TODO: add 'tt' literals
	vector<SLiteral> m_brackets = {
		{ "\"", "\"", false },
		{ "{", "}", false },
		{ "(", ")", false },
		{ "[", "]", false },
		{ "\"\"\"", "\"\"\"", true },
		{ "'''", "'''", true }
	};

	map<string, pair<string, bool>> m_bracketsMap;
};

