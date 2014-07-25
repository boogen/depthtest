#include "include/GL/glew.h"
#include "include/GL/glfw.h"
#include <cstdlib>
#include <iostream>
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

GLuint program;

char *textFileRead(char *fn) {


	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}


void checkCompilationStatus(GLuint s) {
    GLint status = 0;

    glGetShaderiv(s, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        int infologLength = 0;
        int charsWritten  = 0;

        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &infologLength);

        if (infologLength > 0)
        {
            GLchar* infoLog = (GLchar *)malloc(infologLength);
            if (infoLog == NULL)
            {
                printf( "ERROR: Could not allocate InfoLog buffer");
                exit(1);
            }
            glGetShaderInfoLog(s, infologLength, &charsWritten, infoLog);
            printf( "Shader InfoLog:\n%s", infoLog );
            free(infoLog);
        }
    }

}


void setShaders() {
    GLuint v, f;
	char *vs = NULL,*fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("minimal.vert");
	fs = textFileRead("minimal.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
    checkCompilationStatus(v);
	glCompileShader(f);
    checkCompilationStatus(f);

	program = glCreateProgram();
	glAttachShader(program,v);
	glAttachShader(program,f);

    GLuint error;
	glLinkProgram(program);
	glUseProgram(program);
}


int main(int argc, char* argv[]) {

    glfwInit();

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwOpenWindow(800, 600, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);
    glViewport(0, 0, 800, 600);
    glfwSetWindowTitle("VBO");

    glewExperimental = GL_TRUE;
    GLenum result = glewInit();
    if (result != GLEW_OK) {
        std::cout << "Error: " << glewGetErrorString(result) << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    setShaders();

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
        0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 
        0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f
    };


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint pos = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLuint col = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(col);
    glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));



    glm::mat4 view = glm::lookAt(
        glm::vec3(2.0f, 2.0f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
        );
    GLint uniView = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(60.0f, 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(program, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    GLint uniModel = glGetUniformLocation(program, "model");

    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glClearDepth(0.0f);
    float rotation = 0.0f;

    while (glfwGetWindowParam(GLFW_OPENED)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glm::mat4 model;
        rotation += 3.0f;
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));


        //glDepthRange(1.0f, 1.0f);
         glDepthFunc(GL_LESS);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        glfwSwapBuffers();        
        glfwSleep(0.016);

   }
    
}
