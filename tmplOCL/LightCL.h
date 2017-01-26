//#pragma once

struct Light {
	float3 position;
	float3 color;
	float lightIntensity;
	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;
};

float calculateStrength(struct Light l, const float distance) {
	return l.lightIntensity / (l.attenuationConstant + l.attenuationLinear*distance + l.attenuationQuadratic*distance*distance);
}