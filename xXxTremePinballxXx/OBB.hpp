#pragma once

#include "RE\ReEngAppClass.h"
#include "GOTransform.h"

struct OBB {

	vector3 r;
	vector3 s;
	vector3 t;

	vector3 c;
	matrix3 u;
	vector3 e;

	std::vector<vector3> verts;

	std::vector<vector3> GetWorldVerts() {
		std::vector<vector3> worldVerts;
		std::vector<vector3>::iterator it;
		for (it = verts.begin(); it != verts.end(); ++it) {
			worldVerts.push_back((*it) + c);
		}
		return worldVerts;
	}
};