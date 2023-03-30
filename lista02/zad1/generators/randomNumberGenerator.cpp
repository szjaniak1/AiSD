#include <iostream>
#include <random>
#include <math.h>

void getNumbers(const int amount)
{	
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };
	std::uniform_int_distribution<int> range{ 0, 2 * amount - 1 };

	for (int i = 0; i < amount; i++)
	{
		std::cout << range(mt) << " ";
	}
}

int main(int argc, char *argv[])
{
	const int amount = atoi(argv[1]);
	std::cout << amount << " ";
	getNumbers(amount);

	return 0;
}
