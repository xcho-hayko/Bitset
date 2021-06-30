#include"My_Bitset.h"
#include<iostream>

int main() {
	My_bitset<12> obj = 25;

	std::cout << obj;
	std::cout << std::endl;
	 std::cout << obj.all() << std::endl;
	 std::cout << obj.any() << std::endl;
	 std::cout << obj.none() << std::endl;
	 obj.flip();
	 std::cout << obj ;
	 std::cout << std::endl;
	 std::cout << obj.count() << std::endl;
	 obj.set();
	 std::cout << obj;
	 std::cout << std::endl;
	 std::cout << obj.count() << std::endl;
	 obj.reset();
	 std::cout << obj;
	 std::cout << std::endl;
	 std::cout << obj.count() << std::endl;

}


