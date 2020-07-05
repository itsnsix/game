
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/obj/types/obj_t.h"
#include "src/obj/loadObj/loadObj.h"
#include "src/obj/utils/objUtils.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

int createShader();

void render();


int main(int argc, char *argv[]) {
    obj = loadObjFromFile(MONKEY_OBJ_PATH);
    setenv("DISPLAY", "127.0.0.1:0", 1);
    setenv("SDL_VIDEO_X11_VISUALID", "", 1);
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

    openGlData.window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
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

    if (!createShader()) {
        printf("Couldn't create shaders\n");
        return -1;
    }


    SDL_Event e;

    //Enable text input
    SDL_StartTextInput();

    //While application is running
    int quit = 0;
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        //Render quad
        render();

        //Update screen
        SDL_GL_SwapWindow(openGlData.window);
    }

    //Destroy window
    SDL_DestroyWindow(openGlData.window);
    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

int createShader() {
    char infoLog[512];

    // create our shader program
    openGlData.programId = glCreateProgram();

    // Create the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *vertexShaderSource[] = {
            "#version 140\nin vec3 LVertexPos3D; void main() { gl_Position = vec4( LVertexPos3D.x, LVertexPos3D.y, LVertexPos3D.z, 1.0 ); }"
    };
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d\n", vertexShader);
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Error: %s\n", infoLog);
        return 0;
    }
    glAttachShader(openGlData.programId, vertexShader);
    glDeleteShader(vertexShader);

    // create the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *fragmentShaderSource[] = {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
    };
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
    if (fShaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d\n", fragmentShader);
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Error: %s\n", infoLog);
        return 0;
    }
    glAttachShader(openGlData.programId, fragmentShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(openGlData.programId);
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(openGlData.programId, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", openGlData.programId);
        return 0;
    }


    openGlData.vertexPos3DLocation = -1;
    openGlData.vertexPos3DLocation = glGetAttribLocation(openGlData.programId, "LVertexPos3D");
    if (openGlData.vertexPos3DLocation == -1) {
        printf("LVertexPos3D is not a valid glsl program variable!\n");
        return 0;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);



    //VBO data
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
    glUseProgram(openGlData.programId);
    glBindVertexArray(openGlData.VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, obj->faceCount * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#ifdef __MINGW32__

int WinMain(int argc, char *argv[]) {
    main(argc, argv);
}

#endif