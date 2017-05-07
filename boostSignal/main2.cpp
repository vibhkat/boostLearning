#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include <boost/signals2.hpp>
#include <boost/smart_ptr.hpp>

class Player
{
        int m_numberofGoals;
public:
        Player(std::string const & name):m_name(name)
	{
		 m_numberofGoals = 0;
	} 
    
        std::string m_name;
        //boost signal comes in
     

	typedef boost::signals2::signal<void(std::string, int)> SignalType;
	SignalType Scores;

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
	Coach coach;
	Player p("John");
	p.Scores.connect(
		boost::bind(&Coach::PlayerScored, &coach, _1));


	p.Score();
	p.Score();	

	//Deleting the object when going out of scope

	Player p1("Johny");
	{
		auto coach1 = boost::make_shared<Coach>();
		p1.Scores.connect(
			Player::SignalType::slot_type
			(&Coach::PlayerScored, coach1.get(), _1).track(coach1)
		);
		p1.Score();
	}
	p1.Score();
	return 0;
}

















