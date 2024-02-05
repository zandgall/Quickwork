#pragma once
#ifndef QUICKWORK_UI_H
#define QUICKWORK_UI_H
#include <glm/glm.hpp>
#include <string>
#include <map>
namespace qwui {
	enum Anchor {
		left = 1, middle = 2, right = 4,
		top = 8, center = 16, bottom = 32
	};

	struct frame {
		glm::vec2 offset, size;
	};

	class component {
	protected:
		glm::vec2 relative_pos;
		int anchor, screen_anchor;
	public:
		component(): relativePos(0,0), anchor(left|top), screen_anchor(left|top) {}
		virtual glm::vec2 getPos(const frame* screen); // Returns position on screen

		virtual void tick() = 0;
		virtual glm::vec2 getSize(const frame* screen) const = 0; // Returns size of element
		virtual void render(const frame* screen = nullptr) = 0;

		virtual glm::vec4 getScreenRect(const frame* screen) {return glm::vec4(getPos(screen), getSize(screen));} // Returns the position and size of the element on screen
		virtual glm::vec2 getRelativePos() {return relative_pos;} // Returns pos relative to the anchors
		virtual void setRelativePos(float x, float y) {this->relative_pos = glm::vec2(x, y);}
		virtual void setAnchor(int a) {anchor = a;} // Sets the anchor for the element. If it were, say, centered, then getPos will offset by half 
		virtual void setScreenAnchor(int a) {screen_anchor = a;}
	};

	class text : public component {
	public:
		std::string content, font;
		float font_size;

		text(std::string content, std::string font, float font_size): content(content), font(font), font_size(font_size) {}

		void tick() {}

		glm::vec2 getSize(const frame* screen) const;
		void render(const frame* screen = nullptr);
	};

	class interface {
		frame frame;
		int top_left_anchor, bottom_right_anchor;
		glm::vec2 top_left_pos, bottom_right_pos;
	public:
		std::map<std::string, component*> components = std::map<std::string, component*>();
		void tick();
		void render();
		void setAnchor(int a) {anchor = a;}
		void setScreenAnchor(int a) {screen_anchor = a;}
	}
}
#endif