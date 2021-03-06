#include "Plunger.h"

#include <glm/glm.hpp>

Plunger::Plunger(const vector3& start, const vector3 end)
	: Entity((mesh = new PrimitiveClass(), mesh->GenerateCube(1, RERED), mesh)),
	start(start), end(end), speed(speed)
{
	launching = false;
	Scale(vector3(1.f, 0.3f, 0.4f));
	launchPct = 0.f;
	speed = 3.f;
	collisionTest = ObjectType::Ball;

	slide = new ChuteSlide();
}

Plunger::~Plunger()
{
	if (slide != nullptr) {
		delete slide;
		slide = nullptr;
	}
}

void Plunger::Update(double dt)
{
	if (launching)
	{
		slide->ToggleOff();
		launchPct += (float)(speed * dt);
	}
	else
	{
		launchPct -= (float)(speed * dt);
	}

	if (slideTriggered) {
		slideElapsed += dt;
		if (slideElapsed > slideTriggerTime)
		{
			slide->ToggleOn();
			slideTriggered = false;
		}
	}

	if (launchPct > .95f) {
		slideElapsed = 0;
		slideTriggered = true;
	}

	launchPct = glm::clamp(launchPct, 0.f, 1.f);

	GetTransform()->SetPosition(glm::lerp(start, end, launchPct));

	Entity::Update(dt);
}

void Plunger::StartLaunch()
{
	launching = true;
}

void Plunger::EndLaunch()
{
	launching = false;
}

void Plunger::OnCollision(const CollisionEvent& collision)
{
	if (collision.collidee->GetType() == ObjectType::Ball)
	{
		Entity* ball = reinterpret_cast<Entity*>(collision.collidee);
		if (glm::length(ball->GetVelocity()) <= 3.f)
		{
			ball->GetTransform()->SetPosition(GetPosition() + vector3(-0.2f, 0.3f, 0.f));
		}

		if (launching)
		{
			float s = (end - GetPosition()).y * 4.f;
			vector3 v = ball->GetVelocity();
			v.y = glm::max(v.y, s);
			ball->SetVelocity(v);
		}
	}
}