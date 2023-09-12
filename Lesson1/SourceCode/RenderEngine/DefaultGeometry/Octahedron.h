#pragma once

#include "../RenderObject.h"

/*

*/

class Octahedron : public RenderObject
{
public:
	Octahedron();

private:
	inline static const PosColorVertex s_octahedronVertices[] =
	{
		{  1.0f,  0.0f,  0.0f, 0xffffffff }, // white
		{  0.0f,  2.0f,  0.0f, 0xff0000ff }, // red
		{ -1.0f,  0.0f,  0.0f, 0xff00ff00 }, // green
		{  0.0f, -2.0f,  0.0f, 0xffff0000 }, // blue
		{  0.0f,  0.0f,  1.0f, 0xff00ffff }, // yellow
		{  0.0f,  0.0f, -1.0f, 0xff000000 }, // black
	};

	inline static const uint16_t s_octahedronTriList[] =
	{
		
		1, 0, 4,
		2, 1, 4,
		3, 2, 4,
		3, 4, 0,
		0, 1, 5,
		1, 2, 5,
		2, 3, 5,
		3, 0, 5,
	};
};

