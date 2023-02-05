#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Particle.h"


class ParticleAccelerator {

	std::vector<Particle*> particles;

public:
	ParticleAccelerator();
	~ParticleAccelerator();

	Particle* InitParticle(const glm::vec3&);
	void UpdateStep(glm::vec3 direction, float time);

};
