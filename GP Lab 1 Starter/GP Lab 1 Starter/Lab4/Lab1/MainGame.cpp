#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	
	CreatePointers();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::CreatePointers()
{
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Audio* audioDevice();
	Texture* brickTexture();
	Texture* waterTexture();
	Shader* standard();
	Shader* noise();
	Shader* blur();
	Shader* rim();
	Shader* toon();
}
void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	
	
	LoadModels();
	InitialiseShaders();
	
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void MainGame::LoadModels()
{
	mesh1.loadModel("..\\res\\Models\\tree.obj");
	mesh2.loadModel("..\\res\\Models\\monkey3.obj");
	mesh3.loadModel("..\\res\\Models\\Pokemon.obj");
}

void  MainGame::InitialiseShaders()
{
	standardShader.Initialise("..\\res\\shader.vert", "..\\res\\shader.frag");
	noiseShader.Initialise("..\\res\\shaderNoise.vert", "..\\res\\shaderNoise.frag");
	blurShader.Initialise("..\\res\\shaderBlur.vert", "..\\res\\shaderBlur.frag");
	rimShader.Initialise("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	toonShader.Initialise("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");
}
void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{
	
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audioDevice.playSound(Source, pos);
	}
}

void MainGame::UpdateModel(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	transform.SetPos(pos);
	transform.SetRot(rot);
	transform.SetScale(scale);
}

void MainGame::UpdateShader(ShaderTypes shader) 
{

	switch (shader)
	{
	default:
		standardShader.Bind();
		standardShader.Update(transform, myCamera);
		break;
	case Noise:
		noiseShader.Bind();
		noiseShader.Update(transform, myCamera);
		break;
	}
}

void MainGame::LoadTextures() 
{
	brickTexture.LoadTexture("..\\res\\bricks.jpg");
	waterTexture.LoadTexture("..\\res\\water.jpg");
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	LoadTextures();
	

	UpdateModel(glm::vec3(-1.5, 0.5, 0.5),
		glm::vec3(0.0, counter * 2.0,0),
		glm::vec3(0.1, 0.1, 0.1));

	UpdateShader(mesh1Shader);
	brickTexture.Bind(0);
	mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.62f);
	

	

	UpdateModel(glm::vec3(2, 0.5, 0.5),
		glm::vec3(0.0, counter * 2, 0),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateShader(mesh2Shader);
	brickTexture.Bind(0);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);

				
	UpdateModel(glm::vec3(.5, .5, 0.5),
		glm::vec3(0.0, counter * 2, 0 ),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateShader(mesh3Shader);
	brickTexture.Bind(0);
	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);


	counter = counter + 0.05f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 