#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "stdafx.h"

#include "Serializable.h"
#include "ComponentType.h"
#include "PyTadPoleGameObject.h"

namespace tadPole
{
	class GameObjectManager;
	class Component;
	class MeshComponent;
	class CameraComponent;
	class LightComponent;
	class PythonScriptComponent;
	enum class LightType;

	/**
	* A representation of an object that is in the scene. GameObjects act as an anchor
	* point for components such as meshes, lights, physics bodies, etc.
	*/
	class GameObject : public Serializable
	{
		// @@@@@ FRIENDS @@@@@
		friend class Scene;
	

		// @@@@@ ATTRIBUTES @@@@@
	protected:
		std::string name;															///< The unique name of the GameObject.
		bool active;																///< Whether the GameObject is visible in the scene and can be interacted with.
		GameObject * parentObject;													///< The parent GameObject of this GameObject.
		std::vector<GameObject *> children;											///< The children of this GameObject.
		Ogre::SceneNode * sceneNode;												///< The OGRE representation of this GameObject.
		PyTadPole_GameObject * pythonGameObject;									///< The Python representation of this GameObject.
		std::map<tadPole::ComponentType, std::vector<Component *>> components;		///< All components that this GameObject has, grouped by ComponentType.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* GameObject constructor for the root GameObject (without a parent).
		*/
		GameObject(
			std::string name	///< The unique name of the GameObject.
		);

		/**
		* GameObject constructor for the normal GameObjects (with rootObject as the default parent).
		*/
		GameObject(
			GameObject * rootObject,	///< The default parent GameObject of this GameObject.
			std::string name			///< The unique name of the GameObject.
		);

		/**
		* GameObject destructor.
		*/
		~GameObject();


		// @@@@@ BASE CLASS / INTERFACE METHODS @@@@@
	public:
		/**
		* Turn this GameObject into a std::string of valid, formatted JSON.
		*/
		std::string serialize();
		
		
		// @@@@@ UPDATE / RENDER METHODS @@@@@
	public:
		/**
		* Update this GameObject and all of its components.
		*/
		void update(float deltaTime);


		// @@@@@ COMPONENT CREATION METHODS @@@@@
	public:
		/**
		* Create a new MeshComponent and add it to this GameObject.
		*/
		MeshComponent * createMeshComponent(
			std::string fileName	///< The file name of the file from which to create the MeshComponent.
		);

		/**
		* Create a new CameraComponent and add it to this GameObject.
		*/
		CameraComponent * createCameraComponent();

		/**
		* Create a new LightComponent and add it to this GameObject.
		*/
		LightComponent * createLightComponent(
			LightType type	///< The type of the LightComponent to create.
		);

		/**
		* Create a new PythonScriptComponent and add it to this GameObject.
		*/
		PythonScriptComponent * createPythonScriptComponent(
			std::string scriptName	///< The name of the script to attach to this GameObject.
		);


		// @@@@@ GENERAL GETTERS @@@@@
	public:
		/**
		* Get the unique name of this GameObject.
		*/
		std::string getName();

		/**
		* Get the number of components of the given ComponentType attached to this GameObject.
		*/
		int getComponentCount(
			ComponentType type	///< The type of components to count.
		);

		/**
		* Returns the Python representation of this GameObject;
		*/
		PyTadPole_GameObject * getPyObject();


		// @@@@@ TRANSFORM GETTERS @@@@@
	public:
		/**
		* Get the position of this GameObject in terms of this GameObject's local axes.
		*/
		glm::vec3 getLocalPosition();

		/**
		* Get the position of this GameObject in terms of the world's axes.
		*/
		glm::vec3 getWorldPosition();

		/**
		* Get the orientation of this GameObject in terms of this GameObject's local axes.
		*/
		glm::quat getLocalOrientation();

		/**
		* Get the orientation of this GameObject in terms of the world's axes.
		*/
		glm::quat getWorldOrientation();

		/**
		* Get the scale of this GameObject in terms of this GameObject's local axes.
		*/
		glm::vec3 getLocalScale();

		/**
		* Get the scale of this GameObject in terms of the world's axes.
		*/
		glm::vec3 getWorldScale();


		// @@@@@ GENERAL SETTERS @@@@@
	public:
		/**
		* Set whether this GameObject is visible and can be interacted with in its Scene.
		*/
		void setActive(
			bool active	///< Whether this GameObject is visible in the scene and can be interacted with.
		);

		/**
		* Change the current parent GameObject of this GameObject to the given GameObject. Translate
		* the world position, orientation, and scale to be relative to the new parent.
		*/
		void setParent(
			GameObject * parent	///< The new parent GameObject of this GameObject.
		);

		/**
		* Change the current parent GameObject of this GameObject to the given GameObject. Keep the
		* current world position, orientation, and scale unchanged.
		*/
		void setParentInPlace(
			GameObject * parent	///< The new parent GameObject of this GameObject.
		);

		/**
		* Change the Python representation of this GameObject.
		*/
		void setPyObject(
			PyTadPole_GameObject * pyObject	///< The new pyObject reference for this GameObject.
		);


		// @@@@@ ABSOLUTE TRANSFORM SETTERS @@@@@
	public:
		/**
		* Set the position of this GameObject in terms of the world's axes.
		*/
		void setPosition(
			glm::vec3 position	///< The new position of the GameObject.
		);

		/**
		* Set the position of this GameObject in terms of the world's axes.
		*/
		void setPosition(
			float x,	///< The x comopnent of the new position of the GameObject.
			float y,	///< The y comopnent of the new position of the GameObject.
			float z		///< The z comopnent of the new position of the GameObject.
		);

		/**
		* Set the orientation of this GameObject in terms of the world's axes.
		*/
		void setOrientation(
			glm::vec3 axis,		///< The axis of the new orientation of the GameObject. 
			float angleDegrees	///< The angle of the new orientation of the GameObject in degrees.
		);

		/**
		* Set the orientation of this GameObject in terms of the world's axes.
		*/
		void setOrientation(
			float axisX,		///< The x component of the axis of the new orientation of the GameObject. 
			float axisY,		///< The y component of the axis of the new orientation of the GameObject. 
			float axisZ,		///< The z component of the axis of the new orientation of the GameObject. 
			float angleDegrees	///< The angle of the new orientation of the GameObject in degrees.
		);

		/**
		* Set the scale of this GameObject in terms of the world's axes.
		*/
		void setScale(
			float scale	///< The new scale of this GameObject. Applied to all three axes.
		);

		/**
		* Set the scale of this GameObject in terms of the world's axes.
		*/
		void setScale(
			glm::vec3 scale	///< The new scale of this GameObject.
		);

		/**
		* Set the scale of this GameObject in terms of the world's axes.
		*/
		void setScale(
			float x,	///< The x component of the new scale of this GameObject.
			float y,	///< The y component of the new scale of this GameObject.
			float z		///< The z component of the new scale of this GameObject.
		);


		// @@@@@ RELATIVE TRANSFORM SETTERS @@@@@
	public:
		/**
		* Translate this GameObject relative to its current position in terms of its local axes.
		*/
		void translateLocal(
			glm::vec3 translation	///< The vector by which to translate this GameObject.
		);

		/**
		* Translate this GameObject relative to its current position in terms of its local axes.
		*/
		void translateLocal(
			float x,	///< The x component of the vector by which to translate this GameObject.
			float y,	///< The y component of the vector by which to translate this GameObject.
			float z		///< The z component of the vector by which to translate this GameObject.
		);

		/**
		* Translate this GameObject relative to its current position in terms of the world's axes.
		*/
		void translateWorld(
			glm::vec3 translation	///< The vector by which to translate this GameObject. 
		);

		/**
		* Translate this GameObject relative to its current position in terms of the world's axes.
		*/
		void translateWorld(
			float x,	///< The x component of the vector by which to translate this GameObject.
			float y,	///< The y component of the vector by which to translate this GameObject.
			float z		///< The z component of the vector by which to translate this GameObject.
		);

		/**
		* Rotate this GameObject relative to its current position in terms of its local axes.
		*/
		void rotateLocal(
			glm::vec3 axis,		///< The axis around which to rotate this GameObject.
			float angleDegrees	///< The angle by which to rotate this GameObject in degrees.
		);

		/**
		* Rotate this GameObject relative to its current position in terms of its local axes.
		*/
		void rotateLocal(
			float axisX,		///< The x component of the axis around which to rotate this GameObject.
			float axisY,		///< The y component of the axis around which to rotate this GameObject.
			float axisZ,		///< The z component of the axis around which to rotate this GameObject.
			float angleDegrees	///< The angle by which to rotate this GameObject in degrees.
		);

		/**
		* Rotate this GameObject relative to its current position in terms of the world's axes.
		*/
		void rotateWorld(
			glm::vec3 axis,		///< The axis around which to rotate this GameObject.
			float angleDegrees	///< The angle by which to rotate this GameObject in degrees.
		);

		/**
		* Rotate this GameObject relative to its current position in terms of the world's axes.
		*/
		void rotateWorld(
			float axisX,		///< The x component of the axis around which to rotate this GameObject.
			float axisY,		///< The y component of the axis around which to rotate this GameObject.
			float axisZ,		///< The z component of the axis around which to rotate this GameObject.
			float angleDegrees	///< The angle by which to rotate this GameObject in degrees.
		);

		/**
		* Scale this GameObject relative to its current position in terms of its local axes.
		*/
		void scale(
			float scale	///< The amount by which to scale this GameObject. Applied to all three axes.
		);

		/**
		* Scale this GameObject relative to its current position in terms of its local axes.
		*/
		void scale(
			glm::vec3 scale	///< The amount by which to scale this GameObject.
		);

		/**
		* Scale this GameObject relative to its current position in terms of its local axes.
		*/
		void scale(
			float x,	///< The amount by which to scale this GameObject along the x axis.
			float y,	///< The amount by which to scale this GameObject along the y axis.
			float z		///< The amount by which to scale this GameObject along the z axis.
		);
	};
}

#endif
