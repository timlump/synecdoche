//http://fhtr.blogspot.ie/2013/12/opus-2-glsl-ray-tracing-tutorial.html
//http://www.clockworkcoders.com/oglsl/rt/gpurt1.htm
//http://www.scratchapixel.com/code.php?id=9&origin=/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle
//https://www.shadertoy.com/view/4ljGRd

#version 150

uniform vec3 screenRes;
uniform samplerBuffer tboTex;
uniform vec3 rayOrigin = vec3(0.0);

out vec4 outColor;

struct Ray
{
	vec3 origin;
	vec3 dir;
};

struct Triangle
{
	vec3 a;
	vec3 b;
	vec3 c;
};

bool isTriIntersect(Ray r, Triangle t)
{
	return true;
};

void main()
{
	vec2 uv = gl_FragCoord.xy/screenRes.xy - vec2(0.5);
	uv.x *= screenRes.x/screenRes.y;
	
	vec3 orig = vec3(0.0);
	vec3 dir = normalize(vec3(uv.x,uv.y,-1));
	
	Ray ray;
	ray.origin = rayOrigin;
	ray.dir = dir;
	
	float r = texelFetch(tboTex,0).r;
	outColor = vec4(r,0.0,0.0,1.0);
}