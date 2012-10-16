#include "NBodyWnd.h"

int main (int argc, char **argv) {
    NBodyWnd wndMain(800, "Density wave simulation");
    wndMain.Init();
    wndMain.MainLoop();
    return 0;
}

