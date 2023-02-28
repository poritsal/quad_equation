#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include "quad.h"

void safe_open(std::ifstream& file)
{
	file.open("file.txt");
	if (!file.is_open())
	{
		std::cout << "file open error";
		exit(1);
	}
}

void safe_out(std::ofstream& file)
{
	file.open("output.txt", std::ofstream::app);
	if (!file.is_open())
	{
		std::cout << "file open error";
		exit(1);
	}
}

std::vector <double> parser(std::ifstream& file)
{
	safe_open(file);
	std::vector <double> a;
	std::string s;
	while (!file.eof())
	{
		s = "";
		file >> s;
		if (s != "")
		{
			a.push_back(std::atof(s.c_str()));
		}
	}
	file.close();
	return a;
}

void quad_out(int r, double a, double b, double c)
{
	std::ofstream file;
	safe_out(file);
	if (r == 3)
	{
		file << "the equation has infinitely many roots\n";
	}
	else if (r == 0)
	{
		file << "the equation has no real roots\n";
	}
	else if (r == 4)
	{
		file << "the equation has one real root: " << (-c) / (b) << '\n';
	}
	else if (r == 5)
	{
		file << "the equation has one real root: " << (-b) / (2 * a) << '\n';
	}
	else if (r == 2)
	{
		file << "the equation has two real roots: ";
		if ((-b - sqrt(b * b - 4 * a * c)) / (2 * a) > (-b + sqrt(b * b - 4 * a * c)) / (2 * a))
		{
			file << (-b + sqrt(b * b - 4 * a * c)) / (2 * a) << ' ' << (-b - sqrt(b * b - 4 * a * c)) / (2 * a) << '\n';
		}
		else
		{
			file << (-b - sqrt(b * b - 4 * a * c)) / (2 * a) << ' ' << (-b + sqrt(b * b - 4 * a * c)) / (2 * a) << '\n';
		}
	}
	file.close();
}

void quad_sol(std::ifstream& file)
{
	std::vector <double> coef = parser(file);
	if (coef.size() % 3 != 0)
	{
		std::cout << "Input Error"; // or in file?
		exit(2);
	}

	for (int i = 0; i < coef.size(); i = i + 3)
	{
		double a = coef[i], b = coef[i + 1], c = coef[i + 2], d = b * b - 4 * a * c;

		if (a == 0 && b == 0 && c == 0)
		{
			quad_out(3, a, b, c);
		}
		else if (a == 0 && b == 0 && c != 0)
		{
			quad_out(0, a, b, c);
		}
		else if (a == 0 && b != 0)
		{
			quad_out(4, a, b, c);
		}
		else if (d < 0)
		{
			quad_out(0, a, b, c);
		}
		else if (d == 0)
		{
			quad_out(5, a, b, c);
		}
		else if (d > 0)
		{
			quad_out(2, a, b, c);
		}
	}
}
