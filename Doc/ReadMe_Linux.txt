Linux �µ�OpenGL��̻������Fedora��

1���������նˣ��л���root �û�

2���������� locate libgult.so ��鱾���Ƿ��Ѿ���OpenGL������glut
���ļ�������л������ӦĿ¼ ���£�(��ͬ�汾��Fedora���ܱ����Ŀ�İ汾�᲻һ��������
����϶���ࣩ

  /usr/lib/libglut.so.3
  /usr/lib/libglut.so.3.9.0

3���������� locate libGLU.so ���GLU�⣬����Ŀ¼���£�
 
  /usr/lib/libGLU.so
  /usr/lib/libGLU.so.1
  /usr/lib/ibGLU.so.1.3.070700

4���������� locate libGL.so ���GL�⣬����Ŀ¼���£�
  
   /usr/lib/libGL.so
   /usr/lib/libGL.so.1

  /usr/lib/libGL.so.1.2

5����鶼������Ŀ��ļ��Ժ���Ҫ��װ���п�������Ҫ��ͷ�ļ�����ʱ���Linuxϵͳ�Ƿ�ɹ����ӵ�������
   ������ɹ����ӵ��˻�������ֱ���������yum install mesa* ���� yum install mesa-libGL-devel mesa-libGLU-devel
Ȼ��س����ȵ���װ�����غ��Ժ����� y Ȼ��Ϳ��԰�װ�� GL�� GLU ��Ҫ��ͷ�ļ�

6���������� ��yum install freeglut* ���� yum install freeglut-devel ��װglut.hͷ�ļ�

7���������� ��yum install glew* ���� yum install glew-devel ��װ��glew.hͷ�ļ��������Լ�������װ��

8������һ���ļ� test.c �������´��룬���ļ��ƶ���һ��ϵͳ������Ŀ¼�£��������/home/myUseer/OpenGL�£�

#include <GL/glut.h>


  void init();


  void display();


int main(int argc, char* argv[])


{

  glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);


        glutInitWindowPosition(0, 0);

        glutInitWindowSize(300, 300);


        glutCreateWindow("OpenGL 3D View");

        init(); glutDisplayFunc(display);


        glutMainLoop();


        return 0;


}


void init()

{


            glClearColor(0.0, 0.0, 0.0, 0.0);

            glMatrixMode(GL_PROJECTION);


            glOrtho(-5, 5, -5, 5, 5, 15);


            glMatrixMode(GL_MODELVIEW);


            gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);


}


void display()


{


                glClear(GL_COLOR_BUFFER_BIT);

                glColor3f(1.0, 0, 0);


                glutWireTeapot(3);

                glFlush();

}

9���ն��л����ļ���Ŀ¼�£��������� gcc test.c -o test -lGL -lGLU -lglut �س������룬�������û�д���˵�������������
 
10�� ���б���Ľ������������ ./test �س��Ϳ��Կ���һ�����ڣ���������ĳ�������н����