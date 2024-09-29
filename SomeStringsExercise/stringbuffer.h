#pragma once
#include <cstdlib>
#include <cstdint>
#include <string>

namespace ms {

	constexpr size_t maxstr = 1024;
	constexpr int maxindex = 15;

	static const char* errnum = "error";

	static const char* words[] = {
		"yellow", "elephant", "house", "flower", "never", "walking", "tricycle", "up", "vermouth", "lying", "beautiful", "sad", "mystery", "lullaby", "of", "running"
	};

	class sentence {
		char* buf = nullptr;
		int buflen = 0;
		void initbuf();
		void clearbuf();
		void appendbuf(const char* s);
	public:
		sentence();
		const char* makeSentence(const int arr[], const int &n);
	};
}