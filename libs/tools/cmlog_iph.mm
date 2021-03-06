#include "stdafx.h"

#include "cmlog.h"


#define XCODE_COLORS_ESCAPE_MAC @"\033["
#define XCODE_COLORS_ESCAPE_IOS @"\xC2\xA0["

#if 0
#define XCODE_COLORS_ESCAPE  XCODE_COLORS_ESCAPE_IOS
#else
#define XCODE_COLORS_ESCAPE  XCODE_COLORS_ESCAPE_MAC
#endif


#define XCODE_COLORS_RESET     XCODE_COLORS_ESCAPE @";"   // Clear any foreground or background color

void IPHLogColor (const char *content, LOG_LVL lvl )
{
    
    setenv("XcodeColors", "YES", 0); // Enables XcodeColors (you obviously have to install it too)
    
    char *xcode_colors = getenv("XcodeColors");
    
    NSAutoreleasePool*pool=[[NSAutoreleasePool alloc]init];

    if (xcode_colors && (strcmp(xcode_colors, "YES") == 0))
    {
         switch (lvl) {
            case CM_LOGL_TRACE:
                NSLog((XCODE_COLORS_ESCAPE @"fg181,181,181;" "%@" XCODE_COLORS_RESET),[NSString stringWithUTF8String:content]);
                
                break;
                
            case CM_LOGL_DEBUG:
                NSLog((XCODE_COLORS_ESCAPE @"fg25,25,255;" "%@" XCODE_COLORS_RESET),[NSString stringWithUTF8String:content]);
                
                break;
                
            case CM_LOGL_INFO:
                NSLog((XCODE_COLORS_ESCAPE @"fg51,204,51;" "%@" XCODE_COLORS_RESET),[NSString stringWithUTF8String:content]);
                
                break;
                
            case CM_LOGL_WARNING:
                NSLog((XCODE_COLORS_ESCAPE @"fg255,255,102;" "%@" XCODE_COLORS_RESET),[NSString stringWithUTF8String:content]);
                
                break;
                
            case CM_LOGL_ERR:
                NSLog((XCODE_COLORS_ESCAPE @"fg255,51,0;" "%@" XCODE_COLORS_RESET),[NSString stringWithUTF8String:content]);
                
                break;
                
            case CM_LOGL_CRIT:
                NSLog((XCODE_COLORS_ESCAPE @"fg255,51,0;" "%@" XCODE_COLORS_RESET),[NSString stringWithUTF8String:content]);
                
                break;
                
            default:
                break;
        }
        
    }
    else
    {
        NSLog(@"%@", [NSString stringWithUTF8String:content]);
    }
    
    [pool drain];

}

void IPHLog (const char *format, ...)
{
    NSAutoreleasePool*pool=[[NSAutoreleasePool alloc]init];
    va_list arglist;
    va_start(arglist, format);
    NSString *s = [[NSString alloc] initWithUTF8String:format];
     NSLogv(s, arglist);

    [s release];
    
    va_end(arglist);
    [pool drain];

}