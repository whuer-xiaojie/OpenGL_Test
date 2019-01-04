#include <iostream>
// GLEW
#define GLEW_STATIC
//#include <GL/glut.h>
//#include<unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void checkError(GLuint shader, GLbyte status);

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSourceOrange = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const GLchar* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

GLuint vertexShader, fragmentShaderOrange, fragmentShaderYellow, shaderProgramOrange, shaderProgramYellow;
GLuint VBO1, VAO1;
GLuint VBO2, VAO2, EBO2;

void shaderInit() {
    // 顶点 shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 检查编译错误
    checkError(vertexShader, GL_COMPILE_STATUS);

    // 初始化橙色片段 shader
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glCompileShader(fragmentShaderOrange);
    // 检查事件错误
    checkError(fragmentShaderOrange, GL_COMPILE_STATUS);

    //初始化黄色片段shader
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    glCompileShader(fragmentShaderYellow);
    // 检查事件错误
    checkError(fragmentShaderYellow, GL_COMPILE_STATUS);

    // 链接橙色 shader
    shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    // 检查链接错误
    checkError(shaderProgramOrange, GL_LINK_STATUS);

    //链接黄色 shader
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    // 检查链接错误
    checkError(shaderProgramYellow, GL_LINK_STATUS);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);
}

void vertexObjectInit() {
    //不使用索引缓冲对象用两个三角形绘制一个梯形
    // 设置顶点缓存和属性指针
    GLfloat vertices1[] = {
        -0.5f, 0.2f, 0.0f, // BottomLeft  
        0.5f, 0.2f, 0.0f, // BottomRight 
        -0.2f,  0.5f, 0.0f,  // TopLeft 

        0.5f, 0.2f, 0.0f, // BottomRight 
        -0.2f,  0.5f, 0.0f,  // TopLeft
        0.2f,  0.5f, 0.0f  // TopRight
    };
    //创建索引缓冲对象
    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    // 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);// 这个方法将顶点属性指针注册到VBO作为当前绑定顶点对象，然后我们就可以安全的解绑
    glBindVertexArray(0);// 解绑 VAO (这通常是一个很好的用来解绑任何缓存/数组并防止奇怪错误的方法)

    // 使用索引缓冲对象用两个三角形绘制一个长方形
    GLfloat vertices[] = {
        -0.5f, 0.2f, 0.0f, // TopLeft  
        0.5f, 0.2f, 0.0f, // TopRight 
        -0.5f,  -0.5f, 0.0f,  // BottomLeft   
        0.5f,  -0.5f, 0.0f  // BottomRight 
    };
    GLuint indices[] = {
        0,1,2,
        1,2,3
    };
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
}

int main()
{
    //初始化GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //创建窗口对象
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //注册键盘回调
    glfwSetKeyCallback(window, key_callback);

    //初始化GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    //告诉OpenGL渲染窗口尺寸大小
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    //初始化并绑定shaders
    shaderInit();

    //初始化顶点对象数据
    vertexObjectInit();

    //让窗口接受输入并保持运行
    while (!glfwWindowShouldClose(window))
    {
        //检查事件
        glfwPollEvents();

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //绘制梯形
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        //绘制长方形
        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);

        //交换缓冲
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);

    //释放资源
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void checkError(GLuint shader,GLbyte status) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, status, &success);
    if (!success)
	{		/*		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			fprintf(stderr, "Shaderlog:\n%s", log);
			free(log);
		}
		*/
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
    }
}