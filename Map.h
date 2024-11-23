	#pragma once

	#include <iostream>
	#include <string>
	#include <windows.h>
	#include <fstream>
	#include <locale>
	#include <thread>
	#include <chrono>
	using namespace std;

	class Map {
	private:
		int row;
		int col;

	public:
		void ResizeConsole(int row, int col); //cm
		void DisplayMap1();
	};
