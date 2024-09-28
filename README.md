# hsv_check
An image hsv_checking package for ros2 and qt, and tested in ros2 humble.
feel free to use when checking the binary values.

Configurations:
- Ubunt 22.04
- Ros2 Humble
- qt5

reference:
- this package subscribes image with sensor_msgs/msg/Image.
- change topic name and msg type Depending on the image format your camera supports.
- each row of sliding bar means h, s, v in order.
- left side of sliding bar is low value, right side of sliding bar means high value.
- current sliding bar value is checked in the terminal window, with order of h_low, h_high, s_low, s_high, v_low, v_high.


# how to build

```bash
colcon build
```

# how to use
Make sure you have sourced your workspace, connect your camera node and then run in terminal:

```bash
cd <your_workspace>
source install/setup.bash
ros2 run hsv_check hsv_check
```
