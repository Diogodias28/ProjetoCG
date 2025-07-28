#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <sys/stat.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "../data_structs/Settings.hpp"

extern void getGlobalCatmullRomPoint(float gt, std::vector<std::vector<float>> controlPoints, float *pos, float *deriv);

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
bool showCurve = true;     // Linha da Curva
GLuint vertexCount, buffer[2];


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

    if (time - timebase > 100) { // Atualiza FPS
        fps = frame * 1000.0f / (time - timebase);
        timebase = time;
        frame = 0;
    }

    updateWindowTitle();

    glutPostRedisplay();
}

void drawCatmullRomCurve(const std::vector<std::vector<float>>& controlPoints) {
    if (controlPoints.size() < 4) return; // Precisa de pelo menos 4 pontos
    
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    const int segments = 100;
    for (int i = 0; i <= segments; ++i) {
        float t = i / (float)segments;
        float pos[3];
        getGlobalCatmullRomPoint(t, controlPoints, pos, nullptr);
        glVertex3fv(pos);
    }
    
    glEnd();
}

void drawFigures(Group g) {

    std::vector<Transform> transformations = getTransformations(g);
    std::vector<Model> models = getModels(g);
    std::vector<Group> subgroups = getSubgroup(g);

    
    glPushMatrix();

    for (auto& t : transformations) {
        char type = getType(t);
        Point tv = getTransVal(t);
        float time = getTime(t);

        if(type == 'R' && time > 0) {
            
            float angle = (glutGet(GLUT_ELAPSED_TIME)/1000.0f/time) * 360.0f;
            glRotatef(angle, getX(tv), getY(tv), getZ(tv));
        }
        else if(type == 'T' && time > 0) {
            std::vector<Point> points = getPoints(t);
            std::vector<std::vector<float>> controlPoints;
            for(auto& p : points) {
                controlPoints.push_back({getX(p), getY(p), getZ(p)});
            }
            
            if(showCurve){
                drawCatmullRomCurve(controlPoints);
            }
            
            float pos[3], deriv[3];
            float gt = fmod(glutGet(GLUT_ELAPSED_TIME)/1000.0f, time)/time;
            getGlobalCatmullRomPoint(gt, controlPoints, pos, deriv);
            
            
            glTranslatef(pos[0], pos[1], pos[2]);
            
            
            if(getAlign(t)) {
                float z[3], y[3], rot[16];
                float up[3] = {0,1,0}; 
                
                
                normalizeVector(deriv);
                
                
                cross(deriv, up, z);
                normalizeVector(z);
                
                
                cross(z, deriv, y);
                normalizeVector(y);
                
               
                rot[0] = deriv[0]; rot[1] = deriv[1]; rot[2] = deriv[2]; rot[3] = 0;
                
                rot[4] = y[0]; rot[5] = y[1]; rot[6] = y[2]; rot[7] = 0;
                
                rot[8] = z[0]; rot[9] = z[1]; rot[10] = z[2]; rot[11] = 0;
                
                rot[12] = 0; rot[13] = 0; rot[14] = 0; rot[15] = 1;
                
                glMultMatrixf(rot);
            }
        }
        else {
            // Transformações estáticas
            switch(type) {
                case 'R': 
                    glRotatef(getAngle(t), getX(tv), getY(tv), getZ(tv)); 
                    break;
                case 'T': 
                    glTranslatef(getX(tv), getY(tv), getZ(tv)); 
                    break;
                case 'S': 
                    glScalef(getX(tv), getY(tv), getZ(tv)); 
                    break;
            }
        }
    }

    
    for (int i = 0; i < models.size(); i++) {
        float r,g,b;
        getColor(models[i], r, g, b);

        glColor3f(r,g,b);

        vertexCount = getVertexCount(models[i]);
        buffer[0] = getBuffer_0(models[i]);
        buffer[1] = getBuffer_1(models[i]);

        glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
        glVertexPointer(3,GL_FLOAT,0,0);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }


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
        case 'c': // Altera a visibilidade das linhas das curvas
            showCurve = !showCurve;
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
    if (set == NULL) {
        fprintf(stderr, "Failed to load settings from XML file\n");
        return 1; 
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
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Projeto CG");

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);   

    //Init model buffers
    initGroupBuffers(group);

    // VBO and Normal
    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY); (só na próxima fase)

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
    
    // enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}