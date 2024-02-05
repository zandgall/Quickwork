#include "quickwork_ui.h"
#include "quickwork.h"
using namespace qwui;

glm::vec2 anchor::getPos(const frame* screen) {
	glm::vec2 offset = screen==nullptr ? glm::vec2(0) : screen->offset;
	glm::vec2 screen_size = screen==nullptr ? glm::vec2(qw::width, qw::height) : screen->size;

	if(snapping & middle)
		offset.x += screen_size.x / 2;
	else if(snapping & right)
		offset.x += screen_size.x;
	if(snapping & center)
		offset.y += screen_size.y / 2;
	else if(snapping & bottom)
		offset.y += screen_size.y;

	return getRelativePos()+offset;
}

glm::vec2 component::getPos(const frame* screen) {
	glm::vec2 offset = anch.getPos(screen);
	glm::vec2 size = getSize(screen);
	
	if(alignment & middle)
		offset.x -= size.x / 2;
	else if(alignment & right)
		offset.x -= size.x;
	if(alignment & center)
		offset.y -= size.y / 2;
	else if(alignment & bottom)
		offset.y -= size.y;

	return offset;
}

glm::vec2 text::getSize(const frame* screen) const {
	glm::vec2 y_span = qw::measure_y_span(content, font, font_size);
	return glm::vec2(qw::measure(content, font, font_size), y_span.x + y_span.y);
}

void text::render(const frame* screen) {
	glm::vec2 y_span = qw::measure_y_span(content, font, font_size);
	glm::vec4 rect = getScreenRect(screen);
	qw::draw_string(content, font, font_size, rect.x, rect.y + y_span.x);
}

void interface::tick() {

}

void interface::render() {

}