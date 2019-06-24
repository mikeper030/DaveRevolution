#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Controller.h"
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib , "sfml-audio-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib , "sfml-audio-d.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include "Exceptions.h"
int main()
 {
	try {
		Controller c;
		c.startGame();
	}
	catch (FileNotFoundException & fne)
	{
		std::cerr << fne.what();
		exit(-1);
	}
	catch (BadCastException& bce) {
		std::cerr << bce.what();
		exit(-1);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what();
	}
	catch (...)
	{
		std::cout << "Unknown Error" << std::endl;
	}
	return 0;
}