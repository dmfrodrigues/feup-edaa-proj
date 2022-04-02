#include <fstream>
#include <iomanip>
#include <random>

#include "EdgeType.h"
#include "MapGraph.h"
#include "MapGraphView.h"
#include "MapRunsView.h"
#include "MapViewer.h"

#include "Run.h"

#include "QuadTreeClosestPoint.h"
#include "FortuneAlgorithm.h"

#include "graphviewer.h"

#include <X11/Xlib.h>

void view(const MapGraph &M){
    MapGraphView view(M);
    view.drawRoads();
}

void voronoi(const MapGraph &M) {
    std::vector<Site> sites;

    for (int i = 0; i < 10; i++)
        sites.push_back(Site{Vector2(i, i)});

    VoronoiDiagram diagram = FortuneAlgorithm().construct(sites);
}

void voronoi_display(const MapGraph &M) {
    MapGraphView view(M);
    view.drawVoronoi();
}

void view_runs(const MapGraph &M, const std::vector<Run> &runs){
    std::cout << "Building graph from runs..." << std::endl;
    const size_t N = 50000;
    MapGraph R;
    {
        std::map<coord_t, DWGraph::node_t> points;
        auto it = runs.begin();
        for(size_t i = 0; i < N; ++i, ++it){
            for(const coord_t &c: it->coords){
                if(!points.count(c)){
                    size_t u = points.size();
                    points[c] = u;
                    R.addNode(u, c);
                }
            }
        }
        std::cout << "Gathered run coords..." << std::endl;
        it = runs.begin();
        for(size_t i = 0; i < N; ++i, ++it){
            MapGraph::way_t w;
            for(const coord_t &c: it->coords){
                w.nodes.push_back(points.at(c));
            }
            R.addWay(w);
        }
        std::cout << "Built graph from runs" << std::endl;
    }

    MapRunsView view(R);
    view.drawRuns();
}

int main(int argc, char *argv[]){
    XInitThreads();

    try {
        if(argc < 2) throw std::invalid_argument("at least one argument must be provided");
        std::string opt = argv[1];

        std::cout << "Loading map..." << std::endl;
        MapGraph M("res/map/processed/AMP");
        std::cout << "Loaded map" << std::endl;

        if(opt == "view"){ view(M); return 0; }
        if(opt == "voronoi"){ voronoi(M); return 0; }
        if(opt == "voronoi-display"){ voronoi_display(M); return 0; }
        
        std::cout << "Loading runs..." << std::endl;
        std::vector<Run> runs = Run::loadRuns("res/data/pkdd15-i/pkdd15-i.runs");
        std::cout << "Loaded runs" << std::endl;

        if(opt == "view-runs"){ view_runs(M, runs); return 0; }
        
    } catch(const std::invalid_argument &e){
        std::cout << "Caught exception: " << e.what() << "\n";
        std::cout << "Usage: ./main (view | ...)\n";
        return EXIT_FAILURE;
    }
    return 0;
}
