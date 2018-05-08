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
	Shader* rimToon();
	Shader* ripple();
	Shader* explode();
	Transform* mesh1Trans();
	Transform* mesh2Trans();
	Transform* mesh3Trans();
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


void MainGame::InitialiseTransforms()
{

}

void MainGame::UpdateTransforms(Transform trans, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	trans.SetPos(pos);
	trans.SetRot(rot);
	trans.SetScale(scale);

	transform.SetPos(pos);
	transform.SetRot(rot);
	transform.SetScale(scale);
}
void  MainGame::InitialiseShaders()
{
	standardShader.Initialise("..\\res\\Shaders\\shader.vert", "..\\res\\Shaders\\shader.frag");
	noiseShader.Initialise("..\\res\\Shaders\\shaderNoise.vert", "..\\res\\Shaders\\shaderNoise.frag");
	blurShader.Initialise("..\\res\\Shaders\\shaderBlur.vert", "..\\res\\Shaders\\shaderBlur.frag");
	rimShader.Initialise("..\\res\\Shaders\\shaderRim.vert", "..\\res\\Shaders\\shaderRim.frag");
	toonShader.Initialise("..\\res\\Shaders\\shaderToon.vert", "..\\res\\Shaders\\shaderToon.frag");
	rimToonShader.Initialise("..\\res\\Shaders\\shaderRimToon.vert", "..\\res\\Shaders\\shaderRimToon.frag");
	//ripple.Initialise("..\\res\\Shaders\\shaderToonRipple.vert", "..\\res\\Shaders\\shaderToonRipple.frag");
	explode.Initialise("..\\res\\Shaders\\shaderExplode.vert", "..\\res\\Shaders\\shaderExplode.frag", "..\\res\\Shaders\\shaderExplode.geom");



	mesh1Shader = Standard;
	mesh2Shader = Rim;
	mesh3Shader = Toon;
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
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					_gameState = GameState::EXIT;

					break;
				case SDLK_0:
					mesh1Shader = Standard;
					mesh2Shader = Standard;
					mesh3Shader = Standard;
					break;
				case SDLK_1:
					mesh1Shader = Blur;
					mesh2Shader = Blur;
					mesh3Shader = Blur;
					break;
				case SDLK_2:
					mesh1Shader = Rim;
					mesh2Shader = Rim;
					mesh3Shader = Rim;
					break;
				case SDLK_3:
					mesh1Shader = Toon;
					mesh2Shader = Toon;
					mesh3Shader = Toon;
					break;
				case SDLK_4:
					mesh1Shader = RimToon;
					mesh2Shader = RimToon;
					mesh3Shader = RimToon;
					break;
				case SDLK_5:
					mesh1Shader = Ripple;
					mesh2Shader = Ripple;
					mesh3Shader = Ripple;
					break;
				case SDLK_6:
					mesh1Shader = Explode;
					mesh2Shader = Explode;
					mesh3Shader = Explode;
					break;
				}
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
	Possible values of statetrans.SetPos(pos);
	trans.SetRot(rot);
	trans.SetScale(scale);
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

void MainGame::UpdateModel(Transform trans)
{

}

void MainGame::UpdateShader(ShaderTypes shader, Transform trans) 
{

	switch (shader)
	{
	default:
		standardShader.Bind();
		standardShader.Update(transform, myCamera);
		break;
	case Blur:
		blurShader.Bind();
		blurShader.Update(transform, myCamera);
		break;
	case Rim:
		rimShader.Bind();
		rimShader.Update(transform, myCamera);
		break;
	case Toon:
		toonShader.Bind();
		toonShader.Update(transform, myCamera);
		break;
	case RimToon:
		rimToonShader.Bind();
		SetRimToon(trans);
		rimToonShader.Update(transform, myCamera);
		break;
	case Ripple:
		ripple.Bind();
		SetRipple();
		ripple.Update(transform, myCamera);
	case Explode:
		explode.Bind();
		SetExplosion(trans);
		explode.Update(transform, myCamera);
		break;
	}
}

 void MainGame::SetRimToon(Transform trans)
{

	rimToonShader.SetMatrix4("u_vm", myCamera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	rimToonShader.SetMatrix4("u_pm", myCamera.GetViewProjection());
	rimToonShader.SetMatrix4("v_pos", trans.GetModel());
	rimToonShader.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));

}

 void MainGame::SetRipple()
 {
	// ripple.SetFloat("time", SDL_GetTicks());
 }

 void MainGame :: SetExplosion(Transform trans)
 {
	 explode.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 explode.SetMatrix4("u_vm", myCamera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 explode.SetMatrix4("u_pm", myCamera.GetProj());
	 explode.SetMatrix4("v_pos", trans.GetModel());
	 explode.SetFloat("time", 0.1f + (counter * 15));

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
	

	UpdateTransforms(mesh1Transform, glm::vec3(-1.5, 0.5, 0.5),
		glm::vec3(0.0, counter * 2.0,0),
		glm::vec3(0.1, 0.1, 0.1));

	UpdateModel(mesh1Transform);
	UpdateShader(mesh1Shader, mesh1Transform);
	brickTexture.Bind(0);
	mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.62f);
	

	

	UpdateTransforms(mesh2Transform, glm::vec3(2, 0.5, 0.5),
		glm::vec3(0.0, counter * 2, 0),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateModel(mesh2Transform);
	UpdateShader(mesh2Shader, mesh2Transform);
	brickTexture.Bind(0);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);

				
	UpdateTransforms(mesh3Transform, glm::vec3(.5, .5, 0.5),
		glm::vec3(0.0, counter * 2, 0 ),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateModel(mesh3Transform);
	UpdateShader(mesh3Shader, mesh3Transform);
	brickTexture.Bind(0);
	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);


	counter = counter + 0.05f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 