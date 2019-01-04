Linux 下的OpenGL编程环境搭建（Fedora）

1，打开命令终端，切换到root 用户

2，输入命令 locate libgult.so 检查本机是否已经有OpenGL开发的glut
库文件。如果有会给出相应目录 如下：(不同版本的Fedora可能保护的库的版本会不一样，不过
大概上都差不多）

  /usr/lib/libglut.so.3
  /usr/lib/libglut.so.3.9.0

3，输入命令 locate libGLU.so 检查GLU库，给出目录如下：
 
  /usr/lib/libGLU.so
  /usr/lib/libGLU.so.1
  /usr/lib/ibGLU.so.1.3.070700

4，输入命令 locate libGL.so 检查GL库，给出目录如下：
  
   /usr/lib/libGL.so
   /usr/lib/libGL.so.1

  /usr/lib/libGL.so.1.2

5，检查都有上面的库文件以后，需要安装进行开发所需要的头文件，这时检查Linux系统是否成功链接到互联网
   ，如果成功链接到了互联网则直接输入命令：yum install mesa* 或者 yum install mesa-libGL-devel mesa-libGLU-devel
然后回车，等到安装包下载好以后输入 y 然后就可以安装好 GL和 GLU 需要的头文件

6，输入命令 ：yum install freeglut* 或者 yum install freeglut-devel 安装glut.h头文件

7，输入命令 ：yum install glew* 或者 yum install glew-devel 安装个glew.h头文件（根据自己的需求安装）

8，创建一个文件 test.c 输入如下代码，把文件移动到一个系统的任意目录下（假如放在/home/myUseer/OpenGL下）

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

9，终端切换到文件的目录下，输入命令 gcc test.c -o test -lGL -lGLU -lglut 回车。编译，如果编译没有错则说明环境搭配好了
 
10， 运行编译的结果，输入命令 ./test 回车就可以看到一个窗口，就是上面的程序的运行结果。