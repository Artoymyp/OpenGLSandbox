#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include "Vertex.h"

#include <iostream>
#include "Placeble_object.h"
#include "Vertex_array.h"
#include "Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.4.camera.vs", "7.4.camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<Vertex> vertices = {
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
        
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
        Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        
        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        
        Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex( 0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 1.0f),
        Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f)
    };

    std::vector<Vertex> ramp_vertices = {
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
        
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 0.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        
        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
        
        Vertex(-0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
        Vertex( 0.5f, -0.5f, -0.5f,  1.0f, 1.0f),
        Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f,  0.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 0.0f),
    };
    
    std::vector<Vertex_array*> vaos;
    auto vaow = Vertex_array();
    {
        vaos.push_back(&vaow);
        vaow.activate();
        vaow.set_vertices(vertices);
    }
    
    auto vaow1 = Vertex_array();
    {
        vaos.push_back(&vaow1);
        vaow1.activate();
        vaow1.set_vertices(ramp_vertices);
    }

    // world space positions of our cubes
    std::vector<Placeble_object> cubePositions = {
        Placeble_object(glm::vec3( 0.0f,  0.0f,  0.0f)),
        Placeble_object(glm::vec3( 2.0f,  5.0f, -15.0f)),
        Placeble_object(glm::vec3(-1.5f, -2.2f, -2.5f)),
        Placeble_object(glm::vec3(-3.8f, -2.0f, -12.3f)),
        Placeble_object(glm::vec3( 2.4f, -0.4f, -3.5f))
    };
    vaow.set_model_to(cubePositions);

    std::vector<Placeble_object> ramp_positions = {
        Placeble_object(glm::vec3(-1.7f,  3.0f, -7.5f)),
        Placeble_object(glm::vec3(1.3f, -2.0f, -2.5f)),
        Placeble_object(glm::vec3(1.5f,  2.0f, -2.5f)),
        Placeble_object(glm::vec3(1.5f,  0.2f, -1.5f)),
        Placeble_object(glm::vec3(-1.3f,  1.0f, -1.5f))
    };
    vaow1.set_model_to(ramp_positions);

    // load and create a texture 
    Texture texture0{ FileSystem::getPath("resources/textures/container.jpg"), false };
    Texture texture1{ FileSystem::getPath("resources/textures/awesomeface.png"), true };


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture0", 0);
    ourShader.setInt("texture1", 1);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // bind textures on corresponding texture units
        texture0.set_to_texture_unit_and_activate(0);
        texture1.set_to_texture_unit_and_activate(1);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render objects
        for each (auto vao in vaos) {
            vao->activate();
            for (unsigned int i = 0; i < vao->objects.size(); i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, vao->objects[i]->location);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                ourShader.setMat4("model", model);

                vao->draw();
            }
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //// optional: de-allocate all resources once they've outlived their purpose:
    //// ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}