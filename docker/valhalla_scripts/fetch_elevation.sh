#!/bin/bash
mkdir -p /data/valhalla/elevation

apt-get update
apt-get install curl -y

# Eu elevation bounding box (39GB)
valhalla_build_elevation -10.63 40.87 27.01 71.6 /data/valhalla/elevation 32

# Us (+most of CA) elevation bounding box (50GB)
#valhalla_build_elevation -128.67 -64.51 22.8 52.32 /data/valhalla/elevation 32

# mexico
#valhalla_build_elevation -118.6 -64.2 1.5 34.2  /data/valhalla/elevation 32

# south america
#valhalla_build_elevation -82.3 -34.5 -55.9 13.2  /data/valhalla/elevation 32

