#include <cstdint>
#include "test.h"
#include "mjolnir/osmnode.h"
#include "mjolnir/pbfgraphparser.h"
#include "midgard/sequence.h"

#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>

#include "baldr/graphconstants.h"
#include "baldr/directededge.h"

using namespace std;
using namespace valhalla::mjolnir;
using namespace valhalla::baldr;

namespace {

const std::string config_file = "test/test_config_ut";

const auto node_predicate = [](const OSMWayNode& a, const OSMWayNode& b) {
  return a.node.osmid < b.node.osmid;
};

OSMNode GetNode(uint64_t node_id, sequence<OSMWayNode>& way_nodes) {
  auto found = way_nodes.find({node_id}, node_predicate);
  if(found == way_nodes.end())
    throw std::runtime_error("Couldn't find node: " + std::to_string(node_id));
  return (*found).node;
}

auto way_predicate = [](const OSMWay& a, const OSMWay& b){
  return a.osmwayid_ < b.osmwayid_;
};

OSMWay GetWay(uint64_t way_id, sequence<OSMWay>& ways) {
  auto found = ways.find({way_id}, way_predicate);
  if(found == ways.end())
    throw std::runtime_error("Couldn't find way: " + std::to_string(way_id));
  return *found;
}


void Bike(const std::string& config_file) {
  boost::property_tree::ptree conf;
  boost::property_tree::json_parser::read_json(config_file, conf);

  std::string ways_file = "test_ways_utrecht.bin";
  std::string way_nodes_file = "test_way_nodes_utrecht.bin";
  std::string access_file = "test_access_utrecht.bin";
  std::string restriction_file = "test_complex_restrictions_utrecht.bin";

  auto osmdata = PBFGraphParser::Parse(conf.get_child("mjolnir"), {"test/data/utrecht_netherlands.osm.pbf"}, ways_file,
                                       way_nodes_file, access_file, restriction_file);
  sequence<OSMWay> ways(ways_file, false);
  ways.sort(way_predicate);

  auto way = GetWay(127361688, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != true || way.bike_backward() != true || way.bus_backward() != true) {
    throw std::runtime_error("Access is not correct for way 127361688.");
  }

  way = GetWay(7062008, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 7062008.");
  }

  way = GetWay(48672084, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 48672084.");
  }

  way = GetWay(7053107, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 7053107.");
  }

  way = GetWay(7053048, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 7053048.");
  }

  way = GetWay(221051138, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != false || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 221051138.");
  }

  way = GetWay(23544607, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != true || way.bike_backward() != true || way.bus_backward() != true) {
    throw std::runtime_error("Access is not correct for way 23544607.");
  }

  way = GetWay(221051142, ways);
  if (way.auto_forward() != false || way.bus_forward() != false || way.bike_forward() != true || way.pedestrian() != false ||
      way.auto_backward() != false || way.bike_backward() != false || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 221051142.");
  }

  way = GetWay(72906238, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 72906238.");
  }

  way = GetWay(7010549, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 7010549.");
  }

  way = GetWay(7007629, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != false) {
    throw std::runtime_error("Access is not correct for way 7007629.");
  }

  boost::filesystem::remove(ways_file);
  boost::filesystem::remove(way_nodes_file);
  boost::filesystem::remove(access_file);
}

void Bus(const std::string& config_file) {
  boost::property_tree::ptree conf;
  boost::property_tree::json_parser::read_json(config_file, conf);

  std::string ways_file = "test_ways_utrecht.bin";
  std::string way_nodes_file = "test_way_nodes_utrecht.bin";
  std::string access_file = "test_access_utrecht.bin";
  std::string restriction_file = "test_complex_restrictions_utrecht.bin";

  auto osmdata = PBFGraphParser::Parse(conf.get_child("mjolnir"), {"test/data/utrecht_netherlands.osm.pbf"},
                                       ways_file, way_nodes_file, access_file, restriction_file);
  sequence<OSMWay> ways(ways_file, false);
  ways.sort(way_predicate);

  auto way = GetWay(33648196, ways);
  if (way.auto_forward() != true || way.bus_forward() != true || way.bike_forward() != true || way.pedestrian() != true ||
      way.auto_backward() != false || way.bike_backward() != true || way.bus_backward() != true) {
    throw std::runtime_error("Access is not correct for way 33648196.");
  }

  boost::filesystem::remove(ways_file);
  boost::filesystem::remove(way_nodes_file);
  boost::filesystem::remove(access_file);
}

void TestBike() {
  //write the tiles with it
  Bike(config_file);
}

void TestBus() {
  //write the tiles with it
  Bus(config_file);
}

void DoConfig() {
  std::ofstream file;
  try {
    file.open(config_file, std::ios_base::trunc);
    file << "{ \
      \"mjolnir\": { \
      \"tile_dir\": \"test/data/parser_tiles\" \
      } \
    }";
  }
  catch(...) {

  }
  file.close();
}

}

int main() {

  test::suite suite("utrecht");

  suite.test(TEST_CASE(DoConfig));
  suite.test(TEST_CASE(TestBike));
  suite.test(TEST_CASE(TestBus));

  return suite.tear_down();
}
