#!/bin/bash

# Set parameters needed for rosrun cmvision cmvision image:=</image/topic> command


# make sure to source your workspace
source ../../devel/setup.bash

# set params
rosparam set /cmvision/color_file /home/turtlebot/squirtlebot_ws/src/cmvision/colors.txt
rosparam set /cmvision/mean_shift_on false
rosparam set /cmvision/debug_on false
rosparam set /cmvision/spatial_radius_pix 0
rosparam set /cmvision/color_radius_pix 0
