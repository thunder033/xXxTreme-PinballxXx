#pragma once

#include "RE\ReEngAppClass.h"
class Projection
{
	double min;
	double max;

	void Project(std::vector<vector3> verts, vector3 axis) {
		if (glm::length(axis) == 0 || verts.size() == 0) {
			return;
		}
		
		vector3 nAxis = glm::normalize(axis);

		min = glm::dot(verts[0], axis);
		max = min;

		std::vector<vector3>::iterator it;
		for (it = verts.begin(); it != verts.end(); ++it) {
			double p = glm::dot(*it, axis);
			if (p > max) {
				max = p;
			} else if (p < min) {
				min = p;
			}
		}
		
	}

public:
	Projection(float min, float max) {
		this->min = min;
		this->max = max;
	};

	Projection(std::vector<vector3> verts, vector3 axis) {
		min = 0;
		max = 0;
		Project(verts, axis);
	}

	~Projection() {

	};

	bool Overlaps(Projection proj) {
		return !(max < proj.min || proj.max < min);
	}
};

