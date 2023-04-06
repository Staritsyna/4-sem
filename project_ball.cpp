#include <math.h>
#include <GL/glut.h>
#include <set>
#include <gmsh.h>
#include <iostream>



//dtart time
float t = 0.0;
//ball's radius
float r = 0.4;
//time interval
float dt=0.0001;

std::vector<float> MF(6,0);//moments and forces
std::vector<float> coor={-1,-1,0};//coordinates
std::vector<float> vel={3,6,0};//velocity

std::vector<float> accel(3,0);//acceleration
std::vector<float> rot={0,0,1000};//rotation
std::vector<float> ang(3,0);//angle
std::vector<float> u(3,0);//velocity of flow
float mu=0.01;
//gas density
float p_o=0;
//ball density
float p_t=2;
//mass
float m = p_t*4*M_PI*pow(r,3)/3;
//acceleration of free fall
float g=9.81;



//create gmsh model of ball? radius=r
void gmsh_ball(){
    gmsh::initialize();
    gmsh::model::add("m");
    double lc = 1e-1;
    gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  
    gmsh::model::geo::addPoint(r, 0, 0, lc, 2);
    gmsh::model::geo::addPoint(-r, 0, 0, lc, 3);

    gmsh::model::geo::addPoint(0, r, 0, lc, 4);
    gmsh::model::geo::addPoint(0, -r, 0, lc, 5);

    gmsh::model::geo::addPoint(0, 0, r, lc, 6);
    gmsh::model::geo::addPoint(0, 0, -r, lc, 7);
    
    gmsh::model::geo::addCircleArc(2, 1, 4,1);
    gmsh::model::geo::addCircleArc(4, 1, 3,2);
    gmsh::model::geo::addCircleArc(3, 1, 5,3);
    gmsh::model::geo::addCircleArc(5, 1, 2,4);
    
    gmsh::model::geo::addCircleArc(2, 1, 6,5);
    gmsh::model::geo::addCircleArc(6, 1, 3,6);
    gmsh::model::geo::addCircleArc(3, 1, 7,7);
    gmsh::model::geo::addCircleArc(7, 1, 2,8);
    
    gmsh::model::geo::addCircleArc(4, 1, 6,9);
    gmsh::model::geo::addCircleArc(6, 1, 5,10);
    gmsh::model::geo::addCircleArc(5, 1, 7,11);
    gmsh::model::geo::addCircleArc(7, 1, 4,12);
    
    
    gmsh::model::geo::addCurveLoop({1,9,-5},1);
    gmsh::model::geo::addSurfaceFilling({1}, 1);
    gmsh::model::geo::addCurveLoop({2,-6,-9},2);
    gmsh::model::geo::addSurfaceFilling({2}, 2);
    gmsh::model::geo::addCurveLoop({3,-10,6},3);
    gmsh::model::geo::addSurfaceFilling({3}, 3);
    gmsh::model::geo::addCurveLoop({4,5,10},4);
    gmsh::model::geo::addSurfaceFilling({4}, 4);
    
    gmsh::model::geo::addCurveLoop({1,-12,8},5);
    gmsh::model::geo::addSurfaceFilling({5}, 5);
    gmsh::model::geo::addCurveLoop({2,7,12},6);
    gmsh::model::geo::addSurfaceFilling({6}, 6);
    gmsh::model::geo::addCurveLoop({3,11,-7},7);
    gmsh::model::geo::addSurfaceFilling({7}, 7);
    gmsh::model::geo::addCurveLoop({4,-8,-11},8);
    gmsh::model::geo::addSurfaceFilling({8}, 8);


    gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4,5,6,7,8}, 1);
  
   // gmsh::model::geo::addVolume({1});
    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);
 }   
void drawFilledelipse(GLfloat x, GLfloat y, GLfloat xcenter,GLfloat ycenter) { 
    int i; 
    int triangleAmount = 20; //# of triangles used to draw circle 
 
    //GLfloat radius = 0.8f; //radius 
    GLfloat twicePi = 2.0f * M_PI; 
 
    glBegin(GL_TRIANGLE_FAN); 
    glVertex2f(x, y); // center of circle 
    for (i = 0; i <= triangleAmount; i++) { 
        glVertex2f( 
            x + ((xcenter+1)* cos(i * twicePi / triangleAmount)), 
            y + ((ycenter-1)* sin(i * twicePi / triangleAmount)) 
        ); 
    } 
    glEnd(); 
}
void changeSize(int w, int h) { 
 
    // Prevent a divide by zero, when window is too short 
    // (you cant make a window of zero width). 
    if(h == 0) 
        h = 1; 
 
    float ratio = 1.0* w / h; 
 
    // Reset the coordinate system before modifying 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
     
    // Set the viewport to be the entire window 
    glViewport(0, 0, w, h); 
 
    // Set the correct perspective. 
    gluPerspective(45,ratio,1,1000); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
    gluLookAt(0.0,0.0,5.0,  
              0.0,0.0,-1.0, 
              0.0f,1.0f,0.0f); 
} 
//calculate force and moments 
void SpinM(std::vector<float>& Moment_force,std::vector<float>& v,std::vector<float>& w,std::vector<float>& u) {
    std::vector<double> nodesCoord;
    std::vector<std::size_t> nodeTags;
    std::vector<double> parametricCoord;
    gmsh::model::mesh::getNodes(nodeTags, nodesCoord, parametricCoord);
    
    Moment_force[0]=0;
    Moment_force[1]=0;
    Moment_force[2]=0;
  
    for (int i=0; i<nodeTags.size();i++){

    	float v_x=-v[0]+(nodesCoord[i*3+2]*w[1]-nodesCoord[i*3+1]*w[2])+u[0];
    	float v_y=-v[1]+(nodesCoord[i*3]*w[2]-nodesCoord[i*3+2]*w[0])+u[1];
    	float v_z=-v[2]+(nodesCoord[i*3+1]*w[0]-nodesCoord[i*3]*w[1])+u[2];
    	Moment_force[0]+= -mu*(-nodesCoord[i*3+2]*v_y+v_z*nodesCoord[i*3+1]);
    	Moment_force[1]+= -mu*(nodesCoord[i*3+2]*v_x-v_z*nodesCoord[i*3]);
    	Moment_force[2]+= -mu*(nodesCoord[i*3]*v_y-v_x*nodesCoord[i*3+1]);
    	
    }
   //calculate forces on the center
   Moment_force[3] = (p_o*4*M_PI*pow(r,3)/3)*(w[1]*(u[2]-v[2])-w[2]*(u[1]-v[1]));
   Moment_force[4] = (p_o*4*M_PI*pow(r,3)/3)*(w[2]*(u[0]-v[0])-w[0]*(u[2]-v[2]))-(p_t-p_o)*g*4*M_PI*pow(r,3)/3;
   Moment_force[5] = (p_o*4*M_PI*pow(r,3)/3)*(w[0]*(u[1]-v[1])-w[1]*(u[0]-v[0]));
	
}

//create image
void renderScene(void) { 
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glClearColor(0.0f, 0.5f , 1.5f,0.0f); 
    
    glPushMatrix(); 
    
    glPushMatrix(); 
    glTranslatef(coor[0],coor[1],coor[2]); 
    glRotatef(ang[0],1.0,0.0,0.0); 
    glRotatef(ang[1],0.0,1.0,0.0); 
    glRotatef(ang[2],0.0,0.0,1.0);
    glColor3f(1.0f, 1.5f , 0.5f);  
    glutSolidSphere(r,30,30); 
    glColor3f(1.0f, 0.5f , 0.5f);
    glBegin(GL_TRIANGLES); 
        float a = 0.1;
    	glVertex3f(-a,-a,0.0); 
        glVertex3f(-a,a,0.0); 
        glVertex3f(a,-a,0.0); 
     
    glEnd(); 
    glBegin(GL_TRIANGLES); 

    	glVertex3f(a,-a,0.0); 
        glVertex3f(a,a,0.0); 
        glVertex3f(-a,a,0.0); 
     
    glEnd(); 
    
    glPopMatrix(); 

    
    for (int i=0;i< MF.size();i++){MF[i]=0;}
    SpinM(MF,vel, rot, u);
    for (int i=0;i< ang.size();i++){ang[i]+=rot[i]*dt;}
    for (int i=0;i< rot.size();i++){rot[i]+=MF[i]*dt*2/(m*r*r);}

    for (int i=0;i< accel.size();i++){accel[i]=MF[3+i]/m;}
    for (int i=0;i< vel.size();i++){vel[i]+=accel[i]*dt;}
    for (int i=0;i< coor.size();i++){coor[i]+=vel[i]*dt+accel[i]*pow(dt,2)/2;}

    t+=dt;
    glutSwapBuffers(); 
} 
 

 
int main(int argc, char **argv) { 

    gmsh_ball();
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowPosition(100,100); 
    glutInitWindowSize(720,820); 
    glutCreateWindow("Ball"); 
  
    glutDisplayFunc(renderScene); 
    glutIdleFunc(renderScene); 
    glutReshapeFunc(changeSize); 
 
    glutMainLoop(); 
}
