#pragma once

#include <vector>
#include <random>

using namespace std;

struct Vec2 { float x, y; };
struct StateVec{
    float x, y, vx, vy, ax, ay, m;
    //uint32_t morton = 0;
};
struct Particles{
    vector<Vec2> pos;
    vector<Vec2> vel;
    vector<Vec2> acc;
    vector<float> mass;
    vector<uint32_t> morton;
    Particles(size_t Count){
        pos.reserve(Count);
        vel.reserve(Count);
        acc.reserve(Count);
        mass.reserve(Count);
        morton.reserve(Count);
    }
};
struct QuadNode {
    // bounds of this node
    float x, y;        // center or top-left, depending on your convention
    float size_x;      // width of this square
    float size_y;
    // children
    QuadNode* children[4] = {nullptr, nullptr, nullptr, nullptr};

    // objects in this node
    Vec2 COM;
    float mass = 0;
    bool first = true;;
    vector<Vec2> same_node;
    QuadNode* nxtfree = nullptr;
    //node functions
    bool isleaf(){
        return (children[0]==nullptr)&&(children[1]==nullptr)&&(children[2]==nullptr)&&(children[3]==nullptr);
    }
};
class QuadNodePool{
public:
    QuadNodePool(size_t blockSize)
    : blockSize(blockSize) {}

    QuadNode* allocate(){
        if(!freeList) addBlock();

        QuadNode* n = freeList;

        freeList = freeList->nxtfree;

        fill(n->children, n->children + 4, nullptr);
        n->mass = 0;
        //n->nxtfree = nullptr;
        n->COM = {0.0f, 0.0f};

        return n;
    }

    void deallocate(QuadNode* n) {
        n->nxtfree = freeList;
        freeList = n;
    }

    ~QuadNodePool() {
        for (auto block : blocks)
            delete[] block;
    }
public:
    QuadNode* freeList = nullptr;
    QuadNode* block = nullptr;
private:
    size_t blockSize;
    vector<QuadNode*> blocks;
    void addBlock() {
        block = new QuadNode[blockSize];
        blocks.push_back(block);

        // chain into freelist
        for (std::size_t i = 0; i < blockSize - 1; ++i)
            block[i].nxtfree = &block[i + 1];

        block[blockSize - 1].nxtfree = freeList;
        freeList = block;
    }

};

class Simulation{
    private:
        const Vec2 windowDimensions;
        const Vec2 corner;
        const long long N;
        const float timestep;
        const float MIN_SIZE = 0.0f;
        const float softening = 25.0f;
        const float theta_squared = 0.75;
        const unsigned int depth = 16;
        QuadNodePool nodes;
    public:
        Simulation(const Vec2& Dimensions, const Vec2& corner, long long ParticleCount, float timestep);
        ~Simulation();
        vector<Vec2> generate_positions();
        Particles generateGalaxy(Vec2 core1, Vec2 core2, float M1, float M2);
        void initialise(Particles& Config);
        void NewState(Particles& Config, unsigned int& out);

    private:
        Vec2 com(Vec2& pos1, float m1, Vec2& pos2, float m2);
        unsigned int build_tree(Vec2& coord, QuadNode* node, QuadNodePool& nodes, float m);
        Vec2 GetForce(Vec2& coord, QuadNode* node);
        Vec2 getForce(Vec2& coord, QuadNode* node);
        void UpdatePosition(Vec2& coord, Vec2& Force, Vec2& Velocity, Vec2& target);
        void UpdateVelocity(Vec2& Force, Vec2& Velocity, Vec2& target);
        inline void FindMortonCode(Vec2& coord, unsigned int& out);
};