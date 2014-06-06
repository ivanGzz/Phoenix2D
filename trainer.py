from Controller import *

c = Controller()
c.connect("127.0.0.1")
time = c.cycle()
c.changeTo("play_on")
while time < 6000:
	time = c.cycle();
c.disconnect()