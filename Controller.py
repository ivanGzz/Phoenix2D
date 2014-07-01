import socket
import re

class Controller:

	ctype = "p"
	host = "localhost"
	port = 6000
	server = ""
	player = ""
	player_types = []

	#
	# Constructor
	#

	def __init__(self, c_type = "p"):
		self.ctype = c_type
		if self.ctype == "t":
			self.port = 6001
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	#
	# Connect method
	# only needs the host where the trainer will connect
	# and initialize all the necessary information with
	# the data received from the server
	#

	def connect(self, host = "localhost", team = "phoenix"):
		self.host = host
		if self.ctype == "t":
			self.sendMessage("(init (version 15.0))")
		else:
			self.sendMessage("(init " + team + " (version 15.0))")
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
		if self.ctype == "t":
			self.sendMessage("(eye on)")
		else:
			self.sendMessage("(synch_see)")
		print self.receiveMessage()

	#
	# Returns the current game time
	# it is a blocking method which waits until a see_global or
	# sense_body message is received. In consequence, some 
	# messages could get lost

	def cycle(self):
		regex = "\\(see_global\\s(\\d+)\\s"
		if self.ctype == "p":
			regex = "\\(sense_body\\s(\\d+)\\s"
		m = re.search(regex, self.receiveMessage())
		while m != None:
			m = re.search(regex, self.receiveMessage())
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
		msg = msg + '\0'
		self.sock.sendto(msg, (self.host, self.port))

	def receiveMessage(self):
		data, addr = self.sock.recvfrom(4096)
		self.port = addr[1] #update the port
		return data