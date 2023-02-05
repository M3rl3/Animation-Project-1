#include "Particle.h"

Particle::Particle() : Particle(glm::vec3(0.f)) {

}

Particle::Particle(const glm::vec3& position) {
    this->position = position;
    this->velocity = glm::vec3(0.f);
    this->acceleration = glm::vec3(0.f);
    this->force = glm::vec3(0.f);
    this->damping = .98f;
    this->mass = 1.f;
    this->inv_mass = 1.f;
    this->age = -1.f;
}

Particle::~Particle() {

}

Particle Particle::operator=(const Particle& particle) {
    return Particle();
}

//Calculate particle position and velocity
void Particle::Calculate(float dt) {
     
    inv_mass = InvMass(mass);
    acceleration = force * inv_mass;

    velocity = velocity + acceleration * dt;
    velocity = velocity * damping;
    position = position + velocity * dt;

    //age = age - dt;
}

void Particle::ApplyForce(const glm::vec3& direction) {
    if (inv_mass <= 0)
        return;

    force += direction; 
}

float Particle::InvMass(float mass) {
    return mass /= 1;
}

void Particle::KillAllForces() {
    force = glm::vec3(0.f, 0.f, 0.f);
}

void Particle::print() {
    std::cout << "\nPosition: (" << position.x << ", " << position.y << ", " << position.z << ") " << std::endl;
    std::cout << "\nVelocity: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ") " << std::endl;
}