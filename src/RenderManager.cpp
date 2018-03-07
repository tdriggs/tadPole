#include "stdafx.h"
#include "RenderManager.h"

#include "Exception.h"
#include "Application.h"
#include "CameraComponent.h"

tadPole::RenderManager::RenderManager(HWND windowHandle) : Singleton<RenderManager>()
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

	Ogre::NameValuePairList windowParams;
	windowParams["externalWindowHandle"] = std::to_string((size_t)windowHandle);
	this->renderWindow = this->root->createRenderWindow("tadPole", SCREEN_WIDTH, SCREEN_HEIGHT, false, &windowParams);

	// Initialize SceneManager
	this->sceneManager = this->root->createSceneManager();
	this->sceneManager->addRenderQueueListener(this->overlaySystem);
	this->sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	this->sceneManager->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f));

	// To move to SceneView class after Big Picture
	this->mainCamera = this->sceneManager->createCamera("MAIN");
	this->mainViewport = this->renderWindow->addViewport(this->mainCamera);
	this->mainViewport->setBackgroundColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

tadPole::RenderManager::~RenderManager()
{
	delete this->root;
	delete this->overlaySystem;
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
#pragma warning(disable: 4996)
	if (!(this->root->restoreConfig() || this->root->showConfigDialog()))
	{
		EXCEPTION("No valid render systems available.");
	}
}
