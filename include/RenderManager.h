#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define RENDER_MANAGER RenderManager::getInstance()

namespace tadPole
{
	typedef Ogre::NameValuePairList WindowParams;

	class RenderManager : public Singleton<RenderManager>
	{
	public:
		Ogre::Root * root;
		Ogre::RenderSystem * renderSystem;
		Ogre::RenderWindow * renderWindow;
		Ogre::SceneManager * sceneManager;
		Ogre::OverlaySystem * overlaySystem;
		Ogre::OverlayManager * overlayManager;

		Ogre::Camera * mainCamera;
		Ogre::Viewport * mainViewport;

		float bulletTimer = 0;
		int numBullets = 0;

		RenderManager(WindowParams & windowParams);
		~RenderManager();

		void initialize(WindowParams & windowParams);
		void initializeBaseScene();
		void update(float deltaTime);
		void render();

	protected:
		void load_resources(std::string resources_file);
		void load_renderSystem();
	};
}

#endif
