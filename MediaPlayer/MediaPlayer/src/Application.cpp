#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "AudioManger.h"
#include "MediaPlayer.h"


void DrawImguiWindow(bool window, ImVec4 clearColor, ImGuiIO io);
void HandleUserInput(MediaPlayer& mediaPlayer);

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
    window = glfwCreateWindow(640, 480, "Media Player", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

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

    AudioManger audioManager;
    MediaPlayer mediaPlayer(audioManager);

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

        HandleUserInput(mediaPlayer);
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawImguiWindow(show_another_window, clear_color,io);

        /* Render here */
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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

void DrawImguiWindow(bool window, ImVec4 clearColor, ImGuiIO io)
{
    static float f = 0.0f;
    static int counter = 0;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void HandleUserInput(MediaPlayer& mediaPlayer)
{
    if (_kbhit())
    {
        int key = _getch();
        switch (key)
        {
        case 32: //Space
            mediaPlayer.TogglePauseAudio();
            break;

        case 97: //a
            mediaPlayer.PlayAudio();
            break;
        case 115: //s
            mediaPlayer.StopAudio();
            break;
        }

    }
}
