# Get latest version of the image
docker-compose pull

# Download OSM data files, as configured in data/conf/osm_url_list
docker-compose run update_osm

# Download elevation information
docker-compose run fetch_elevation

# Download timezone information
docker-compose run fetch_timezones

# Build admin information (ideally should download planet OSM for this)
docker-compose run build_admins

# Download transit information
docker-compose run fetch_transit

# Build car graph
docker-compose run build_tiles


# Update

# (Re)-Download transit information
docker-compose run fetch_transit

# (Re)-Build car graph when transit fetched
docker-compose run build_tiles



# Running the service
docker-compose up valhalla -d
