#pragma once
#include"Shader.h"
#include "Camera.h"
struct Uniform
{
public:
	Uniform();
	~Uniform();

	void SetRimToon(Shader shader,Camera camera )
	{
	shader.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shader.SetMatrix4("u_vm", camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	shader.SetMatrix4("u_pm", camera.GetViewProjection());

	}
};

