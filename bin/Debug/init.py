import pyTadPole

pyTadPole.log("This is a message from Python!")

# pyTadPole.loadScene("lv01.json")

pyTadPole.clearScene()

pyTadPole.createGroup("python_objects")
go1 = pyTadPole.GameObject("python_objects", "pyObj1")
go2 = pyTadPole.GameObject("python_objects", "pyObj2")

go3 = pyTadPole.GameObject("python_objects", "pyObj3")
pyTadPole.deleteGameObject("pyObj3")

pyTadPole.setGroupActive("python_objects", False)

pyTadPole.saveScene("pyScene.txt")
