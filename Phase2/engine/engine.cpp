#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "../data_structs/Settings.hpp"

// Variáveis da câmara
int height, width;
float alphaCam, betaCam, radius;
float camx, camy, camz;
float lookAtx, lookAty, lookAtz;
float upx, upy, upz;
float fov, nearPlane, farPlane;

// fps
int timebase = 0;
int frame = 0;
float fps = 0.0f;

int startX, startY, tracking = 0;
float yaw = 0.0f, pitch = 0.0f;

Settings set;
Group group;

GLenum drawmode = GL_LINE; // Modo de Desenho
bool showAxes = true;      // Eixos

void updateWindowTitle() {
    char coords[100];
    sprintf(coords, "Camera Position: x=%.2f, y=%.2f, z=%.2f | FPS: %.2f", camx, camy, camz, fps);

    // Atualiza o título da janela
    glutSetWindowTitle(coords);
}

void updateCamera() {
    // Atualiza a direção da câmera com base no yaw e pitch
    lookAtx = camx + cos(yaw) * cos(pitch);
    lookAty = camy + sin(pitch);
    lookAtz = camz + sin(yaw) * cos(pitch);
    
}

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

void updateFPS() {
    int time = glutGet(GLUT_ELAPSED_TIME);
    frame++;

    if (time - timebase > 100) { // Atualiza FPS a cada segundo
        fps = frame * 1000.0f / (time - timebase);
        timebase = time;
        frame = 0;
    }

    updateWindowTitle();

    glutPostRedisplay();
}

void drawFigures(Group g) {

    std::vector<Transform> transformations = getTransformations(g);
    std::vector<Model> models = getModels(g);
    std::vector<Group> subgroups = getSubgroup(g);

    glPushMatrix();

    for (int i = 0; i < transformations.size(); i++) {
        char type = getType(transformations[i]);
        Point tv = getTransVal(transformations[i]);

        if(type == 'R'){
            float angle = getAngle(transformations[i]);
            glRotatef(angle, getX(tv), getY(tv), getZ(tv));
        } else if (type == 'T'){
            glTranslatef(getX(tv), getY(tv), getZ(tv));
        } else if (type == 'S'){
            glScalef(getX(tv), getY(tv), getZ(tv));
        }
    }   

    glBegin(GL_TRIANGLES);
    
    for (int i = 0; i < models.size(); i++) {
        std::vector<Point> m_points = getPoints(models[i]);
        float r,g,b;
        getColor(models[i], r, g, b);

        glColor3f(r,g,b);

        for (int j = 0; j<m_points.size(); j++){
            glVertex3f(getX(m_points[j]),getY(m_points[j]), getZ(m_points[j]));
        }
    }

    glEnd();


    for(int i = 0; i < subgroups.size(); i++){
        drawFigures(subgroups[i]);
    }
    glPopMatrix();
}

void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    // primeiro triplo: onde a camera esta
    // segundo triplo: para onde a camera esta a olhar
    gluLookAt(camx, camy, camz,
            lookAtx, lookAty, lookAtz,
            upx, upy, upz);

    if (showAxes) {
        glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);

        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);

        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
        glEnd();
    }
        
          
    glPolygonMode(GL_FRONT_AND_BACK, drawmode);
    
    drawFigures(group); 

    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
    
    float speed = 0.2f;

    switch (c) {
        case 'w':  // Andar para frente
            camx += cos(yaw) * cos(pitch) * speed;
            camy += sin(pitch) * speed;
            camz += sin(yaw) * cos(pitch) * speed;
            break;
        case 's':  // Andar para trás
            camx -= cos(yaw) * cos(pitch) * speed;
            camy -= sin(pitch) * speed;
            camz -= sin(yaw) * cos(pitch) * speed;
            break;
        case 'd':
            camx -= cos(yaw - M_PI / 2) * speed;
            camz -= sin(yaw - M_PI / 2) * speed;
            break;
        case 'a':
            camx += cos(yaw - M_PI / 2) * speed;
            camz += sin(yaw - M_PI / 2) * speed;
            break;
        case '+': // Subir
            camy += 0.2f;
            break;
        case '-': // Descer
            camy -= 0.2f;
            break;
        case 'm': // Altera os modos de desenho
            if (drawmode == GL_FILL) drawmode = GL_LINE;
            else if (drawmode == GL_LINE) drawmode = GL_POINT;
            else drawmode = GL_FILL;
            break;
        case 'p': // Altera a visualização dos eixos
            showAxes = !showAxes;
            break;
    }
    updateCamera();
    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        tracking = 0;
    }
}

void processMouseMotion(int xx, int yy) {

    int deltaX = xx - startX;
    int deltaY = yy - startY;

    if (tracking == 1) {
        yaw += deltaX * 0.01f;  // Sensibilidade do rato
        pitch -= deltaY * 0.01f;

        // Limita o pitch para evitar inversões
        if (pitch > M_PI / 2) pitch = M_PI / 2;
        if (pitch < -M_PI / 2) pitch = -M_PI / 2;
    }

    startX = xx;
    startY = yy;

    updateCamera();
}


int main(int argc, char **argv) {

    if(argc<2){
        fprintf(stderr, "Usage: %s <path_to_xml>\n", argv[0]);
        return 1;
    }

    set = xmlToSettings(argv[1]);

    height  = getHeight(set);
    width   = getWidth(set);
    camx    = getXPosCam(set);
    camy    = getYPosCam(set);
    camz    = getZPosCam(set);
    radius  = sqrt(camx*camx + camy*camy + camz*camz);
    lookAtx = getXLookAt(set);
    lookAty = getYLookAt(set);
    lookAtz = getZLookAt(set);
    upx     = getXUp(set);
    upy     = getYUp(set);
    upz     = getZUp(set);
    fov     = getFov(set);
    nearPlane = getNear(set);
    farPlane = getFar(set);
    group = getGroup(set);
    

    yaw = atan2f(lookAtz - camz, lookAtx - camx);
    pitch = atan2f(lookAty - camy, sqrtf(pow(lookAtx - camx, 2) + pow(lookAtz - camz, 2)));

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(width,height);
    glutCreateWindow("Projeto CG");

    // Inicializar o tempo base para FPS
    timebase = glutGet(GLUT_ELAPSED_TIME);
        
    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

    // fps
    glutIdleFunc(updateFPS);
    
    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}
