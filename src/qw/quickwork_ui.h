#pragma once
#ifndef QUICKWORK_UI_H
#define QUICKWORK_UI_H
#include <glm/glm.hpp>
#include <string>
#include <map>
namespace qwui {
	enum snap {
		left = 1, center = 2, right = 4,
		top = 8, middle = 16, bottom = 32,

		topLeft = top|left, topCenter = top|center, bottomRight = top|right,
		middleLeft = middle|left, middleCenter = middle|center, middleRight = middle|right,
		bottomLeft = bottom|left, bottomCenter = bottom|center, bottomRight = bottom|right
	};

	struct frame {
		glm::vec2 offset, size;
	};

	class anchor {
	protected:
		glm::vec2 relative_pos;
		int snapping;
	public:
		anchor(): relative_pos(0), snapping(left | top) {}
		glm::vec2 getPos(const frame* screen);
		glm::vec2 getRelativePos() {return relative_pos;}
		void setRelativePos(glm::vec2 pos) {this->relative_pos = pos;}
		void setSnapping(int snapping) {this->snapping = snapping;}
		void set(glm::vec2 pos, int snapping) {setRelativePos(pos); setSnapping(snapping);}
		int getSnapping() {return snapping;}
	};

	class component {
	protected:
		anchor anch;
		int alignment;
	public:
		component(): anch(), alignment(left|top) {}
		glm::vec2 getPos(const frame* screen); // Returns position on screen

		virtual void tick() = 0;
		virtual glm::vec2 getSize(const frame* screen) const = 0; // Returns size of element
		virtual void render(const frame* screen = nullptr) = 0;

		virtual glm::vec4 getScreenRect(const frame* screen) {return glm::vec4(getPos(screen), getSize(screen));} // Returns the position and size of the element on screen
		virtual glm::vec2 getRelativePos() {return anch.getRelativePos();} // Returns pos relative to the anchors
		virtual void setRelativePos(float x, float y) {anch.setRelativePos(glm::vec2(x, y));}
		virtual void setAlignment(int a) {alignment = a;} // Sets the anchor for the element. If it were, say, centered, then getPos will offset by half 
		virtual void setSnapping(int a) {anch.setSnapping(a);}
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
		anchor top_left, bottom_right;
	public:
		std::map<std::string, component*> components = std::map<std::string, component*>();
		void tick();
		void render();
		anchor& topLeft() {return top_left;}
		anchor& bottomRight() {return bottom_right;}
	};
}
#endif