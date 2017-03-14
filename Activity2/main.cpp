/*
 TC3022. Computer Graphics
 Sergio Ruiz
 External geometry loader activity.
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>
// NATE ROBINS' OBJ MODEL LOADER (http://devernay.free.fr/hacks/glm/)
#include "glm.h" /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#include "cPlaneCreator.h"

#define DO_ROTATION_X

GLfloat		rotationY = 0.0f;
GLfloat		rotationX = 0.0f;

GLfloat*	mat0_specular;
GLfloat*	mat0_diffuse;
GLfloat*	mat0_shininess;
GLfloat*	light0_position;

GLMmodel*	model;
PlaneCreator* pc;

void init(void)
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glClearColor(0.2, 0.2, 0.2, 1.0);
    
    pc = new PlaneCreator(20, 30);
    //pc->create();
    
    /*
     A C T I V I T Y    2.  (90 minutes). PERSONAL / PROJECT TEAMS
     --------------------------------------------------------------
     
     1. GEOMETRY
     1.1 Open a new text file (in Notepad or some editor) and type lines 54-73:
     # THIS IS A COMMENT.
     
     # CUBE TC3022. EXTERNAL GEOMETRY
     
     # VERTICES. Format:
     # v X Y Z
     
     v -1.0 -1.0  1.0
     v  1.0 -1.0  1.0
     v  1.0  1.0  1.0
     v -1.0  1.0  1.0
     
     # NORMALS. Format:
     # vn X Y Z
     
     vn  0  0  1
     
     # FACES. Format:
     # f VERTEX_INDEX/TEXTURE_INDEX/NORMAL_INDEX
     # >>>Indices start from 1.
     
     f 1//1 2//1 3//1 4//1
     
     1.2 Save the file as "assets/cube.obj" inside this project.
     1.3 This information is the front face only. Finish the cube:
     1.3.1 Do not repeat vertices, normals or faces.
     1.3.2 To make the process easier, complete the faces in the following order: FRONT, RIGHT, BACK, LEFT, TOP, BOTTOM
     1.3.3 Write vertices forming each face starting from the bottom-left and counter-clockwise. Remember not to repeat the vertices you already have.
     1.4 When the cube is ready, create a new folder (ACTIVITY2) and copy your cube.obj and a screen capture of this application (NOT any other OBJ viewer) displaying your cube to the ACTIVITY2 folder.
     
     2. MATERIALS
     2.1 Open a new text file (in Notepad or some editor) and type lines 78-92:
     
     # cube_material.mtl for cube_material.obj
     
     # material name:
     newmtl cube_mat
     
     # light power:
     illum 1
     # AMBIENT COMPONENT:
     Ka 0.1 0.01 0.01
     # DIFFUSE COMPONENT:
     Kd 1.0 0.101960786 0.05882353
     # SPECULAR COPONENT:
     Ks 0.0 0.0 0.0
     # SPECULAR POWER:
     Ns 1.0
     
     2.2 Save the file as "assets/cube_material.mtl" inside this project.
     2.3 Save a copy of your "assets/cube.obj" file as "assets/cube_material.obj". Edit "assets/cube_material.obj" inserting the following lines before the vertices (insert around line 3):
     
     mtllib cube_material.mtl
     usemtl cube_mat
     
     2.4 You'll end up with two new files: "assets/cube_material.mtl" and "assets/cube_material.obj". Now edit this file (main.cpp), at the display function to go from this:
     
     glmDraw(model, GLM_SMOOTH);
     
     To this:
     
     glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);
     
     2.5 When the cube is ready, copy your cube_material.obj, cube_material.mtl and a screen capture of this application (NOT any other OBJ viewer) displaying your cube with materials to the ACTIVITY2 folder.
     
     3. SCALING
     3.1 Download mystery1.obj to your assets folder.
     3.2 Read the rest of this code and add a screen capture of this application displaying the full shape of mystery1.obj to your ACTIVITY2 folder.
     
     4. GENERATION OF NORMALS
     4.1 Download mystery2.obj to your assets folder.
     4.2 Read the rest of this code and use the GLM library to generate model normals after loading. Add a screen capture of this application displaying the full shape of mystery2.obj with the generated normals to your ACTIVITY2 folder.
     
     5. DO YOUR OWN
     5.1 Visit http://tf3dm.com/ and download an OBJ you like. Display it and save a screenshot of this application to your ACTIVITY2 folder.
     
     6. ADVANCED: CREATE GEOMETRY PROGRAMMATICALLY
     6.1 Complete cPlaneCreator.cpp and uncomment line 44 in this file to generate plane.obj (20x30 triangles).
     6.1.1 Complete the constructor with the size of "faces" (line 9). Consider that the final shape will have (rows-1) X (columns-1) cells, and each cell will have 2 faces (triangles).
     6.1.2 In the "create" function, fill the "faces" array and finally write the output to the file.
     6.2 Copy cPlaneCreator.cpp and plane.obj to your ACTIVITY2 folder.
     
     7. Upload ACTIVITY2.zip to Blackboard, checking that you send:
     
     * cube.obj (10 points)
     * cube SCREENSHOT (10 points)
     * cube_material.obj (10 points)
     * cube_material.mtl (10 points)
     * cube_material SCREENSHOT (10 points)
     * mystery1 SCREENSHOT (10 points)
     * mystery2 SCREENSHOT (10 points)
     * your geometry SCREENSHOT (10 points)
     * cPlaneCreator.cpp (10 points)
     * plane.obj (10 points)
     */
    
    model = glmReadOBJ("/Users/jacobotapia/Desktop/Activity2/cube.obj");
    // When the model is too big make it fit inside a 1x1x1 cube:
    //glmUnitize(model);
    // You can also scale it later:
    //glmScale(model, 2.0f);
    
    // When the model doesn't have normals, glm can add them automatically for you:
    //glmVertexNormals(model, 45.0f, false); // first per vertex...
    //glmFacetNormals(model); // ...and then per face
    
    light0_position = new GLfloat[4];
    light0_position[0] = 3;
    light0_position[1] = 3;
    light0_position[2] = 0;
    light0_position[3] = 1; // POINT LIGHT
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    
    mat0_specular = new GLfloat[4];
    mat0_specular[0] = 1.0f;
    mat0_specular[1] = 1.0f;
    mat0_specular[2] = 1.0f;
    mat0_specular[3] = 1.0f;
    
    mat0_diffuse = new GLfloat[4];
    mat0_diffuse[0] = 0.8f;
    mat0_diffuse[1] = 0.7f;
    mat0_diffuse[2] = 0.6f;
    mat0_diffuse[3] = 1.0f;
    
    mat0_shininess = new GLfloat[1];
    mat0_shininess[0] = 100.0f;
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat0_shininess);
    
    glPushMatrix();
    {
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glmDraw(model, GLM_MATERIAL | GLM_SMOOTH);
    }
    glPopMatrix();
    glutSwapBuffers();
}

void idle(void)
{
    rotationY += 0.08f;
    if (rotationY > 360)
    {
        rotationY = 0;
    }
    
#ifdef DO_ROTATION_X
    rotationX += 0.02f;
    if (rotationX > 360)
    {
        rotationX = 0;
    }
#endif
    
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)w / (GLdouble)h, 0.01, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2.1, 5.3, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("OBJ Loader!");
    glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
