# This script was made using information from the following web address: 
# https://randomnerdtutorials.com/raspberry-pi-motion-detector-photo-capture/

# Python script to passively monitor a motion sensor that
# will take a picture using the Pi Camera and label the image
# with the date and time

# Located on Raspberry Pi Zero W

# Importing the required library elements
from time     import sleep
from gpiozero import MotionSensor
from picamera import PiCamera
from signal   import pause
import os
import datetime

# Defining the different resources that are used
camera = PiCamera()
sensor = MotionSensor(18)
count = 0

# Initializing the camera
camera.resolution = (1024, 768)
camera.rotation = 90
camera.start_preview()
sleep(2)

# Wait for the motion sensor to finish powering on
sleep(1)
print("ready")

# A function to take a picture and appropriately store it
# with the date and time
def take_pic():
  print("MOTION!")
  date = datetime.datetime.now()
  day  = date.strftime("%d-%m-%Y")
  time = date.strftime("%H:%M:%S")
  try:
    os.mkdir("/home/pi/archive/{}".format(day))
  except FileExistsError :
    pass
  file_location = "/home/pi/archive/{}/{}.jpg".format(day, time)
  camera.capture(file_location)

# When the sensor detects motion, it will call the function
# to take a picture
sensor.when_motion = take_pic

pause()
