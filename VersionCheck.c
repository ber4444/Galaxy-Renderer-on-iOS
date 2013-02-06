#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "TargetConditionals.h"
    
char iPhone[] = "iPhone1,1";
char iPhone3G[] = "iPhone1,2";
char iPhone3GS[] = "iPhone2,1";
char iPhone4[] = "iPhone3,1";
char iPhone4Verizon[] = "iPhone3,3";
char iPhone4S[] = "iPhone4,1";
char iPhone5[] = "iPhone5,2";
char iPod[] = "iPod1,1";
char iPod2[] = "iPod2,1";
char iPod3[] = "iPod3,1";
char iPod4[] = "iPod4,1";
char iPod5[] = "iPod5,1";
char simulator[] = "i386";
char simulator2[] = "x86_64";
    
int width;
int height;

int uname(struct utsname *name);
struct utsname platform;
int rc;

//returns the width of the current device (iPad target not included in our project)
//on the simulator, you need to manually adjust depending on which mode you select in the Device menu
int GetWidth()
{
#if TARGET_OS_IPHONE==1
    width = 320;
#endif
#if TARGET_OS_IPHONE==0
    width = 800;
#endif
    
    rc = uname(&platform);
    char *device = platform.machine;
    if(rc != -1){
        
        if(strcmp(device, iPod4) == 0 || strcmp(device, iPhone4) == 0 || strcmp(device, iPhone4S) == 0 || strcmp(device, iPhone4Verizon) == 0
           || strcmp(device, iPod5)  == 0 || strcmp(device, iPhone5)  == 0)
            width = 640;
        
        if(strcmp(device, iPod3)  == 0|| strcmp(device, iPod2)  == 0 || strcmp(device, iPod)  == 0|| strcmp(device, iPhone) == 0 || strcmp(device, iPhone3G)  == 0|| strcmp(device, iPhone3GS) == 0 )
            width = 320;
    
        if (strcmp(device, simulator)  == 0 || strcmp(device, simulator2)  == 0)
            width = 640; // for high resolution mode (Hardware > Device menu of the simulator)
        
        fprintf(stdout, "hardware platform: %s\n", device);
    }
    
    return width;
}

//returns the height of the curent device
int GetHeight()
{
#if TARGET_OS_IPHONE==1
    height = 480;
#endif
#if TARGET_OS_IPHONE==0
    height = 800;
#endif
    
    rc = uname(&platform);
    char *device = platform.machine;
    if(rc != -1){
        
        if(strcmp(device, iPod4) == 0 || strcmp(device, iPhone4) == 0 || strcmp(device, iPhone4S) == 0 || strcmp(device, iPhone4Verizon) == 0)
            height = 960;
        
        if(strcmp(device, iPod3)  == 0|| strcmp(device, iPod2)  == 0 || strcmp(device, iPod)  == 0|| strcmp(device, iPhone) == 0 || strcmp(device, iPhone3G)  == 0|| strcmp(device, iPhone3GS) == 0 )
            height = 480;
        
        if(strcmp(device, iPod5)  == 0 || strcmp(device, iPhone5)  == 0)
            height = 1136;
        
        if (strcmp(device, simulator)  == 0 || strcmp(device, simulator2)  == 0)
            height = 1136; // for high resolution mode (Hardware > Device menu of the simulator)        
    }
    
    return height;
}
