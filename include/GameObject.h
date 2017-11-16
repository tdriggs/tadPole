#ifndef TADPOLE_GAME_OBJECT_H
#define TADPOLE_GAME_OBJECT_H

#include "stdafx.h"

#include "ComponentType.h"

namespace tadPole
{
	class GameObjectManager;
	class Component;
	class MeshComponent;

	class GameObject
	{
		// Friends with Scene class.
		friend class GameObjectManager;

	protected:
		std::string name;
		bool active;
		Ogre::SceneNode * parentSceneNode;
		Ogre::SceneNode * sceneNode;

		std::map<tadPole::ComponentType, std::vector<Component *>> components;

		GameObject(std::string name);
		~GameObject();

	public:
		void initialize();
		void setActive(bool active);
		void setParent(GameObject * parent);

		void setScaleInheritance(bool inherit);
		void setOrientationInheritance(bool inherit);

		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);
		void setOrientation(glm::quat orientation);
		void setOrientation(glm::vec3 axis, float angle_degrees);
		void setOrientation(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void setScale(float scale);
		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);

		void translateLocal(glm::vec3 translation);
		void translateLocal(float x, float y, float z);
		void translateWorld(glm::vec3 translation);
		void translateWorld(float x, float y, float z);
		void rotateLocal(glm::quat rotation);
		void rotateLocal(glm::vec3 axis, float angle_degrees);
		void rotateLocal(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void rotateWorld(glm::quat rotation);
		void rotateWorld(glm::vec3 axis, float angle_degrees);
		void rotateWorld(float axis_x, float axis_y, float axis_z, float angle_degrees);
		void scale(float scale);
		void scale(glm::vec3 scale);
		void scale(float x, float y, float z);

		glm::vec3 getLocalPosition();
		glm::vec3 getWorldPosition();
		glm::quat getLocalOrientation();
		glm::quat getWorldOrientation();
		glm::vec3 getLocalScale();
		glm::vec3 getWorldScale();

		MeshComponent * createMeshComponent(std::string fname);
		void update(float deltaTime);
	};
}

#endif
