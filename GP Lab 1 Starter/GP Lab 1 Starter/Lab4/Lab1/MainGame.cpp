#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;
Transform treeTransform;
Transform monkeyTransform;
Transform ivysaurTransform;

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
	Texture* grassTexture();
	
	Shader* standard();
	Shader* noise();
	Shader* blur();
	Shader* rim();
	Shader* toon();
	Shader* rimToonShader();
	Shader* ripple();
	Shader* explode();
	Shader* toonFog();
	Shader* blinnPhon();
	
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
	tree.loadModel("..\\res\\Models\\tree.obj");
	monkey.loadModel("..\\res\\Models\\monkey3.obj");
	ivysaur.loadModel("..\\res\\Models\\Pokemon.obj");
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
	fog.Initialise("..\\res\\Shaders\\shaderToonFog.vert", "..\\res\\Shaders\\shaderToonFog.frag");
	blend.Initialise("..\\res\\Shaders\\shaderBlend.vert", "..\\res\\Shaders\\shaderBlend.frag");
	glass.Initialise("..\\res\\Shaders\\shaderGlass.vert", "..\\res\\Shaders\\shaderGlass.frag");

	//diffuse.Initialise("..\\res\\Lighting\\diffuseLighting.vert", "..\\res\\Lighting\\diffuseLighting.frag");
	blinnPhong.Initialise("..\\res\\Lighting\\blinnPhong.vert", "..\\res\\Lighting\\blinnPhong.frag");






	treeShader = Explode;
	monkeyShader = Fog;
	ivysaurShader = RimToon;
}
void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(tree.getSpherePos(), tree.getSphereRadius(), monkey.getSpherePos(), monkey.getSphereRadius());
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
					treeShader = Standard;
					monkeyShader = Standard;
					ivysaurShader = Standard;
					break;
				case SDLK_1:
					treeShader = Blur;
					monkeyShader = Blur;
					ivysaurShader = Blur;
					break;
				case SDLK_2:
					treeShader = Rim;
					monkeyShader = Rim;
					ivysaurShader = Rim;
					break;
				case SDLK_3:
					treeShader = Toon;
					monkeyShader = Toon;
					ivysaurShader = Toon;
					break;
				case SDLK_4:
					treeShader = RimToon;
					monkeyShader = RimToon;
					ivysaurShader = RimToon;
					break;
				case SDLK_5:
					treeShader = Glass;
					monkeyShader = Glass;
					ivysaurShader = Glass;
					break;
				case SDLK_6:
					treeShader = Explode;
					monkeyShader = Explode;
					ivysaurShader = Explode;
					break;
				case SDLK_7:
					treeShader = Fog;
					monkeyShader = Fog;
					ivysaurShader = Fog;
					break;
				case SDLK_8:
					treeShader = BlinnPhong;
					monkeyShader = BlinnPhong;
					ivysaurShader = Rim;
					break;
				case SDLK_9:
					treeShader = Blend;
					monkeyShader = Blend;
					ivysaurShader = Blend;
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

void MainGame::UpdateShader(ShaderTypes shader, Transform trans, glm::vec3 spherePos)
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
		SetRimToon(trans, spherePos);
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
	case Fog:
		fog.Bind();
		SetFog(trans, spherePos);
		fog.Update(transform, myCamera);
		break;
	case Diffuse:
		diffuse.Bind();
		SetDiffuse(trans, spherePos);
		diffuse.Update(transform, myCamera);
		break;
	case Blend:
		blend.Bind();
		blend.Update(transform, myCamera);
		break;
	case Glass:
		glass.Bind();
		SetGlass(trans);
		glass.Update(transform, myCamera);
		break;
	case BlinnPhong:
		blinnPhong.Bind();
		SetBlinnPhong();
		blinnPhong.Update(transform, myCamera);
		break;
	}
}

 void MainGame::SetRimToon(Transform trans, glm::vec3 spherePos)
{

	 rimToonShader.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 rimToonShader.SetMatrix4("u_vm", myCamera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 rimToonShader.SetMatrix4("u_pm", myCamera.GetProj());
	 rimToonShader.SetMatrix4("v_pos", transform.GetModel());

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

 void MainGame::SetBlinnPhong()
 {

	 blinnPhong.SetVector3("viewPos", myCamera.getPos());
	 blinnPhong.SetVector3("lightPos", ivysaur.getSpherePos());
	 blinnPhong.SetInteger("blinn", true);
 }

 void MainGame::SetFog(Transform trans, glm::vec3 spherePos)
 {
	 fog.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));

	 fog.SetMatrix4("u_vm", myCamera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 fog.SetMatrix4("u_pm", myCamera.GetProj());


	 fog.SetVector3("fogColor", glm::vec3(1, 0, 1));
	 fog.SetFloat("minDist", -5.0f);
	 fog.SetFloat("maxDist", 5.0f);

	 fog.SetFloat("zpos", spherePos.z);


 }

 void MainGame::SetGlass(Transform trans)
 {
	 glass.SetMatrix4("u_modelMatrix", trans.GetModel());
	 glass.SetMatrix4("u_viewProjectionMatrix", myCamera.GetViewProjection());
	 glass.SetMatrix4("u_normalMatrix", myCamera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 glass.SetVector4("u_camera", glm::vec4(myCamera.getPos().x, myCamera.getPos().y, myCamera.getPos().z, 1.0));
 }

 void MainGame::SetDiffuse(Transform trans, glm::vec3 spherePos)
 {
	 diffuse.SetVector3("lightPos", spherePos);

 }

 void MainGame::LoadTextures() 
{
	brickTexture.LoadTexture("..\\res\\bricks.jpg");
	waterTexture.LoadTexture("..\\res\\water.jpg");
	grassTexture.LoadTexture("..\\res\\grass.png");

}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	LoadTextures();
	

	UpdateTransforms(treeTransform, glm::vec3(sinf(counter), 0.5, 0.0),
		glm::vec3(0.0, counter * 2, 0.0),
		glm::vec3(0.1, 0.1, 0.1));

	UpdateModel(treeTransform);
	UpdateShader(treeShader, treeTransform, tree.getSpherePos());
	grassTexture.Bind(0);
	tree.draw();
	tree.updateSphereData(*transform.GetPos(), 0.62f);
	

	

	UpdateTransforms(monkeyTransform, glm::vec3(-sinf(counter), -1.0, -sinf(counter) * 5),
		glm::vec3(0.0,/* counter **/ 2, 0.0),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateModel(monkeyTransform);
	UpdateShader(monkeyShader, monkeyTransform, monkey.getSpherePos());
	grassTexture.Bind(0);
	monkey.draw();
	monkey.updateSphereData(*transform.GetPos(), 0.62f);

				
	UpdateTransforms(ivysaurTransform, glm::vec3(-sinf(counter), -sinf(counter), -sinf(counter)),
		glm::vec3(glm::vec3(0.0, counter * 2, 0.0)),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateModel(ivysaurTransform);
	UpdateShader(ivysaurShader, ivysaurTransform, ivysaur.getSpherePos());
	grassTexture.Bind(0);
	ivysaur.draw();
	ivysaur.updateSphereData(*transform.GetPos(), 0.62f);


	counter = counter + 0.05f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 