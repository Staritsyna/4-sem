#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t2");

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



  gmsh::model::geo::addCurveLoop({4,5,32,-9}, 40);
  gmsh::model::geo::addPlaneSurface({40}, 40);
  
  gmsh::model::geo::addCurveLoop({28,14,-30,18}, 41);
  gmsh::model::geo::addPlaneSurface({41}, 41);
  

//  gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4}, 1);
 // gmsh::model::geo::addVolume({1});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(2);

  gmsh::write("t12.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}
