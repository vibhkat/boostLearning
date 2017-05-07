#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include <boost/signals2.hpp>
#include <boost/smart_ptr.hpp>


template <typename T> struct average
{
	typedef T result_type;
	
	template<typename II> T operator()(II first, II last) const
	{
		if(first == last) return T();
		float sum = 0.0;
		int count = 0;
		while (first != last)
		{
			sum += *first++;
			count++;
		}
		return sum/count;
	}

};


int main(int argc, char **argv)
{
	boost::signals2::signal<float(float, float)> s;
	s.connect([](float a, float b) { return a+b; } );
	s.connect([](float a, float b) { return a*b; } );
	//Will return the vlaue of the last slot
	std::cout << *s(3,4) << std::endl;

	// Providing a handler to use the results from each slots
	boost::signals2::signal<float(float, float), average<float>> s1;
	s1.connect([](float a, float b) { return a+b; } );
	s1.connect([](float a, float b) { return a*b; } );
	
	std:: cout << s1(3,4) << std::endl;
	return 0;
}
