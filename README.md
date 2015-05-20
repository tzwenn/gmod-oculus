# GMod-Oculus

Very basic Oculus Rift support for Garry's Mod. In case lauching it with `-vr` just freezes or crashes your GMod application.

Tested on OS X 10.9, Oculus SDK 0.5.0.1-beta, a Rift DK1 and Garry's Mod 13.

## Usage

You need the Oculus SDK 0.4 or later installed to `/opt/LibOVR`, than use CMake to configure and compile the program. Upon `make install` all dependencies will be put in your local Steam installation.

Connect the Oculus Rift and start a new game.
In your Spawn Menu choose **Post Process** and under **Effects** activate **Oculus Rift Support**. You can recenter the sensor on the current player's view by clicking **Reset Orientation**.

![activation](http://i.imgur.com/dxRy2ii.png)

## Context

This tool is part of the CHI15 publication [Level-Ups: Motorized Stilts that Simulate Stair Steps in Virtual Reality](http://hpi.de/baudisch/projects/motorized-stilts-that-simulate-stair-steps-in-virtual-reality.html).