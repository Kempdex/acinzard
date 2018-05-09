#pragma once
#include <renderer/texture.h>
#include <renderer/shader.h>
#include <ecs/component/component.h>
#include <ecs/component/components/transform.h>
#include <renderer/renderer.h>

#include <util/logger.h>

namespace acinzard {
	class sprite : public component
	{
		transform* _transform;
		core::shader* _shader;
		core::texture* _texture;
		core::renderer* _renderer;
	public:
		sprite();
		~sprite();

		void set_transform_component(transform* tr);
		void set_shader(core::shader* sh);
		void set_texture(core::texture* tx);
		void set_renderer(core::renderer* rnd);

		void update() override;
		void draw();
	};
}
