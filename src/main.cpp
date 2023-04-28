/**
  * @file
  */
#ifdef DEBUG

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include "game.h"
#include "board.h"
#include "utils.h"
#include "dict.h"
#include "fonts.h"


void testGame(GLFWwindow *window);
void testBoard();
void testDict()
{
}
int testGUI();
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
    // Main code
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "RP Scrabble", NULL, NULL);
    if (window == NULL) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking
    // io.IniFilename = "assets/layout.ini";

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont *schibstedReg = io.Fonts->AddFontFromMemoryCompressedTTF(font_SchibstedGroteskReg_compressed_data, font_SchibstedGroteskReg_compressed_size, 18.0f);
    ImFont *schibstedRegSmall = io.Fonts->AddFontFromMemoryCompressedTTF(font_SchibstedGroteskReg_compressed_data, font_SchibstedGroteskReg_compressed_size, 12.0f);
    ImFont *schibstedBold = io.Fonts->AddFontFromMemoryCompressedTTF(font_SchibstedGroteskBold_compressed_data, font_SchibstedGroteskBold_compressed_size, 18.0f);
    ImFont *schibstedBoldLarge = io.Fonts->AddFontFromMemoryCompressedTTF(font_SchibstedGroteskBold_compressed_data, font_SchibstedGroteskBold_compressed_size, 36.0f);
    ImFont *schibstedSemiBold = io.Fonts->AddFontFromMemoryCompressedTTF(font_SchibstedGroteskSemiBold_compressed_data, font_SchibstedGroteskSemiBold_compressed_size, 36.0f);
    IM_ASSERT(schibstedReg != NULL);
    IM_ASSERT(schibstedRegSmall != NULL);
    IM_ASSERT(schibstedBold != NULL);
    IM_ASSERT(schibstedBoldLarge != NULL);
    IM_ASSERT(schibstedSemiBold != NULL);

    FontCollection_t *fonts = new FontCollection_t;
    fonts->reg = schibstedReg;
    fonts->bold = schibstedBold;
    fonts->title = schibstedBoldLarge;
    fonts->small = schibstedRegSmall;
    fonts->semiBold = schibstedSemiBold;

    Game g(window, fonts);
    g.run();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete(fonts);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// int main()
// {
// }

void testGame(GLFWwindow *window)
{
}

#else

#include "game.h"

int main()
{
    Game newGame;
    newGame.run();

    return 0;
}

#endif
