
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "src/obj/types/obj_t.h"
#include "src/obj/loadObj/loadObj.h"
#include "src/obj/utils/objUtils.h"
#include "src/glsl/utils/glslUtils.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct {
    SDL_Window *window;
    SDL_GLContext *context;
    GLuint programId;
    GLint vertexPos3DLocation;
    GLuint VBO;
    GLuint VAO;
    GLuint IBO;
} OpenGLData_t;

obj_t *obj;
OpenGLData_t openGlData;

int createShader2();

void render();


int main(int argc, char *argv[]) {
    obj = loadObjFromFile(DATA_DIR "monkey.obj");
    // xming windows stuff:
    // setenv("DISPLAY", "127.0.0.1:0", 1);
    // setenv("SDL_VIDEO_X11_VISUALID", "", 1);
    //The window we'll be rendering to
    openGlData.window = NULL;
    openGlData.context = NULL;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    openGlData.window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                         SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (openGlData.window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    openGlData.context = SDL_GL_CreateContext(openGlData.window);
    if (openGlData.context == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
        return -1;
    }

    if (!createShader2()) {
        printf("Couldn't create shaders\n");
        return -1;
    }


    SDL_Event e;

    //Enable text input
    SDL_StartTextInput();

    //While application is running
//    int quit = 0;
//    while (!quit) {
//        //Handle events on queue
//        while (SDL_PollEvent(&e) != 0) {
//            //User requests quit
//            if (e.type == SDL_QUIT) {
//                quit = 1;
//            }
//        }
//
//        //Render quad
//
//
//        //Update screen
//        //
//    }
    render();
    SDL_GL_SwapWindow(openGlData.window);
    SDL_Delay(2000);

    //Destroy window
    SDL_DestroyWindow(openGlData.window);
    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

int createShader2() {
    openGlData.programId = glCreateProgram();

    createShaderFromFile(DATA_DIR "basicVertexShader.glsl", GL_VERTEX_SHADER, openGlData.programId);
    createShaderFromFile(DATA_DIR "basicFragmentShader.glsl", GL_FRAGMENT_SHADER, openGlData.programId);
    linkProgram(openGlData.programId);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    GLfloat *vertexData = flattenVerts(obj);

    openGlData.VBO = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    // Create VBO
    glGenBuffers(1, &openGlData.VBO);

    // Create EBO
    GLuint *indices = flattenFaces(obj);
    glGenBuffers(1, &openGlData.IBO);

    glGenVertexArrays(1, &openGlData.VAO);
    glBindVertexArray(openGlData.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, openGlData.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj->vertexCount * 3, vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, openGlData.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * obj->faceCount * 3, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);

    return 1;
}

void render() {
    float red = sin(((float)clock())/CLOCKS_PER_SEC);
    float green = sin(((float)clock())/CLOCKS_PER_SEC + M_PI_2);
    float blue = sin(((float)clock())/CLOCKS_PER_SEC + M_PI);
    int vertexColorLocation = glGetUniformLocation(openGlData.programId, "ourColor");
    glUseProgram(openGlData.programId);
    glUniform4f(vertexColorLocation, red, green, blue, 1.0f);
    glBindVertexArray(openGlData.VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, obj->faceCount * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#ifdef __MINGW32__

int WinMain(int argc, char *argv[]) {
    main(argc, argv);
}

#endif