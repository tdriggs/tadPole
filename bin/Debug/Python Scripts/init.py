import pyTadPole

# pyTadPole.loadScene('scTest.json')

pyTadPole.loadScript('RandomPenguin.py')
pyTadPole.loadScene('SceneView.json')

pyTadPole.createGroup("SceneComponents")
for i in range(5):
	penguin = pyTadPole.RandomPenguin("SceneComponents", "sc" + str(i))
	penguin.getGameObject().createMeshComponent("penguin.mesh")
	penguin.getGameObject().scale(0.15, 0.15, 0.15)
	penguin.getGameObject().translateWorld(10 * (2 - i), 0, 0)

pyTadPole.saveScene("scTest.json")
