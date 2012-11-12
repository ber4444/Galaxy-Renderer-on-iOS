//
//  VersionCheck.c
//  Demos
//
//  Created by Steven Robichaud on 2012-11-09.
//
//

#include <stdio.h>
#include <sys/utsname.h>
#include "TargetConditionals.h"

//iPod and iPhone Versions
char iPhone[] = "iPhone1,1";
char iPhone3G[] = "iPhone1,2";
char iPhone3GS[] = "iPhone2,1";
char iPhone4[] = "iPhone3,1";
char iPhone4S[] = "iPhone4,1";
char iPhone5[] = "iPhone5,1";
char iPod[] = "iPod1,1";
char iPod2[] = "iPod2,1";
char iPod3[] = "iPod3,1";
char iPod4[] = "iPod4,1";
char iPod5[] = "iPod5,1";

int width;
int height;

int uname(struct utsname *name);
struct utsname platform;
int rc;

//returns the width of the current device
int GetWidth()
{
#if TARGET_OS_IPHONE==1
    width = 320;
#endif
#if TARGET_OS_IPHONE==0
    width = 800;
#endif
    
    rc = uname(&platform);
    if(rc == -1){
        /* handle error */
    }
    else{
        
        if(strcmp(platform.machine, iPod4) == 0 || strcmp(platform.machine, iPhone4) == 0 || strcmp(platform.machine, iPhone4S) == 0)
        {
            width = 640;
        }
        
        if(strcmp(platform.machine, iPod3)  == 0|| strcmp(platform.machine, iPod2)  == 0 || strcmp(platform.machine, iPod)  == 0|| strcmp(platform.machine, iPhone) == 0 || strcmp(platform.machine, iPhone3G)  == 0|| strcmp(platform.machine, iPhone3GS) == 0 )
        {
            width = 320;
        }
        
        if(strcmp(platform.machine, iPod5)  == 0 || strcmp(platform.machine, iPhone5)  == 0)
        {
            width = 640;
        }
        
        fprintf(stdout, "hardware platform: %s", platform.machine);
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
    if(rc == -1){
        /* handle error */
    }
    else{
        
        if(strcmp(platform.machine, iPod4) == 0 || strcmp(platform.machine, iPhone4) == 0 || strcmp(platform.machine, iPhone4S) == 0)
        {
            height = 960;
        }
        
        if(strcmp(platform.machine, iPod3)  == 0|| strcmp(platform.machine, iPod2)  == 0 || strcmp(platform.machine, iPod)  == 0|| strcmp(platform.machine, iPhone) == 0 || strcmp(platform.machine, iPhone3G)  == 0|| strcmp(platform.machine, iPhone3GS) == 0 )
        {
            height = 480;
        }
        
        if(strcmp(platform.machine, iPod5)  == 0 || strcmp(platform.machine, iPhone5)  == 0)
        {
            height = 1136;
        }
        
        fprintf(stdout, "hardware platform: %s", platform.machine);
    }
    
    return height;
}