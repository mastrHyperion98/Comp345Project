//
// Created by hyperion on 2020-02-27.
//

#include "ResourceCalculator.h"
#include "../src/GBMap.h"
#include "../src/Square.h"
#include "../src/Resources.h"
#include <map>
#include <deque>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"

ResourceCalculator::ResourceCalculator() {

}
ResourceCalculator::~ResourceCalculator() = default;
int* ResourceCalculator::computeResources(ResourceTrails trail) {
    // setup -- first step is to add the elements of the main root to the total for each resources
    int *resources = {new int[4]};
    deque<vertex_t> root_queue;
    deque<vertex_t> next_e_queue;
    map<vertex_t, Quad> map;
    int num_vertices = boost::num_vertices(trail);
    auto vertices = trail.vertex_set();
    vertex_t root = vertices[0];
    // Add the starting resources from the root to the count?
    next_e_queue.push_back(root);
    /*
     * Now this is where the real fun begins
     */
    while(!next_e_queue.empty()){
        // this means we are the root so we add all our resources to the count
        vertex_t next_element = next_e_queue.front();
        ResourceTypes *tile = trail[next_element].getTile().getTileContent();
        if(root_queue.empty()){
            for(int i = 0; i < 4; i++){
               addResources(resources, tile[i]);
            }
            Quad quad;
            for(int i= 0; i < 4; i++) {
                quad.isMatching[i] = true;
            }
            *quad.current_visit_count = *quad.current_visit_count + 1;
            map.insert(pair<vertex_t, Quad>(next_element, quad));
        }
        // otherwise their is a defined root
        else{
            bool exist = false;
            root = root_queue.front();
            /*
             * Now the more complicate part starts
             * We need to compute adjacency connection between root and neighbour.
             *  first we determine direction
             */

            int direction = trail[root].getPosition() - trail[next_element].getPosition();
            if(direction == *DOWN){
                // compare index 2 of root to index 0 of next element
                Quad next_quad;
                if(map.find(next_element) == map.end()) {
                    next_quad = map[next_element];
                    exist = true;
                }
                ResourceTypes *root_resources = trail[root].getTile().getTileContent();
                ResourceTypes *next_resources = trail[next_element].getTile().getTileContent();
                if(root_resources[2] == next_resources[0] && !next_quad.isMatching[0]){
                    next_quad.isMatching[0] = true;
                    addResources(resources, next_resources[0]);
                }
                if(root_resources[3] == next_resources[1] && !next_quad.isMatching[1]){
                    next_quad.isMatching[1] = true;
                    addResources(resources, next_resources[1]);
                }
                /*
                 * Now we need to check within the element itself if other of its own nodes connect
                 */
                setQuadInner(resources,next_quad, next_resources);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
            else if(direction == *UP){
                // compare index 2 of root to index 0 of next element
                Quad next_quad;
                if(map.find(next_element) == map.end()) {
                    next_quad = map[next_element];
                    exist = true;
                }
                ResourceTypes *root_resources = trail[root].getTile().getTileContent();
                ResourceTypes *next_resources = trail[next_element].getTile().getTileContent();
                if(root_resources[0] == next_resources[2] && !next_quad.isMatching[2]){
                    next_quad.isMatching[2] = true;
                    addResources(resources, next_resources[2]);
                }
                if(root_resources[1] == next_resources[3] && !next_quad.isMatching[3]){
                    next_quad.isMatching[3] = true;
                    addResources(resources, next_resources[3]);
                }
                /*
                 * Now we need to check within the element itself if other of its own nodes connect
                 */
                setQuadInner(resources,next_quad, next_resources);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
            else if(direction == *LEFT){
                // compare index 2 of root to index 0 of next element
                Quad next_quad;
                if(map.find(next_element) == map.end()) {
                    next_quad = map[next_element];
                    exist = true;
                }
                ResourceTypes *root_resources = trail[root].getTile().getTileContent();
                ResourceTypes *next_resources = trail[next_element].getTile().getTileContent();
                if(root_resources[0] == next_resources[1] && !next_quad.isMatching[1]){
                    next_quad.isMatching[1] = true;
                    addResources(resources, next_resources[1]);
                }
                if(root_resources[2] == next_resources[3] && !next_quad.isMatching[3]){
                    next_quad.isMatching[3] = true;
                    addResources(resources, next_resources[3]);
                }
                /*
                 * Now we need to check within the element itself if other of its own nodes connect
                 */
                setQuadInner(resources,next_quad, next_resources);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
            else if(direction == *RIGHT){
                // compare index 2 of root to index 0 of next element
                Quad next_quad;
                if(map.find(next_element) == map.end()) {
                    next_quad = map[next_element];
                    exist = true;
                }
                ResourceTypes *root_resources = trail[root].getTile().getTileContent();
                ResourceTypes *next_resources = trail[next_element].getTile().getTileContent();
                if(root_resources[1] == next_resources[0] && !next_quad.isMatching[0]){
                    next_quad.isMatching[0] = true;
                    addResources(resources, next_resources[0]);
                }
                if(root_resources[3] == next_resources[2] && !next_quad.isMatching[2]){
                    next_quad.isMatching[2] = true;
                    addResources(resources, next_resources[2]);
                }
                /*
                 * Now we need to check within the element itself if other of its own nodes connect
                 */
                setQuadInner(resources,next_quad, next_resources);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
        }
        // now we build the queues
        ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;
        tie(neighbourIt, neighbourEnd) = adjacent_vertices(next_element, trail);
        for (; neighbourIt != neighbourEnd; ++neighbourIt) {
            // get ourselves our vertex
            vertex_t vertex = vertices[*neighbourIt];
            // check if the quad for said vertex exists if it does verify count
            if(map.find(next_element) == map.end()) {
               Quad next_quad = map[next_element];
               if(*next_quad.current_visit_count <= *next_quad.MAX_VISIT)
                   next_e_queue.push_back(vertex);
            }
            // not yet defined push to queue
            else{
                next_e_queue.push_back(vertex);
            }
        }
        next_e_queue.pop_front();
        root_queue.pop_front();
        root_queue.push_back(next_element);
    }
    return resources;
}
// compute Inner
inline void ResourceCalculator::setQuadInner(int *arr, Quad quad, ResourceTypes* resource){
    /*
     * check if 0 and 2 matches, 0 and 1, 1 and 3 and 3 and 2 in that order
     */
    // i know a lot of conditional checks but we cant avoid that
    if(resource[0] == resource[1]&& quad.isMatching[0]&& !quad.isMatching[1]) {
        quad.isMatching[1] = true;
        addResources(arr, resource[0]);
    }
    if(resource[1] == resource[3] && quad.isMatching[1] && !quad.isMatching[3]) {
        quad.isMatching[3] = true;
        addResources(arr, resource[1]);
    }
    if(resource[1] == resource[0] && quad.isMatching[1] && !quad.isMatching[0]) {
        quad.isMatching[0] = true;
        addResources(arr, resource[1]);
    }
    if(resource[3] == resource[1] && quad.isMatching[3] && !quad.isMatching[1]) {
        quad.isMatching[1] = true;
        addResources(arr, resource[3]);
    }
    if(resource[0] == resource[2]&& quad.isMatching[0]&& !quad.isMatching[2]) {
        quad.isMatching[2] = true;
        addResources(arr, resource[0]);
    }
    if(resource[2] == resource[0]&& quad.isMatching[2]&& !quad.isMatching[0]) {
        quad.isMatching[0] = true;
        addResources(arr, resource[2]);
    }
    if(resource[2] == resource[3]&& quad.isMatching[2]&& !quad.isMatching[3]) {
        quad.isMatching[3] = true;
        addResources(arr, resource[2]);
    }
    if(resource[3] == resource[2]&& quad.isMatching[3]&& !quad.isMatching[2]) {
        quad.isMatching[2] = true;
        addResources(arr, resource[3]);
    }
}

inline void ResourceCalculator::addResources(int *arr, ResourceTypes type){
    if(type == ResourceTypes::WHEAT)
       arr[*WHEAT] =  arr[*WHEAT] + 1;
    else if(type == ResourceTypes::SHEEP)
        arr[*SHEEP] =  arr[*SHEEP] + 1;
    else if(type == ResourceTypes::STONE)
        arr[*STONE] =  arr[*STONE] + 1;
    else
        arr[*WOOD] =  arr[*WOOD] + 1;
}