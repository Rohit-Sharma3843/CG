#include<iostream>
#include<GL/glut.h>
using namespace std;
int le[500],re[500],flag=0;
void init(){
    glClearColor(0.0,0.0,0.2,0.0);
    glColor3f(0.0,1.0,0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500,500,-500,500,-1,1);
}
void edge(int x0,int y0,int x1,int y1){
    if(y0>y1){
        swap(x0,x1);
        swap(y0,y1);
    }
    int dx=x1-x0,dy=y1-y0;
    int x=x0;
    if(dy!=0){
        float slope=dx/dy;
        for(int y=y0;y<y1;y++){
            if(x<le[y]){
                le[y]=x;
            }
            if(x>re[y]){
                re[y]=x;
            }
            x+=slope;
        }
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100,100);
    glVertex2i(300,100);
    glVertex2i(200,200);
    glVertex2i(300,300);
    glVertex2i(100,300);
    glEnd();
    for(int i=0;i<500;i++){
        le[i]=500;
        re[i]=0;
    }
    edge(200,200,300,300);
    edge(300,300,100,300);
    edge(100,300,100,100);
    edge(100,250,100,100);
    edge(100,100,300,100);
    edge(300,100,200,200);
    if(flag==1){
        glColor3f(1.0,0.0,0.0);
        for(int i=0;i<500;i++){
            if(le[i]<re[i]){
                glBegin(GL_POINTS);
                for(int j=le[i];j<=re[i];j++){
                    glVertex2f(j,i);
                }
                glEnd();
            }
        }
    }
    glFlush();
}
void scanmenu(int id){
    if(id==1){
        flag=1;
    }
    else if(id==2){
        flag=0;
    }
    else{
        exit(0);
    }
    glutPostRedisplay();
}
void createmenu(){
    int s_id=glutCreateMenu(scanmenu);
    glutAddMenuEntry("Fill",1);
    glutAddMenuEntry("Clear",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Scaline Algo");
    createmenu();
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
