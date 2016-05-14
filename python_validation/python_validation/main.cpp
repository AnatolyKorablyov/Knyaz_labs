#include "Validator.h"

using namespace std;

void main()
{
	CValidator validator;

#if 1
	// TODO: use raw literals
	string code = "fn main():\n\tprint([1 + 12 * (2 + 1 / 3), 201, 0])\n\tstr = \"\"\"hello world{}}}}}\ncomment\"\"\"";//ok
#else
	string code;
	cin >> code;
#endif
	
	if (validator.ProcessCode(code))
	{
		cerr << "All is ok" << endl;
	}
	else
	{
		cerr << "Syntax error" << endl;
	}
}