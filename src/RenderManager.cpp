#include "stdafx.h"
#include "RenderManager.h"

#include "Exception.h"
#include "Application.h"
#include "GameObject.h"

tadPole::RenderManager::RenderManager(WindowParams & windowParams) : Singleton<RenderManager>()
{
	RENDER_MANAGER->initialize(windowParams);
}

tadPole::RenderManager::~RenderManager()
{
	delete this->root;
	delete this->overlaySystem;
}

void tadPole::RenderManager::initialize(WindowParams & windowParams)
{
#ifdef _DEBUG
	std::string plugins = "plugins_d.cfg";
	std::string resources = "resources_d.cfg";
#else
	std::string plugins = "plugins.cfg";
	std::string resources = "resources.cfg";
#endif

	// Create New OGRE Objects
	this->root = new Ogre::Root(plugins);
	this->overlaySystem = new Ogre::OverlaySystem();

	this->load_renderSystem();
	this->load_resources(resources);

	// Initialize Ogre and Create a Context
	this->root->initialise(false);
	this->overlayManager = Ogre::OverlayManager::getSingletonPtr();
	this->renderWindow = this->root->createRenderWindow("tadPole", SCREEN_WIDTH, SCREEN_HEIGHT, false, &windowParams);

	// Initialize SceneManager
	this->sceneManager = this->root->createSceneManager();
	this->sceneManager->addRenderQueueListener(this->overlaySystem); 
	this->sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	this->sceneManager->setAmbientLight(Ogre::ColourValue(0.8f, 0.8f, 0.8f));

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void tadPole::RenderManager::initializeBaseScene()
{
	Ogre::SceneNode* camNode = this->sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Light * light = this->sceneManager->createLight();
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(0, -1, 0);
	light->setDiffuseColour(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
	camNode->setPosition(0, 15, 30);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	this->mainCamera = this->sceneManager->createCamera("myCam");
	this->mainCamera->setNearClipDistance(0.1f);
	this->mainCamera->setFarClipDistance(1000.0f);
	this->mainCamera->setAutoAspectRatio(true);
	camNode->attachObject(this->mainCamera);
	this->mainViewport = this->renderWindow->addViewport(this->mainCamera);
	this->mainViewport->setBackgroundColour(Ogre::ColourValue::ColourValue(0.4f, 0.4f, 0.4f));
	this->render();

	GAME_OBJECT_MANAGER->createGroup("rotaters");
	GAME_OBJECT_MANAGER->createGroup("rotaters/left");
	GAME_OBJECT_MANAGER->createGroup("rotaters/left/orbiterBase");
	GAME_OBJECT_MANAGER->createGroup("rotaters/orbiter");
	GAME_OBJECT_MANAGER->createGroup("rotaters/central");
	GAME_OBJECT_MANAGER->createGroup("rotaters/central/orbiterBase");
	GAME_OBJECT_MANAGER->createGroup("bullets");
	GAME_OBJECT_MANAGER->createGroup("base");

	GameObject * base = GAME_OBJECT_MANAGER->createGameObject("base");
	MeshComponent * baseMesh = base->createMeshComponent("Barrel.mesh");
	base->scale(20.0f, 20.0f, 20.0f);
	base->translateWorld(0.0f, -70.0f, -30.0f);

	GameObject * central = GAME_OBJECT_MANAGER->createGameObject("rotaters/central");
	MeshComponent * centralMesh = central->createMeshComponent("Sinbad.mesh");

	GameObject * left = GAME_OBJECT_MANAGER->createGameObject("rotaters/left");
	MeshComponent * leftMesh = left->createMeshComponent("robot.mesh");
	left->scale(0.15f, 0.15f, 0.15f);

	GameObject * leftOrbiterBase = GAME_OBJECT_MANAGER->createGameObject("rotaters/left/orbiterBase");
	GameObject * centralOrbiterBase = GAME_OBJECT_MANAGER->createGameObject("rotaters/central/orbiterBase");
	GameObject * orbiter = GAME_OBJECT_MANAGER->createGameObject("rotaters/orbiter");
	MeshComponent * orbiterMesh = orbiter->createMeshComponent("penguin.mesh");
	orbiter->setParent(leftOrbiterBase);
	orbiter->scale(0.1f, 0.1f, 0.1f);
	orbiter->translateParent(10, 0, 0);

	left->translateLocal(-25, -6, -25);
	tadPole::Vector3 leftPosition = left->getWorldPosition();
	tadPole::Vector3 centralPosition = central->getWorldPosition();
	leftOrbiterBase->setPosition(leftPosition.x, leftPosition.y, leftPosition.z);
	centralOrbiterBase->setPosition(centralPosition.x, centralPosition.y, centralPosition.z);
}

void tadPole::RenderManager::update(float deltaTime)
{
	this->bulletTimer += deltaTime;

	GAME_OBJECT_MANAGER->getGameObject("rotaters/central")->rotateLocal(0, 1, 0, deltaTime * -20);
	GAME_OBJECT_MANAGER->getGameObject("rotaters/left")->rotateLocal(0, 1, 0, deltaTime * 10);
	GAME_OBJECT_MANAGER->getGameObject("rotaters/left/orbiterBase")->rotateLocal(0, 1, 0, deltaTime * 40);
	GAME_OBJECT_MANAGER->getGameObject("rotaters/central/orbiterBase")->rotateLocal(0, 1, 0, deltaTime * 40);
	GAME_OBJECT_MANAGER->getGameObject("rotaters/orbiter")->rotateLocal(0, 1, 0, deltaTime * -100);


	if (bulletTimer >= 0.5f)
	{
		bulletTimer = 0;
		GAME_OBJECT_MANAGER->createGroup("bullets/" + std::to_string(numBullets));
		GameObject * bullet = GAME_OBJECT_MANAGER->createGameObject("bullets/" + std::to_string(numBullets++));
		MeshComponent * bulletMesh = bullet->createMeshComponent("RZR-002.mesh");
		bullet->scale(0.05f, 0.05f, 0.05f);
		bullet->setOrientation(GAME_OBJECT_MANAGER->getGameObject("rotaters/central")->getRelativeOrientation());
	}

	std::vector<GameObject *> gameObjects = GAME_OBJECT_MANAGER->getGroup("bullets");
	std::vector<GameObject *>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->translateLocal(0, 0, deltaTime * 3);
	}
}

void tadPole::RenderManager::render()
{
	this->root->renderOneFrame();
}

void tadPole::RenderManager::load_resources(std::string resources_file)
{
	Ogre::ConfigFile resourceConfigFile;
	resourceConfigFile.load(resources_file);

	Ogre::ConfigFile::SettingsBySection_ sections = resourceConfigFile.getSettingsBySection();
	Ogre::ConfigFile::SettingsBySection_::iterator sectionsIterator;
	for (sectionsIterator = sections.begin(); sectionsIterator != sections.end(); ++sectionsIterator)
	{
		std::string groupName = sectionsIterator->first;
		Ogre::ConfigFile::SettingsMultiMap settings = sectionsIterator->second;
		Ogre::ConfigFile::SettingsMultiMap::iterator settingsIterator;
		for (settingsIterator = settings.begin(); settingsIterator != settings.end(); ++settingsIterator)
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(settingsIterator->second, settingsIterator->first);
		}
	}
}

void tadPole::RenderManager::load_renderSystem()
{
	/*std::string system_name = "Direct3D11 Rendering Subsystem";
	//std::string system_name = "OpenGL 3+ Rendering Subsystem";

	// Set the Render System (GL4, D3D11, etc.)
	Ogre::RenderSystemList rsl = this->root->getAvailableRenderers();
	if (rsl.size() > 0)
	{
		this->renderSystem = this->root->getRenderSystemByName(system_name);
		if (this->renderSystem->getName() != system_name)
		{
			EXCEPTION("Requested render system is not available.");
		}
		else
		{
			this->renderSystem->setConfigOption("Full Screen", "No");
			this->root->setRenderSystem(this->renderSystem);
		}
	}
	else
		EXCEPTION("No valid render systems available.");*/

#pragma warning(disable: 4996)
	if (!(this->root->restoreConfig() || this->root->showConfigDialog()))
	{
		EXCEPTION("No valid render systems available.");
	}
}
