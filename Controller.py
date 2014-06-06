import socket
import re

class Controller:

	host = "localhost"
	port = 6001
	server = ""
	player = ""
	player_types = []

	#
	# Constructor
	#

	def __init__(self):
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	#
	# Connect method
	# only needs the host where the trainer will connect
	# and initialize all the necessary information with
	# the data received from the server
	#

	def connect(self, host):
		self.host = host
		self.sendMessage("(init (version 15.0))")
		print self.receiveMessage()
		self.server = self.receiveMessage()
		print "Server params done: '(string)server' member"
		self.player = self.receiveMessage()
		print "Player params done: '(string)player' member"
		m = re.search("\\(player_types\\s(\\d+)\\)", self.player)
		types = int(m.group(1))
		for i in range(types):
			self.player_types.append(self.receiveMessage())
		print "Player types done: '(list)player_types' member"
		self.sendMessage("(eye on)")

	#
	# Returns the current game time
	# it is a blocking method which waits until a see_global
	# message is received. In consequence, some messages could
	# get lost

	def cycle(self):
		m = re.search("\\(see_global\\s(\\d+)\\s", self.receiveMessage())
		while m != None:
			m = re.search("\\(see_global\\s(\\d+)\\s", self.receiveMessage())
		return int(m.group(1))

	#
	# Changes the current play mode to the play_mode provided in
	# the argument, and prints the server response
	# Blocking method
	#

	def changeTo(self, play_mode):
		self.sendMessage("(change_mode " + play_mode)
		print self.receiveMessage()

	#
	# Resets the stamina, effort and recovery params of all players
	# in game, and prints the server response
	# Blocking method
	#

	def recover():
		self.sendMessage("(recover)")
		print self.receiveMessage()

	#
	# Disconnects from the server
	#

	def disconnect(self):
		self.sendMessage("(bye)")
		self.sock.close()

	#
	# Methods used only by the Controller class
	#

	def sendMessage(self, msg):
		self.sock.sendto(msg, (self.host, self.port))

	def receiveMessage(self):
		data, addr = self.sock.recvfrom(4096)
		self.port = addr[1] #update the port
		return data