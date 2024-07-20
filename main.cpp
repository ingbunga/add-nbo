#include <iostream>
#include <memory>
#include <cstdio>
#include <stdint.h>
#include <netinet/in.h>


uint32_t tryGetN(char* fileName) {
	auto fp = std::unique_ptr<FILE, decltype(&fclose)>(fopen(fileName, "rb"), &fclose);

	if (fp == NULL) {
		throw std::runtime_error(std::string(fileName) + " not found");	
	}

	fseek(fp.get(), 0, SEEK_END);
    	auto fileSize = ftell(fp.get());
    	fseek(fp.get(), 0, SEEK_SET);

    	if (fileSize < sizeof(uint32_t)) {
        	throw std::runtime_error(std::string(fileName) + " is too small");
    	}
	
	uint32_t y;	
	fread(&y, sizeof(uint32_t), 1, fp.get());
	return ntohl(y);

}


int main(int argc, char* argv[]) {
	if (argc != 3) {	
		std::cout << "Please give two arguments" << std::endl;
		return 1;
	}

	try {
		uint32_t n1 = tryGetN(argv[1]);
		uint32_t n2 = tryGetN(argv[2]);

		uint32_t y = n1 + n2;
		printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, y, y);

	}
	catch(std::runtime_error &err) {
		std::cout << err.what() << std::endl;
		return 1;
	}
	
	return 0;
}
