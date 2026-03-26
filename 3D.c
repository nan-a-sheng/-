#include <GL/glut.h>
#include <math.h>

// 立方体顶点 (中心在原点，边长为2)
float vertices[8][3] = {
    {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
    {-1,-1,1},  {1,-1,1},  {1,1,1},  {-1,1,1}
};

// 12条边
int edges[12][2] = {
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7}
};

float rotateX = 0.0f;
float rotateY = 0.0f;

// 初始化
void init() {
    glEnable(GL_DEPTH_TEST);   // 开启深度缓冲
    glClearColor(0.15, 0.15, 0.15, 1.0); // 灰色背景
    glLineWidth(2.0); // 线加粗，看得清楚
}

// 窗口大小改变时重新计算投影
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// 绘制
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 相机位置：能稳稳看到立方体
    gluLookAt(3.5f, 3.5f, 3.5f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // 旋转立方体
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    // 青色线框
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) {
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);
    }
    glEnd();

    glutSwapBuffers();
}

// 自动旋转
void update(int value) {
    rotateX += 0.6f;
    rotateY += 0.9f;

    if (rotateX > 360) rotateX -= 360;
    if (rotateY > 360) rotateY -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("3D透视旋转立方体");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
