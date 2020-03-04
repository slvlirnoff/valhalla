#!/bin/bash
mkdir -p /data/valhalla/osm
rm /data/valhalla/osm/*
cd /data/valhalla/osm
wget -i /data/valhalla/conf/osm_url_list