#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "res\headers\renderer.h"
#include "res\headers\vertexbuffer.h"
#include "res\headers\indexbuffer.h"
#include "res\headers\vertexarray.h"
#include "res\headers\shader.h"
#include "res\headers\VertexBufferLayout.h"
#include "res\headers\window.hpp"

#include "res\glm\glm.hpp"
#include "res\glm\gtc\matrix_transform.hpp"
#include "res\imgui\imgui.h"
#include "res\imgui\imgui_impl_glfw.h"
#include "res\imgui\imgui_impl_opengl3.h"

#include "Simulation2\simulation.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;
using namespace glm;
using namespace Engine;
//-----------------------------------------------------------------------------------
#define WIDTH 1920.0f
#define HEIGHT 1080.0f
#define ParticleCount 50000
#define timestep 0.01f
#define M 50000.0
//-----------------------------------------------------------------------------------

vector<float> ParticleObjectPoints(vector<Vec2>& positions){

    vector<float> result;
    result.reserve(2*ParticleCount);

    for(int i = 0; i < ParticleCount; ++i){
        result.emplace_back(positions[i].x);
        result.emplace_back(positions[i].y);
    }
    return result;
}
//-----------------------------------------------------------------------------------
bool paused = false;
vector<float> particles;
float zoom = 1;

int main(void){
    float scale = 1.0;
    Window window(WIDTH , HEIGHT, "N-Body");
    Simulation gravity({2*scale*WIDTH, 2*scale*HEIGHT}, {-scale*WIDTH, -scale*HEIGHT}, ParticleCount, timestep);

    {
    
    //vector<Vec2> original_position = gravity.generate_positions();
    //vector<Vec2> Velocities(ParticleCount, {0,0});
    //vector<vector<Vec2>> Config = {original_position, Velocities};
    Particles original_Config = gravity.generateGalaxy({-500.0, 10.0}, {500, 50.0}, M, M);
    Particles Config = original_Config;
//-----------------------------------------------------------------------------------
    VertexBuffer vb(nullptr, 2*ParticleCount*sizeof(float), true);
    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    VertexArray va;
    va.AddBuffer(vb, layout);

    //mat4 proj = ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
    mat4 proj;
    mat4 view = translate(mat4(1.0f), vec3(0,0,0));
    mat4 model = translate(mat4(1.0f), vec3(0,0,0));
    mat4 temp = view * model;
    mat4 mvp;

    Shader shader("res/shaders/simple.shader");

    Renderer renderer;

    shader.Unbind();
    //vb.Unbind();
    //va.Unbind();
    //ib.Unbind();
    
//-----------------------------------------------------------------------------------
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.getNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
//-----------------------------------------------------------------------------------
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//-----------------------------------------------------------------------------------
    unsigned int nodeCount = 0;
    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        renderer.Clear();
//-----------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
//-----------------------------------------------------------------------------------        
        particles = ParticleObjectPoints(Config.pos);
        proj = ortho(-WIDTH/(zoom), WIDTH/(zoom), -HEIGHT/(zoom), HEIGHT/(zoom), -1.0f, 1.0f);
        mvp = proj * temp;
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        
        vb.Update(particles.data(), particles.size()*sizeof(float));
        renderer.DrawP(va, ParticleCount, shader);
        if(!paused){
            gravity.NewState(Config, nodeCount);
        }   
//-----------------------------------------------------------------------------------
       {

            ImGui::Begin("Simulation Data");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Particle Count = %d", ParticleCount);
            if (ImGui::Button("Pause")){                            // Buttons return true when clicked (most widgets return true when edited/activated)
                paused = !paused;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")){                            // Buttons return true when clicked (most widgets return true when edited/activated)
                Config = original_Config;//{original_position, Velocities};
            }
            ImGui::SliderFloat("zoom", &zoom, 0.0f, 4.0f);
            ImGui::Text("Time step = %f", timestep);
            ImGui::Text("Number of nodes = %d", nodeCount);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
       ImGui::Render();
       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        window.pollEvents();
    }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}