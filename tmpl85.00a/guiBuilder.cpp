#include "template.h"

#include "guiBuilder.h"
#include <string>

GUIBuilder::GUIBuilder(Tmpl8::Surface* screen, const Camera* camera) :
	screen(screen), camera(camera) {

}

void GUIBuilder::draw() {
	screen->Print("controls:", 2, 2, 0xFFFFFF);
	screen->Print("w,a,s,d,e,q are used to control the camera position", 2, 10, white);
	screen->Print("the arrow keys are used to control the camera direction", 2, 18, white);
	
	screen->Print("position:", 2, 30, white);
	drawVector(camera->position, 2, 38);

	screen->Print("direction:", 2, 68, white);
	drawVector(camera->direction, 2, 76);

}

void GUIBuilder::drawVector(const glm::vec3 vector, int x, int y) {
	char a[10];
	sprintf(a, "%f", vector.x);
	screen->Print("x:", x, y, white);
	screen->Print(a, x + 12, y, white);

	sprintf(a, "%f", vector.y);
	screen->Print("y:", x, y+=8, white);
	screen->Print(a, x + 12, y, white);

	sprintf(a, "%f", vector.z);
	screen->Print("z:", x, y += 8, white);
	screen->Print(a, x += 12, y, white);
}