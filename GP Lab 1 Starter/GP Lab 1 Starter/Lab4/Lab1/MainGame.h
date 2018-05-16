#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Uniform.h"
#include <iostream>;
enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void daeItLikeForrest();
	enum ShaderTypes { Standard, Noise, Blur, Rim, Toon, RimToon, Ripple, Explode, Fog, Diffuse, Blend, Glass, BlinnPhong, Normal, ExplodeNormal};

	Shader standardShader;
	Shader noiseShader;
	Shader blurShader;
	Shader rimShader;
	Shader toonShader;
	Shader rimToonShader;
	Shader ripple;
	Shader explode;
	Shader fog;
	Shader blend;
	Shader glass;
	Shader normal;
	Shader explodeNormal;

	Shader diffuse;
	Shader blinnPhong;


private:

	ShaderTypes treeShader;
	ShaderTypes monkeyShader;
	ShaderTypes ivysaurShader;

	

	void InitialiseSystems();
	void Input();
	void Loop();
	void Draw();
	void DrawTree();
	void DrawIvysaur();
	void DrawMonkey();
	void CreatePointers();
	void LoadModels();
	void InitialiseShaders();
	void InitialiseTransforms();
	void UpdateTransforms(Transform trans, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);
	void UpdateModel(Transform trans);
	void UpdateShader(ShaderTypes shader, Transform trans, glm::vec3 spherePos);
	void LoadTextures();

	void SetBlur();
	void SetRim();
	void SetToon();
	void SetRimToon(Transform trans, glm::vec3 spherePos);
	void SetRipple();
	void SetExplosion(Transform trans);
	void SetNormal();
	void SetFog(Transform trans, glm::vec3 spherePos);
	void SetDiffuse(Transform trans, glm::vec3 spherePos);
	void SetGlass(Transform trans);
	void SetBlinnPhong();
	void SetNormalExplode();

	Display display;
	GameState state;
	Mesh tree;
	Mesh monkey;
	Mesh ivysaur;
	Camera camera;
	Audio audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;

	Texture brickTexture;
	Texture waterTexture;
	Texture grassTexture;
	
//	Uniform uniform;
};

