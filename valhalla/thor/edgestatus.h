#ifndef VALHALLA_THOR_EDGESTATUS_H_
#define VALHALLA_THOR_EDGESTATUS_H_

#include <unordered_map>
#include <valhalla/baldr/graphid.h>

namespace valhalla {
namespace thor {

// Default size to reserve for the EdgeStatus unordered map
constexpr uint32_t kDefaultEdgeStatusSize = 2000000;

//-------------------------------- Edge states -----------------------------//

// Unreached - not yet encountered in search
constexpr uint32_t kUnreached = 0;

// Permanent - shortest path to this edge has been found
constexpr uint32_t kPermanent = 1;

// Temporary - edge has been encountered but there could still be a shorter
// path to this edge. This edge will be "adjacent" to an edge that is
// permanently labeled.
constexpr uint32_t kTemporary = 2;

// Store the edge label state and its index within the EdgeLabels list
struct EdgeState {
  uint32_t state : 4;
  uint32_t index : 28;

  EdgeState() {
    state = kUnreached;
    index = 0;
  }

  EdgeState(const uint32_t s, const uint32_t idx) {
    state = s;
    index = idx;
  }
};

/**
 * Class to define / lookup the state and index of an edge in the edge label
 * list during shortest path algorithms.
 */
class EdgeStatus {
 public:
  /**
   * Resize the EdgeStatus map to the specified size.
   */
  void resize(const uint32_t sz = kDefaultEdgeStatusSize) {
    edgestatus_.reserve(sz);
  }

  /**
   * Clear the edge status map. Initializes the state to unreached
   * for all edges.
   */
  void clear() {
    edgestatus_.clear();
  }

  /**
   * Set the status of a directed edge given its GraphId.
   * @param  edgeid   GraphId of the directed edge to set.
   * @param  state    Label state for this directed edge.
   * @param  index    Index of the edge label.
   */
  void set(const baldr::GraphId& edgeid, const uint32_t state,
           const uint32_t index) {
    edgestatus_[edgeid.value] = { state, index };
  }

  /**
   * Update the status of a directed edge given its GraphId.
   * @param  edgeid   GraphId of the directed edge to set.
   * @param  state      Label state for this directed edge.
   */
  void update(const baldr::GraphId& edgeid, const uint32_t state) {
    edgestatus_[edgeid.value].state = state;
  }

  /**
   * Get the status info of a directed edge given its GraphId.
   * @param   edgeid  GraphId of the directed edge.
   * @return  Returns edge status info.
   */
  EdgeState get(const baldr::GraphId& edgeid) const {
    auto p = edgestatus_.find(edgeid.value);
    return (p == edgestatus_.end()) ? EdgeState() : p->second;
  }

  uint32_t bucket_count() { return edgestatus_.bucket_count(); }

 private:
  // Map to store the state and index of GraphIds that have been encountered.
  // Any unreached edges are not added to the map.
  std::unordered_map<uint64_t, EdgeState> edgestatus_;
};

}
}

#endif  // VALHALLA_THOR_EDGESTATUS_H_
