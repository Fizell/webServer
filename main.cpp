#include <iostream>
#include "Server.h"

int main() {
    Server webServer = Server(8888);
    webServer.start();
    return 0;
}
