#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <chrono>

namespace fs = std::filesystem;
namespace ch = std::chrono;

struct File {
	fs::path filepath;
	fs::path filename;
	fs::file_time_type last;
};

int main() {
	auto start = ch::high_resolution_clock::now();

	fs::path fpath;
	fs::path migration_path;
	std::unordered_map<fs::path, File> file_map;
	fpath = "Resources/KobDemo"; // replace this with user input
	migration_path = "migration_dir";
	
	for (const auto& dirEntry : fs::recursive_directory_iterator(fpath))
	{
		// check if we have a candidate file
		if (dirEntry.is_regular_file() && 
			(dirEntry.path().extension() == ".mobi" 
			|| dirEntry.path().extension() == ".azw3"
			|| dirEntry.path().extension() == ".pdf"
			|| dirEntry.path().extension() == ".epub")) {
			// create stuct and add it to dir_map
			File f = {
				dirEntry.path().relative_path(),
				dirEntry.path().filename(),
				dirEntry.last_write_time()
			};

			file_map.insert({ dirEntry.path().relative_path(), f });
		}

		std::cout << file_map.size() << "size of dir map\n";
	}

	// Now we have the map constructed. Let's choose a copy zone and begin processing
	// each item in the map.

	 // Copy files into new directory in current dir
	if (fs::is_directory(migration_path)) {
		std::cout << "Migration directory already exists, please check and remove it." << std::endl;
		return -1;
	}
	
	fs::create_directory(migration_path);

	// process our map of files
	for (const auto& [k, v] : file_map) {
		std::error_code ec;
		fs::copy_file(v.filepath, migration_path/v.filename, ec);
		std::cout << ec.message() << std::endl;
	}

	auto finish = ch::high_resolution_clock::now();
	std::cout << "completed in " << ch::duration_cast<ch::seconds>(finish - start).count() << "seconds" << std::endl;
	return 0;
}