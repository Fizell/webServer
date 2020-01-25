#include <iostream>
#include "Server.h"

int main() {
    EventLoop baseLoop;
    Server webServer = Server(&baseLoop, 8880);
    webServer.start();
    return 0;
}
