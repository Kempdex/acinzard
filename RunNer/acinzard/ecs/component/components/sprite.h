#pragma once
#include <renderer/texture.h>
#include <renderer/shader.h>
#include <ecs/component/component.h>

namespace acinzard {
	class sprite : public component
	{
		core::shader* _shader;
		core::texture* _texture;
	public:
		
		sprite();
		~sprite();
	};
}
