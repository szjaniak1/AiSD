#include <iostream>
#include <random>
#include <vector>
#include <bits/stdc++.h>

void getNumbers(const int size)
{
	std::random_device rd;
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::uniform_int_distribution<int> range(0, 2 * size - 1);
	std::mt19937 mt{ ss };
	
	std::vector<int> numbers;
	numbers.reserve(2 * size - 1);
	
	for (int i = 0; i < size; i++)
	{
		numbers.push_back( range(mt) );
	}
	
	std::sort(numbers.rbegin(), numbers.rend());

	for (int num : numbers)
	{
		std::cout << num << " ";
	}
}

int main(int argc, char *argv[])
{
	const int size = atoi(argv[1]);
	std::cout << size << " ";
	getNumbers(size);

	return 0;
}
