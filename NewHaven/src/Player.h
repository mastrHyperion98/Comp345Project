#include<ostream>
#include<cstdint>

// Player can be placed on any open square/space on the GB
struct Player
{
private:
    // Player's Village GB
    VillageGameBoard* villageGameBoard{};
    // Havest Tiles player owns
    HarvestTile* tiles{};
    // Buildings player owns
    Building* buildings{};
    // Player's owened Resource markers
    ResourceMarker* resources{};
    // Player's Gathering and Building Scoring facilities
    Facilities* facilities{};

public:
    // Constructor
    Player(VillageGameBoard, HarvestTiles, Buildings, Resources, GatheringAndBuildingFacilities);
    // Destructor
    ~Player();

    // Methods to be implemented
    void placeHarvestTile();
    void drawBuilding();
    void drawHarvestTile();
    void resourceTracker();
    void buildVillage();
    void calculateResources();
}