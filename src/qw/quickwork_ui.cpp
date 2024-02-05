#include "quickwork_ui.h"
#include "quickwork.h"
using namespace qwui;

glm::vec2 component::getPos(const frame* screen) {
	glm::vec2 offset = screen==nullptr ? glm::vec2(0) : screen->offset;
	glm::vec2 size = getSize(screen), screen_size = screen==nullptr ? glm::vec2(qw::width, qw::height) : screen->size;
	
	if(anchor & middle)
		offset.x -= size.x / 2;
	else if(anchor & right)
		offset.x -= size.x;
	if(anchor & center)
		offset.y -= size.y / 2;
	else if(anchor & bottom)
		offset.y -= size.y;

	if(screen_anchor & middle)
		offset.x += screen_size.x / 2;
	else if(screen_anchor & right)
		offset.x += screen_size.x;
	if(screen_anchor & center)
		offset.y += screen_size.y / 2;
	else if(screen_anchor & bottom)
		offset.y += screen_size.y;

	return getRelativePos()+offset;
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