#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t12");

  double lc = 1e-2;
  gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  
  gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
  gmsh::model::geo::addPoint(-0.1, 0, 0, lc, 3);
  
  gmsh::model::geo::addPoint(.2, 0, 0, lc, 4);
  gmsh::model::geo::addPoint(-0.2, 0, 0, lc, 5);
  
  gmsh::model::geo::addPoint(.15, 0, 0, lc, 6);
  gmsh::model::geo::addPoint(-0.15, 0, 0, lc, 7);
  
  gmsh::model::geo::addPoint(.25, 0, 0, lc, 8);
  gmsh::model::geo::addPoint(-0.25, 0, 0, lc, 9);
  
  gmsh::model::geo::addPoint(.3, 0, 0, lc, 10);
  gmsh::model::geo::addPoint(-0.3, 0, 0, lc, 11);
  
  gmsh::model::geo::addPoint(.2, 0, .05, lc, 12);
  gmsh::model::geo::addPoint(-0.2, 0, .05, lc, 13);
  
  gmsh::model::geo::addPoint(.2, 0, .1, lc, 14);
  gmsh::model::geo::addPoint(-0.2, 0, .1, lc, 15);
  
  
  gmsh::model::geo::addPoint(.2, 0, -.05, lc, 16);
  gmsh::model::geo::addPoint(-0.2, 0, -.05, lc, 17);
  
  gmsh::model::geo::addPoint(.2, 0, -.1, lc, 18);
  gmsh::model::geo::addPoint(-0.2, 0, -.1, lc, 19);
  
  gmsh::model::geo::addPoint(0, 0, -.1, lc, 20);
  gmsh::model::geo::addPoint(0, 0, .1, lc, 21);
  
  gmsh::model::geo::addPoint(0, 0, -.05, lc, 22);
  gmsh::model::geo::addPoint(0, 0, .05, lc, 23);
 // gmsh::model::geo::addPoint(.1, .1, 0, lc, 4);
  


  gmsh::model::geo::addCircleArc(2, 1, 3,1);
  gmsh::model::geo::addCircleArc(3, 1, 2,2);
  
  gmsh::model::geo::addCircleArc(6, 1, 7,3);
  gmsh::model::geo::addCircleArc(7, 1, 6,4);
  
  for (int i=0; i<2; i++){
  	gmsh::model::geo::addCircleArc(6+i, 4+i, 12+i,5+4*i);
  	gmsh::model::geo::addCircleArc(12+i, 4+i, 8+i,6+4*i);
  	gmsh::model::geo::addCircleArc(8+i, 4+i, 16+i,7+4*i);
  	gmsh::model::geo::addCircleArc(16+i, 4+i, 6+i,8+4*i);
  	}
  	
  for (int i=0; i<2; i++){
  	gmsh::model::geo::addCircleArc(2+i, 4+i, 14+i,13+4*i);
  	gmsh::model::geo::addCircleArc(14+i, 4+i, 10+i,14+4*i);
  	gmsh::model::geo::addCircleArc(10+i, 4+i, 18+i,15+4*i);
  	gmsh::model::geo::addCircleArc(18+i, 4+i, 2+i,16+4*i);
  	}
  
  
  gmsh::model::geo::addCircleArc(9, 1, 8,25);
  gmsh::model::geo::addCircleArc(8, 1, 9,26);
  
  gmsh::model::geo::addCircleArc(10, 1, 11,27);
  gmsh::model::geo::addCircleArc(11, 1, 10,28);
  
  gmsh::model::geo::addCircleArc(14, 21, 15,29);
  gmsh::model::geo::addCircleArc(15, 21, 14,30);
  
  gmsh::model::geo::addCircleArc(12, 23, 13,31);
  gmsh::model::geo::addCircleArc(13, 23, 12,32);
  
  gmsh::model::geo::addCircleArc(16, 22, 17,33);
  gmsh::model::geo::addCircleArc(17, 22, 16,34);
  
  gmsh::model::geo::addCircleArc(18, 20, 19,35);
  gmsh::model::geo::addCircleArc(19, 20, 18,36);



  gmsh::model::geo::addCurveLoop({4,5,-32,-9},1);
  gmsh::model::geo::addSurfaceFilling({1}, 1);
  
  gmsh::model::geo::addCurveLoop({-3,5,31,-9},2);
  gmsh::model::geo::addSurfaceFilling({2}, 2);
  
  gmsh::model::geo::addCurveLoop({4,-8,-34,12},3);
  gmsh::model::geo::addSurfaceFilling({3}, 3);
  
  gmsh::model::geo::addCurveLoop({-3,-8,33,12},4);
  gmsh::model::geo::addSurfaceFilling({4}, 4);
  
  gmsh::model::geo::addCurveLoop({2,13,-30,-17},5);
  gmsh::model::geo::addSurfaceFilling({5}, 5);
  
  gmsh::model::geo::addCurveLoop({-1,13,29,-17},6);
  gmsh::model::geo::addSurfaceFilling({6}, 6);
  
  gmsh::model::geo::addCurveLoop({2,-16,-36,20},7);
  gmsh::model::geo::addSurfaceFilling({7}, 7);
  
  gmsh::model::geo::addCurveLoop({-1,-16,35,20},8);
  gmsh::model::geo::addSurfaceFilling({8}, 8);
  
  gmsh::model::geo::addCurveLoop({11,34,-7,-25},9);
  gmsh::model::geo::addSurfaceFilling({9}, 9);
  
  gmsh::model::geo::addCurveLoop({10,25,-6,-32},10);
  gmsh::model::geo::addSurfaceFilling({10}, 10);
  
  gmsh::model::geo::addCurveLoop({31,10,-26,-6},11);
  gmsh::model::geo::addSurfaceFilling({11}, 11);
  
  gmsh::model::geo::addCurveLoop({33,-11,-26,7},12);
  gmsh::model::geo::addSurfaceFilling({12}, 12);
  
  gmsh::model::geo::addCurveLoop({35,-19,-27,15},13);
  gmsh::model::geo::addSurfaceFilling({13}, 13);
  
  gmsh::model::geo::addCurveLoop({19,36,-15,-28},14);
  gmsh::model::geo::addSurfaceFilling({14}, 14);
  
  gmsh::model::geo::addCurveLoop({18,28,-14,-30},15);
  gmsh::model::geo::addSurfaceFilling({15}, 15);
  
  gmsh::model::geo::addCurveLoop({29,18,-27,-14},16);
  gmsh::model::geo::addSurfaceFilling({16}, 16);
  


  gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4,5,6,7,8,9,10,11,12,13,14,15,16}, 1);
  gmsh::model::geo::addVolume({1});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(2);

  gmsh::write("t12.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}
