#include "stdafx.h"
#include "cmfile.h"
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
//#if defined(__APPLE__) || defined(__FreeBSD__)
//#include <copyfile.h>
//#else
#include <sys/sendfile.h>
//#endif

// http://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
// only valid at kernel >= 2.6.33
int OSCopyFile(const char* source, const char* destination)
{
    int input, output;
    if ((input = open(source, O_RDONLY)) == -1)
    {
        return -1;
    }
    if ((output = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
    {
        close(input);
        return -1;
    }

    //Here we use kernel-space copying for performance reasons
//#if defined(__APPLE__) || defined(__FreeBSD__)
//    //fcopyfile works on FreeBSD and OS X 10.5+
//    int result = fcopyfile(input, output, 0, COPYFILE_ALL);
//#else
    //sendfile will work with non-socket output (i.e. regular file) on Linux 2.6.33+
    off_t bytesCopied = 0;
    struct stat fileinfo = {0};
    if (0 != fstat(input, &fileinfo)) {
    	CM_ERRP("fstat %s failed errno %d", source, errno);
    }

    CM_ERRP("fileinfo size %d %d", (int)fileinfo.st_size, fileinfo.st_size);
    int result = sendfile(output, input, &bytesCopied, (int)fileinfo.st_size);
    if(result == -1) {
    	CM_ERRP("OSCopyFile from %s to %s failed. errno %d",source, destination, errno);
    }
    else if (result != fileinfo.st_size) {
    	CM_ERRP("OSCopyFile from %s to %s failed. size need %d result %d",source, destination, fileinfo.st_size, result);
    }
//#endif

    close(input);
    close(output);

    return result;
}

BOOL CopyFile(const char* src, const char* dst)
{
    FILE *fs=fopen( src, "rb" );
    if (fs == NULL) {
    	return FALSE;
    }
    FILE *fd=fopen( dst, "wb" );
    if (fd == NULL) {
    	fclose(fs);
    	return FALSE;
    }

	const int bufsize = 4096;
    char buff[bufsize]={0,};
    int n;

    while((n = fread(buff, 1, bufsize, fs)) > 0)
    {
    	char* ptr = buff;
    	int nw;
    	do
    	{
    		nw = fwrite(ptr, 1, n, fd );
    		if (nw > 0) {
    			n -= nw;
    			ptr += nw;
    		}
    		else {
    			CM_ERRP("CopyFile from %s to %s failed. fwrite failed. errno %d", src, dst, errno);
    			goto err;
    		}
    	}while (n > 0);
    }

    if (n == 0) {
    	if (feof(fs)) {
    	    fclose(fd);
    	    fclose(fs);
    		return TRUE;
    	}
    	else {
    		CM_ERRP("CopyFile from %s to %s failed. fread failed. errno %d", src, dst, errno);
    	}
    }

err:
    fclose(fd);
    fclose(fs);

	if(remove(dst) != 0)
	{
		//失败删除文件
		CM_ERRP("CopyFile failed. Delete %s failed. errno %d", dst, errno);
	}

    return FALSE;
}

BOOL DeleteFileList(const char* src)
{
	struct stat buff;
	lstat(src, &buff);
	if(S_ISDIR(buff.st_mode) && (strcmp(src, ".") != 0) && (strcmp(src, "..") != 0))
	{
		DIR *pdir;
		if(( pdir = opendir(src)) != NULL)
		{
			struct dirent *ent;
			while( ( ent = readdir(pdir)) != NULL)
			{
				if((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				{
					char newpath[260];
					memset(newpath, 0, 260);
					strcpy(newpath, src);
					strcat(newpath, "/");
					strcat(newpath, ent->d_name);
					if( !DeleteFileList(newpath))
						return FALSE;
					if(remove(newpath) != 0)//rmdir
						return FALSE;	
				}
			}
		}
	}
	else if((strcmp(src, ".") != 0) && (strcmp(src, "..") != 0))
		if(remove(src) != 0)
			return FALSE;
	return TRUE;
}

BOOL DeleteFile(const char* src)
{
	if(remove(src) != 0)
		return FALSE;
	return TRUE;
}
BOOL RenameFile(const char* src, const char* dst)
{
	if(rename(src, dst) != 0)
		return FALSE;
	return TRUE;
}
