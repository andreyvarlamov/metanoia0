#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef GLuint TexID;

static void _key_callback(
    GLFWwindow *window,
    int key,
    int scancode,
    int action,
    int mode
)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

static char* _read_file(const char *path)
{
    FILE *f;
    unsigned long len;
    char *content;

    f = fopen(path, "rb");
    assert(f);

    fseek(f, 0, SEEK_END);
    len = (unsigned long) ftell(f);
    assert(len > 0);

    fseek(f, 0, SEEK_SET);
    content = (char*) calloc(1, len);
    assert(content);

    fread(content, 1, len, f);
    assert(strlen(content) > 0);

    fclose(f);

    return content;
}

static TexID _load_texture(const char *path)
{
    char *content;
    int width, height, nr_channels;
    unsigned char *data;
    TexID tex_id;
    
    content = _read_file(path);

    data = stbi_load(content, &width, &height, &nr_channels, 0);

    glGenTextures(1, &tex_id);

    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    free(content);

    return tex_id;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow *window = glfwCreateWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "METANOIA",
        NULL,
        NULL
    );

    glfwMakeContextCurrent(window);
    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetKeyCallback(window, _key_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    TexID tex_id = _load_texture("res/texture/cp437.png");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
