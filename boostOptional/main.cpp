
#include <iostream>
#include <string>
#include <boost/optional.hpp>

using namespace boost;

class Address
{
public:
	Address(std::string const & streetName ):
		m_streetName(streetName){}

	std::string m_streetName;

};



class Person
{
public:
	Person(const std::string & firstName, const std::string & lastName):
			m_firstName(firstName), m_lastName(lastName) {}
	std::string m_firstName;
	std::string m_lastName;
	boost::optional<std::string> m_middleName;
	boost::optional<Address> m_address;
};




int main(int argc, char * argv[])
{
	Person p{"John", "Watson"};
	
	std::cout << (p.m_middleName ? *p.m_middleName : "No middle Name" ) << std::endl;
	

	p.m_middleName = "Hamish";
	p.m_middleName = "The Gambler";
std::cout << (p.m_middleName ? *p.m_middleName : "No middle Name" ) << std::endl;

	p.m_address = Address { "Boulder"} ;
	
	if(p.m_address)
	{
		std::cout << p.m_address -> m_streetName << std::endl;
	}	


	return 0;
}

