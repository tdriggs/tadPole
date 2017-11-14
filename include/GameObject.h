#ifndef TADPOLE_GAME_OBJECT_H
#define TADPOLE_GAME_OBJECT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "TMath.h"

namespace tadPole
{
	class GameObjectManager;
	class Component;
	class MeshComponent;

	class GameObject
	{
		friend class GameObjectManager;

	protected:
		std::string name;
		bool active;
		Ogre::SceneNode * parentSceneNode;
		Ogre::SceneNode * sceneNode;

		std::map<tadPole::ComponentType, std::vector<Component *>> components;

		GameObject(std::string name);
		virtual ~GameObject();

	public:
		void initialize();
		void setActive(bool active);
		void setParent(GameObject * parent);

		void setScaleInheritance(bool inherit);
		void setOrientationInheritance(bool inherit);
		void setPosition(float x, float y, float z);
		void setScale(float x, float y, float z);
		void setOrientation(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void setOrientation(Ogre::Quaternion orientation);
		void rotateWorld(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void rotateParent(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void rotateLocal(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void translateWorld(float x, float y, float z);
		void translateParent(float x, float y, float z);
		void translateLocal(float x, float y, float z);
		void scale(float x, float y, float z);

		void update(float deltaTime);

		Ogre::Quaternion getRelativeOrientation();
		Ogre::Quaternion getWorldOrientation();
		Vector3 getRelativePosition();
		Vector3 getWorldPosition();
		Vector3 getRelativeScale();
		Vector3 getWorldScale();

		MeshComponent * createMeshComponent(std::string fname);
	};
}

#endif
