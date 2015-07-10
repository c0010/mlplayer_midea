//
//  cmcoursedownload_iph.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-2-25.
//  Copyright (c) 2014年 w. All rights reserved.
//
//  iphone解压缩后利用这个类调回主线程
//
//

#ifndef CMCourseDownloadIph_HEADER_INCLUDED_B19B17D3
#define CMCourseDownloadIph_HEADER_INCLUDED_B19B17D3




class CMCourseDownload;

class CMCourseDownload_Iph
{
public:
    
    CMCourseDownload_Iph(CMCourseDownload* obj);
    ~CMCourseDownload_Iph();

    void GoOnDownload_iph();
    
protected:
    
    void* coursedownload_mid;
    CMCourseDownload* coursedownload;
    
};





#endif
