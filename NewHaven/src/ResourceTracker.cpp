//
// Created by hyperion on 2020-02-27.
//

#include "ResourceTracker.h"
#include "../src/GBMap.h"
#include "../src/Square.h"
#include "../src/Resources.h"
#include <map>
#include <deque>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"

ResourceTracker::ResourceTracker(): score{new std::map<ResourceTypes, std::uint_least16_t> }{
}
ResourceTracker::~ResourceTracker(){
    delete score;
    delete DOWN;
    delete UP;
    delete LEFT;
    delete RIGHT;
    
}
ResourceTracker::ResourceTracker(const ResourceTracker& scores): score{ new std::map<ResourceTypes, std::uint_least16_t> }{
    *score =*scores.score;
}
ResourceTracker& ResourceTracker::operator=(const ResourceTracker& scores){
    if(&scores == this)
        return *this;
    *score = *scores.score;
    return *this;
}
void ResourceTracker::computeScore(ResourceTrails trail) {
    score->clear();
    // setup -- first step is to add the elements of the main root to the total for each resources
    deque<NodeID> queue;
    Map map;
    int num_vertices = boost::num_vertices(trail);
    auto vertices = trail.vertex_set();
    NodeID root = vertices[0];
    // Add the starting resources from the root to the count?
    queue.push_back(root);
    ResourceTypes *r_resources{(*trail[root].tile).getTileContent()};
    Quad *quad = new Quad();
            for(int i = 0; i < 4; i++){
               ResourceTypes resource{r_resources[i]};
               addResources(resource);
                quad->isMatching[i] = true;
            }
            (*quad->current_visit_count)++;
            map.insert(Pair(root, quad));
    while(!queue.empty()){
        root = queue.front();
        Quad *root_quad{map[root]};
        // now we build the queues
        ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;

        ResourceTypes *root_resources{(*trail[root].tile).getTileContent()};
        for (tie(neighbourIt, neighbourEnd) = adjacent_vertices(root, trail); neighbourIt != neighbourEnd; ++neighbourIt) {
            // get ourselves our vertex
            Quad *next_quad;
            NodeID next_element{vertices[*neighbourIt]};
            ResourceTypes *next_resources{(*trail[next_element].tile).getTileContent()};
            // compare index 2 of root to index 0 of next element
            if(map.find(next_element) != map.end())
                next_quad = map[next_element];
            else
                next_quad = new Quad();
            int direction = *trail[root].position - *trail[next_element].position;
            if(direction == *LEFT){
                if(root_resources[0] == next_resources[1] && !next_quad->isMatching[1] && root_quad->isMatching[0]){
                    next_quad->isMatching[1] = true;
                    addResources(next_resources[1]);
                }
                if(root_resources[3] == next_resources[2] && !next_quad->isMatching[2] && root_quad->isMatching[3]){
                    next_quad->isMatching[2] = true;
                    addResources( next_resources[2]);
                }
            }
            else if(direction == *RIGHT){
                if(root_resources[1] == next_resources[0] && !next_quad->isMatching[0] && root_quad->isMatching[1]){
                    next_quad->isMatching[0] = true;
                    addResources( next_resources[0]);
                }
                if(root_resources[2] == next_resources[3] && !next_quad->isMatching[3] && root_quad->isMatching[2]){
                    next_quad->isMatching[3] = true;
                    addResources(next_resources[3]);
                }
            }
            else if(direction <= *DOWN){
                if(root_resources[3] == next_resources[0] && !next_quad->isMatching[0] && root_quad->isMatching[3]){
                    next_quad->isMatching[0] = true;
                    addResources(next_resources[0]);
                }
                if(root_resources[2] == next_resources[1] && !next_quad->isMatching[1]  && root_quad->isMatching[2]){
                    next_quad->isMatching[1] = true;
                    addResources( next_resources[1]);
                }
            }
            else if(direction >= *UP){
                if(root_resources[0] == next_resources[3] && !next_quad->isMatching[3] && root_quad->isMatching[0]){
                    next_quad->isMatching[3] = true;
                    addResources( next_resources[3]);
                }
                if(root_resources[1] == next_resources[2] && !next_quad->isMatching[2] && root_quad->isMatching[1]){
                    next_quad->isMatching[2] = true;
                    addResources( next_resources[2]);
                }
            }

            setQuadInner(next_quad, next_resources, direction);
            (*next_quad->current_visit_count)++;
            // check if the quad for said vertex exists if it does verify count
            if(map.find(next_element) == map.end()) {
                map.insert(Pair(next_element, next_quad));
            }
            if(*next_quad->current_visit_count <= *next_quad->MAX_VISIT)
                    queue.push_back(next_element);
        }
        queue.pop_front();
    }
    // perform  backstepping ( from num_vertices - 2 to (num_vertices/2 - 2)
    // efficiency of N/2 operations
   for(int j = num_vertices-1; j >= 0; j--)
      backstepping(j, &map, trail);

   // delete and repoint all entries in the map to null_pointer
    // Create a map iterator and point to beginning of map
   Map::iterator it{map.begin()};

    // Iterate over the map using Iterator till end.
    while (it != map.end())
    {
        // delete the quad
        delete it->second;
        // assign nullptr
        it->second = nullptr;
        it++;
    }
}
// compute Inner
void ResourceTracker::setQuadInner(Quad *quad, ResourceTypes* resource, int direction){
    /*
     * check if 0 and 2 matches, 0 and 1, 1 and 3 and 3 and 2 in that order
     */
    // i know a lot of conditional checks but we cant avoid that
    if(direction == *LEFT){
        if(resource[1] == resource[2] && quad->isMatching[1] && !quad->isMatching[2]) {
            quad->isMatching[2] = true;
            addResources( resource[2]);
        }
        else if(resource[2] == resource[1] && quad->isMatching[2] && !quad->isMatching[1]) {
            quad->isMatching[1] = true;
            addResources( resource[2]);
        }
        if(resource[1] == resource[0] && quad->isMatching[1] && !quad->isMatching[0]) {
            quad->isMatching[0] = true;
            addResources( resource[1]);
        }
        if(resource[0] == resource[3] && quad->isMatching[0]&& !quad->isMatching[3]) {
            quad->isMatching[3] = true;
            addResources( resource[0]);
        }
        if(resource[2] == resource[3]&& quad->isMatching[2]&& !quad->isMatching[3]) {
            quad->isMatching[3] = true;
            addResources( resource[3]);
        }
        if(resource[3] == resource[0]&& quad->isMatching[3]&& !quad->isMatching[0]) {
            quad->isMatching[0] = true;
            addResources( resource[3]);
        }
    }
    else if(direction == *RIGHT){
        if(resource[0] == resource[3] && quad->isMatching[0]&& !quad->isMatching[3]) {
            quad->isMatching[3] = true;
            addResources( resource[0]);
        }
        else if(resource[3] == resource[0]&& quad->isMatching[3]&& !quad->isMatching[0]) {
            quad->isMatching[0] = true;
            addResources( resource[3]);
        }
        if(resource[0] == resource[1]&& quad->isMatching[0]&& !quad->isMatching[1]) {
            quad->isMatching[1] = true;
            addResources( resource[0]);
        }
        if(resource[1] == resource[2] && quad->isMatching[1] && !quad->isMatching[2]) {
            quad->isMatching[2] = true;
            addResources( resource[2]);
        }
        if(resource[3] == resource[2]&& quad->isMatching[3]&& !quad->isMatching[2]) {
            quad->isMatching[2] = true;
            addResources( resource[3]);
        }
        if(resource[2] == resource[1] && quad->isMatching[2] && !quad->isMatching[1]) {
            quad->isMatching[1] = true;
            addResources( resource[2]);
        }
    }
    else if(direction == *UP){
        if(resource[3] == resource[2]&& quad->isMatching[3]&& !quad->isMatching[2]) {
            quad->isMatching[2] = true;
            addResources( resource[3]);
        }
        else if(resource[2] == resource[3]&& quad->isMatching[2]&& !quad->isMatching[3]) {
            quad->isMatching[3] = true;
            addResources( resource[2]);
        }
         if(resource[3] == resource[0]&& quad->isMatching[3]&& !quad->isMatching[0]) {
            quad->isMatching[0] = true;
            addResources( resource[3]);
        }
        if(resource[0] == resource[1]&& quad->isMatching[0]&& !quad->isMatching[1]) {
            quad->isMatching[1] = true;
            addResources(resource[0]);
        }
        if(resource[2] == resource[1] && quad->isMatching[2] && !quad->isMatching[1]) {
            quad->isMatching[1] = true;
            addResources(resource[2]);
        }
        if(resource[1] == resource[0] && quad->isMatching[1] && !quad->isMatching[0]) {
            quad->isMatching[0] = true;
            addResources(resource[1]);
        }
    }
    else if(direction == *DOWN){
        if(resource[0] == resource[1]&& quad->isMatching[0]&& !quad->isMatching[1]) {
            quad->isMatching[1] = true;
            addResources(resource[0]);
        }
        else if(resource[1] == resource[0] && quad->isMatching[1] && !quad->isMatching[0]) {
            quad->isMatching[0] = true;
            addResources(resource[1]);
        }
        if(resource[0] == resource[3] && quad->isMatching[0]&& !quad->isMatching[3]) {
            quad->isMatching[3] = true;
            addResources(resource[0]);
        }
        if(resource[3] == resource[2]&& quad->isMatching[3]&& !quad->isMatching[2]) {
            quad->isMatching[2] = true;
            addResources(resource[3]);
        }
        if(resource[1] == resource[2] && quad->isMatching[1] && !quad->isMatching[2]) {
            quad->isMatching[2] = true;
            addResources(resource[2]);
        }
        if(resource[2] == resource[3]&& quad->isMatching[2]&& !quad->isMatching[3]) {
            quad->isMatching[3] = true;
            addResources(resource[2]);
        }
    }
}

inline void ResourceTracker::addResources(ResourceTypes type){
        if(score->find(type) == score->end())
            score->insert(pair<ResourceTypes, std::uint_least16_t>(type, 1));
        else
            (*score)[type] = (*score)[type] + 1;
}

// constant time efficiency
void ResourceTracker::backstepping(NodeID root, Map *map, ResourceTrails &trail) {
    Quad *root_quad{(*map)[root]};
    auto vertices{trail.vertex_set()};
    // now we build the queues
   ResourceTrails ::adjacency_iterator neighbourIt, neighbourEnd;
    ResourceTypes *root_resources{(*trail[root].tile).getTileContent()};
    for ( tie(neighbourIt, neighbourEnd) = adjacent_vertices(root, trail); neighbourIt != neighbourEnd; ++neighbourIt) {
        // get ourselves our vertex
        NodeID next_element{vertices[*neighbourIt]};
        Quad *next_quad{(*map)[next_element]};
        ResourceTypes *next_resources = (*trail[next_element].tile).getTileContent();

        int direction = *trail[root].position - *trail[next_element].position;
        if(direction == *DOWN){
            // compare index 2 of root to index 0 of next element
            if(root_resources[3] == next_resources[0] && !next_quad->isMatching[0] && root_quad->isMatching[3]){
                next_quad->isMatching[0] = true;
                addResources( next_resources[0]);
            }
            if(root_resources[2] == next_resources[1] && !next_quad->isMatching[1]  && root_quad->isMatching[2]){
                next_quad->isMatching[1] = true;
                addResources(next_resources[1]);
            }
        }
        else if(direction == *UP){
            // compare index 2 of root to index 0 of next element
            if(root_resources[0] == next_resources[3] && !next_quad->isMatching[3] && root_quad->isMatching[0]){
                next_quad->isMatching[3] = true;
                addResources( next_resources[3]);
            }
            if(root_resources[1] == next_resources[2] && !next_quad->isMatching[2] && root_quad->isMatching[1]){
                next_quad->isMatching[2] = true;
                addResources(next_resources[2]);
            }
        }
        else if(direction == *LEFT){
            // compare index 2 of root to index 0 of next element
            if(root_resources[0] == next_resources[1] && !next_quad->isMatching[1] && root_quad->isMatching[0]){
                next_quad->isMatching[1] = true;
                addResources( next_resources[1]);
            }
            if(root_resources[3] == next_resources[2] && !next_quad->isMatching[2] && root_quad->isMatching[3]){
                next_quad->isMatching[2] = true;
                addResources(next_resources[2]);
            }
        }
        else if(direction == *RIGHT){
            // compare index 2 of root to index 0 of next element
            if(root_resources[1] == next_resources[0] && !next_quad->isMatching[0] && root_quad->isMatching[1]){
                next_quad->isMatching[0] = true;
                addResources( next_resources[0]);
            }
            if(root_resources[2] == next_resources[3] && !next_quad->isMatching[3] && root_quad->isMatching[2]){
                next_quad->isMatching[3] = true;
                addResources( next_resources[3]);
            }
        }
        setQuadInner(next_quad, next_resources, direction);
        delete next_resources;
    }
}

void ResourceTracker::printScore()
{
    for (std::pair<ResourceTypes, std::uint_least16_t> i : *score)	//Printing score
    {
        std::cout << '\n' << i.first << ":\t" << i.second << '\n';
    }
}

bool ResourceTracker::consumeResources(ResourceTypes type, std::uint_least16_t amount) {
    // check if the resource is contianed within
    if(hasResources(type, amount)) {
        (*score)[type] = (*score)[type] - amount;
        return true;
    }

    return false;
}

bool ResourceTracker::hasResources(ResourceTypes type, std::uint_least16_t amount){
    // check if the resource is contianed within
    if(score->find(type) != score->end()){

        if ((*score)[type] >= amount){
            return true;
        }
    }
    return false;
}
ResourceTracker::Quad::Quad(): isMatching{new bool[4]{false, false, false, false}}{
    current_visit_count = new int(0);
}

ResourceTracker::Quad::Quad(const Quad &quad): isMatching{new bool[4]{false, false, false, false}}{
    current_visit_count = new int(*quad.current_visit_count);
    for(int i = 0; i < 4; i++)
        isMatching[i] = quad.isMatching[i];
}

ResourceTracker::Quad & ResourceTracker::Quad::operator=(const Quad &quad) {
    if(this == &quad)
        return *this;
    *current_visit_count = *quad.current_visit_count;
     for(int i = 0; i < 4; i++)
         isMatching[i] = quad.isMatching[i];

     return *this;
}

ResourceTracker::Quad::~Quad(){
    delete[] isMatching;
    delete current_visit_count;
    delete MAX_VISIT;
}

inline void ResourceTracker::reset(){
    score->clear();
    score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::WHEAT,0));
    score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::WOOD,0));
    score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::STONE,0));
    score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::SHEEP,0));
}

bool ResourceTracker::isEmpty() {
    int num_empty{0};
    for(std::map<ResourceTypes, std::uint_least16_t>::iterator it=score->begin(); it!=score->end(); ++it){
        if(it->second <= 0)
            num_empty++;
    }

    if(num_empty == score->size())
        return true;
    else
        return false;
}