#include <iostream>
#include <string>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>



void token_demo()
{
	std::string s = "To be, or not to be?";
	//Using default separator
	boost::tokenizer<> t(s);
	
	for(auto const & part : t)
	{
		std::cout << "<"<<part << ">" << std::endl;
	}
	
	//Separate by 'o' and keep spaces and keep empty tokens

	std::cout << "------------------------------------------" << std::endl;
	boost::char_separator<char> sep("o", " ", boost::keep_empty_tokens);
	
	boost::tokenizer<boost::char_separator<char>> t1(s, sep);
    
        for(auto const & part : t1)
        {
                std::cout << "<"<<part << ">" << std::endl;
        }   

        std::cout << "------------------------------------------" << std::endl;

	int offsets[] = {1,2,3};
	boost::offset_separator os(offsets, offsets + 3);
	auto start = boost::make_token_iterator<std::string>(s.begin(), s.end(),os);
	auto end = boost::make_token_iterator<std::string>(s.end(), s.end(), os);
	for (; start != end; ++start)
	{
		std::cout << "<" << *start << ">" << std::endl;
	}
	
}


void lc_demo()
{
	std::string s = "2.1";
	double d = boost::lexical_cast<double>(s);
	
	std::string ss = "12345";
	int n = boost::lexical_cast<int>(ss);
		
	std::cout << d << " : " << n << std::endl;

	try{
		boost::lexical_cast<int>("abcde");
	}
	catch(const boost::bad_lexical_cast & e)
	{
		std::cout << e.what() << std::endl;
	}

}


void algo_demo()
{
	std::string test = "hello  world\r\n";
	//Does not remove the spaces
	boost::algorithm::trim(test);
	std::cout << "<" << test <<">" << std::endl;

	std::string test1 = "hello  world\r\n";
        //Removes double space and replace by single space
	boost::algorithm::trim_all(test1);
        std::cout << "<" << test1 <<">" << std::endl;

}





int main(int argc , char **argv)
{
	token_demo();
	lc_demo();
	algo_demo();
	return 0;
}
