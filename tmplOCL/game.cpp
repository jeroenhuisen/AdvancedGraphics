#include "system.h"
#include "test.h"
#include "Triangle.h"
#include "Light.h"

static Texture* clOutput = 0;
static Shader* shader = 0;
static Kernel* testFunction;
static Buffer* outputBuffer;

bool Game::Init()
{
	// load shader and texture
	clOutput = new Texture(SCRWIDTH, SCRHEIGHT, Texture::FLOAT);
	shader = new Shader("shaders/vignette.vert", "shaders/vignette.frag");
	// load OpenCL code
	testFunction = new Kernel("programs/raytracer.cl", "TestFunction");

	cl_float3 pos = { 0.0f, 0.0f, 0.0f };
	cl_float3 target = { 0.0f, 0.0f, 1.0f };
	// link cl output texture as an OpenCL buffer
	outputBuffer = new Buffer(clOutput->GetID(), Buffer::TARGET);
	testFunction->SetArgument(0, outputBuffer);
	//fix this so c++ style can be used
	clSetKernelArg(testFunction->GetKernel(), 1, sizeof(cl_float3), &pos);
	clSetKernelArg(testFunction->GetKernel(), 2, sizeof(cl_float3), &target);
	int amountOfTriangles = 2;
	Triangle* triangles = new Triangle[amountOfTriangles];
	Material material,material2;
	material.color = { 1,0,0 };
	material2.color = { 0,1,0 };
	Triangle triangle = createTriangle(vec3(0, 0, 1), vec3(0.5, -0.5, 1), vec3(-1, -1, 1), material);
	Triangle triangle2 = createTriangle(vec3(0, 0, 1), vec3(-0.5, 0.5, 1), vec3(1, 1, 1), material2);
	triangles[0] = triangle;
	triangles[1] = triangle2;

	cl_mem deviceBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, amountOfTriangles * sizeof(Triangle), triangles, 0);
	clSetKernelArg(testFunction->GetKernel(), 3, sizeof(cl_mem), &deviceBuffer);//triangles
	//testFunction->SetArgument(4, amountOfTriangles);
	clSetKernelArg(testFunction->GetKernel(), 4, sizeof(int), &amountOfTriangles);
	Light l;
	clSetKernelArg(testFunction->GetKernel(), 5,  sizeof(Light), &l);//triangles
	int amountOfLights = 1;
//	testFunction->SetArgument(6, amountOfLights);
	clSetKernelArg(testFunction->GetKernel(), 6, sizeof(int), &amountOfLights);
	int* ints = new int[2];
	ints[0] = 0;
	ints[1] = 1;

	cl_mem deviceBuffer1 = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 2 * sizeof(int), ints, 0);
	clSetKernelArg(testFunction->GetKernel(), 7, sizeof(cl_mem), &deviceBuffer1);

	vec3 position = vec3(0, 0, 0);
	vec3 dir = vec3(0, 0, 1);
	GeneratePrimaryRay(400, 240, position, dir);
	// done
	return true;
}

void Game::Tick()
{
	testFunction->Run( outputBuffer );
	shader->Bind();
	shader->SetInputTexture( GL_TEXTURE0, "color", clOutput );
	shader->SetInputMatrix( "view", mat4::Identity() );
	DrawQuad();
}

void Game::Shutdown()
{
}

// EOF