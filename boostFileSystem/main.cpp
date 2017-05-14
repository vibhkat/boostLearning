#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

void check_path(const char* p)
{
	boost::filesystem::path myPath(p);
	
	if(exists(myPath))
	{
		if(is_regular_file(myPath))
		{       //replace extension will replace the extension of the file with the given one, if not given, it will remove it   
			std::cout << "path " << myPath.filename().replace_extension() << " is a regular file of size " << boost::filesystem::file_size(myPath) << std::endl; 
		}
		else if(is_directory(myPath))
		{
			std::cout << "path " << myPath.filename() << " is a directory " << std::endl;
			
		}
	}
	else 
	{
		std::cout << "path " << myPath << " does not exist" << std::endl;
	}
}

void check_file(boost::filesystem::path p)
{
	auto s = boost::filesystem::status(p);
	auto t = s.type();

	std::cout << "the type is " << t << std::endl;

	auto ps = s.permissions();
	if((ps & boost::filesystem::owner_write) != boost::filesystem::owner_write)
	{
		std::cout << "no permissions t o write " << std::endl;
	}
	
}


void dir_nav(boost::filesystem::path dir)
{
	using it = boost::filesystem::directory_iterator;
	it end;
	for(it i(dir); i != end; ++i)
	{
		auto p = i -> path();
		if(is_regular_file(p))
		{
			std::cout << p.filename() << std::endl;
		}
		else if(is_directory(p))
		{
			std::cout << "directory " << p.filename() << "==================================" << std::endl;
			dir_nav(p); 
		}
	}	
}

int main(int argc, char** argv)
{

	check_path("foo");
	check_path(argv[0]);
	
	// getting the parent directory
	auto dir = boost::filesystem::path(argv[0]).parent_path();	
	check_path(dir.string().c_str());

	// decompostition
	for(auto & child : dir)
	{
		std::cout << child << std::endl;
	}

	// catching filesystem exceptions
	try
	{
		boost::filesystem::path p("junk");
		std::cout << boost::filesystem::file_size(p) << std::endl;
	}
	catch(const boost::filesystem::filesystem_error & e)
	{
		std::cout << e.what() << std::endl; 
	}
	
	check_file(boost::filesystem::path(argv[0]));

	auto parent = boost::filesystem::path(argv[0]).parent_path().parent_path();

	dir_nav(parent);
	return 0;
}
