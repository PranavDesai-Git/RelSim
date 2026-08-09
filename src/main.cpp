#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);

#define MAX_VEL 0.2

float origin[] = {0, 0, 0};
float scale = 1;
float speed = 0.001;
float velocity = 0;
float points[] = {
    0.0f,  0.5f,  0.0f, // x,y,z of first point.
    0.5f,  -0.5f, 0.0f, // x,y,z of second point.
    -0.5f, -0.5f, 0.0f  // x,y,z of third point.
};

const char *vertex_shader = "#version 410 core\n"
                            "layout(location = 0) in vec3 vp;"
                            "uniform vec3 origin;"
                            "uniform float scale;"
                            "void main() {"
                            "  gl_Position = vec4( vp * scale + origin, 1.0 );"
                            "}";

const char *fragment_shader = "#version 410 core\n"
                              "out vec4 frag_colour;"
                              "void main() {"
                              "  frag_colour = vec4( 0.5, 0.5, 0.5, 1.0 );"
                              "}";

int main() {
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(600, 900, "RelSym", NULL, NULL);

    if (!window) {
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return 1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program);

        GLint origin_loc = glGetUniformLocation(shader_program, "origin");
        glUniform3f(origin_loc, origin[0], origin[1], origin[2]);

        GLint scale_loc = glGetUniformLocation(shader_program, "scale");
        glUniform1f(scale_loc, 0.1);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "error:%s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    int change_const;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_W) {
        if (velocity != MAX_VEL)
            velocity += speed;
        origin[1] += velocity;
    }
    if (key == GLFW_KEY_S) {
        if (velocity != MAX_VEL)
            velocity += speed;
        origin[1] -= velocity;
    }
    if (key == GLFW_KEY_A) {
        if (velocity != MAX_VEL)
            velocity += speed;
        origin[0] -= velocity;
    }
    if (key == GLFW_KEY_D) {
        if (velocity != MAX_VEL)
            velocity += speed;
        origin[0] += velocity;
    }
    if (action == GLFW_RELEASE) {
        while (velocity > 0) {
            velocity -= speed;
        }
    }
}
