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
	state = GameState::PLAY;
	
	CreatePointers();
}

MainGame::~MainGame()
{
}

void MainGame::daeItLikeForrest()
{
	InitialiseSystems(); 
	Loop();
}

///<This Creates all the pointers necessary for the game>
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
	Shader* blur();
	Shader* rim();
	Shader* toon();
	Shader* rimToonShader();
	Shader* explode();
	Shader* toonFog();
	Shader* blinnPhon();
	Shader* normal();
	Shader* explodeNormal();
	
	Transform* mesh1Trans();
	Transform* mesh2Trans();
	Transform* mesh3Trans();
}

///<This will initialise objects and load data from files>
void MainGame::InitialiseSystems()
{
	display.initDisplay(); 
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	LoadModels();
	InitialiseShaders();
	camera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)display.getWidth()/display.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

///<This Loads Models from files>
void MainGame::LoadModels()
{
	tree.loadModel("..\\res\\Models\\tree.obj");
	monkey.loadModel("..\\res\\Models\\monkey3.obj");
	ivysaur.loadModel("..\\res\\Models\\Pokemon.obj");
}


void MainGame::InitialiseTransforms()
{

}

///<This takes in parameters to update a transform >
void MainGame::UpdateTransforms(Transform trans, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	trans.SetPos(pos);
	trans.SetRot(rot);
	trans.SetScale(scale);

	transform.SetPos(pos);
	transform.SetRot(rot);
	transform.SetScale(scale);
}

///<This Loads the Shaders>
void  MainGame::InitialiseShaders()
{
	//loads shaders from files
	standardShader.InitialiseShader("..\\res\\Shaders\\shader.vert", "..\\res\\Shaders\\shader.frag");
	blurShader.InitialiseShader("..\\res\\Shaders\\shaderBlur.vert", "..\\res\\Shaders\\shaderBlur.frag");
	rimShader.InitialiseShader("..\\res\\Shaders\\shaderRim.vert", "..\\res\\Shaders\\shaderRim.frag");
	toonShader.InitialiseShader("..\\res\\Shaders\\shaderToon.vert", "..\\res\\Shaders\\shaderToon.frag");
	rimToonShader.InitialiseShader("..\\res\\Shaders\\shaderRimToon.vert", "..\\res\\Shaders\\shaderRimToon.frag");
	explode.InitialiseShader("..\\res\\Shaders\\shaderExplode.vert", "..\\res\\Shaders\\shaderExplode.frag", "..\\res\\Shaders\\shaderExplode.geom");
	fog.InitialiseShader("..\\res\\Shaders\\shaderToonFog.vert", "..\\res\\Shaders\\shaderToonFog.frag");
	normal.InitialiseShader("..\\res\\Shaders\\shaderNormal.vert", "..\\res\\Shaders\\shaderNormal.frag", "..\\res\\Shaders\\shaderNormal.geom");
	explodeNormal.InitialiseShader("..\\res\\Shaders\\shaderNormalExplode.vert", "..\\res\\Shaders\\shaderNormalExplode.frag", "..\\res\\Shaders\\shaderNormalExplode.geom");
	blinnPhong.InitialiseShader("..\\res\\Lighting\\blinnPhong.vert", "..\\res\\Lighting\\blinnPhong.frag");

	///the starting shaders are set 
	treeShader = Explode;
	monkeyShader = Fog;
	ivysaurShader = RimToon;
}
///<The Main game loop>
void MainGame::Loop()
{
	while (state != GameState::EXIT)
	{
		Input();
		Draw();
		//checks for collision
		collision(tree.getSpherePos(), tree.getSphereRadius(), monkey.getSpherePos(), monkey.getSphereRadius());
		//iterates counter
		counter = counter + 0.05f;
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

///<this checks input>
void MainGame::Input()
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
					state = GameState::EXIT;

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
					treeShader = Normal;
					monkeyShader = Normal;
					ivysaurShader = Normal;
					break;
				case SDLK_6:
					treeShader = Explode;
					monkeyShader = Explode;
					ivysaurShader = Explode;
					break;
				case SDLK_7:
					treeShader = ExplodeNormal;
					monkeyShader = ExplodeNormal;
					ivysaurShader = ExplodeNormal;
					break;
				case SDLK_8:
					treeShader = BlinnPhong;
					monkeyShader = BlinnPhong;
					ivysaurShader = Rim;
					break;
				case SDLK_9:		
					treeShader = Fog;
					monkeyShader = Fog;
					ivysaurShader = Fog;
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
		audioDevice.setlistener(camera.getPos(), m1Pos); //add bool to mesh
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

///<this is where the shaders are bound, uniforms are set, and updated>
void MainGame::UpdateShader(ShaderTypes shader, Transform trans, glm::vec3 spherePos)
{

	switch (shader)
	{
	default:
		standardShader.BindShader();
		standardShader.UpdateShader(transform, camera);
		break;
	case Blur:
		blurShader.BindShader();
		SetBlur();
		blurShader.UpdateShader(transform, camera);
		break;
	case Rim:
		rimShader.BindShader();
		SetRim();
		rimShader.UpdateShader(transform, camera);
		break;
	case Toon:
		toonShader.BindShader();
		SetToon();
		toonShader.UpdateShader(transform, camera);
		break;
	case RimToon:
		rimToonShader.BindShader();
		SetRimToon(trans, spherePos);
		rimToonShader.UpdateShader(transform, camera);
		break;
	case Ripple:
		ripple.BindShader();
		SetRipple();
		ripple.UpdateShader(transform, camera);
	case Explode:
		explode.BindShader();
		SetExplosion(trans);
		explode.UpdateShader(transform, camera);
		break;
	case Fog:
		fog.BindShader();
		SetFog(trans, spherePos);
		fog.UpdateShader(transform, camera);
		break;
	case Diffuse:
		diffuse.BindShader();
		SetDiffuse(trans, spherePos);
		diffuse.UpdateShader(transform, camera);
		break;
	case Blend:
		blend.BindShader();
		blend.UpdateShader(transform, camera);
		break;
	case Glass:
		glass.BindShader();
		SetGlass(trans);
		glass.UpdateShader(transform, camera);
		break;
	case BlinnPhong:
		blinnPhong.BindShader();
		SetBlinnPhong();
		blinnPhong.UpdateShader(transform, camera);
		break;
	case Normal:
		normal.BindShader();
		SetNormal();
		normal.UpdateShader(transform, camera);
		break;
	case ExplodeNormal:
		explodeNormal.BindShader();
		SetNormalExplode();
		explodeNormal.UpdateShader(transform, camera);
		break;
	}
}

///<Sets Blur>
void MainGame::SetBlur()
{
	blurShader.SetBoolean("horizontal", true);
}

///<Sets Rim>
void MainGame::SetRim()
{
	rimShader.SetMatrix4("u_vm", camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	rimShader.SetMatrix4("u_pm", camera.GetProj());
	/*rimShader.SetMatrix4("v_pos", transform.GetModel());
	rimShader.SetVector3 ("v_norm", ivysaur.):*/
}

///<Sets Toon>
void MainGame::SetToon()
{
	toonShader.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
}

///<Sets RimToon>
 void MainGame::SetRimToon(Transform trans, glm::vec3 spherePos)
{
	 //Rim
	 rimToonShader.SetMatrix4("u_vm", camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 rimToonShader.SetMatrix4("u_pm", camera.GetProj());
	 //Toon
	 rimToonShader.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 //RimToon
	 rimToonShader.SetMatrix4("v_pos", transform.GetModel());

}

 void MainGame::SetRipple()
 {
	// ripple.SetFloat("time", SDL_GetTicks());
 }

 ///<Sets Explosion>
 void MainGame :: SetExplosion(Transform trans)
 {
	 //Toon
	 explode.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 //Rim
	 explode.SetMatrix4("u_vm",
		 camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 explode.SetMatrix4("u_pm", camera.GetProj());
	 //Rim Toon
	 explode.SetMatrix4("v_pos", transform.GetModel());
	 //Explode
	 explode.SetFloat("time", 0.1f + (counter * 7.5f));
 }

 ///<Sets Normal shader>
 void MainGame::SetNormal()
 {
	 //Normal
	 normal.SetFloat("magnitude", 0.2f);
	 //Rim
	 normal.SetMatrix4("u_vm", camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 normal.SetMatrix4("u_pm", camera.GetProj());
	 //Toon
	 normal.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 //RimToon
	 normal.SetMatrix4("v_pos", transform.GetModel());
 }

 ///<Sets normal-Explode SHader>
 void MainGame::SetNormalExplode()
 {
	 //Normal
	 normal.SetFloat("magnitude", 0.2f);
	 //explode
	 explodeNormal.SetFloat("time", 0.1f + (counter * 3));
	 //Rim
	 explodeNormal.SetMatrix4("u_vm",
		 camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 explodeNormal.SetMatrix4("u_pm", camera.GetProj());
	 //Toon
	 explodeNormal.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 //RimToon
	 explodeNormal.SetMatrix4("v_pos", transform.GetModel());
 }
 
 ///<Sets Blinn Phong Lighting>
 void MainGame::SetBlinnPhong()
 {
	 blinnPhong.SetVector3("viewPos", camera.getPos());
	 blinnPhong.SetVector3("lightPos", ivysaur.getSpherePos());
	 blinnPhong.SetInteger("blinn", true);
 }

 ///<Sets Fog>
 void MainGame::SetFog(Transform trans, glm::vec3 spherePos)
 {
	 //Rim-Toon
	 fog.SetVector3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	 fog.SetMatrix4("u_vm", 
		 camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 fog.SetMatrix4("u_pm", camera.GetProj());
	 //Fog
	 fog.SetVector3("fogColor", glm::vec3(0.2, 0, 0.2));
	 fog.SetFloat("minDist", -5.0f);
	 fog.SetFloat("maxDist", 5.0f);
	 fog.SetFloat("zpos", spherePos.z);
 }

 ///<This isnot usesd>
 void MainGame::SetGlass(Transform trans)
 {
	 glass.SetMatrix4("u_modelMatrix", trans.GetModel());
	 glass.SetMatrix4("u_viewProjectionMatrix", camera.GetViewProjection());
	 glass.SetMatrix4("u_normalMatrix", camera.GetTheBandThatDoneThatOneSongAboutWearingTheSamePairOfJeans());
	 glass.SetVector4("u_camera", glm::vec4(camera.getPos().x, camera.getPos().y, camera.getPos().z, 1.0));
 }

 ///<This isnot usesd>
 void MainGame::SetDiffuse(Transform trans, glm::vec3 spherePos)
 {
	 diffuse.SetVector3("lightPos", spherePos);

 }

 ///<Loads textures from files>
 void MainGame::LoadTextures() 
{
	brickTexture.LoadTexture("..\\res\\bricks.jpg");
	waterTexture.LoadTexture("..\\res\\water.jpg");
	grassTexture.LoadTexture("..\\res\\grass.png");

}

 ///<Draws the game>
void MainGame::Draw()
{
	//sets backgorund clolour
	display.clearDisplay(0.5f, 0.5f, 1.0f, 1.0f);
	//Loads Textures
	LoadTextures();
	//Draws the models
	DrawTree();
	DrawIvysaur();
	DrawMonkey();

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();
	//swaps buffer witht the second, hidden, window
	display.swapBuffer();
} 

void MainGame::DrawTree()
{
	UpdateTransforms(treeTransform, glm::vec3(sinf(counter), 0.5, 0.0),
		glm::vec3(0.0, counter * 2, 0.0),
		glm::vec3(0.1, 0.1, 0.1));

	UpdateModel(treeTransform);
	UpdateShader(treeShader, treeTransform, tree.getSpherePos());
	grassTexture.Bind(0);
	tree.draw();
	tree.updateSphereData(*transform.GetPos(), 0.62f);
}

void MainGame::DrawIvysaur()
{
	UpdateTransforms(ivysaurTransform, glm::vec3(-sinf(counter), -sinf(counter), -sinf(counter)),
		glm::vec3(glm::vec3(0.0, counter * 2, 0.0)),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateModel(ivysaurTransform);
	UpdateShader(ivysaurShader, ivysaurTransform, ivysaur.getSpherePos());
	grassTexture.Bind(0);
	ivysaur.draw();
	ivysaur.updateSphereData(*transform.GetPos(), 0.62f);
}

void MainGame::DrawMonkey()
{
	UpdateTransforms(monkeyTransform, glm::vec3(-sinf(counter), -1.0, -sinf(counter) * 5),
		glm::vec3(0.0,/* counter **/ 2, 0.0),
		glm::vec3(0.6, 0.6, 0.6));

	UpdateModel(monkeyTransform);
	UpdateShader(monkeyShader, monkeyTransform, monkey.getSpherePos());
	grassTexture.Bind(0);
	monkey.draw();
	monkey.updateSphereData(*transform.GetPos(), 0.62f);
}