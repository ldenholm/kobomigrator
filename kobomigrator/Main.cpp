#include <iostream>
#include <filesystem>


struct File {
	std::filesystem::path filepath;
	std::string filename;
	std::filesystem::file_time_type last;
};

int main() {
	std::cout << "hello";
	std::filesystem::path filepath;
	filepath = 
}