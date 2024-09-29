/*#include <iterator>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>


namespace fs = boost::filesystem;

void read_dir(int argc, char* argv[]) {
	fs::path p(argc > 1 ? argv : ".");
	std::vector<fs::directory_entry> v;

	if (is_directory(p)) {
		copy(fs::directory_iterator(p), fs::directory_iterator(), back_inserter(v));
		std::cout << p << " constains:\n";
		for (const auto& t : v) {
			std::cout << (t).path().string() << std::endl;
		}
	}
}



void create_dir() {
	const auto dirName = "testDir";
	fs::path pp{ dirName };

	try {
		if (create_directory(pp)) {
			rename(pp, dirName);
			//fs::remove(dirName);
		}
	}
	catch (fs::filesystem_error & e) {
		std::cerr << e.what() << '\n';
	}
}

void write_file() {
	fs::path fpath{ "test.txt" };
	fs::ofstream ofs{ fpath };
	for (int i = 0; i < 10; i++) {
		ofs << i << '\n';
	}
}

int main() {

	create_dir();
	write_file();

	return 0;
}*/