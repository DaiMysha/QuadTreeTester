#include <iostream>
#include <ctime>
#include <list>

#include <DMUtils\QuadTree.hpp>

int  N_ITEMS = 10000;
#define SIZE  1000

typedef DMUtils::physics::AABB<float> testAABB;

struct Point {
    float x,y;

    Point() : x(0), y(0) {}
    Point(float xx, float yy) : x(xx), y(yy) {}
    Point(const Point& p) : x(p.x), y(p.y) {}
    bool operator==(const Point& p) const {
        return this == &p;
    }
};

bool operator==(const testAABB& a, const testAABB& b) {
    return &a == &b;
}

Point* points = nullptr;
testAABB* aabbs = nullptr;

std::vector<Point> vPoint;
std::vector<Point*> vPointPtr;
DMUtils::QuadTree<Point> qPoint(SIZE,SIZE);

std::vector<testAABB*> vAABB;
DMUtils::QuadTree<testAABB> qAABB(SIZE,SIZE);

Point makeRandomPoint(float xmax, float ymax) {
    return Point(rand()%(int)xmax, rand()%(int)ymax);
}

testAABB makeRandomAABB(float xmax, float ymax) {
    float x = rand()%(int)xmax;
    float y = rand()%(int)ymax;
    return testAABB(x,y,rand()%(int)(xmax-x),rand()%(int)(ymax-y));
}

void fillVec() {
    for(int i=0;i<N_ITEMS;++i) vPoint.push_back(points[i]);
}

void fillVecPtr() {
    for(int i=0;i<N_ITEMS;++i) vPointPtr.push_back(&points[i]);
}

void fillTree() {
    for(int i=0;i<N_ITEMS;++i) qPoint.insert(points[i].x, points[i].y, &points[i]);
}

void fill() {
    fillVec();
    fillVecPtr();
    fillTree();
}

void reset() {
    vPoint.clear();
    vPointPtr.clear();
    qPoint.clear();
    fill();
}

std::list<const Point*> query(const std::vector<Point>& vec, const testAABB& map) {
    std::list<const Point*> ans;
    for(size_t i=0;i<vec.size();++i) {
        if(map.contains(vec[i].x,vec[i].y)) ans.push_back(&vec[i]);
    }
    return ans;
}

std::list<const Point*> query(const std::vector<Point*>& vec, const testAABB& map) {
    std::list<const Point*> ans;
    for(size_t i=0;i<vec.size();++i) {
        if(map.contains(vec[i]->x,vec[i]->y)) ans.push_back(vec[i]);
    }
    return ans;
}

std::list<const testAABB*> query(const std::vector<testAABB*>& vec, const testAABB& map) {
    std::list<const testAABB*> ans;
    for(size_t i=0;i<vec.size();++i) {
        if(map.collides(*vec[i])) ans.push_back(vec[i]);
    }
    return ans;
}

int main(int argc, char** argv) {
    srand(time(0));

    std::cout << "Point amount ?\n>";
    std::cin>>N_ITEMS;
    std::cout<<std::endl;

    points = new Point[N_ITEMS];
    aabbs = new testAABB[N_ITEMS];
    //fills the two data
    clock_t clock_before, clock_after;

    for(int i = 0; i < N_ITEMS; ++i) {
        points[i] = makeRandomPoint(SIZE,SIZE);
        aabbs[i] = makeRandomAABB(SIZE,SIZE);
    }

    for(int i=0;i<N_ITEMS;++i) vAABB.push_back(&aabbs[i]);
    for(int i=0;i<N_ITEMS;++i) qAABB.insert(aabbs[i], &aabbs[i]);

    clock_t clock_vector, clock_tree;

    {
        std::cout << "****** FILLING POINTS *****" << std::endl;
        clock_before = clock();
        fillVec();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms" << std::endl;

        clock_before = clock();
        fillVecPtr();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvectorPtr: " << clock_vector << " ms" << std::endl;

        clock_before = clock();
        fillTree();
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "****** CLEAR POINTS *****" << std::endl;
        clock_before = clock();
        vPoint.clear();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms" << std::endl;

        clock_before = clock();
        qPoint.clear();
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms" << std::endl;
        std::cout << std::endl;
        reset();
    }
    if(false) {
        std::cout << "****** DEL 1/2 POINTS *****" << std::endl;
        clock_before = clock();
        for(int i=N_ITEMS-1;i>=0;i-=2) std::remove(vPoint.begin(),vPoint.end(),vPoint[i]);
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms" << std::endl;

        auto ll = qPoint.data();
        clock_before = clock();
        for(auto it = ll.begin(); it != ll.end();) {
            qPoint.remove(*it);
            ++it; ++it;
        }
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms" << std::endl;
        std::cout << std::endl;
        reset();
    }

    {
        testAABB map(0,0,SIZE,SIZE);
        size_t n;
        std::cout << "****** QUERY WHOLE MAP POINTS *****" << std::endl;
        clock_before = clock();
        n = query(vPoint,map).size();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms (" << n << ")" << std::endl;

        clock_before = clock();
        n = query(vPointPtr,map).size();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvectorPtr: " << clock_vector << " ms (" << n << ")" << std::endl;

        auto ll = qPoint.data();
        clock_before = clock();
        n = qPoint.query(map).size();
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms (" << n << ")" << std::endl;
        std::cout << std::endl;
    }

    {
        testAABB map(makeRandomAABB(SIZE,SIZE));
        size_t n;
        std::cout << "****** QUERY RANDOM MAP POINTS *****" << std::endl;
        std::cout << "\tmap : " << map.left << ", " << map.top << ", " << map.width << ", " << map.height << std::endl;
        clock_before = clock();
        n = query(vPoint,map).size();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms (" << n << "/" << N_ITEMS << ")" << std::endl;

        auto ll = qPoint.data();
        clock_before = clock();
        n = qPoint.query(map).size();
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms (" << n << "/" << N_ITEMS << ")" << std::endl;
        std::cout << std::endl;
    }

    {
        testAABB map(SIZE/4,SIZE/4,SIZE/2,SIZE/2);
        size_t n;
        std::cout << "****** QUERY HALF MAP POINTS *****" << std::endl;
        std::cout << "\tmap : " << map.left << ", " << map.top << ", " << map.width << ", " << map.height << std::endl;
        clock_before = clock();
        n = query(vPoint,map).size();
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms (" << n << "/" << N_ITEMS << ")" << std::endl;

        auto ll = qPoint.data();
        clock_before = clock();
        n = qPoint.query(map).size();
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms (" << n << "/" << N_ITEMS << ")" << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "****** QUERY ALL AABB POINTS *****" << std::endl;
        clock_before = clock();
        for(int i=0;i<N_ITEMS;++i) {
            query(vAABB,*vAABB[i]);
        }
        clock_after = clock();

        clock_vector = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tvector   : " << clock_vector << " ms" << std::endl;

        auto ll = qAABB.data();
        clock_before = clock();
        for(auto lll : ll) qAABB.query(*lll);
        clock_after = clock();
        clock_tree = (clock_after - clock_before)*1000/CLOCKS_PER_SEC;
        std::cout << "\tquadTree : " << clock_tree << " ms" << std::endl;
        std::cout << std::endl;
    }

    delete[] points;
    delete[] aabbs;
    return 0;
}
