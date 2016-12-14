#pragma once

#include "template.h"
#include "camera.h"

class GUIBuilder {
private:
	Tmpl8::Surface* screen;
	Tmpl8::Pixel white = 0xFFFFFF;
	const Camera* camera;
public:
	GUIBuilder(Tmpl8::Surface* screen, const Camera* camera);
	void drawVector(const glm::vec3 vector, int x, int y);
	void draw();
};