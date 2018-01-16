#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define RENDER_MANAGER tadPole::RenderManager::getInstance()	///<

namespace tadPole
{
	class RenderManager : public Singleton<RenderManager>
	{
		// @@@@@ FRIENDS @@@@@
		friend class DebugOverlay;
		friend class GameObject;
		friend class MeshComponent;
		friend class LightComponent;
		friend class CameraComponent;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		Ogre::Root * root;							///<
		Ogre::RenderSystem * renderSystem;			///<
		Ogre::RenderWindow * renderWindow;			///<
		Ogre::SceneManager * sceneManager;			///<
		Ogre::OverlaySystem * overlaySystem;		///<
		Ogre::OverlayManager * overlayManager;		///<
		Ogre::Viewport * mainViewport;				///<
		Ogre::Camera * mainCamera;					///<


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* 
		*/
		RenderManager(
			HWND windowHandle	///<
		);

		/**
		*
		*/
		~RenderManager();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		*
		*/
		void render();


		// @@@@@ PROTECTED METHODS @@@@@
	protected:
		/**
		*
		*/
		void initialize(
			HWND windowHandle	///<
		);

		/**
		*
		*/
		void load_resources(
			std::string resourcesFile	///<
		);

		/**
		*
		*/
		void load_renderSystem();
	};
}

#endif
