#include "stdafx.h"
#include "CMFile.h"
#import <Foundation/Foundation.h>

BOOL CopyFile(const char* src, const char* dst)
{

	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	NSString *srcPath = [NSString stringWithUTF8String:src];
	NSString *destinationPath = [NSString stringWithUTF8String:dst];
	NSError *error = nil;
	
	if (![fileManager copyItemAtPath:srcPath toPath:destinationPath error:&error]) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL DeleteFileList(const char* src)
{
	NSString *sPath = [NSString stringWithUTF8String:src];
	
	NSFileManager *fm = [NSFileManager defaultManager];
	
	NSDirectoryEnumerator *dirEnum = [fm enumeratorAtPath:sPath]; 
	// 创建文件遍历管理类 
	NSString *filePath; 
	
	while(filePath = [dirEnum nextObject]) 
	{ 		
		NSString *strPath =  ([[NSString alloc] initWithFormat:@"%@%@",sPath,filePath]);
		NSError *error = nil;
		
		[fm removeItemAtPath:strPath error:&error];
	}
	return TRUE;
}

BOOL DeleteFile(const char* src)
{
	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	NSString *srcPath = [NSString stringWithUTF8String:src];
	NSError *error = nil;

	if (![fileManager removeItemAtPath:srcPath error:&error]) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}
BOOL RenameFile(const char* src, const char* dst)
{
	NSFileManager *fileManager = [NSFileManager defaultManager];

	NSString *srcPath = [NSString stringWithUTF8String:src];
	NSString *destinationPath = [NSString stringWithUTF8String:dst];
	NSError *error = nil;

	if (![fileManager moveItemAtPath:srcPath toPath:destinationPath error:&error]) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}
