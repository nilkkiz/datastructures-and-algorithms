// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <unordered_map>
#include <memory>
#include <functional>
#include <set>
#include <cmath>
#include <math.h>
#include <queue>
#include <map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <string.h>
#include <random>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <array>
#include <list>

// Types for IDs
using StopID = long int;
using RegionID = std::string;
using RouteID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
RouteID const NO_ROUTE = "!!NO_ROUTE!!";
StopID const NO_STOP = -1;
RegionID const NO_REGION = "!!NO_REGION!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for time of day in minutes from midnight (i.e., 60*hours + minutes)
using Time = int;

// Return value for cases where color was not found
Time const NO_TIME = std::numeric_limits<Time>::min();

// Type for a duration of time (in minutes)
using Duration = int;

// Return value for cases where Duration is unknown
Duration const NO_DURATION = NO_VALUE;

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;

// PRG2 IMPLEMETATION BELOW ######

struct Node;

struct Edge {
    std::shared_ptr<Node> source;
    std::shared_ptr<Node> destination;
    Distance distance = NO_DISTANCE;
    RouteID route = NO_ROUTE;
};

struct RouteStopInfo {
    StopID stop = NO_STOP;
    std::shared_ptr<Node> node;
    std::deque<Time> times;
};

struct Node {
    StopID stopID = NO_STOP;
    Coord coordinate = NO_COORD;
    std::vector<std::shared_ptr<Edge>> edges;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Basicly there's only if-clause
    // and size function in unordered_map is O(1).
    int stop_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Basicly it goes throught
    // every element in containers and clear them.
    // This method is not tested in performance tests
    // so I haven't even tried to optimize it.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: First we check if
    // the container is empty, so we don't need to extra work.
    // ".empty()" for map is O(1) and transform algorithm is O(n).
    // NOT TESTED IN PERFORMANCE TESTS
    std::vector<StopID> all_stops();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Finding a item in unordered map
    // is O(1), but it could be O(n), if
    // every element is in same bucket. Push_back to vector is O(1).
    bool add_stop(StopID id, Name const& name, Coord xy);

    // Estimate of performance: θ(1) but sometimes O(n)
    // Short rationale for estimate: Because find method is O(1) in best case,
    // and in worst case it's O(n).
    Name get_stop_name(StopID id);

    // Estimate of performance: θ(1) but sometimes O(n)
    // Short rationale for estimate: Because find method is O(1) in best case,
    // and in worst case it's O(n).
    Coord get_stop_coord(StopID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log n), best O(n).
    // Short rationale for estimate: Check if container is empty is O(1),
    // random_shuffle is O(n) and sort algorithm (n log n). Also
    // for_each algorithm is O(n).
    std::vector<StopID> stops_alphabetically();

    // Estimate of performance: worst O(n log n), best O(n).
    // Short rationale for estimate: Check if container is empty is O(1).
    // If vector is not sorted by coords, it sorts it's and that method is O(n).
    // For_each algorithm is O(n) and push_back to vector O(1).
    std::vector<StopID> stops_coord_order();

    // Estimate of performance: worst O(n log n), best O(1).
    // Short rationale for estimate: Check if container is empty O(1).
    // If stops arent sorted by coords in vector, it sorts them O(n log n).
    StopID min_coord();

    // Estimate of performance: worst O(n log n), best O(1)
    // Short rationale for estimate: Check if container is empty O(1).
    // If stops arent sorted by coords in vector, it sorts them O(n log n).
    StopID max_coord();

    // Estimate of performance: worst O(n log n), best O(n)
    // Short rationale for estimate: Check if container is empty O(1).
    // if stops arent sorted by name in vector O(n log n).
    // While loop is O(n) and push_back is O(1). Also find_if is O(n).
    std::vector<StopID> find_stops(Name const& name);

    // Estimate of performance: worst O(n), best θ(1)
    // Short rationale for estimate: std::find function is the slowest
    // and it has time complexity of θ(1), but the worst case scenario is O(n).
    bool change_stop_name(StopID id, Name const& newname);

    // Estimate of performance: worst O(n), best θ(1)
    // Short rationale for estimate: std::find function is the slowest
    // and it has time complexity of θ(1), but the worst case scenario is O(n
    bool change_stop_coord(StopID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: worst O(n), best θ(1)
    // Short rationale for estimate: std::find algorithm is θ(1) usually
    // but sometimes can be O(n). Inserting to unordered map average is O(1),
    // but can be O(n) at it's worst scenario.
    bool add_region(RegionID id, Name const& name);

    // Estimate of performance: worst O(n), best θ(1)
    // Short rationale for estimate: std::find function is the slowest
    // and it has time complexity of θ(1), but the worst case scenario is O(n).
    // Also, there's no inner loops or any slower actions.
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Checking if container is empty O(1),
    // transform algorithm is O(n). And insert to vector is O(1).
    std::vector<RegionID> all_regions();

    // Estimate of performance: worst O(n), usually θ(1)
    // Short rationale for estimate: std::find is the slowest action
    // in the function and it's time complexity is usually θ(1), but
    // at the worst case scenario is O(n).
    bool add_stop_to_region(StopID id, RegionID parentid);

    // Estimate of performance: worst O(n), usually θ(1)
    // Short rationale for estimate: std::find is the slowest action
    // in the function and it's time complexity is usually θ(1), but
    // at the worst case scenario is O(n).
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Finding element in unordered map
    // is usually O(1) but can be O(n). If region has parent
    // it goes to findRegionParents method, which is O(n log n).
    std::vector<RegionID> stop_regions(StopID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Finding element in unordered map is
    // usually O(1), but can be O(n). If element exists in container
    // it calls findRegionChilds method, which is O(n log n).
    // For_each algorithm is O(n).
    std::pair<Coord, Coord> region_bounding_box(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding element in unordered map is
    // usually O(1), but can be O(n). For_each algorithm is O(n), also
    // the boolean sort operation is O(n) and push_backs into vector O(1).
    std::vector<StopID> stops_closest_to(StopID id);

    // Estimate of performance: Probably O(n^2)
    // Short rationale for estimate: Slowest function, the slowness
    // comes by looping every item in vectors and erasing specific one.
    bool remove_stop(StopID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Finding elements in unordered maps
    // is usually O(1), but can be O(n). Both methods findRegionParentsSecond
    // and findCommonRegion are O(n).
    RegionID stops_common_region(StopID id1, StopID id2);

    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Function checks that routeContainer is not empty, which
    // has time complexity of O(1). The function's slowest operation is for_each algorithm
    // which has time complexity of O(n).
    std::vector<RouteID> all_routes();

    // Estimate of performance: O(n)
    // Short rationale for estimate: There's only one for-loop which has time complexity
    // of O(n). Other operations are O(1) so that's why can say the function is operation
    // with time complexity of O(n)
    bool add_route(RouteID id, std::vector<StopID> stops);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Since the function checks first that the key exists
    // in the container and after it uses for_each algorithm, which is has time complexity
    // of O(n) and find is O(log n), so we can say this function is O(n log n).
    std::vector<std::pair<RouteID, StopID>> routes_from(StopID stopid);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Since the function checks first that the key exists
    // in the container and after it uses for_each algorithm, which is has time complexity
    // of O(n) and find is O(log n), so we can say this function is O(n log n).
    std::vector<StopID> route_stops(RouteID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: First we clear route container, then we use for-loop
    // to go throught every stop in the container. After it we clear every edge in node.
    // clear function has time complexity of O(n) and also for loop has the same time
    // complexity.
    void clear_routes();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: This uses journey_least_stop function.
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_any(StopID fromstop, StopID tostop);

//    // Non-compulsory operations

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Since it's calling for helper ("journey_least_stops_helper")
    // function to solve this problem and that has time complexity of O(n^2).
    // We can come to that conclusion that this has performance of O(n^2), because
    // the main function is faster than the helper function.
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_least_stops(StopID fromstop, StopID tostop);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: This function is calling for helper function
    // ("journey_with_cycle_helper"), which is recursive, but it has time complexity of O(n^2).
    // This function has only one for loop, which has time complexity of O(n), but they are not
    // inner loops. So we can say function has time complexity of O(n^2).
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_with_cycle(StopID fromstop);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: This function has while-loop and for-loop inside of it.
    // Because there is inner loop and both has time complexity of O(n) it becomes O(n^2).
    // Helper function ("journey_shortest_distance_helper") has time complexity of O(n).
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_shortest_distance(StopID fromstop, StopID tostop);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: First we find if route-id exist, which has time complexity
    // of O(n log), then we use for-loop, which has time complexity of O(n). So overall it becomes
    // O(n log n).
    bool add_trip(RouteID routeid, const std::vector<Time> &stop_times);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: The function checks if route-id exists O(log n).
    // If it exists it uses for-loop O(n) and then uses .at() for deque (n).
    // So over all the time complexity is O(n^2)
    std::vector<std::pair<Time, Duration> > route_times_from(RouteID routeid, StopID stopid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Time>> journey_earliest_arrival(StopID fromstop, StopID tostop, Time starttime);

    // Estimate of performance:
    // Short rationale for estimate:
    void add_walking_connections(); // Note! This method is completely optional, and not part of any testing

private:

    // Estimate of performance: O(1)
    // Nothing special about this, casual math
    double twoPointDistance(Coord coord1, Coord coord2);

    // Estimate of performance: O(n)
    // Find method is usually O(1), but can be O(n).
    // Because method uses recursion it's O(n).
    void findRegionParents(RegionID region, std::vector<RegionID> &regions);

    // Estimate of performance: O(n)
    // Find method is usually O(1), but can be O(n).
    // Because method uses recursion it's O(n).
    void findRegionParentsSecond(RegionID region, std::vector<RegionID> &regions);

    // Estimate of performance: O(n)
    // Find method is usually O(1), but can be O(n).
    // Because method uses recursion it's O(n). And for loop is O(n).
    void findRegionChilds(RegionID region, std::vector<RegionID> &regions);

    // Estimate of performance: O(1)
    // Vectors intersection find is O(1) and push_back is O(1).
    RegionID findCommonRegion(const std::vector<RegionID> &regions1, const std::vector<RegionID> &regions2);

    // Estimate of performance: O(n log n)
    // random_shuffle O(n) and sort algorithm O(n log n).
    void sortStopsByCoord();

    void sortStopsByName();

    int getDistanceBetweenTwoStops(Coord source, Coord destination);

    bool journey_least_stops_helper(StopID source, StopID destination, std::unordered_map<StopID, Edge*> &pred);

    bool journey_with_cycle_helper(std::shared_ptr<Node> current, std::unordered_map<StopID, bool> &visited, std::unordered_map<StopID, bool> &stack,
                                   std::vector<std::tuple<StopID, RouteID, Distance>> &route, RouteID routeid = NO_ROUTE, Distance dist = 0);

    std::vector<std::tuple<StopID, RouteID, Distance>> journey_shortest_distance_helper(std::unordered_map<StopID, Edge*> &pred, StopID destination);

    //bool journey_earliest_arrival(StopID source, StopID destination, std::unordered_map<StopID, Edge*>)

    struct RegionStructure
    {
        Name name = NO_NAME;
        std::shared_ptr<RegionID> parent;
        std::set<std::shared_ptr<RegionID>> children;
    };

    struct StopStructure
    {
        Name name = NO_NAME;
        Coord coordinate;
        std::shared_ptr<RegionID> region;
    };

    struct CompareDistance
    {
        bool operator()(const std::pair<Coord, StopID>&itemOne, const std::pair<Coord, StopID>& itemTwo) const {
            double itemOneDistance = sqrt(pow(itemOne.first.x, 2) + pow(itemOne.first.y,2));
            double itemTwoDistance = sqrt(pow(itemTwo.first.x, 2) + pow(itemTwo.first.y,2));
            if(itemOneDistance < itemTwoDistance){
                return true;
            } else if(itemOneDistance > itemTwoDistance){
                return false;
            } else {
                if(itemOne.first.y < itemTwo.first.y){
                    return true;
                } else if(itemOne.first.y > itemTwo.first.y){
                    return false;
                } else {
                    return true;
                }
            }
        }
    };

    struct CompareClosest
    {
        bool operator()(const std::pair<StopID, std::pair<Coord, double>>&itemOne, const std::pair<StopID, std::pair<Coord, double>>& itemTwo) const {
            if(itemOne.second.second < itemTwo.second.second){
                return true;
            } else if(itemOne.second.second > itemTwo.second.second){
                return false;
            } else {
                if(itemOne.second.first.y < itemTwo.second.first.y){
                    return true;
                } else if(itemOne.second.first.y > itemTwo.second.first.y){
                    return false;
                } else {
                    return true;
                }
            }
        }
    };

    std::unordered_map<RegionID, RegionStructure> m_regionContainer;
    std::unordered_map<StopID, StopStructure> m_container;
    std::vector<std::pair<Coord, StopID>> m_sortedStopsByCoord;
    std::vector<std::pair<Name, StopID>> m_sortedStopsByName;
    bool m_isSortedStopsByCoord = false;
    bool m_isSortedStopsByName = false;

    // ######### PRG2 IMPLEMENTATION BELOW ###########
    std::unordered_map<RouteID, std::deque<RouteStopInfo>> m_routeContainer;
    std::unordered_map<StopID, std::shared_ptr<Node>> m_graph;
};

#endif // DATASTRUCTURES_HH
