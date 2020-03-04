#!/bin/bash
valhalla_build_tiles -c /conf/valhalla.json /data/valhalla/osm/*.osm.pbf
find /data/valhalla/tiles | sort -n | tar cf /data/valhalla/tiles.tar --no-recursion -T -
