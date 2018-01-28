#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"

#include "Serializable.h"
#include "Singleton.h"
#include "GameObject.h"

#define NO_GROUP_NAME "No Group"				///< The name of the group for GameObjects that don't belong to a group.
#define SCENE tadPole::Scene::getInstance()		///< Convienience macro for the singleton instance.

namespace tadPole
{
	/**
	* A representation of a collection of GameObjects and the groups to which they belong.
	*/
	class Scene : public Serializable, public Singleton<Scene>
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		GameObject * rootObject;									///< The GameObject that is the root of this Scene.
		std::map<std::string, std::vector<GameObject *>> objects;	///< The collection of GameObjects in this Scene and the groups to which they belong.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Scene constructor.
		*/
		Scene();

		/**
		* Scene destructor.
		*/
		~Scene();


		// @@@@@ BASE CLASS / INTERFACE METHODS @@@@@
	public:
		/**
		* Turn this Scene into a std::string of valid, formatted JSON.
		*/
		std::string serialize();


		// @@@@@ INITIALIZATION METHODS @@@@@
	public:
		/**
		* Write the serialized string of this Scene to the Scene's file.
		*/
		void save(
			std::string fileName	///< The name of the file to which to save.
		);

		/**
		* Reload the Scene from the Scene's file.
		*/
		void load(
			std::string fileName	///< The name of the file from which to load.
		);

		/**
		* Remove all GameObjects from the scene and delete all groups.
		*/
		void clear();
		

		// @@@@@ GROUP MANIPULATION METHODS @@@@@
	public:
		/**
		* Create a new group to which GameObjects can be added.
		*/
		void createGroup(
			std::string group	///< The name of the group to be created.
		);

		/**
		* Delete a group and all GameObjects in that group.
		*/
		void deleteGroup(
			std::string group	///< The name of the group to be deleted.
		);

		/**
		* Set whether all GameObjects in a group are visible and can be interacted with in this Scene.
		*/
		void setGroupActive(
			std::string group,	///< The name of the group to modify.
			bool active			///< Whether this group is visible in the scene and can be interacted with.
		);


		// @@@@@ GAME OBJECT MANIPULATION METHODS @@@@@
	public:
		/**
		* Create a GameObject that is not in a group.
		*/
		GameObject * createGameObject(
			std::string name	///< The unique name of the GameObject to be created.
		);

		/**
		* Create a GameObject and add it to a group immediately. This method requires the group
		* to have already been created.
		*/
		GameObject * createGameObject(
			std::string group,	///< The name of the group to which the GameObject will be added.
			std::string name	///< The unique name of the GameObject to be created.
		);

		/**
		* Delete a GameObject no matter what group it is in.
		*/
		void deleteGameObject(
			std::string name	///< The unique name of the GameObject to be deleted.
		);


		// @@@@@ GENERAL GETTERS @@@@@
	public:
		/**
		* Get all GameObjects in a group.
		*/
		std::vector<GameObject *> getGroup(
			std::string group	///< The name of the group to get.
		);

		/**
		* Get a specific GameObject.
		*/
		GameObject * getGameObject(
			std::string name	///< The unique name of the GameObject to get.
		);
	};
}

#endif
