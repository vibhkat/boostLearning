#include <iostream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;




int main (int argc, char ** argv)
{
	//INSTEAD OF GETTING VALUE, WE DIRECTLY STORE IT
	int value;

	po::options_description desc("Program options");
	desc.add_options()
		("help,h", "print info")
		("filename,F", po::value<std::string>() -> default_value("default.txt"), "file to process")
		("value,v", po::value<int>(&value) -> default_value(42))
		("files,f", po::value<std::vector<std::string>>() -> multitoken(), "input files");

	po::variables_map vm;
	//parse the command line 	
	auto parsed = po::parse_command_line(argc, argv, desc);

	//store the data in variable map
	po::store(parsed, vm);
	
	po::notify(vm);
	
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}

	std::string filename = vm["filename"].as<std::string>();
	
	if(vm.count("files"))
	{
		int i = 0;
		auto files = vm["files"].as<std::vector<std::string>>();
		for( auto s : files)
		{
			std::cout << ++i << ":" << s << std::endl;
		}
	}


	std::cout << "Processing filename : " << filename << std::endl;
	std::cout << "The value is " << value << std::endl;
	std::cout << "Done " << std::endl;	
	return 0;
}
