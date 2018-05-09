#include "sprite.h"

using namespace acinzard;

sprite::sprite()
{
	_shader = NULL;
	_texture = NULL;
}

sprite::~sprite()
{
}

void sprite::set_transform_component(transform* tr)
{
	this->_transform = tr;
}

void sprite::set_shader(core::shader* sh)
{
	this->_shader = sh;
}

void sprite::set_texture(core::texture* tx)
{
	this->_texture = tx;
}

void sprite::set_renderer(core::renderer* rnd)
{
	this->_renderer = rnd;
}

void sprite::update()
{
	draw();
}

void sprite::draw()
{
	if (!_texture) {
		core::logger::error("Sprite component", "Texture not found");
	}
	if (!_transform) {
		core::logger::error("Sprite component", "Transform component not found");
	}
	if (!_shader) {
		core::logger::error("Sprite component", "Shader not found");
	}
	//TODO: Запихнуть рендерер в статическую переменную
	if (!_renderer) {
		core::logger::error("Sprite component", "Renderer not found");
	}

	//Вызываем рендерер, передаем текстуру, шейдер и матрицу модели
	_renderer->draw_object(_shader, _texture, _transform->get_model());
}
