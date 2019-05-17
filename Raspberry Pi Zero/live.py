# Basic python script to take a picture
#
# Located on Pi Zero
from picamera import PiCamera

camera = PiCamera()

camera.capture('/home/pi/live.jpg')
