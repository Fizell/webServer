#include <iostream>
#include "Server.h"

int main() {
    EventLoop baseLoop;
    Server webServer = Server(&baseLoop, 8889);
    webServer.start();
    return 0;
}
