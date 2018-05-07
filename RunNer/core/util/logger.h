#pragma once
#include <iostream>
#include <stdint.h>

namespace core {
	class logger
	{
		static uint32_t call_counter;

		static void break_recursion();

		template <typename T>
		static void gen_message(const char* title, T msg);

		logger();
	public:

		template <typename T, typename... Args>
		static void debug(T first, Args... args);

		static void debug();

		template <typename T, typename... Args>
		static void info(T first, Args... args);

		static void info();

		template <typename T, typename... Args>
		static void warning(T first, Args... args);

		static void warning();

		template <typename T, typename... Args>
		static void error(T first, Args... args);

		static void error();

	};

	

	template<typename T>
	inline void logger::gen_message(const char * title, T msg)
	{
		if (call_counter == 0) {
			std::cout << title << " ";
		}

		std::cout << msg << " ";
	}

	template<typename T, typename ...Args>
	inline void logger::debug(T first, Args ...args)
	{
		gen_message("[DEBUG]", first);
		call_counter++;
		debug(args...);
	}
	template<typename T, typename ...Args>
	inline void logger::info(T first, Args ...args)
	{
		gen_message("[INFO]", first);
		call_counter++;
		info(args...);
	}
	template<typename T, typename ...Args>
	inline void logger::warning(T first, Args ...args)
	{
		gen_message("[WARNING]", first);
		call_counter++;
		info(args...);
	}
	template<typename T, typename ...Args>
	inline void logger::error(T first, Args ...args)
	{
		gen_message("[ERROR]", first);
		call_counter++;
		error(args...);
	}
}
