#pragma once
#include <ecs/component/component_type.h>
#include <stdint.h>
#include <cstdio>

namespace acinzard {
	class component
	{
	protected:

	public:
		component() {}
		
		virtual void update() {}
		virtual ~component() {}
	};


	inline uint32_t get_component_type_id() {
		static uint32_t last_id;
		return last_id++;
	}

	template<typename T>
	inline uint32_t get_component_type_id() noexcept {
		static uint32_t type_id = get_component_type_id();
		return type_id;
	}
}
