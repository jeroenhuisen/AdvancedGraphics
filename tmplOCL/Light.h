struct Light {
	cl_float3 position;
	cl_float3 color;
	cl_float lightIntensity;
	cl_float attenuationConstant;
	cl_float attenuationLinear;
	cl_float attenuationQuadratic;
};

