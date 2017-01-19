#include "../shared.h"
#include "randomnumbers.h"
#include "raytracer.h"


__kernel void TestFunction( write_only image2d_t outimg, float3 pos, float3 target )
{
	uint x = get_global_id( 0 );
	uint y = get_global_id( 1 );
	const uint pixelIdx = x + y * SCRWIDTH;
	if (pixelIdx >= (SCRWIDTH * SCRHEIGHT)) return;
	// do calculations
	float3 color = Trace( x, y, pos, target );
	// send result to output array
	/*int r = (int)(clamp( color.x, 0.f, 1.f ) * 255.0f);
	int g = (int)(clamp( color.y, 0.f, 1.f ) * 255.0f);
	int b = (int)(clamp( color.z, 0.f, 1.f ) * 255.0f);*/
	float r = (clamp(color.x, 0.f, 1.f));
	float g = (clamp(color.y, 0.f, 1.f) );
	float b = (clamp(color.z, 0.f, 1.f) );

	write_imagef( outimg, (int2)(x, y), (float4)( r, g, b, 1 ) );
}


