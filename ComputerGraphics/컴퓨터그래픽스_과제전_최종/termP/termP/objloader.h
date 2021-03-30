#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>

struct vec3
{
	float x, y, z;
};
struct vec2
{
	float x, y;
};

bool loadOBJ(
	const char * path,
	std::vector<vec3> & out_vertices,
	std::vector<vec2> & out_uvs,
	std::vector<vec3> & out_normals
);


bool loadAssImp(
	const char * path,
	std::vector<unsigned short> & indices,
	std::vector<vec3> & vertices,
	std::vector<vec2> & uvs,
	std::vector<vec3> & normals
);


#endif

//http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-7-model-loading/