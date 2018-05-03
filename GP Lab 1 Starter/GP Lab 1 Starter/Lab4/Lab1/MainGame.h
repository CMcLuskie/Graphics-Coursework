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

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	enum ShaderTypes { Standard, Noise, Blur, Rim, Toon, RimToon };

	Shader standardShader;
	Shader noiseShader;
	Shader blurShader;
	Shader rimShader;
	Shader toonShader;
	Shader rimToonShader;

private:
	ShaderTypes mesh1Shader;
	ShaderTypes mesh2Shader;
	ShaderTypes mesh3Shader;

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void CreatePointers();
	void LoadModels();
	void InitialiseShaders();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);
	void UpdateModel(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	void UpdateShader(ShaderTypes shader);
	void LoadTextures();
	void SetRimToon();

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Camera myCamera;
	Audio audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;

	Texture brickTexture;
	Texture waterTexture;

	
//	Uniform uniform;
};

