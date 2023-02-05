#pragma once

#include <iostream>
#include <glm/glm.hpp>

class Particle {
public:
    glm::vec3 position;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    glm::vec3 force;


    Particle();
    Particle(const glm::vec3& position);
    ~Particle();
    float damping;
    float mass;
    float inv_mass;
    float age;

    void Calculate(float);
    float InvMass(float);
    void print();
    void ApplyForce(const glm::vec3& direction);
    void KillAllForces();

    Particle operator=(const Particle& particle);

    inline const glm::vec3& GetPosition() const { return position; }
    inline const glm::vec3& GetVelocity() const { return velocity; }
    inline const glm::vec3& GetAcceleration() const { return acceleration; }
};