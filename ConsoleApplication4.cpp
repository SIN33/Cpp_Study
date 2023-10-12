// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CustomMemoryMng.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    CMemoryMgr mgr(sizeof(unsigned), 16, 4);
	std::vector<unsigned*> j;
	
	for (int i = 0; i < 104857600 / 10; i++)
	{
		unsigned* pi = reinterpret_cast<unsigned*> (mgr.Allocate());
		*pi = 1 + i;
		j.push_back(pi);
	}
	
	for(auto* i : j)
		mgr.Deallocate(i);
	
	
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
