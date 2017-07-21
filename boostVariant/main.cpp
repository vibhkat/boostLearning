#include <iostream>
#include <boost/variant.hpp>
#include <boost/variant/multivisitors.hpp>

struct A
{
	void process()
	{
		std::cout << "In A" << std::endl;
	}

	int get()
	{
		return 1;
	}

	auto send()
	{
		return i;
	}

	int i =10;

};


struct B
{
	void process()
	{
		std::cout << "In B" << std::endl;
	}

	std::string get()
	{
		return "Hello World";
	}

	auto send()
	{
		return i;
	}

	int i =100;

};

typedef boost::variant<int, std::string> type_t;
struct C
{

	struct output : public boost::static_visitor<type_t>
	{
		template<class T>
		auto operator()(T t) const
		{
			return t.get();
		}
		/*
		void operator()(A a) const { a.process();}
		void operator()(B b) const { b.process();}
		*/
	};

	//Constructors
	C(A a):op(a){}
	C(B b):op(b){}

	auto call()
	{
		return boost::apply_visitor(output{},op);
	}

	boost::variant<A,B> op;
};

void make(boost::variant<A,B> & temp)
{

	int input = 0;
	std::cin >> input;

	if(input ==1)
		temp = A{};
	else
		temp= B{};
}


auto makeNew()
{
	auto ptr = new boost::variant<A,B>(B{});

	return ptr;
}


int main()
{
	boost::variant<double, char, std::string> v;
	v = 3.14;
  std::cout << boost::get<double>(v) << '\n';
  v = 'A';
  std::cout << boost::get<char>(v) << '\n';
  v = "Boost";
  std::cout << boost::get<std::string>(v) << '\n';


  boost::variant<A,B> x {A()};
  boost::get<A>(x).process();

  C c(B{});
  std::cout << c.call() << std::endl;

  x=B{};

  int j = 9;
  std::cout << boost::apply_visitor([&](auto o)
  {
  	return o.send()+j;
  }
  	,x) << std::endl;

  boost::variant<A,B> c2 ;

  //make(c2); 

  auto point = makeNew();
	std::cout << boost::apply_visitor([&](auto o)
  {
  	return o.send()+j;
  }
  	,*point) << std::endl;




	return 0;
}
