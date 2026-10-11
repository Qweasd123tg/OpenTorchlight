// Additional executed receipts for the existing A* restorations.
#include "AstarPathfinder.h"
#include "AutoTest.h"
#include <cstdlib>
#include <cstring>
#include <malloc.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

typedef CAstarPathfinder Pathfinder;
typedef Pathfinder::CAstarNode Node;
typedef Pathfinder::NodeStack Stack;

TL_ORIGINAL(Node*, originalReverse, (Pathfinder*, Node*), "_ZN16CAstarPathfinder12reverseNodesEPNS_10CAstarNodeE")
TL_ORIGINAL(void, originalPropagate, (Pathfinder*, Node*), "_ZN16CAstarPathfinder13propagateDownEPNS_10CAstarNodeE")
TL_ORIGINAL(void, originalSuccessor, (Pathfinder*, Node*, unsigned int, unsigned int, unsigned int, unsigned int), "_ZN16CAstarPathfinder17generateSuccessorEPNS_10CAstarNodeEjjjj")
TL_ORIGINAL(void, originalSuccessors, (Pathfinder*, Node*, unsigned int, unsigned int), "_ZN16CAstarPathfinder18generateSuccessorsEPNS_10CAstarNodeEjj")
TL_ORIGINAL(void, originalFree, (Pathfinder*), "_ZN16CAstarPathfinder9freeNodesEv")
TL_ORIGINAL(void, originalCreate, (Pathfinder*, int, int, int, int, bool), "_ZN16CAstarPathfinder10createPathEiiiib")
TL_ORIGINAL(void, originalWide, (Pathfinder*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&), "_ZN16CAstarPathfinder19findNearestWideOpenEjjjjRjS0_")
TL_ORIGINAL(void, originalNearest, (Pathfinder*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&), "_ZN16CAstarPathfinder15findNearestOpenEjjjjRjS0_")
TL_ORIGINAL(void, originalDirected, (Pathfinder*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&), "_ZN16CAstarPathfinder23findNearestOpenDirectedEjjjjRjS0_")
TL_ORIGINAL(bool, originalFind, (Pathfinder*, float, float, float, float), "_ZN16CAstarPathfinder8findPathEffff")

namespace
{
struct Context
{
    Pathfinder* path;
    Node* nodes[16];
    int mode;
    int round;
    unsigned int x, y, goalX, goalY;
    short tiles[40][40];
    short occupied[40][40];
    short* tileColumns[40];
    short* occupiedColumns[40];
};

struct Snapshot
{
    unsigned int size;
    unsigned char bytes[256 * 1024];

    void add(const void* p, unsigned int n)
    {
        if (size + n > sizeof(bytes))
            _exit(4);
        memcpy(bytes + size, p, n);
        size += n;
    }
    void integer(int value) { add(&value, sizeof(value)); }
};

struct Nodes
{
    Node* nodes[4096];
    int count;

    int index(Node* node)
    {
        if (!node)
            return -1;
        for (int i = 0; i < count; ++i)
            if (nodes[i] == node)
                return i;
        if (count == 4096)
            _exit(5);
        nodes[count] = node;
        return count++;
    }
};

void capture(Context& c, Snapshot& out)
{
    Pathfinder* p = c.path;
    out.add(&p->m_bPathFound, 1);
    out.add(&p->m_iHeight, 16);
    out.add(&p->m_fOriginX, 16);
    Nodes map;
    map.count = 0;
    for (int i = 0; i < 16; ++i)
        if (c.nodes[i])
            map.index(c.nodes[i]);
    out.integer(map.index(p->m_pOpen));
    out.integer(map.index(p->m_pClosed));
    out.integer(map.index(p->m_pClosest));
    out.integer(map.index(p->m_pCurrent));
    Stack* entry = p->m_pStack->m_pNext;
    int stackCount = 0;
    while (entry && stackCount < 100)
    {
        out.integer(map.index(entry->m_pNode));
        entry = entry->m_pNext;
        ++stackCount;
    }
    // The remaining stack was not observed, even if both prefixes match.
    if (entry)
        _exit(6);
    out.integer(-2);
    for (int i = 0; i < map.count; ++i)
    {
        Node* node = map.nodes[i];
        out.add(node, 24);
        out.integer(map.index(node->m_pParent));
        for (int j = 0; j < 8; ++j)
            out.integer(map.index(node->m_pChildren[j]));
        out.integer(map.index(node->m_pNext));
    }
    out.integer(map.count);
    int used = mallinfo().uordblks;
    out.integer(used);
}

extern "C" Node* candidateReverse (Pathfinder*, Node*) __asm__("_ZN16CAstarPathfinder12reverseNodesEPNS_10CAstarNodeE");
extern "C" void candidatePropagate (Pathfinder*, Node*) __asm__("_ZN16CAstarPathfinder13propagateDownEPNS_10CAstarNodeE");
extern "C" void candidateSuccessor (Pathfinder*, Node*, unsigned int, unsigned int, unsigned int, unsigned int) __asm__("_ZN16CAstarPathfinder17generateSuccessorEPNS_10CAstarNodeEjjjj");
extern "C" void candidateSuccessors (Pathfinder*, Node*, unsigned int, unsigned int) __asm__("_ZN16CAstarPathfinder18generateSuccessorsEPNS_10CAstarNodeEjj");
extern "C" void candidateFree (Pathfinder*) __asm__("_ZN16CAstarPathfinder9freeNodesEv");
extern "C" void candidateCreate (Pathfinder*, int, int, int, int, bool) __asm__("_ZN16CAstarPathfinder10createPathEiiiib");
extern "C" void candidateWide (Pathfinder*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&) __asm__("_ZN16CAstarPathfinder19findNearestWideOpenEjjjjRjS0_");
extern "C" void candidateNearest (Pathfinder*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&) __asm__("_ZN16CAstarPathfinder15findNearestOpenEjjjjRjS0_");
extern "C" void candidateDirected (Pathfinder*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, unsigned int&) __asm__("_ZN16CAstarPathfinder23findNearestOpenDirectedEjjjjRjS0_");
extern "C" bool candidateFind (Pathfinder*, float, float, float, float) __asm__("_ZN16CAstarPathfinder8findPathEffff");
void build(Context& c, int mode, int round)
{
    memset(&c, 0, sizeof(c));
    c.mode = mode;
    c.round = round;
    for (int x = 0; x < 40; ++x)
    {
        c.tileColumns[x] = c.tiles[x];
        c.occupiedColumns[x] = c.occupied[x];
        for (int y = 0; y < 40; ++y)
        {
            unsigned int bits = (x * 113u + y * 37u + round * 29u) % 19;
            c.tiles[x][y] = round % 7 == 0 ? 0 : bits < 5 ? 1 : 0;
            c.occupied[x][y] = bits == 8 ? 2 : 0;
        }
    }
    c.path = static_cast<Pathfinder*>(calloc(1, sizeof(Pathfinder)));
    Pathfinder* p = c.path;
    p->m_iWidth = 40;
    p->m_iHeight = 40;
    p->m_iTileCount = 1600;
    p->m_fTileSize = 0.75f + (round % 5) * 0.5f;
    p->m_fOriginX = -3.25f;
    p->m_fOriginY = 8.125f;
    p->m_pTiles = c.tileColumns;
    p->m_pOccupiedTiles = c.occupiedColumns;
    p->m_bIgnoreOccupancy = round % 2;
    p->m_bPathFound = true;
    p->m_bCompletePath = true;
    p->m_iMaxIterations = 150;
    p->m_pStack = static_cast<Stack*>(calloc(1, sizeof(Stack)));
    p->m_pOpen = static_cast<Node*>(calloc(1, sizeof(Node)));
    p->m_pClosed = static_cast<Node*>(calloc(1, sizeof(Node)));
    for (int i = 0; i < 16; ++i)
    {
        c.nodes[i] = static_cast<Node*>(calloc(1, sizeof(Node)));
        c.nodes[i]->m_iX = i + 1;
        c.nodes[i]->m_iY = 3;
        c.nodes[i]->m_iTile = i + 121;
        c.nodes[i]->m_fPathCost = (round + i * 7) % 13;
        c.nodes[i]->m_fGoalCost = (round + i) % 11;
        c.nodes[i]->m_fTotalCost = c.nodes[i]->m_fPathCost + c.nodes[i]->m_fGoalCost;
    }
    p->m_pCurrent = c.nodes[0];
    c.x = 12;
    c.y = 3;
    c.goalX = 7;
    c.goalY = 9;
    if (mode == 0)
    {
        int length = round % 16;
        for (int i = 0; i < length; ++i)
            c.nodes[i]->m_pParent = c.nodes[i + 1];
    }
    else if (mode == 1)
    {
        for (int i = 0; i < 7; ++i)
        {
            c.nodes[i]->m_pChildren[0] = c.nodes[2 * i + 1];
            c.nodes[i]->m_pChildren[1] = c.nodes[2 * i + 2];
        }
        c.nodes[0]->m_pChildren[round % 3] = NULL;
        if (round % 5 == 0)
            for (int i = 0; i < 8; ++i)
                c.nodes[0]->m_pChildren[i] = c.nodes[i + 1];
        if (round % 11 == 0)
        {
            unsigned int nan = 0x7fc00001;
            memcpy(&c.nodes[4]->m_fPathCost, &nan, 4);
        }
        if (round % 4 == 0)
        {
            Stack* entry = static_cast<Stack*>(calloc(1, sizeof(Stack)));
            entry->m_pNode = c.nodes[1];
            p->m_pStack->m_pNext = entry;
        }
    }
    else if (mode == 2)
    {
        c.nodes[0]->m_fPathCost = round % 3;
        Node* existing = c.nodes[11];
        existing->m_fPathCost = round % 5;
        for (int i = 0; i < round % 8; ++i)
            c.nodes[0]->m_pChildren[i] = c.nodes[i + 1];
        if (round % 3 == 0)
            p->m_pOpen->m_pNext = existing;
        else if (round % 3 == 1)
        {
            p->m_pClosed->m_pNext = existing;
            existing->m_pChildren[0] = c.nodes[12];
            c.nodes[12]->m_fPathCost = 20.0f;
        }
        else
        {
            p->m_pOpen->m_pNext = c.nodes[2];
            c.nodes[2]->m_pNext = c.nodes[3];
            c.nodes[2]->m_fTotalCost = round % 2 ? 500.0f : 0.0f;
            c.nodes[3]->m_fTotalCost = 100.0f;
            p->m_pClosest = round % 2 ? c.nodes[2] : NULL;
            if (round % 4 == 3)
                c.nodes[2]->m_fGoalCost = 1000.0f;
        }
    }
    else if (mode == 3)
    {
        c.nodes[0]->m_iX = round < 256 ? 10 : round % 5 == 0 ? 0 : round % 5 == 1 ? 39 : 10;
        c.nodes[0]->m_iY = round < 256 ? 10 : round % 6 == 0 ? 0 : round % 6 == 1 ? 39 : 10;
        c.nodes[0]->m_iTile = c.nodes[0]->m_iY * 40 + c.nodes[0]->m_iX;
        int bit = 0;
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int x = c.nodes[0]->m_iX + dx;
                int y = c.nodes[0]->m_iY + dy;
                if (x >= 0 && x < 40 && y >= 0 && y < 40)
                {
                    c.tiles[x][y] = (round & (1 << bit)) ? 0 : 1;
                    c.occupied[x][y] = 0;
                }
                ++bit;
            }
    }
    else if (mode == 4)
    {
        if (round % 6 == 0)
        {
            free(p->m_pOpen);
            p->m_pOpen = NULL;
        }
        else
        {
            int count = round % 6 == 1 ? 0 : 8;
            p->m_pOpen->m_pNext = count ? c.nodes[0] : NULL;
            for (int i = 0; i + 1 < count; ++i)
                c.nodes[i]->m_pNext = c.nodes[i + 1];
        }
        if (round % 7 == 0)
        {
            free(p->m_pClosed);
            p->m_pClosed = NULL;
        }
        else
        {
            int count = round % 7 == 1 ? 0 : 8;
            p->m_pClosed->m_pNext = count ? c.nodes[8] : NULL;
            for (int i = 8; i + 1 < count + 8; ++i)
                c.nodes[i]->m_pNext = c.nodes[i + 1];
        }
    }
    else
    {
        static const int coordinates[] = {0, 1, 10, 20, 39, 40, 50, -1};
        c.x = coordinates[round % 8];
        c.y = coordinates[(round / 8) % 8];
        c.goalX = coordinates[(round + 3) % 8];
        c.goalY = coordinates[(round / 8 + 2) % 8];
        if (mode == 5 || mode == 9)
        {
            c.x = round % 35 + 1;
            c.y = (round * 3) % 35 + 1;
            c.goalX = (round * 7) % 35 + 1;
            c.goalY = (round * 11) % 35 + 1;
            if (round % 11 == 0)
            {
                c.goalX = c.x;
                c.goalY = c.y;
            }
            static const int limits[] = {-1, 0, 1, 2, 5, 150};
            p->m_iMaxIterations = limits[round % 6];
            p->m_bGoalBlocked = round % 3 == 0;
            if (mode == 9 && round % 19 == 0)
                c.x = c.y = static_cast<unsigned int>(-2);
            if (mode == 9 && round % 19 == 1)
                c.goalX = c.goalY = static_cast<unsigned int>(-4);
        }
        if (round % 9 == 0)
            memset(c.tiles, 1, sizeof(c.tiles));
        if (round % 9 == 1)
        {
            memset(c.tiles, 1, sizeof(c.tiles));
            for (int x = 18; x <= 20; ++x)
                for (int y = 18; y <= 20; ++y)
                {
                    c.tiles[x][y] = 0;
                    c.occupied[x][y] = 0;
                }
            if (mode >= 6 && mode <= 8)
                c.goalX = c.goalY = 18;
        }
        if ((mode == 6 || mode == 7) && round % 13 == 0)
            p->m_fTileSize = 10000.0f;
        if (mode == 8 && round % 13 == 0)
        {
            c.x = c.goalX;
            c.y = c.goalY;
        }
        if ((mode == 6 || mode == 7) && round % 17 < 4)
        {
            memset(c.tiles, 1, sizeof(c.tiles));
            memset(c.occupied, 0, sizeof(c.occupied));
            c.x = c.y = 1;
            c.goalX = c.goalY = round % 17 == 1 ? 20 : 10;
            p->m_fTileSize = 1.0f;
            int centerX = round % 17 == 1 ? 4 : round % 17 == 2 ? 10 : 26;
            int centerY = round % 17 == 1 ? 20 : round % 17 == 2 ? 26 : 10;
            int radius = mode == 6 ? 1 : 0;
            if (round % 17 == 3)
                centerX = mode == 6 ? 8 : 9;
            for (int dx = -radius; dx <= radius; ++dx)
                for (int dy = -radius; dy <= radius; ++dy)
                    c.tiles[centerX + dx][centerY + dy] = 0;
            if (round % 17 == 3)
                for (int dx = -radius; dx <= radius; ++dx)
                    for (int dy = -radius; dy <= radius; ++dy)
                        c.tiles[20 - centerX + dx][centerY + dy] = 0;
        }
        if (mode == 8 && (round % 23 == 1 || round % 23 == 2))
        {
            memset(c.tiles, 1, sizeof(c.tiles));
            memset(c.occupied, 0, sizeof(c.occupied));
            c.tiles[3][0] = 0;
            c.goalX = c.goalY = c.y = 0;
            c.x = round % 23 == 1 ? 6 : 12;
            p->m_fTileSize = 1e-9f;
            p->m_fOriginX = p->m_fOriginY = 0.0f;
        }
        if (mode == 5 && round % 23 < 2)
        {
            memset(c.tiles, 0, sizeof(c.tiles));
            memset(c.occupied, 0, sizeof(c.occupied));
            c.x = c.y = 3;
            c.goalX = c.goalY = round % 23 == 0 ? 5 : 20;
            p->m_bGoalBlocked = round % 23 == 0;
            p->m_iMaxIterations = round % 23 == 0 ? 150 : 0;
        }
        if (mode == 9 && round % 31 < 4)
        {
            memset(c.tiles, 0, sizeof(c.tiles));
            memset(c.occupied, 0, sizeof(c.occupied));
            c.x = c.y = 10;
            c.goalX = c.goalY = 20;
            p->m_iMaxIterations = 150;
            static const int dx[] = {0, 0, 1, -1};
            static const int dy[] = {-1, 1, 0, 0};
            c.tiles[10 + dx[round % 31]][10 + dy[round % 31]] = 1;
        }
    }
}

void release(Context& c)
{
    for (int i = 0; i < 16; ++i)
        free(c.nodes[i]);
    Stack* entry = c.path->m_pStack;
    while (entry)
    {
        Stack* next = entry->m_pNext;
        free(entry);
        entry = next;
    }
    free(c.path->m_pOpen);
    free(c.path->m_pClosed);
    free(c.path);
}


void executeObserved(Context&c,bool ours,autotest::Capture&out){
 Pathfinder*p=c.path;Node*node=c.nodes[0];Snapshot snap;snap.size=0;
 switch(c.mode){
 case 0:{Node*(*fn)(Pathfinder*,Node*)=ours?candidateReverse:originalReverse;
  if(!autotest::beginInvocation(out,fn))return;Node*result=fn(p,c.round%6?node:NULL);out.callCompleted=1;
  int index=-1;for(int i=0;i<16;++i)if(result&&c.nodes[i]==result)index=i;snap.integer(index);break;}
 case 1:autotest::invoke(out,ours?candidatePropagate:originalPropagate,p,node);break;
 case 2:autotest::invoke(out,ours?candidateSuccessor:originalSuccessor,p,node,c.x,c.y,c.goalX,c.goalY);break;
 case 3:autotest::invoke(out,ours?candidateSuccessors:originalSuccessors,p,node,c.goalX,c.goalY);break;
 case 4:{autotest::invoke(out,ours?candidateFree:originalFree,p);
  snap.integer(mallinfo().uordblks);void*reused[16];
  for(int i=0;i<16;++i){reused[i]=malloc(sizeof(Node));int index=-1;for(int j=0;j<16;++j)if(reused[i]==c.nodes[j])index=j;snap.integer(index);}
  for(int i=0;i<16;++i)free(reused[i]);out.add(snap.bytes,snap.size);return;}
 case 5:autotest::invoke(out,ours?candidateCreate:originalCreate,p,static_cast<int>(c.goalX),static_cast<int>(c.goalY),static_cast<int>(c.x),static_cast<int>(c.y),c.round%2!=0);break;
 case 6:case 7:case 8:{unsigned x=1234,y=5678;
  void(*fn)(Pathfinder*,unsigned,unsigned,unsigned,unsigned,unsigned&,unsigned&)=c.mode==6?(ours?candidateWide:originalWide):c.mode==7?(ours?candidateNearest:originalNearest):(ours?candidateDirected:originalDirected);
  if(!autotest::beginInvocation(out,fn))return;fn(p,c.x,c.y,c.goalX,c.goalY,x,y);out.callCompleted=1;snap.integer(x);snap.integer(y);break;}
 case 9:{float x=float(int(c.x))*p->m_fTileSize+p->m_fOriginX+0.125f;
  float y=float(int(c.y))*p->m_fTileSize+p->m_fOriginY+0.125f;
  float gx=float(int(c.goalX))*p->m_fTileSize+p->m_fOriginX+0.375f;
  float gy=float(int(c.goalY))*p->m_fTileSize+p->m_fOriginY+0.375f;
  autotest::invoke(out,ours?candidateFind:originalFind,p,x,y,gx,gy);break;}
 }
 capture(c,snap);out.add(snap.bytes,snap.size);
}
void observedOriginal(void*p,autotest::Capture&out){executeObserved(*static_cast<Context*>(p),false,out);}
void observedCandidate(void*p,autotest::Capture&out){executeObserved(*static_cast<Context*>(p),true,out);}
int compareObserved(const tlhybrid_host*host,int mode,const char*name){
 const uint64_t addresses[]={
 (uint64_t)(uintptr_t)originalReverse,(uint64_t)(uintptr_t)originalPropagate,(uint64_t)(uintptr_t)originalSuccessor,
 (uint64_t)(uintptr_t)originalSuccessors,(uint64_t)(uintptr_t)originalFree,(uint64_t)(uintptr_t)originalCreate,
 (uint64_t)(uintptr_t)originalWide,(uint64_t)(uintptr_t)originalNearest,(uint64_t)(uintptr_t)originalDirected,(uint64_t)(uintptr_t)originalFind};
 autotest::Coverage coverage(name,addresses[mode]);int rounds=mode==3?512:mode>=5?240:120;
 for(int n=0;n<rounds;++n){Context c;build(c,mode,n);autotest::Outcome a,b;
  autotest::runChild(observedOriginal,&c,a);autotest::runChild(observedCandidate,&c,b);int result=coverage.observe(host,a,b);release(c);
  if(result){host->log("    observed astar mode %d round %d pair %d status %d/%d bytes %lu/%lu\n",mode,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
 }
 coverage.report(host);return 0;
}
}
TL_TEST(astar_observed_reverse){return compareObserved(host,0,"astar_observed_reverse");}
TL_TEST(astar_observed_propagate){return compareObserved(host,1,"astar_observed_propagate");}
TL_TEST(astar_observed_successor){return compareObserved(host,2,"astar_observed_successor");}
TL_TEST(astar_observed_successors){return compareObserved(host,3,"astar_observed_successors");}
TL_TEST(astar_observed_free){return compareObserved(host,4,"astar_observed_free");}
TL_TEST(astar_observed_create){return compareObserved(host,5,"astar_observed_create");}
TL_TEST(astar_observed_wide){return compareObserved(host,6,"astar_observed_wide");}
TL_TEST(astar_observed_nearest){return compareObserved(host,7,"astar_observed_nearest");}
TL_TEST(astar_observed_directed){return compareObserved(host,8,"astar_observed_directed");}
TL_TEST(astar_observed_find){return compareObserved(host,9,"astar_observed_find");}
