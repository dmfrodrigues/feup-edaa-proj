#include <fstream>
#include <iomanip>
#include <random>

#include "EdgeType.h"
#include "MapGraph.h"
#include "MapGraphView.h"
#include "MapViewer.h"

#include "Run.h"

#include "QuadTreeClosestPoint.h"

#include "graphviewer.h"

void eval2DTree_BuildTime(const MapGraph &M){
    std::ofstream os("eval/2d-tree-buildtime.csv");
    os << std::fixed << std::setprecision(3);

    std::unordered_map<DWGraph::node_t, coord_t> nodes = M.getNodes();
    std::vector<coord_t> coords(nodes.size());
    {
        size_t i = 0;
        for(const std::pair<DWGraph::node_t, coord_t> &p: nodes)
            coords[i++] = p.second;
    }
    std::shuffle(coords.begin(), coords.end(), std::mt19937(0));

    const size_t REPEAT = 5;

    std::vector<size_t> szs = {
             1,
          1000,
          2000,
          3000,
          4000,
          5000,
          6000,
          7000,
          8000,
          9000,
         10000, 12500, 15000, 17500,
         20000, 22500, 25000, 27500,
         30000, 32500, 35000, 37500,
         40000, 42500, 45000, 47500,
         50000, 52500, 55000, 57500,
         60000, 62500, 65000, 67500,
         70000, 72500, 75000, 77500,
         80000, 82500, 85000, 87500,
         90000, 92500, 95000, 97500,
        100000,102500,105000,107500,
        110000,112500,115000,117500,
        120000,122500,125000,127500,
        130000,132500,135000,137500,
        140000,142500,145000,147500,
        150000,152500,155000,157500,
        160000,162500,165000,167500,
        170000,172500,175000,177500,
        180000,182500,185000,187500,
        190000,192500,195000,197500,
        200000,202500,205000,207500,
        210000,212500,215000,217500,
        220000,222500,225000,227500,
        230000,232500,235000,237500,
        240000,242500,245000,247500,
        250000,252500,255000,257500,
        260000,262500,265000,267500,
        270000,272500,275000,277500,
        280000,282500,285000,287500,
        290000,292500,295000,297500,
        300000,
        (1<< 1),(1<< 1)+1,
        (1<< 2),(1<< 2)+1,
        (1<< 3),(1<< 3)+1,
        (1<< 4),(1<< 4)+1,
        (1<< 5),(1<< 5)+1,
        (1<< 6),(1<< 6)+1,
        (1<< 7),(1<< 7)+1,
        (1<< 8),(1<< 8)+1,
        (1<< 9),(1<< 9)+1,
        (1<<10),(1<<10)+1,
        (1<<11),(1<<11)+1,
        (1<<12),(1<<12)+1,
        (1<<13),(1<<13)+1,
        (1<<14),(1<<14)+1,
        (1<<15),(1<<15)+1,
        (1<<16),(1<<16)+1,
        (1<<17),(1<<17)+1,
        (1<<18),(1<<18)+1,
    };
    sort(szs.begin(), szs.end());

    for(const size_t &sz: szs){
        os << sz;
        std::cout << "Size: " << sz << std::endl;

        std::list<coord_t> l;
        for(size_t i = 0; i < sz; ++i)
            l.push_back(coords.at(i));

        std::chrono::_V2::system_clock::time_point begin, end;

        QuadTreeClosestPoint t;
        
        begin = std::chrono::high_resolution_clock::now();
        for(size_t i = 0; i < REPEAT; ++i){
            t.initialize(l);
            t.run();
        }
        end = std::chrono::high_resolution_clock::now();
        
        double dt = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count())/double(REPEAT);
        os << "," << dt;

        os << "\n";
    }
}

void eval2DTree_QueryTime(const MapGraph &M, const std::vector<Run> &runs){
    std::ofstream os("eval/2d-tree-querytime.csv");
    os << std::fixed << std::setprecision(3);

    std::unordered_map<DWGraph::node_t, coord_t> nodes = M.getNodes();
    std::vector<coord_t> coords(nodes.size());
    {
        size_t i = 0;
        for(const std::pair<DWGraph::node_t, coord_t> &p: nodes)
            coords[i++] = p.second;
    }
    std::shuffle(coords.begin(), coords.end(), std::mt19937(0));
    
    std::vector<coord_t> candidates;
    for(const Run &r: runs)
        for(const coord_t &c: r.coords)
            candidates.push_back(c);

    const size_t N = 100000;
    const size_t REPEAT = 10;

    std::vector<coord_t> test_coords(N);
    std::set<size_t> indexes;
    while(indexes.size() < N) indexes.insert(rand()%candidates.size());
    size_t j = 0;
    for(const size_t &i: indexes){
        test_coords[j++] = candidates[i];
    }

    std::vector<size_t> szs = {
             1,
          1000,
          2000,
          3000,
          4000,
          5000,
          6000,
          7000,
          8000,
          9000,
         10000, 12500, 15000, 17500,
         20000, 22500, 25000, 27500,
         30000, 32500, 35000, 37500,
         40000, 42500, 45000, 47500,
         50000, 52500, 55000, 57500,
         60000, 62500, 65000, 67500,
         70000, 72500, 75000, 77500,
         80000, 82500, 85000, 87500,
         90000, 92500, 95000, 97500,
        100000,102500,105000,107500,
        110000,112500,115000,117500,
        120000,122500,125000,127500,
        130000,132500,135000,137500,
        140000,142500,145000,147500,
        150000,152500,155000,157500,
        160000,162500,165000,167500,
        170000,172500,175000,177500,
        180000,182500,185000,187500,
        190000,192500,195000,197500,
        200000,202500,205000,207500,
        210000,212500,215000,217500,
        220000,222500,225000,227500,
        230000,232500,235000,237500,
        240000,242500,245000,247500,
        250000,252500,255000,257500,
        260000,262500,265000,267500,
        270000,272500,275000,277500,
        280000,282500,285000,287500,
        290000,292500,295000,297500,
        300000,
        (1<< 1),(1<< 1)+1,
        (1<< 2),(1<< 2)+1,
        (1<< 3),(1<< 3)+1,
        (1<< 4),(1<< 4)+1,
        (1<< 5),(1<< 5)+1,
        (1<< 6),(1<< 6)+1,
        (1<< 7),(1<< 7)+1,
        (1<< 8),(1<< 8)+1,
        (1<< 9),(1<< 9)+1,
        (1<<10),(1<<10)+1,
        (1<<11),(1<<11)+1,
        (1<<12),(1<<12)+1,
        (1<<13),(1<<13)+1,
        (1<<14),(1<<14)+1,
        (1<<15),(1<<15)+1,
        (1<<16),(1<<16)+1,
        (1<<17),(1<<17)+1,
        (1<<18),(1<<18)+1,
    };
    sort(szs.begin(), szs.end());

    for(const size_t &sz: szs){
        os << sz;
        std::cout << "Size: " << sz << std::endl;

        std::list<coord_t> l;
        for(size_t i = 0; i < sz; ++i)
            l.push_back(coords.at(i));

        QuadTreeClosestPoint t;
        t.initialize(l);
        t.run();
        for(const coord_t &u: test_coords){
            std::chrono::_V2::system_clock::time_point begin, end;
            begin = std::chrono::high_resolution_clock::now();
            for(size_t i = 0; i < REPEAT; ++i){
                t.getClosestPoint(u);
            }
            end = std::chrono::high_resolution_clock::now();
            double dt = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count())/double(REPEAT);
            os << "," << dt;
        }
        os << "\n";
    }
}

int main(int argc, char *argv[]){
    try {
        if(argc < 2) throw std::invalid_argument("at least one argument must be provided");
        std::string opt = argv[1];
        
        std::cout << "Loading map..." << std::endl;
        MapGraph M("res/map/processed/AMP");
        std::cout << "Loaded map" << std::endl;

        if(opt == "2d-tree-buildtime"){ eval2DTree_BuildTime(M); return 0; }

        std::cout << "Loading runs..." << std::endl;
        std::vector<Run> runs = Run::loadRuns("res/data/pkdd15-i/pkdd15-i.runs");
        std::cout << "Loaded runs" << std::endl;

        if(opt == "2d-tree-querytime") eval2DTree_QueryTime(M, runs);
    } catch(const std::invalid_argument &e){
        std::cout << "Caught exception: " << e.what() << "\n";
        return -1;
    }
    return 0;
}
