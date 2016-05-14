#include "Validator.h"



CValidator::CValidator()
{
	for (const auto & it : m_brackets)
	{
		m_bracketsMap[it.first] = { it.second, it.comment };
	}

	sort(m_brackets.begin(), m_brackets.end(), [=](const SLiteral & first, const SLiteral & second)
	{
		return first.first.size() > second.first.size();
	});
}


CValidator::~CValidator()
{
}

bool CValidator::ProcessCode(const string & code)
{
	stringstream strCode(code);
	string line;
	vector<string> bracketStack;

	while (getline(strCode, line))
	{
		//position, bracket, isComment
		list<pair<size_t, pair<string, bool>>> bracketLine;
		
		for (const auto & bracket : m_brackets)
		{
			bracketLine.clear();

			if (size_t position = line.find(bracket.first) != string::npos)
			{
				bracketLine.push_back({ position, { bracket.first, true } });
			}
			if (size_t position = line.find(bracket.second) != string::npos)
			{
				bracketLine.push_back({ position, { bracket.second, false } });
			}

			bracketLine.sort([&bracketLine](const pair<size_t, pair<string, bool>> & first, const pair<size_t, pair<string, bool>> & second)
			{
				return (first.first > second.first);
			});

			for (const auto & it : bracketLine)
			{
				if (bracketStack.empty())
				{
					if (it.second.second)
					{
						bracketStack.push_back(it.second.first);
					}
					else
					{
						return false;
					}
				}
				else if (!bracketStack.empty() && !m_bracketsMap[bracketStack[bracketStack.size() - 1]].second)//Если последняя скобка не многострочная
				{
					if (it.second.second)//Если скобка открывающая
					{
						bracketStack.push_back(it.second.first);
					}
					else if (!bracketStack.empty() && m_bracketsMap[bracketStack[bracketStack.size() - 1]].first == it.second.first)//Если скобка закрывающая и предыдущая скобка антоним
					{
						bracketStack.pop_back();
					}
					else
					{
						return false;
					}
				}/*
				else if (!bracketStack.empty() && bracketsMap[bracketStack[bracketStack.size() - 1]].first == it.second.first)
				{
					bracketStack.pop_back();
				}*/
			
			}
		}
	}

	return bracketStack.empty();
}
