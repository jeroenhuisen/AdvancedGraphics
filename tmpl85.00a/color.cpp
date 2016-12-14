#include "template.h"
#include "color.h"


Color::Color(const float r, const float g, const float b): r(r), g(g), b(b)  {

}

Tmpl8::Pixel Color::getRGB() {
	if (r > 255) {
		r = 255;
	}
	if (g > 255) {
		g = 255;
	}
	if (b > 255) {
		b = 255;
	}
	//return floorf(r) * 0x10000 + floorf(g) * 0x100 + floorf(b);
	return (unsigned long) r * 0x10000 + (unsigned long) g * 0x100 + (unsigned long)b;
}

// assuming it was 255 no check
void Color::to1() {
	r /= 255;
	g /= 255;
	b /= 255;
}

//Assuming it was 1
void Color::to255() {
	r *= 255;
	g *= 255;
	b *= 255;
}