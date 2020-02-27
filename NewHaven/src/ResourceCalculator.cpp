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

            }
            else if(direction == *UP){

            }
            else if(direction == *LEFT){

            }
            else if(direction == *RIGHT){

            }
        }


        ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;
        tie(neighbourIt, neighbourEnd) = adjacent_vertices(root, trail);
        for (; neighbourIt != neighbourEnd; ++neighbourIt) {

        }

    }



}
// compute Inner
inline void ResourceCalculator::setQuadInner(Quad quad, ResourceTypes* resource){

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