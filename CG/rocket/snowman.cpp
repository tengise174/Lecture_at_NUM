// Snowman.cpp
// Demonstrates using Quadric Objects
// OpenGL SuperBible
// Richard S. Wright Jr.

#include "GL/freeglut.h" // OpenGL toolkit

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

////////////////////////////////////////////////////////////////////////////
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);
    // glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{

    // Light values and coordinates
    GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};

    glEnable(GL_DEPTH_TEST); // Hidden surface removal
    glFrontFace(GL_CCW);     // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);  // Do not calculate inside

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    // Refresh the Window
    glutPostRedisplay();
}

// Called to draw scene
void RenderScene(void)
{
    GLUquadricObj *pObj; // Quadric Object

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();
    // Move object back and do in place rotation
    glTranslatef(0.0f, 4.0f, -25.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    // Draw something
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    // Main Body
    glPushMatrix();
    glColor3f(1.0f, .0f, .0f);
    gluCylinder(pObj, .40f, .10f, 1.80f, 26, 13); // Bottom
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.40f, 26, 13);
    glEnable(GL_CULL_FACE);
    glTranslatef(0.0f, .0f, 1.80f); // Mid section
    gluDisk(pObj, 0.f, 0.10f, 26, 13);
    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0.0f, .0f, -4.80f); // Mid section
    gluCylinder(pObj, .60f, .4f, 3.00f, 26, 13);
    gluDisk(pObj, 0.f, 0.60f, 26, 13);
    // Bottom

    glTranslatef(0.0f, .0f, -2.80f); // Mid section
    gluCylinder(pObj, .60f, .6f, 2.80, 26, 13);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.60f, 26, 13);
    glEnable(GL_CULL_FACE);
    glColor4f(1.f, .0f, .0f, 0.5f);

    glTranslatef(0.0f, .60f, -1.20f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.10f, 26, 13);
    glEnable(GL_CULL_FACE); // Mid section
    gluCylinder(pObj, .40f, .1f, 1.80, 26, 13);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.40f, 26, 13);
    glEnable(GL_CULL_FACE);

    // leg
    glTranslatef(0.0f, -1.20f, -.0f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.10f, 26, 13);
    glEnable(GL_CULL_FACE); // Mid section
    gluCylinder(pObj, .40f, .1f, 1.80, 26, 13);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.40f, 26, 13);
    glEnable(GL_CULL_FACE);

    glTranslatef(0.6f, .60f, -.0f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.10f, 26, 13);
    glEnable(GL_CULL_FACE); // Mid section
    gluCylinder(pObj, .40f, .1f, 1.80, 26, 13);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.40f, 26, 13);
    glEnable(GL_CULL_FACE);

    glTranslatef(-1.2f, .0f, -.0f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.10f, 26, 13);
    glEnable(GL_CULL_FACE); // Mid section
    gluCylinder(pObj, .40f, .1f, 1.80, 26, 13);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, 0.40f, 26, 13);
    glEnable(GL_CULL_FACE);

    glColor3f(.6f, .6f, .6f);

    glTranslatef(1.2f, 0.0f, 3.3f);
    glRotatef(-90.0f, .0f, 180.0f, 0.0f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, .20f, 26, 13);
    glEnable(GL_CULL_FACE);

    glTranslatef(-.55f, 0.0f, -.0f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, .20f, 26, 13);
    glEnable(GL_CULL_FACE);

    glTranslatef(-.0f, 0.0f, 1.20f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, .20f, 26, 13);
    glEnable(GL_CULL_FACE);

    glTranslatef(.55f, 0.0f, -.0f);
    glDisable(GL_CULL_FACE);
    gluDisk(pObj, 0.f, .20f, 26, 13);
    glEnable(GL_CULL_FACE);

    // glTranslatef(0.0f, .550f, 0.0f); // Mid section
    // gluSphere(pObj, .3f, 26, 13);

    // glTranslatef(0.0f, 0.45f, 0.0f); // Head
    // gluSphere(pObj, 0.24f, 26, 13);

    // // Eyes
    // glColor3f(0.0f, 0.0f, 0.0f);
    // glTranslatef(0.1f, 0.1f, 0.21f);
    // gluSphere(pObj, 0.02f, 26, 13);

    // glTranslatef(-0.2f, 0.0f, 0.0f);
    // gluSphere(pObj, 0.02f, 26, 13);

    // // Nose
    // glColor3f(1.0f, 0.3f, 0.3f);
    // glTranslatef(0.1f, -0.12f, 0.0f);
    // gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
    // glPopMatrix();

    // // Hat
    // glPushMatrix();
    // glColor3f(0.0f, 0.0f, 0.0f);
    // glTranslatef(0.0f, 1.17f, 0.0f);
    // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    // gluCylinder(pObj, 0.17f, 0.17f, 0.4f, 26, 13);

    // // Hat brim
    // glDisable(GL_CULL_FACE);
    // gluDisk(pObj, 0.17f, 0.28f, 26, 13);
    // glEnable(GL_CULL_FACE);

    // glTranslatef(0.0f, 0.0f, 0.40f);
    // gluDisk(pObj, 0.0f, 0.17f, 26, 13);
    glPopMatrix();
    glPopMatrix();

    // Restore the matrix state
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modeling with Quadrics");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();

    return 0;
}