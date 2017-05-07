#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include <boost/signals2.hpp>

class Player
{
	int m_numberofGoals;
public:
	Player(std::string const & name):m_name(name){ m_numberofGoals = 0;}
	
	std::string m_name;
	//boost signal come in
	boost::signals2::signal<void()> m_scores;
	boost::signals2::signal<void(std::string)> m_Scores;
	boost::signals2::signal<void(std::string, int)> Scores;

	void Score()
	{
		m_numberofGoals++;
		Scores(m_name, m_numberofGoals);
	}
	
};

class Coach
{
public:
	void PlayerScored(std::string name)
	{
		std::cout << "well done " << name << std::endl;
	}
};


void third()
{
	std::cout << "Third " << std::endl;
}


int main(int argc, char **argv)
{
	Player p("John");

	//conenct a slot 
	p.m_scores.connect([](){
		std::cout << "Well Done " << std::endl;
	});

	p.m_scores();	
	

	auto c = p.m_Scores.connect([](std::string const & name){
		std::cout << "Well Done, " << name << std::endl;
	});
	

	p.m_Scores(p.m_name);
	p.m_Scores(p.m_name);
	
	//disconnect signal from slot, can use the first option or the second option too
	//c.disconnect();
	p.m_Scores.disconnect_all_slots();
	p.m_Scores(p.m_name);
	p.m_Scores(p.m_name);
	p.m_Scores(p.m_name);
	p.m_Scores(p.m_name);
	
	auto c1 = p.Scores.connect([](std::string name, int count){
		std::cout << "player " << name << "has scored " << count << " goals already " << std::endl; 
	});
	

	p.Score();
	p.Score();
	//Temporary blocking the slot
	{
		boost::signals2::shared_connection_block b(c1);
		p.Score();
		p.Score();	
	}

	p.Score();
	p.Score();
	
	boost::signals2::signal<void()> s;
	//Changing the order of slots by rpoviding the number when connecting
	s.connect(1, [](){ std::cout << "first" << std::endl ; });
	s.connect(0, [](){ std::cout << "second "<< std::endl ; });

	s();

	std::cout << "-----------------------------------------" << std::endl;
	//Applying the scoped connection
	boost::signals2::signal<void()> s1;

	s1.connect(third);
	{
		auto c2 = s1.connect(1, []() { std::cout << "First1 " << std::endl;});
		boost::signals2::scoped_connection sc (c2);
		s1.connect(0, [](){ std::cout << "Second1 " << std::endl;});
		s1();
	}
	std::cout << "===============" << std::endl;
	//Explicitly disconnecting the slot
	s1.disconnect(third);
	s1();

	Coach coach;
	Player player;




	return 0;
}

















