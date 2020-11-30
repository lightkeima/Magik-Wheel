#include "serverSocket.h"

using namespace std;

int main() {
  ServerSocket server(3);
  server.initSocket();
  server.mainLoop();

  return 0;
}