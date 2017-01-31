#include "system.h"
#include "test.h"
#include "Triangle.h"
#include "Light.h"
#include "objectImporter.h"
#include "BVH.h"

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

	//pos = { 0.0f, 0.0f, 0.0f };
	//cl_float3 target = { 0.0f, 0.0f, 1.0f };
	// link cl output texture as an OpenCL buffer
	outputBuffer = new Buffer(clOutput->GetID(), Buffer::TARGET);
	testFunction->SetArgument(0, outputBuffer);
	//fix this so c++ style can be used
	//clSetKernelArg(testFunction->GetKernel(), 1, sizeof(cl_float3), &pos);
	clSetKernelArg(testFunction->GetKernel(), 1, sizeof(cl_float3), &(camera->position));
	clSetKernelArg(testFunction->GetKernel(), 2, sizeof(cl_float3), &(camera->target));
	
	ObjectImporter oi;
	std::vector<Triangle> t = oi.loadObject("importOBJ/box1.obj");
	int amountOfTriangles = t.size();

	Triangle* triangles = new Triangle[amountOfTriangles];
	for (int i = 0; i < amountOfTriangles; i++) {
		triangles[i] = t[i];
		triangles[i].v1.z += 5;
		triangles[i].v2.z += 5;
		triangles[i].v3.z += 5;
	}

	/*Material material,material2;
	material.color = { 1,0,0 };
	material2.color = { 0,1,0 };
	Triangle triangle = createTriangle(vec3(0, 0, 1), vec3(0.5, -0.5, 1), vec3(-1, -1, 1), material);
	Triangle triangle2 = createTriangle(vec3(0, 0, 1), vec3(-0.5, 0.5, 1), vec3(1, 1, 1), material2);
	triangles[0] = triangle;
	triangles[1] = triangle2;*/

	cl_mem triangleBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, amountOfTriangles * sizeof(Triangle), triangles, 0);
	clSetKernelArg(testFunction->GetKernel(), 3, sizeof(cl_mem), &triangleBuffer);//triangles
	//testFunction->SetArgument(4, amountOfTriangles);
	clSetKernelArg(testFunction->GetKernel(), 4, sizeof(int), &amountOfTriangles);

	int amountOfLights = 1;
	Light* lights = new Light[amountOfLights];
	Light l;
	l.position = { 0,0,-1 };
	l.color = { 1,1,1 };
	l.lightIntensity = 3.0f; //100, 1.0, 0.045, 0.0075
	l.attenuationConstant = 1;
	l.attenuationLinear = 0.45f;
	l.attenuationQuadratic = 0.075f;
	lights[0] = l;

//	1.0f, 0.2f, 0.05f);
	/*Light l1;
	l1.position = { 0,0,0 };
	l1.color = { 1,1,1 };
	l1.lightIntensity = 0.5f; //100, 1.0, 0.045, 0.0075
	l1.attenuationConstant = 1.0f;
	l1.attenuationLinear = 0.2f;
	l1.attenuationQuadratic = 0.05f;
	lights[1] = l1;*/

	cl_mem lightBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, amountOfLights * sizeof(Light), lights, 0);
	clSetKernelArg(testFunction->GetKernel(), 5,  sizeof(cl_mem), &lightBuffer);//triangles
	
//	testFunction->SetArgument(6, amountOfLights);
	clSetKernelArg(testFunction->GetKernel(), 6, sizeof(int), &amountOfLights);
	len = 1;
	ptr = new int[len];

	writeBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, len * sizeof(int), ptr, 0);
	clSetKernelArg(testFunction->GetKernel(), 7, sizeof(cl_mem), &writeBuffer);


	BVH bvh;
	unsigned int poolIndex = 0;
	bvh.constructBVH(triangles, amountOfTriangles, &poolIndex);
	poolIndex--;// poolIndex is bvh length and was 1 to much since it was used as the next pointer

	BVHNodeStruct* bvhNodes = new BVHNodeStruct[poolIndex];
	for (int i = 0; i < poolIndex; i++) {
		bvhNodes[i] = bvh.pool[i];
	}

	int test = poolIndex * sizeof(BVHNodeStruct);


	cl_mem bvhBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, test, bvhNodes, 0);
	clSetKernelArg(testFunction->GetKernel(), 8, sizeof(cl_mem), &bvhBuffer);

	cl_mem indicesBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, amountOfTriangles * sizeof(unsigned int), bvh.indices, 0);
	clSetKernelArg(testFunction->GetKernel(), 9, sizeof(cl_mem), &indicesBuffer);
	
	// stack for bvh traverse
	int* stack = new int[poolIndex];
	cl_mem stackBuffer = clCreateBuffer(testFunction->GetContext(), CL_MEM_READ_WRITE, poolIndex * sizeof(int), &stack, 0);
	clSetKernelArg(testFunction->GetKernel(), 10, sizeof(cl_mem), &stackBuffer);


	/*vec3 position = vec3(0, 0, 0);
	vec3 dir = vec3(0, 0, 1);
	GeneratePrimaryRay(400, 240, position, dir);*/
	// done
	timer.init();
	return true;
}

void Game::Tick()
{
	float time = timer.elapsed();
	std::cout<<time<<std::endl;
	timer.reset();
	buttonHandler->updateKeys();
	movementController->update(time);
	clSetKernelArg(testFunction->GetKernel(), 1, sizeof(cl_float3), &(camera->position));
	clSetKernelArg(testFunction->GetKernel(), 2, sizeof(cl_float3), &(camera->target));
	testFunction->Run( outputBuffer );
	clEnqueueReadBuffer(testFunction->GetQueue(), writeBuffer, CL_TRUE, 0, len * sizeof(int), ptr, 0, NULL, NULL);
	shader->Bind();
	shader->SetInputTexture( GL_TEXTURE0, "color", clOutput );
	shader->SetInputMatrix( "view", mat4::Identity() );
	DrawQuad();
}

void Game::Shutdown()
{
}

void Game::KeyDown(unsigned int a_Key) {
	buttonHandler->addButton(a_Key);
	//std::cout << a_Key << std::endl;
}

void Game::KeyUp(unsigned int a_Key) {
	buttonHandler->removeButton(a_Key);
	//std::cout << "up: " << a_Key << std::endl;
}



// EOF