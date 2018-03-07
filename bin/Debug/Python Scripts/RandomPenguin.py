import pyTadPole
import random

class RandomPenguin(pyTadPole.ScriptComponent):
	def OnStart(self):
		self.getGameObject().setScale(0.15, 0.15, 0.15)
		self.rotation = random.uniform(1, 5)
		self.getGameObject().createMeshComponent('penguin.mesh')
		# self.axis = [random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1)]

	def OnUpdate(self):
		self.getGameObject().rotateWorld(0, 1, 0, self.rotation)

pyTadPole.RandomPenguin = RandomPenguin