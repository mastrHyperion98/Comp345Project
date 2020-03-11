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
    resources[0] = 0;
    resources[1] = 0;
    resources[2] = 0;
    resources[3] = 0;
    deque<vertex_t> queue;
    map<vertex_t, Quad> map;
    int num_vertices = boost::num_vertices(trail);
    auto vertices = trail.vertex_set();
    vertex_t root = vertices[0];
    // Add the starting resources from the root to the count?
    queue.push_back(root);
    ResourceTypes *r_resources = (*trail[root].getTile()).getTileContent();
    Quad quad;
            for(int i = 0; i < 4; i++){
               ResourceTypes resource = r_resources[i];
               addResources(resources, resource);
                quad.isMatching[i] = true;
            }
            *quad.current_visit_count = *quad.current_visit_count + 1;
            map.insert(pair<vertex_t, Quad>(root, quad));
    // delete r_resources
    delete r_resources;

    while(!queue.empty()){
        root = queue.front();
        // now we build the queues
        ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;
        tie(neighbourIt, neighbourEnd) = adjacent_vertices(root, trail);
        ResourceTypes *root_resources = (*trail[root].getTile()).getTileContent();
        for (; neighbourIt != neighbourEnd; ++neighbourIt) {
            // get ourselves our vertex
            Quad next_quad;
            vertex_t next_element = vertices[*neighbourIt];
            ResourceTypes *next_resources = (*trail[next_element].getTile()).getTileContent();

            int direction = trail[root].getPosition() - trail[next_element].getPosition();
            if(direction == *DOWN){
                // compare index 2 of root to index 0 of next element
                if(map.find(next_element) != map.end()) {
                    next_quad = map[next_element];
                }
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
                setQuadInner(resources,next_quad, next_resources, direction);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
            else if(direction == *UP){
                // compare index 2 of root to index 0 of next element
                if(map.find(next_element) != map.end()) {
                    next_quad = map[next_element];
                }
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
                setQuadInner(resources,next_quad, next_resources, direction);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
            else if(direction == *LEFT){
                // compare index 2 of root to index 0 of next element
                if(map.find(next_element) != map.end()) {
                    next_quad = map[next_element];
                }
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
                setQuadInner(resources,next_quad, next_resources, direction);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
            }
            else if(direction == *RIGHT){
                // compare index 2 of root to index 0 of next element
                if(map.find(next_element) != map.end()) {
                    next_quad = map[next_element];
                }
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
                setQuadInner(resources,next_quad, next_resources, direction);
                *next_quad.current_visit_count = *next_quad.current_visit_count +1;
                if(*next_quad.current_visit_count <= *next_quad.MAX_VISIT)
                    queue.push_back(next_element);
            }
            // check if the quad for said vertex exists if it does verify count
            if(map.find(next_element) == map.end()) {
                map.insert(pair<vertex_t, Quad>(next_element, next_quad));
            }

            delete next_resources;
        }
        delete root_resources;
        queue.pop_front();
    }
    return resources;
}
// compute Inner
inline void ResourceCalculator::setQuadInner(int *arr, Quad quad, ResourceTypes* resource, int direction){
    /*
     * check if 0 and 2 matches, 0 and 1, 1 and 3 and 3 and 2 in that order
     */
    // i know a lot of conditional checks but we cant avoid that
    if(direction == *LEFT){
        if(resource[1] == resource[3] && quad.isMatching[1] && !quad.isMatching[3]) {
            quad.isMatching[3] = true;
            addResources(arr, resource[3]);
        }
        else if(resource[3] == resource[1] && quad.isMatching[3] && !quad.isMatching[1]) {
            quad.isMatching[1] = true;
            addResources(arr, resource[3]);
        }
        if(resource[1] == resource[0] && quad.isMatching[1] && !quad.isMatching[0]) {
            quad.isMatching[0] = true;
            addResources(arr, resource[1]);
        }
        if(resource[0] == resource[2] && quad.isMatching[0]&& !quad.isMatching[2]) {
            quad.isMatching[2] = true;
            addResources(arr, resource[0]);
        }
        if(resource[3] == resource[2]&& quad.isMatching[3]&& !quad.isMatching[2]) {
            quad.isMatching[2] = true;
            addResources(arr, resource[3]);
        }
        if(resource[2] == resource[0]&& quad.isMatching[2]&& !quad.isMatching[0]) {
            quad.isMatching[0] = true;
            addResources(arr, resource[2]);
        }
    }
    else if(direction == *RIGHT){
        if(resource[0] == resource[2] && quad.isMatching[0]&& !quad.isMatching[2]) {
            quad.isMatching[2] = true;
            addResources(arr, resource[0]);
        }
        else if(resource[2] == resource[0]&& quad.isMatching[2]&& !quad.isMatching[0]) {
            quad.isMatching[0] = true;
            addResources(arr, resource[2]);
        }
        if(resource[0] == resource[1]&& quad.isMatching[0]&& !quad.isMatching[1]) {
            quad.isMatching[1] = true;
            addResources(arr, resource[0]);
        }
        if(resource[1] == resource[3] && quad.isMatching[1] && !quad.isMatching[3]) {
            quad.isMatching[3] = true;
            addResources(arr, resource[3]);
        }
        if(resource[2] == resource[3]&& quad.isMatching[2]&& !quad.isMatching[3]) {
            quad.isMatching[3] = true;
            addResources(arr, resource[2]);
        }
        if(resource[3] == resource[1] && quad.isMatching[3] && !quad.isMatching[1]) {
            quad.isMatching[1] = true;
            addResources(arr, resource[3]);
        }
    }
    else if(direction == *UP){
        if(resource[2] == resource[3]&& quad.isMatching[2]&& !quad.isMatching[3]) {
            quad.isMatching[3] = true;
            addResources(arr, resource[2]);
        }
        else if(resource[3] == resource[2]&& quad.isMatching[3]&& !quad.isMatching[2]) {
            quad.isMatching[2] = true;
            addResources(arr, resource[3]);
        }
         if(resource[2] == resource[0]&& quad.isMatching[2]&& !quad.isMatching[0]) {
            quad.isMatching[0] = true;
            addResources(arr, resource[2]);
        }
        if(resource[0] == resource[1]&& quad.isMatching[0]&& !quad.isMatching[1]) {
            quad.isMatching[1] = true;
            addResources(arr, resource[0]);
        }
        if(resource[3] == resource[1] && quad.isMatching[3] && !quad.isMatching[1]) {
            quad.isMatching[1] = true;
            addResources(arr, resource[3]);
        }
        if(resource[1] == resource[0] && quad.isMatching[1] && !quad.isMatching[0]) {
            quad.isMatching[0] = true;
            addResources(arr, resource[1]);
        }
    }
    else if(direction == *DOWN){
        if(resource[0] == resource[1]&& quad.isMatching[0]&& !quad.isMatching[1]) {
            quad.isMatching[1] = true;
            addResources(arr, resource[0]);
        }
        else if(resource[1] == resource[0] && quad.isMatching[1] && !quad.isMatching[0]) {
            quad.isMatching[0] = true;
            addResources(arr, resource[1]);
        }
        if(resource[0] == resource[2] && quad.isMatching[0]&& !quad.isMatching[2]) {
            quad.isMatching[2] = true;
            addResources(arr, resource[0]);
        }
        if(resource[2] == resource[3]&& quad.isMatching[2]&& !quad.isMatching[3]) {
            quad.isMatching[3] = true;
            addResources(arr, resource[2]);
        }
        if(resource[1] == resource[3] && quad.isMatching[1] && !quad.isMatching[3]) {
            quad.isMatching[3] = true;
            addResources(arr, resource[3]);
        }
        if(resource[3] == resource[2]&& quad.isMatching[3]&& !quad.isMatching[2]) {
            quad.isMatching[2] = true;
            addResources(arr, resource[3]);
        }
    }
}

inline void ResourceCalculator::addResources(int *arr, ResourceTypes type){
    if(type == ResourceTypes::WHEAT)
       arr[*WHEAT] =  arr[*WHEAT] + 1;
    else if(type == ResourceTypes::SHEEP)
        arr[*SHEEP] =  arr[*SHEEP] + 1;
    else if(type == ResourceTypes::STONE)
        arr[*STONE] =  arr[*STONE] + 1;
    else if(type == ResourceTypes::WOOD)
        arr[*WOOD] =  arr[*WOOD] + 1;
}