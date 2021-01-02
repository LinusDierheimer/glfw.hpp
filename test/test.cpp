#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.hpp>
#include <iostream>

static void posCallback(glfw::Window window, int x, int y)
{
    std::cout << "Window pos changed:  " << x << ", " << y << std::endl;
}

static void sizeCallback(glfw::Window window, int width, int height)
{
    std::cout << "Window size changed: " << width << ", " << height << std::endl;
}

static void closeCallback(glfw::Window window)
{
    std::cout << "Window closed" << std::endl;
}

static void refreshCallback(glfw::Window window)
{
    std::cout << "Window refreshed" << std::endl;
}

static void focusCallback(glfw::Window window, bool focusGiven)
{
    if(focusGiven)
        std::cout << "Window focused" << std::endl;
    else
        std::cout << "Window focus losed" << std::endl;
}

static void iconifyCallback(glfw::Window window, bool iconfied)
{
    if(iconfied)
        std::cout << "Window iconified" << std::endl;
    else
        std::cout << "Window un iconified" << std::endl;
}

static void maximizeCallback(glfw::Window window, bool maximized)
{
    if(maximized)
        std::cout << "Window maximized" << std::endl;
    else
        std::cout << "Window un maximized" << std::endl;
}

static void framebufferSizeCallback(glfw::Window window, int width, int height)
{
    std::cout << "Framebuffer size changed: " << width << ", " << height << std::endl;
}

static void contentScaleCallback(glfw::Window window, float xscale, float yscale)
{
    std::cout << "Content scale changed: " << xscale << ", " << yscale << std::endl;
}

static void keyCallback(glfw::Window window, glfw::Key key, glfw::Scancode scancode, glfw::ButtonAction action, glfw::KeyMod keyMod)
{
    std::cout << glfw::getKeyName(key, scancode) << " " << glfw::to_string(action) << "ed" << std::endl;
}

static void run()
{
    std::cout << "GLFW library version: " << glfw::getVersionString() << std::endl;

    glfw::init();

    glfw::defaultWindowHints();
    glfw::windowHint(glfw::Hint::eResizable, true);
    glfw::windowHint(glfw::Hint::eDecorated, true);
    glfw::windowHint(glfw::Hint::eFocused, false); //needed for wayland

    int width = 800;
    int height = 600;

    glfw::Window window = glfw::createWindow(width, height, "GLFW HPP Test");
    window.makeContextCurrent();

    window.setPosCallback(posCallback);
    window.setSizeCallback(sizeCallback);
    window.setCloseCallback(closeCallback);
    window.setRefreshCallback(refreshCallback);
    window.setFocusCallback(focusCallback);
    window.setIconifyCallback(iconifyCallback);
    window.setMaximizeCallback(maximizeCallback);
    window.setFramebufferSizeCallback(framebufferSizeCallback);
    window.setContentScaleCallback(contentScaleCallback);
    //window.setKeyCallback(keyCallback); //somehow this prevents other events from firing on my system

    window.setInputMode(glfw::InputMode::eCursor, glfw::CursorInputMode::eNormal);


    glViewport(0, 0, width, height);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glfw::swapInterval(0);

    while(!window.shouldClose())
    {
        glfw::pollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        window.swapBuffers();
    }

    window.destroy();

    glfw::terminate();
}

int main(int argc, const char** argv)
{
    try
    {
        run();
    }
    catch (const glfw::GlfwError& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        glfwTerminate(); //we dont want exceptions at this point
        return e.code().value();
    }

    return 0;
}
