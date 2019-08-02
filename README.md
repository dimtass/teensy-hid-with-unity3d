Controlling a 3D object in Unity3D with Teensy and MPU-6050
----

This repo is part this blog post here:

[https://www.stupid-projects.com/controlling-a-3d-object-in-unity3d-with-teensy-and-mpu-6050/](https://www.stupid-projects.com/controlling-a-3d-object-in-unity3d-with-teensy-and-mpu-6050/)

You might need to read also the blog post to use this repo.

## Prerequisites
This project is meant to be run on a Linux machine. The only reason that there's
that limitation is because the `HID manager` is written for Linux only (see more
about the `HID manager` later in this file)

## Connections
To connect the MPU-6050 to the Teensy 3.2 use this table

Teensy 3.2 (pin) | MPU-6050
- | -
3V | VCC
GND | GND
18 | SDA
19 | SCL
23 | INT

> Note: You can use any Teensy that supports [RawHID](https://www.pjrc.com/teensy/rawhid.html)

## Needed libraries
You need the I2Cdev and MPU6050 libraries from this repo [here](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/).
To install them, just copy the `I2Cdev` and `MPU6050` fodlers from the repo in
you Arduino library folder.

## Calibration

The easiest way to calibrate the MPU is use the
`mpu6050-calibration/mpu6050-raw-calibration/mpu6050-raw-calibration.ino`
firmware. When you flash this firmware then it will automatically find
the calibration values, which you need to set later in the
`teensy-motion-hid/teensy-motion-hid.ino`.

For better accuracy you can change the `ACCELEROMETER_TOLERANCE` in the source cide
and set it to a smaller number. Be aware that if you use a smaller number, though,
then the algorithm may fail to obtain the calibration values. This is the code
line you need to change.

```cpp
const int ACCELEROMETER_TOLERANCE = 8;
```

When you get the values you just need to replace them 

> Note: Before you start the calibration you need to leave the module powered
on for a few minutes in order for the temperature to stabilize.

> Note: for the other calibration source code and the jupyter notepad
have a look at the [blog post](https://www.stupid-projects.com/controlling-a-3d-object-in-unity3d-with-teensy-and-mpu-6050/).


## HID manager
The `HID manager` is the software that receives the HID raw messages from Teensy
and then copies the data in to a buffer that is shared with Unity. You could
port this code to Windows. Sadly, I'm not having any Windows installed to do this.

To buid the manager:
```sh
cd hid_manager/Makefile
make
```

To run the manager:
```sh
./start.sh
```

The above script will handle the creation of the shared memory buffer in `/tmp`.

## Unity on Ubuntu
To install unity on my Ubuntu I had first to create an account and then install
Unity and Unity Hub. I've downloaded Unity from [here](https://forum.unity.com/threads/unity-on-linux-release-notes-and-known-issues.350256/page-2)
and to install Unity Hub I've followed the instructions
[here](https://www.techrepublic.com/article/how-to-install-the-unity-editor-on-linux/)

A
```sh
sudo apt install libgtk2.0-0 libsoup2.4-1 libarchive13 libpng16-16 libgconf-2-4 lib32stdc++6 libcanberra-gtk-module
wget http://beta.unity3d.com/download/292b93d75a2c/UnitySetup-2019.1.0f2
chmod +x UnitySetup-2019.1.0f2
wget https://public-cdn.cloud.unity3d.com/hub/prod/UnityHubSetup.AppImage
chmod +x UnityHubSetup.AppImage
./UnityHubSetup.AppImage
```

## Arduino versions
The Arduino source codes were tested on version 1.8.9

## Resources
These are some relative resources regarding the project:

* [I2Cdev and MPU6050 for Arduino](https://github.com/jrowberg/i2cdevlib)
* [mpu6050-raw-calibration](https://github.com/melikabarzegaran/mpu6050-raw-calibration)
* [MPU6050-PID-Calibration](https://github.com/thisisG/MPU6050-PID-Calibration)
* [MPU-6050](https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/)
* [Roll, Pitch, and Yaw](https://howthingsfly.si.edu/flight-dynamics/roll-pitch-and-yaw)
* [Visualizing quaternions](https://eater.net/quaternions/)

## Author
Dimitris Tassopoulos <dimtass@gmail.com>