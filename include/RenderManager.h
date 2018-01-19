#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define RENDER_MANAGER tadPole::RenderManager::getInstance()	///< Convienience macro for the singleton instance.

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
		Ogre::Root * root;							///< The OGRE root object. Creates and destroys most other OGRE objects.
		Ogre::RenderSystem * renderSystem;			///< The OGRE representation of the render system (e.g. Direct3D9, OpenGL4, etc.).
		Ogre::RenderWindow * renderWindow;			///< A window in which an OGRE viewport can be rendered.
		Ogre::SceneManager * sceneManager;			///< The OGRE object in charge of creating and destroying objects to be displayed in the scene.
		Ogre::OverlaySystem * overlaySystem;		///< The OGRE object in charge of creating and destroying overlays.
		Ogre::OverlayManager * overlayManager;		///< The OGRE object in charge of managing overlays.
		Ogre::Viewport * mainViewport;				///< An OGRE viewport to be connected to an OGRE camera (To be moved to SceneView).
		Ogre::Camera * mainCamera;					///< An OGRE camera to be display the scene (To be moved to SceneView).


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* RenderManager constructor.
		*/
		RenderManager(
			HWND windowHandle	///< The handle of the window to which the OGRE render window will be attached.
		);

		/**
		* RenderManager destructor.
		*/
		~RenderManager();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Render all objects in the scene and display them to the viewports via any camera in the scene.
		*/
		void render();


		// @@@@@ PROTECTED METHODS @@@@@
	protected:
		/**
		* Load in all resources that are detailed in the resources file given.
		*/
		void load_resources(
			std::string resourcesFile	///< The file from which to retrieve the directories in which the resources to load are loacted.
		);

		/**
		* Autodetect the underlying render system and if it has already been chosen, otherwise prompt
		* the user to select a render system.
		*/
		void load_renderSystem();
	};
}

#endif
