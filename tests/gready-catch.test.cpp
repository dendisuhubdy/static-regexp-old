#include "regexp/regexp2.hpp"
#include <cstdio>

using namespace SRX;

bool testTrio(std::string input, std::string a, std::string b, std::string c)
{
	using SubRegexp = Sequence<OneCatch<1,Plus<Sel<Number,Chr<':'>>>>, Chr<':'>, OneCatch<2,Number>, Chr<':'>, OneCatch<3,Number>>;
	RegularExpression<Begin, SubRegexp, End> regexp;
	if (regexp(input))
	{
		if (std::string(input.c_str()+regexp.getCatch<1>()[0].begin, regexp.getCatch<1>()[0].length) == a)
		{
			if (std::string(input.c_str()+regexp.getCatch<2>()[0].begin, regexp.getCatch<2>()[0].length) == b)
			{
				if (std::string(input.c_str()+regexp.getCatch<3>()[0].begin, regexp.getCatch<3>()[0].length) == c)
				{
					return true;
				}
				else
				{
					fprintf(stderr,"3. group contains bad data '%.*s'!\n",regexp.getCatch<3>()[0].length,input.c_str()+regexp.getCatch<3>()[0].begin);
				}
			}
			else
			{
				fprintf(stderr,"2. group contains bad data '%.*s'!\n",regexp.getCatch<2>()[0].length,input.c_str()+regexp.getCatch<2>()[0].begin);
			}
		}
		else
		{
			fprintf(stderr,"1. group contains bad data '%.*s'!\n",regexp.getCatch<1>()[0].length,input.c_str()+regexp.getCatch<1>()[0].begin);
		}
	}
	else
	{
		fprintf(stderr,"Whole regexp not match!\n");
	}
	return false;
}

bool test1()
{
	if (!testTrio("1:2:3","1","2","3")) return false;
	if (!testTrio("111:2:3","111","2","3")) return false;
	if (!testTrio("1:1:2:3","1:1","2","3")) return false;
	
	return true;
}

int main ()
{
	if (test1()) return 0;
	return 1;
}