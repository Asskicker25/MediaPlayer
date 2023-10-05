#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "AudioManger.h"
#include "MediaPlayer.h"


void DrawImguiWindow(bool window, ImVec4 clearColor, ImGuiIO io, int windowWidth, int windowHeight, Sound& sound);
void GetKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

AudioManger audioManager;
MediaPlayer mediaPlayer(audioManager);

int screenWidth{ 800 };
int screenHeight{ 600 };

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Media Player", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, GetKeyboardCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Sound jaguar;
    jaguar.path = "Assets/Audio/jaguar.wav";
    jaguar.soundID = "Jaguar";
    //jaguar.isLooping = true;
    //jaguar.isStreaming = true;

    Sound singing;
    singing.path = "Assets/Audio/singing.wav";
    singing.soundID = "Singing";

    Sound sneha;
    sneha.path = "Assets/Audio/sneha.wav";
    sneha.soundID = "Sneha";
    //sneha.isStreaming = true;
    //sneha.pitch = 0.75f;
    //sneha.volume = 1.0f;
    //sneha.pan = 1.0f;

    audioManager.LoadSound(sneha);
    audioManager.PlaySound(sneha);

    mediaPlayer.SetSound(sneha);
    mediaPlayer.AdjustPitch(sneha.pitch);
    mediaPlayer.AdjustVolume(sneha.volume);
    mediaPlayer.AdjustPan(sneha.pan);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Poll for and process events */
        glfwPollEvents();

        audioManager.Update();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        glViewport(0, 0, screenWidth, screenHeight);

        int imguiWindowWidth = screenWidth / 2;
        int imguiWindowHeight = screenHeight / 2;

        DrawImguiWindow(show_another_window, clear_color,io, imguiWindowWidth, imguiWindowHeight, sneha);

        /* Render here */
        ImGui::Render();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
       
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void DrawImguiWindow(bool window, ImVec4 clearColor, ImGuiIO io, int windowWidth, int windowHeight, Sound& sound)
{
    int spacingUnit = windowWidth * 0.005f;

    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::SetNextWindowPos(ImVec2((screenWidth/2) - windowWidth/2, (screenHeight/2) - windowHeight/2));

    //ImGui::SetNextWindowSize(ImVec2(800, 600));

    ImGui::Begin("Media Controls");                          // Create a window called "Hello, world!" and append into it.

    ImGui::SetWindowFontScale(windowWidth * 0.0025f);

    ImGui::Text("Playing : %s" , sound.soundID.c_str());   
    

    if (ImGui::Button(mediaPlayer.IsPaused()? "Play" : "Pause"))
    {
        mediaPlayer.TogglePauseAudio();
    }

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();
    ImGui::Dummy(ImVec2(spacingUnit * 3, 0));

    ImGui::SameLine();
    if (ImGui::Button("Stop"))
    {
        mediaPlayer.TogglePauseAudio();
    }

    ImGui::Spacing();
    ImGui::Dummy(ImVec2(0.0f, spacingUnit * 5));


    if (ImGui::SliderFloat("Volume", &sound.volume, 0.0f, 1.0f))
    {
        mediaPlayer.AdjustVolume(sound.volume);
    }

    if (ImGui::SliderFloat("Pitch", &sound.pitch, 0.0f, 2.0f))
    {
        mediaPlayer.AdjustPitch(sound.pitch);
    }

    if (ImGui::SliderFloat("Pan", &sound.pan, -1.0f, 1.0f))
    {
        mediaPlayer.AdjustPan(sound.pan);
    }


    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void GetKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_SPACE)
        {
            mediaPlayer.TogglePauseAudio();
            //mediaPlayer.AdjustPitch(1.0f);
        }
    }
}

