#include "object.h"

Object::Object(std::string fname){
	m_texture.loadFromFile(fname);
	m_sprite.setTexture(m_texture);
}

void Object::Draw(RenderWindow &window){
	window.draw(m_sprite);
}

bool Object::CollideWith(const Object &o) const{
	auto r1 = this->m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	return r1.intersects(r2);
	
}

//getGlobalBounds (te da un rectangulito que representa donde está tu sprite)
//intersects (metodo para ver si se intersectan los dos recangulitos)
