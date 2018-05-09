#pragma once
#include <ecs/component/component.h>
#include <vector>
#include <memory>
#include <bitset>
#include <array>

#include <util/logger.h>

#define MAX_COMPONENTS 64



namespace acinzard {

	class entity
	{
		std::vector<std::unique_ptr<component>> components;
		
		std::bitset<MAX_COMPONENTS> components_bit_set;
		std::array<component*, MAX_COMPONENTS> components_array;

		bool active;
	public:
		entity() {}
		~entity() {}

		bool is_active() const{
			return active;
		}

		void destroy() {
			this->active = false;
		}

		void update() {
			//Не нравится мне эта конструкция
			//Но она работает
			//TODO: Переделать цикл перебора компонентов в классе entity
			for (auto item = components.begin(); item != components.end(); item++) {
				(*item)->update();
			}
		}

		template<typename T, typename... TArgs>
		T& add_component(TArgs&&... mArgs) {
			T* _component(new T(std::forward<TArgs>(mArgs)...));
			std::unique_ptr<component> u_component_ptr{ _component };
			components.emplace_back(std::move(u_component_ptr));

			components_array[get_component_type_id<T>()] = _component;
			components_bit_set[get_component_type_id<T>()] = true;
			
			return *_component;
		}

		template<typename T>
		T& get_component() const {
			auto ptr(components_array[get_component_type_id<T>()]);
			return *static_cast<T*>(ptr);
		}

		template <typename T>
		bool has_component() const {
			return this->components_bit_set[get_component_type_id<T>()];
		}
	};
}
//Acinzard