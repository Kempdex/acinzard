#include "transform.h"

using namespace acinzard;

transform::transform()
{
	model = glm::mat4(1.0f);
}

transform::~transform()
{
}

glm::mat4 transform::get_model() const
{
	return this->model;
}

void transform::translate(glm::vec3 vec)
{
	model = glm::translate(model, vec);
}

void transform::scale(glm::vec3 vec)
{
	model = glm::scale(model, vec);
}

void transform::rotate(glm::vec3 vec, float angle)
{
	model = glm::rotate(model, angle, vec);
}
