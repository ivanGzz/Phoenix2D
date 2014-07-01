from Controller import *

#
# The controller is created and connected to localhost
#
c = Controller()
c.connect("127.0.0.1")
#
# Wait for the server to start sending the see sensor
#
time = c.cycle()
#
# Change the current play mode to play_on
#
c.changeTo("play_on")
#
# Iterate all over the game
#
while time < 6000:
	#
	# Wait the new cycle
	#
	time = c.cycle();
#
# The controller disconnects
#
c.disconnect()