#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define RENDER_MANAGER tadPole::RenderManager::getInstance()

namespace tadPole
{
	class RenderManager : public Singleton<RenderManager>
	{
		// Friends with GameObject and all OGRE related Component classes.
		friend class DebugOverlay;
		friend class GameObject;
		friend class MeshComponent;

	public:
		Ogre::OverlayManager * overlayManager;

		RenderManager(HWND windowHandle);
		~RenderManager();

		// Get rid of these
		void initializeBaseScene();
		void update(float deltaTime);

		void render();

	protected:
		Ogre::Root * root;
		Ogre::RenderSystem * renderSystem;
		Ogre::RenderWindow * renderWindow;
		Ogre::SceneManager * sceneManager;
		Ogre::OverlaySystem * overlaySystem;

		float bulletTimer = 0;
		int numBullets = 0;

		void initialize(HWND windowHandle);
		void load_resources(std::string resources_file);
		void load_renderSystem();
	};
}

#endif
