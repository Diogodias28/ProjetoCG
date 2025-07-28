#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "../data_structs/Point.hpp"
#include "../data_structs/Model.hpp"
#include "../data_structs/Settings.hpp"

// Variáveis da câmara
int height;
int width;
float alphaCam;
float betaCam;
float radius;
float camx;
float camy;
float camz;
float lookAtx;
float lookAty;
float lookAtz;
float upx;
float upy;
float upz;
float fov;
float nearPlane;
float farPlane;

Settings set;
std::vector<Model> models = std::vector<Model>();

GLenum drawmode = GL_LINE; // Modo de Desenho

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawFigures(std::vector<Model> models) {

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < models.size(); i++) {
		std::vector<Point> m_points = getPoints(models[i]);
		for (int j = 0; j<m_points.size(); j++){
			glVertex3f(getX(m_points[j]),getY(m_points[j]), getZ(m_points[j]));
		}
	}
	glEnd();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	// primeiro triplo: onde a camera esta
	// segundo triplo: para onde a camera esta a olhar
	// (r, alphaCam, betaCam) -> (x, y, z)
	gluLookAt(radius*cosf(betaCam)*sinf(alphaCam),radius*sinf(betaCam),radius*cosf(betaCam)*cosf(alphaCam),
		      lookAtx, lookAty, lookAtz,
			  upx,upy,upz); 

    glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f( 100.0f, 0.0f, 0.0f);
        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f,-100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f,-100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
          
	glPolygonMode(GL_FRONT_AND_BACK, drawmode);

	glColor3f(1.0f, 0.6f, 0.7f);
	drawFigures(models); 

	// End of frame
	glutSwapBuffers();

}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here
	switch (c) {
		case 'w':
			if (betaCam <= (M_PI / 2)) betaCam += 0.5f;
			break;
		case 's':
			if (betaCam >= (-M_PI / 2)) betaCam -= 0.5;
			break;
		case 'd':
			alphaCam -= 0.2f;
			break;
		case 'a':
			alphaCam += 0.2f;
			break;
		case '+': // Zoom In
			radius -= 0.2f;
			break;
		case '-': // Zoom out
			radius += 0.2f;
			break;
		case 'm': // Altera os modos de desenho
			if (drawmode == GL_FILL) drawmode = GL_LINE;
			else if (drawmode == GL_LINE) drawmode = GL_POINT;
			else drawmode = GL_FILL;
			break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}


int main(int argc, char **argv) {

	if(argc<2){
		fprintf(stderr, "Usage: %s <path_to_xml>\n", argv[0]);
		return 1;
	}

	set = xmlToSettings(argv[1]);

	std::vector<std::string> paths = getPaths(set);

	for (int i = 0; i < paths.size(); i++) {
		std::vector<Point> points = readFromFile(paths[i]);
		if (points.empty()) {
			fprintf(stderr, "Error: Could not read points from file %s\n", paths[i].c_str());
		}
		Model m = makeModel(points);
    	models.push_back(m);      
	}

	height  = getHeight(set);
	width   = getWidth(set);
	camx    = getXPosCam(set);
	camy    = getYPosCam(set);
	camz    = getZPosCam(set);
	radius  = sqrt(camx*camx + camy*camy + camz*camz);
	lookAtx = getXLookAt(set);
	lookAty = getYLookAt(set);
	lookAtz = getZLookAt(set);
	upx 	= getXUp(set);
	upy 	= getYUp(set);
	upz 	= getZUp(set);
	alphaCam    = acos(camz/sqrt(camx*camx + camz*camz));
	betaCam  = asin(camy/radius);
	fov     = getFov(set);
	nearPlane = getNear(set);
	farPlane     = getFar(set);

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width,height);
	glutCreateWindow("Projeto CG");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
