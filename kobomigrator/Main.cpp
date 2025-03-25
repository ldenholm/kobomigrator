#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <chrono>

namespace fs = std::filesystem;

struct File {
	fs::path filepath;
	fs::path filename;
	fs::file_time_type last;
};

int main() {
	fs::path fpath;
	std::unordered_map<fs::path, File> dir_map;
	fpath = "Resources/KobDemo";
	
	for (const auto& dirEntry : fs::recursive_directory_iterator(fpath))
	{
		// check if we have a file
		if (dirEntry.is_regular_file() && 
			(dirEntry.path().extension() == ".mobi" 
			|| dirEntry.path().extension() == ".azw3"
			|| dirEntry.path().extension() == ".pdf"
			|| dirEntry.path().extension() == ".epub")) {
			// create stuct and add it to dir_map
			//std::cout << dirEntry.path().stem() << "filename w/o extension" << std::endl;
			//std::cout << dirEntry.path().extension() << std::endl;
			//std::cout << dirEntry.path().filename() << "filename path component" << std::endl;
			//std::cout << dirEntry.path().relative_path() << "root path" << std::endl;
			File f = {
				dirEntry.path().relative_path(),
				dirEntry.path().filename(),
				dirEntry.last_write_time()
			};

			dir_map.insert({ dirEntry.path().relative_path(), f });
		}
		std::cout << dirEntry.is_regular_file() << std::endl;
		std::cout << dirEntry.path() << std::endl;

		std::cout << dir_map.size() << "size of dir map\n";
	}
}