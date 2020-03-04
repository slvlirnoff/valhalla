#!/bin/bash
cd /valhalla_scripts

valhalla_build_admins --config /conf/valhalla.json /data/valhalla/osm/*.osm.pbf

