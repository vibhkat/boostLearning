#include <iostream>
#include <vector>
#include <string>

#include <boost/any.hpp>


struct A 
{
	int n;
};

struct B
{
	std::string n;
};

int main(int argc, char **argv)
{
	boost::any w;
	boost::any x { 2.0 };
	std::vector<boost::any> y {42, "life"};
	boost::any z = std::string("test");
	
	if (!x.empty())
	{
		std::cout << x.type().name() << std::endl;
	}
	
	std::cout << boost::any_cast<int> (y[0]) << std::endl;

	try{
		int b = boost::any_cast<int>(y[1]);	
	}
	catch (boost::bad_any_cast const & e)
	{
		std::cout << "wrong type" << std::endl;
	}

	for(auto a : y)
	{	
		std::cout << "********" <<  a.type().name() << std::endl;
		int * value = boost::any_cast<int>(&a); 
		if(value) std::cout << *value << std::endl;	

		const char ** text = boost::any_cast<const char*>(&a);
		if(text) std::cout << *text << std::endl;
	}

	std::vector<boost::any> test;
	test.emplace_back(A{4});
	test.emplace_back(B{"Hello"});	
		
	for (auto const & i : test)
	{
		std::cout << "********" <<  i.type().name() << std::endl;
		auto * a =  boost::any_cast<B>(&i);
		if(a) std::cout << a -> n << std::endl;
	}

	return 0;
}














