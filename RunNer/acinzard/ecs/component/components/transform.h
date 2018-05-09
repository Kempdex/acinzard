#pragma once
#include <ecs/component/component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace acinzard {
	class transform : public component
	{
		glm::mat4 model;
	public:
		transform();
		~transform();
		glm::mat4 get_model() const;
		void translate(glm::vec3 vec);
		void scale(glm::vec3 vec);
		void rotate(glm::vec3 vec, float angle);
	};
}