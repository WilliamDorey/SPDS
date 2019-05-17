#!/bin/bash
# This is a script to stop the motion_camera.py script,
# send the pictures to the webserver, send a current
# image, clean up the sent pictures to make space and then
# restart the motion_camera.py script again

# Located on Raspberry Pi Zero W

# This script is triggered every 10 minutes by crontabs

# stop the previous motion_camera.py
sudo kill $(pgrep 'python')

# Transfer images to server
scp -r /home/pi/archive/* pi@server:/home/pi/archive_temp/
ssh pi@server sudo rsync -av /home/pi/archive_temp/* /var/www/html/archive/
ssh pi@server sudo rm -r /home/pi/archive_temp/*

# grad an image of the location and send it to the webserver
sudo python3 live.py
scp /home/pi/live.jpg pi@server:/home/pi/archive_temp/
ssh pi@server sudo cp /home/pi/archive_temp/live.jpg /var/www/html/archive/live.jpg
ssh pi@server sudo rm /home/pi/archive_temp/live.jpg

# Remove images and restart motion_camera.py
sudo rm -r /home/pi/archive/*
sudo python3 /home/pi/motion_camera.py&
