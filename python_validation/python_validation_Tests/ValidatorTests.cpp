#include "stdafx.h"
#include "../python_validation/Validator.h"

BOOST_AUTO_TEST_SUITE(Code_validation)
CValidator validator;
BOOST_AUTO_TEST_CASE(code)
{
	// TODO: use raw literals
	BOOST_CHECK(validator.ProcessCode("fn main():\n\tprint([1 + 12 * (2 + 1 / 3), 201, 0])\n\tstr = \"\"\"hello world{}}}}}\ncomment\"\"\""));
	BOOST_CHECK(!validator.ProcessCode("fn main():\n\tprint([1 + 12 * (2 + 1 / 3), 201, 0])\n\tstr = \"\"\"hello world{}}}}}\ncomment\"\"\"}"));
	BOOST_CHECK(validator.ProcessCode("print([1 + 12 * (2 + 1 / 3), 201, 0])"));
	BOOST_CHECK(!validator.ProcessCode("print([1 + 12 * (2 + 1 / 3}, 201, 0])"));
}
BOOST_AUTO_TEST_SUITE_END()