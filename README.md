:hourglass_flowing_sand: Loading Animation for C++
==================================================================================================================================================


:eye: Overview
--------------------------------------------------------------------------------------------------------------------------------------------------


This small C++ library provides a simple loading animation to console applications.
The animation runs in a separate thread, allowing your main task to continue uninterrupted.


:beginner: Getting Started
--------------------------------------------------------------------------------------------------------------------------------------------------


- Download and include the [LoadingAnimation.hpp](https://github.com/a13xe/LoadingAnimation/releases/download/v1.0.0/LoadingAnimation.hpp) file into your project.
- If your function prints something to the console, you need to clear the loading symbol beforehand:
```c
std::cout << "\r";
```
- You can customize the animation symbols and speed in `LoadingAnimation.hpp`: edit the `ANIMATION_SYMBOLS` array and `ANIMATION_SPEED_MS`.

:joystick: Example
--------------------------------------------------------------------------------------------------------------------------------------------------


```c
#include <iostream>
#include "LoadingAnimation.hpp"

void function1() {
    for (int i = 0; i < 4; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        std::cout << "\r"; // Clear the loading symbol
        std::cout << "Processing step " << i + 1 << "/4" << std::endl;
    }
}

int function2(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int sum = a * b;
    std::cout << "\r" << "The sum is: " << sum << std::endl;
    return sum;
}

int main() {
    // Use like this:
    loading_anim(function1);

    // Or like this if the function has parameters:
    int sum = loading_anim(function2, 10, 20);

    // Or even manually like this:
    ConsoleLoadingAnimation anim;
    anim.start();
    function1();
    anim.stop();

    return 0;
}
```

<table align="center">
  <tr>
    <td align="center">
      <video alt="" width=50% src="https://github.com/a13xe/LoadingAnimation/assets/77492646/21794705-68cb-4735-9895-f5a93fbe8544"/>
      <br>
    <td align="center">
      <video alt="" width=50% src="https://github.com/a13xe/LoadingAnimation/assets/77492646/0b88b127-f3ec-444a-99a7-d0b53a097f51"/>
      <br>
  <tr>
    <td align="center"> ANIMATION_SYMBOLS[] = {'|', '/', '-', '\\'};
    <td align="center"> ANIMATION_SYMBOLS[] = {'-', '=', 'x', 'X', '|', 'X', 'x', '='};
</table>
