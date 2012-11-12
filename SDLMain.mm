#include "NBodyWnd.h"
extern "C" int GetWidth();
extern "C" int GetHeight();

int main (int argc, char **argv) {
    
    NBodyWnd wndMain(GetWidth(), GetHeight(), "Density wave simulation");
    wndMain.Init(); 
    wndMain.MainLoop(); 
    return 0;
}

