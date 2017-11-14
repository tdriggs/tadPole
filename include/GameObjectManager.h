#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "stdafx.h"
#include "Singleton.h"
#include "GameObject.h"

#define GAME_OBJECT_MANAGER GameObjectManager::getInstance()

// Tree Structure
//
// --- map<string, TreeNode>
//	  |
//    |-"player/"- map<string, TreeNode> (depth 1)
//	          |
//            |-"weapons/"- map<string, TreeNode> (depth 2)
//                    |
//                    |--- GameObject [name="player/weapons/sword"]
//                    |--- GameObject [name="player/weapons/axe"]
//	          |
//            |-"armor/"- map<string, TreeNode> (depth 2)
//                    |--- GameObject [name="player/armor/gauntlets"]
//                    |--- GameObject [name="player/armor/leggings"]
//    |-"enemies/"- map<string, TreeNode> (depth 1)
//	          |
//            |-"stealth/"- map<string, TreeNode> (depth 2)
//                    |--- GameObject [name="enemies/stealth/skin1"]
//                    |--- GameObject [name="enemies/stealth/skin2"]
//	          |
//            |-"brawl/"- map<string, TreeNode> (depth 2)
//                    |--- GameObject [name="enemies/brawl/skin1"]
//                    |--- GameObject [name="enemies/brawl/skin2"]


namespace tadPole
{
	class GameObjectManager : public Singleton<GameObjectManager>
	{
	protected:
		class GOMTreeNode
		{
		public:
			GOMTreeNode * parent;
			GameObject * data;
			std::map<std::string, GOMTreeNode *> children;
			bool active;

			GOMTreeNode(GOMTreeNode * parent);
			~GOMTreeNode();

			std::pair<std::string, std::string> splitName(std::string name);

			void addNode(std::string namePath);
			GOMTreeNode * getNode(std::string namePath);

			std::vector<GameObject *> getObjectsInGroup();
			void setGroupActive(bool active);
		};

		GOMTreeNode * rootNode;

	public:
		 GameObjectManager();
		 ~GameObjectManager();

		 void createGroup(std::string groupPath);
		 void setGroupActive(std::string groupPath, bool active);
		 void deleteGroup(std::string groupPath);
		 GameObject * getGameObject(std::string namePath);
		 GameObject * createGameObject(std::string namePath);
		 std::vector<GameObject *> getGroup(std::string groupPath);
	};
}

#endif
