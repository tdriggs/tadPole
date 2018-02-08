import pyTadPole
import random

class RandomPenguin(pyTadPole.ScriptComponent):
	def OnStart(self):
		self.rotation = random.uniform(1, 5)
		self.axis = [random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1)]

	def OnUpdate(self):
		self.getGameObject().rotateWorld(self.axis[0], self.axis[1], self.axis[2], self.rotation)

pyTadPole.RandomPenguin = RandomPenguin