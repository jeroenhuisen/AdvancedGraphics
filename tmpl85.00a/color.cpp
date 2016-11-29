#include "template.h"
#include "color.h"


Color::Color(float r, float g, float b): r(r), g(g), b(b)  {

}

Tmpl8::Pixel Color::getRGB() {
	return floorf(r) * 0xFF0000 + floorf(g) * 0x00FF00 + floorf(b) * 0x0000FF;
}