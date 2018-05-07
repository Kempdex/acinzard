#include "logger.h"

using namespace core;
uint32_t logger::call_counter = 0;

void core::logger::break_recursion()
{
	std::cout << "\n";
    call_counter = 0;
}

logger::logger()
{
	//No imp
}

void core::logger::debug()
{
	break_recursion();
}

void core::logger::info()
{
	break_recursion();
}

void core::logger::warning()
{
	break_recursion();
}

void core::logger::error()
{
	break_recursion();
}
