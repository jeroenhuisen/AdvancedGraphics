#pragma once

#define SCRWIDTH	 1280
#define SCRHEIGHT	 800

#include "raytracer.h"
#include "camera.h"
#include "scene.h"
#include "sphere.h"
#include "material.h"
#include "plane.h"
#include "pointlight.h"
//#include "sceneBuilder.cpp"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	Game();
	void SetTarget( Surface* _Surface ) { screen = _Surface; }
	void Init();
	void Shutdown() { /* implement if you want code to be executed upon app exit */ };
	void HandleInput( float dt );
	void Tick( float dt );
	void MouseUp( int _Button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int _Button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int _X, int _Y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int a_Key ) { /* implement if you want to handle keys */ }
	void KeyDown( int a_Key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;

	Camera camera;
	Scene scene;
	Raytracer tracer;
};

}; // namespace Tmpl8