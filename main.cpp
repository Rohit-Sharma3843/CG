#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
int selection=1;
float X1,Y1,X2,Y2;
class Line{
    void dda(){
        float dx,dy,xin,yin,step,x,y;
        dx=X2-X1;
        dy=Y2-Y1;
        cout<<"DDA"<<endl;
        x=X1,y=Y1;
        if(abs(dx)>abs(dy)){
            step=dx;
        }
        else{
            step=dy;
        }
        xin=dx/step;
        yin=dy/step;
        glBegin(GL_POINTS);
        glColor3f(1.0,1.0,0);
        glVertex2f(x,y);
        glEnd();
        for(int i=1;i<=step;i++){
            x+=xin;
            y+=yin;
            glBegin(GL_POINTS);
            glColor3f(1.0,1.0,0);
            glVertex2f(x,y);
        }
        glEnd();
        glutPostRedisplay();
        glFlush();
    }
    void Bresenham(){
        cout<<"Bresenham"<<endl;
        float x,y,dx,dy,pk;
        x=X1,y=Y1,dx=X2-X1,dy=Y2-Y1;
        pk=2*dy-dx;
        for(int i=1;i<=dx;i++){
            glBegin(GL_POINTS);
            glColor3f(0.0,0.5,0);
            glVertex2i(x,y);
            if(pk<0){
                pk+=2*dy;
                x+=1;
            }
            else{
                pk+=2*dy-2*dx;
                x+=1;
                y+=1;
            }
        }
        glEnd();
        glutPostRedisplay();
        glFlush();
    }
public:
    static void display(){
        Line l;
        switch(selection){
            case 1:l.dda();break;
            case 2:l.Bresenham();break;
            default:break;
        }
    }
};
void init(){
    glClearColor(0.0,0.0,0.2,0.0);
    glLoadIdentity();
    glOrtho(-500,500,-500,500,-1,1);
    glMatrixMode(GL_PROJECTION);
    glViewport(0,0,640,640);
}
void lineGeneration(int i){
    if(i==4){exit(0);}
}
void keyboard(unsigned char key,int x,int y){
    if(key=='D' || key=='d'){selection =1;}
    else if(key=='b' || key=='B'){selection=2;}
    else if(key=='3'){
        exit(0);
    }
}
void createMenu(){
    int s_id=glutCreateMenu(lineGeneration);
    glutAddMenuEntry("DDA",1);
    glutAddMenuEntry("Bresenham",2);
    int m_id=glutCreateMenu(lineGeneration);
    glutAddSubMenu("Algorithm",s_id);
    glutAddMenuEntry("Exit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc,char**argv){
    cout<<"Enter coordinates : ";
    cin>>X1>>Y1>>X2>>Y2;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutCreateWindow("Line Generation ");
    init();
    glutDisplayFunc(Line :: display);
    glutKeyboardFunc(keyboard);
    createMenu();
    glutMainLoop();
    return 0;
}
