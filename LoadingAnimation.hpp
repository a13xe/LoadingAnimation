#ifndef LOADINGANIMATION_HPP
#define LOADINGANIMATION_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <type_traits>


// Animation symbols and speed configuration
// ----------------------------------------------------------------------------------------------
// Speed of the animation in milliseconds
const int ANIMATION_SPEED_MS = 100;
// Symbols
const char ANIMATION_SYMBOLS[] = {'|', '/', '-', '\\'};
// Symbol counter
const int ANIMATION_SYMBOL_COUNT = sizeof(ANIMATION_SYMBOLS) / sizeof(ANIMATION_SYMBOLS[0]);


// Main class
// ----------------------------------------------------------------------------------------------
class ConsoleWaitAnimation
{
public:
    ConsoleWaitAnimation() : currentIndex(0) {}
    void start()
    {
        isRunning = true;
        animThread = std::thread(&ConsoleWaitAnimation::runAnimation, this);
    }
    void stop()
    {
        clearCurrentLine();
        isRunning = false;
        if (animThread.joinable())
        {
            animThread.join();
        }
    }
private:
    int currentIndex;
    std::thread animThread;
    bool isRunning = false;
    void runAnimation()
    {
        while (isRunning)
        {
            std::cout << "\r" << ANIMATION_SYMBOLS[currentIndex++] << std::flush;
            if (currentIndex >= ANIMATION_SYMBOL_COUNT) currentIndex = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(ANIMATION_SPEED_MS));
        }
    }
    void clearCurrentLine()
    {
        std::cout << "\r" << std::string(100, ' ') << "\r";
    }
};


// Function template for non-void returning functions
// ----------------------------------------------------------------------------------------------
template <typename Func, typename... Args>
auto wait_anim(Func func, Args&&... args) ->
typename std::enable_if<!std::is_void<typename std::result_of<Func(Args...)>::type>::value,
typename std::result_of<Func(Args...)>::type>::type
{
    ConsoleWaitAnimation animation;
    animation.start();
    auto result = func(std::forward<Args>(args)...);
    animation.stop();
    return result;
}


// Overload for void returning functions
// ----------------------------------------------------------------------------------------------
template <typename Func, typename... Args>
auto wait_anim(Func func, Args&&... args) ->
typename std::enable_if<std::is_void<typename std::result_of<Func(Args...)>::type>::value>::type
{
    ConsoleWaitAnimation animation;
    animation.start();
    func(std::forward<Args>(args)...);
    animation.stop();
}


#endif // LOADINGANIMATION_HPP
