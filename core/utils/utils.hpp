#pragma once
#include <iostream>

namespace utils {
	template <typename t>
	t get_vfunc(void* class_pointer, size_t index) {
		return (*(t**)class_pointer)[index];
	}

	static void log(const char* msg) {
		std::cout << msg << std::endl;
	}
}