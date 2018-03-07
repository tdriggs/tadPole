import pyTadPole

pyTadPole.loadScript('enums.py')
pyTadPole.loadScript('RandomPenguin.py')

pyTadPole.createGroup("Cameras")
camera = pyTadPole.GameObject("Cameras", "mainCamera")
camera.translateWorld(0, 30, 100)
camera.setOrientation(1, 0, 0, -20)
cameraComponent = camera.createCameraComponent()
cameraComponent.setViewport(0)
cameraComponent.setClipDistances(0.1, 1000)

pyTadPole.createGroup('Lights')
frontLight = pyTadPole.GameObject('Lights', 'frontLight')
frontLight.setPosition(*camera.getWorldPosition())
lightComponent = frontLight.createLightComponent(pyTadPole.SPOT_LIGHT)
lightComponent.setDiffuseColor(255, 255, 255)
lightComponent.setSpecularColor(255, 255, 255)
lightComponent.setDirection(0, 0, -1)
topLight = pyTadPole.GameObject('Lights', 'topLight')
lightComponent = topLight.createLightComponent(pyTadPole.DIRECTIONAL_LIGHT)
lightComponent.setDiffuseColor(255, 255, 255)
lightComponent.setSpecularColor(255, 255, 255)
lightComponent.setDirection(0, -1, 0)

pyTadPole.createGroup('Floor')
floor = pyTadPole.GameObject('Floor', 'floor')
floor.createMeshComponent('barrel.mesh')
floor.setScale(20, 20, 20)
floor.setPosition(0, -65, 0)

pyTadPole.createGroup("penguins")
for i in range(20):
	penguin = pyTadPole.RandomPenguin("penguins", "sc" + str(i))
	penguin.getGameObject().setOrientation(0, 1, 0, i * (360 / 20))
	penguin.getGameObject().translateLocal(0, 0, 45)

pyTadPole.saveScene("scTest.json")
