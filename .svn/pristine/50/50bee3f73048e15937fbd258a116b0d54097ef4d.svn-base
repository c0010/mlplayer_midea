// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

//当前模块是网络模块
#define FILE_MOD CM_LOGM_NET

#if defined(__IPHONE_OS__)
#include <objc/runtime.h>
#include <objc/message.h>
#endif

#include "stdafx.h"
#include "cmhttpc.h"
#if defined(PLAT_AND)
#include <jni.h>
#include "android/env.h"

#endif

#include <pthread.h>
#include <errno.h>


#if defined(PLAT_IOS)
#include <curl.h>
#include "cmhttpc_iph.h"
#else
#include <curl/curl.h>
#endif



#include "cmnetworkmgr.h"

#define TIMEOUT_INTERVAL  30
#define MINIMAL_PROGRESS_FUNCTIONALITY_INTERVAL     5
static const char buf[] = "Expect:";

#define CURL_CHECKLE(s) \
__extension__ ({ \
	CURLcode rcode = s; \
	if (rcode != CURLE_OK) { \
		CM_ERRP("CURL_CHECKLE error %s", curl_easy_strerror(rcode));   \
	}  \
})

#define CURL_CHECKME(s) \
__extension__ ({ \
	CURLMcode rcode = s; \
	if (rcode != CURLM_OK) { \
		CM_ERRP("CURL_CHECKME error %s", curl_multi_strerror(rcode));   \
	}  \
})

typedef enum {
    NoRequest = 0,
    Connect,
    Send,
    Response,
    Receive
    
} httpStatus;


struct fcurl_data {
	CURL*             curl;            //curl
	CMHttpC*          http;            //http指针

	char*             buffer;          //外部缓存，Read函数传入
	size_t            buffer_len;      //外部缓存需要写长度
	size_t            buffer_pos;      //外部缓存已经写长度
	char*             buffer_ext;      //写缓存，需要释放
	size_t            buffer_ext_len;  //写缓存长度
	size_t            buffer_ext_pos;  //写缓存当前位置
	size_t            buffer_ext_max;  //写缓存最大位置

	int               still_running;   //传输结束内部标志
	bool              exit;            //是否退出
	double            lastruntime;     //xxx
    httpStatus        nStatus;

	pthread_mutex_t   mutex;           //锁，锁exit http
	pthread_cond_t    cond;            //状态量
	bool              unpause;         //状态参数

	bool              autorloc;        //是否自动重定向
	CMHTTPRspHeader*  resp;            //临时响应头，重定向时用，后续去掉
	bool              save_resp;       //重定向是否结束标志
    
    double            lastdltotal;     //上一次的数据
    double            lastdlnow;
    double            lastultotal;
    double            lastulnow;
    
    
};

void* CMHttpC::curl_proc(void* param)
{
	fd_set fdread;
	fd_set fdwrite;
	fd_set fdexcep;
	struct timeval timeout;
	int rc;

	fcurl_data* data = (fcurl_data*)param;

    CM_LOGP(CM_LOGL_DEBUG, "curl thread %x created", pthread_self());

    pthread_mutex_lock(&data->mutex);
	
    CMHttpC* pHttp = (CMHttpC*)data->http;
    CURLM* multi_handle = NULL;
	struct curl_slist *headerlist=NULL;

	struct curl_httppost *formpost=NULL;
	struct curl_httppost *lastptr=NULL;

#if defined(PLAT_AND)

    int status;
    JNIEnv* env;
    JavaVM* vm = NULL;
    bool isAttached = false;
    if ((vm = GetJavaVM()) != NULL)
    {
        status = vm->GetEnv((void **) &env, JNI_VERSION_1_4);
        if(status < 0) {
            CM_LOG(CM_LOGL_WARNING, "CMSocketC::ProcFunc:failed to get JNI environment, assuming native thread"); //错误提示行
            status = vm->AttachCurrentThread(&env, NULL);
            if(status < 0) {
            	CM_ERR("failed to attach current thread");
            }
            else
            	isAttached = true;
        }
    }
#elif defined(PLAT_IOS)
    id pool = objc_msgSend(objc_msgSend((id)objc_getClass("NSAutoreleasePool"), sel_registerName("alloc")), sel_registerName("init"));
#endif


	data->curl = curl_easy_init();

	//禁止异常
	CURL_CHECKLE(curl_easy_setopt(data->curl,CURLOPT_NOSIGNAL, 1L));

	//检查网络
    CMNetConnMgr& mgr = CMNetConnMgr::Instance();
    CMNetConnMgr::TYPE mType = mgr.CurrentType();
    CMUrl cUrl;
    if(!pHttp)
    {
    	CM_ERR("data->http null");
    	//pHttp->m_pNotify->OnResponse(MERN_INITIALIZE, NULL);
    	goto end;
    }
    cUrl = pHttp->m_cReqHeader.GetUrl();

    if (mType == CMNetConnMgr::NONE)
    {
    	CM_ERR("network connection none");
    	pHttp->m_pNotify->OnResponse(MERN_INITIALIZE, NULL);
    	goto end;
    }
    else if (mType == CMNetConnMgr::CMWAP)
    {
        CHAR sTmp[100];

        //现在不再把wap特殊对待，只是认为普通proxy

        if (!mgr.Proxy())
        {
            CM_ERR("network is cmwap but no proxy");
            pHttp->m_pNotify->OnResponse(MERN_ERROR, NULL);
            goto end;
        }

        snprintf(sTmp, 100,"%s:%d",(const CHAR*)mgr.Proxy()->Host(), mgr.Proxy()->Port());
        curl_easy_setopt(data->curl, CURLOPT_PROXY, sTmp);
//        CM_ERRP("proxy is %s", sTmp);
    }

    pHttp->m_cRspHeader.Clean();

	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_URL, (const char*)cUrl.Url()));

	//自动跳转
	if (data->autorloc)
	{
		CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_FOLLOWLOCATION, 1L));
//		curl_easy_setopt(data->curl, CURLOPT_AUTOREFERER, 1L);
	}

	//添加头信息
	char keyvalue[256];
    for(CMMap<CMString, CMString>::const_iterator it = pHttp->m_cReqHeader.m_mValues.begin(); it != pHttp->m_cReqHeader.m_mValues.end(); it++)
    {
    	if (strcasecmp(HH_RANGER, (const CHAR*)(CMString)it.key()) == 0)
    	{
    		//发现通过curl_slist_append传递的参数不能通过重定向，临时处理下
//    		CM_ERRP("range %s", (const CHAR*)(CMString)it.value());
    		CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_RANGE, (const CHAR*)(CMString)it.value()));
    	}
    	else
    	{
			snprintf(keyvalue, 256,"%s: %s", (const CHAR*)(CMString)it.key(), (const CHAR*)(CMString)it.value());
			headerlist = curl_slist_append(headerlist, keyvalue);
    	}
    }

	if (pHttp->m_cReqHeader.GetType() == CMHTTPReqHeader::POST)
	{
		if (pHttp->m_cReqHeader.m_pPostData != NULL && pHttp->m_cReqHeader.m_nPostLen > 0)
		{
			//普通post
            headerlist = curl_slist_append(headerlist, buf);

			CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_POST, 1L));
            CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_POSTFIELDSIZE, pHttp->m_cReqHeader.m_nPostLen));
			CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_POSTFIELDS, pHttp->m_cReqHeader.m_pPostData));

//			//使用xml方式发送请求，这里应该上层设置
//			headerlist = curl_slist_append(headerlist, "Content-Type: application/xml");

//			CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_READFUNCTION, read_callback));
//			CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_READDATA, pHttp));
		}
		else
		{
			//form post


		    for(CMList<FormData>::const_iterator it = pHttp->m_cReqHeader.m_lstPost.begin(); it != pHttp->m_cReqHeader.m_lstPost.end(); it++)
		    {
		    	const FormData& fd = *it;

//                CM_ERRP("key:%s \n",(const CHAR*)(CMString)fd.key);
//                CM_ERRP("value:%s \n",(const CHAR*)(CMString)fd.value);

				if (fd.dataType == 2)
				{
					/* Fill in the file upload field */
					curl_formadd(&formpost,
								 &lastptr,
								 CURLFORM_COPYNAME, fd.key.c_str(),
								 CURLFORM_FILE, fd.value.c_str(),
								 CURLFORM_END);
				}
				else
				{
					curl_formadd(&formpost,
								 &lastptr,
								 CURLFORM_COPYNAME, fd.key.c_str(),
								 CURLFORM_COPYCONTENTS, fd.value.c_str(),
								 CURLFORM_END);
				}
		    }

			headerlist = curl_slist_append(headerlist, buf);

			CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_HTTPPOST, formpost));
		}
	}
	else
	{
		CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_HTTPGET, 1L));
	}

	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_HTTPHEADER, headerlist));

	//单项https验证，客户端不验证服务器证书
	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_SSL_VERIFYPEER, FALSE));

	//响应内容处理
	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_WRITEDATA, data));
	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_WRITEFUNCTION, write_callback));

	//响应头处理
	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_HEADERFUNCTION, head_callback));
	CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_HEADERDATA, data));

	//进度上报
    data->lastruntime = 0;
    CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_PROGRESSFUNCTION, older_progress));
    /* pass the struct pointer into the progress function */
    CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_PROGRESSDATA, data));
    CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_NOPROGRESS, 0L));
    
//    CURL_CHECKLE(curl_easy_setopt(data->curl, CURLOPT_CONNECTTIMEOUT, 2));

    //开始监听
    multi_handle = curl_multi_init();

    CURL_CHECKME(curl_multi_add_handle(multi_handle, data->curl));

	/* lets start the fetch */
	CURL_CHECKME(curl_multi_perform(multi_handle, &data->still_running));

    if (data->still_running == 0) {
        //开始网络就无数据
        //在连接的过程中出错，而且并未进行Response操作
        CM_ERRP("connect failed, errno %d", errno);
        pHttp->m_pNotify->OnResponse(MERN_ERROR, NULL);
        goto end;
    }
	while (data->still_running) {
		int maxfd = -1;
		long curl_timeo = -1;

		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcep);

		/* set a suitable timeout to fail on */
		timeout.tv_sec = TIMEOUT_INTERVAL; /* 1 minute */
		timeout.tv_usec = 0;
        
		CURL_CHECKME(curl_multi_timeout(multi_handle, &curl_timeo));


		if (curl_timeo >= 0) {
			timeout.tv_sec = curl_timeo / 1000;
			if (timeout.tv_sec > 1)
				timeout.tv_sec = 1;
			else
				timeout.tv_usec = (curl_timeo % 1000) * 1000;
		}

		/* get file descriptors from the transfers */
		CURL_CHECKME(curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd));

	    pthread_mutex_unlock(&data->mutex);
		rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
		pthread_mutex_lock(&data->mutex);
//		CM_ERRP("select ret %d", rc);
		switch (rc) {
		case -1:
			/* select error */
			CM_ERRP("select return -1, errno %d", errno);
			break;

		case 0:
                if(curl_timeo<0)
                {
                    if(pHttp && pHttp->m_pNotify)
                    {

                        switch (data->nStatus) {
                        	case Connect:
                            case Response:
                                pHttp->m_pNotify->OnResponse(MERN_TIMEOUT, NULL);
                                break;

                            case Receive:
                                pHttp->m_pNotify->OnRead(MERN_TIMEOUT, 0
                                                         );
                                break;

                            case Send:
                                pHttp->m_pNotify->OnSend(MERN_TIMEOUT, 0
                                                         );
                                break;
                                
                            default:
                            	CM_ERRP("time out wrong state. errno %d, status %d", errno, data->nStatus);
                                break;
                        }
                        
                    }
                    goto end;
                }
		default:
			/* timeout or readable/writable sockets */
			CURLMcode cm = curl_multi_perform(multi_handle, &data->still_running);
			CM_LOGP(CM_LOGL_DEBUG, "curl_multi_perform %d, still_running %d status %d", cm, data->still_running, data->nStatus);
			if (data->still_running == 0 && data->nStatus == Connect) {
				//在连接的过程中出错，而且并未进行Response操作
				CM_ERRP("connect failed, errno %d", errno);
				pHttp->m_pNotify->OnResponse(MERN_ERROR, NULL);
				goto end;
			}
            if (data->nStatus == Response) {
                //刚读完头，还没开始读，等待
                data->unpause = true;
                pthread_cond_wait(&data->cond, &data->mutex);
                if (data->exit)
                {
                    goto end;
                }
            }
			size_t want = data->buffer_len - data->buffer_pos;
			if (want > 0)
			{
				//开始读数据了
				size_t have = data->buffer_ext_max - data->buffer_ext_pos;
//				CM_ERRP("need read %d have %d", want, have);
				while (have >= want  && !data->exit)
				{
//					CM_ERRP("read %d have %d", want, have);
					memcpy(data->buffer, &data->buffer_ext[data->buffer_ext_pos], want);
					data->buffer_pos = data->buffer_len;

					data->buffer_ext_pos += want;

                    if(pHttp)
                        pHttp->m_pNotify->OnRead(MER_OK, data->buffer_len);

					want = data->buffer_len - data->buffer_pos;
					have = data->buffer_ext_max - data->buffer_ext_pos;

					if (data->exit || (want == 0 && have == 0))
						break;
					if (want == 0)
					{
						//暂停读
//					CM_ERR("no read,pause");
						data->unpause = true;
						pthread_cond_wait(&data->cond, &data->mutex);

						want = data->buffer_len - data->buffer_pos;
						have = data->buffer_ext_max - data->buffer_ext_pos;

						if (data->exit || (want == 0 && have == 0))
							break;
					}

				}

			}
			break;
		}
	}

end:
	if (!data->exit) {
		//完成，等待结束
		CM_LOG(CM_LOGL_DEBUG, "curl_multi_perform out, wait for exit");
		pthread_cond_wait(&data->cond, &data->mutex);
	}

	pthread_mutex_unlock(&data->mutex);

	CM_LOGP(CM_LOGL_DEBUG, "curl thread %x ended", pthread_self());

	if (multi_handle)
		curl_multi_remove_handle(multi_handle, data->curl);

	/* cleanup */
	if (data->curl)
		curl_easy_cleanup(data->curl);

	if (multi_handle)
		curl_multi_cleanup(multi_handle);

	if (formpost)
		curl_formfree(formpost);
    
    if(headerlist)
        curl_slist_free_all(headerlist);

	data->http = NULL;
	data->curl = NULL;
	if (data->buffer_ext)
	{
		delete[] data->buffer_ext;
		data->buffer_ext = NULL;
	}

    pthread_mutex_destroy(&data->mutex);
    pthread_cond_destroy(&data->cond);

	SAFEDELETE(data->resp);
	SAFEDELETE(data);
#if defined(PLAT_AND)

    if(isAttached)
    	vm->DetachCurrentThread();
#elif defined(PLAT_IOS)
	objc_msgSend(pool, sel_registerName("drain"));
#endif
    

	return NULL;
}

/* this is how the CURLOPT_XFERINFOFUNCTION callback works */
static int xferinfo(void *p,
                    curl_off_t dltotal, curl_off_t dlnow,
                    curl_off_t ultotal, curl_off_t ulnow)
{
  return 0;
}

/* for libcurl older than 7.32.0 (CURLOPT_PROGRESSFUNCTION) */
int CMHttpC::older_progress(void *p,
                          double dltotal, double dlnow,
                          double ultotal, double ulnow)
{
//	CM_ERRP("UP: %lf of %lf DOWN: %lf of %lf\n", ulnow, ultotal, dlnow, dltotal);
//  return xferinfo(p,
//                  (curl_off_t)dltotal,
//                  (curl_off_t)dlnow,
//                  (curl_off_t)ultotal,
//                  (curl_off_t)ulnow);
	//不支持超过double大小下载
        
	fcurl_data* data = (fcurl_data*)p;

	CMHttpC* pHttp = (CMHttpC*)data->http;
	CURL *curl = data->curl;
	double curtime = 0;


    
	if (data->exit)
	{
		CM_LOG(CM_LOGL_DEBUG, "exit from older_progress");
		return 1;
	}

	curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &curtime);

	/* under certain circumstances it may be desirable for certain functionality
	 to only run every N seconds, in order to do this the transaction time can
	 be used */
	

	if (dltotal == 0)
	{
		//还未知道下载大小，表明现在应该处在请求时
		//请求通知不使用 CURLOPT_READFUNCTION 的原因是不想使用定制的读
        if (ulnow == 0)
        {
            //减少无用上报
            return 0;
        }
        data->nStatus=Send;
		pHttp->m_pNotify->OnSend(MER_OK, ulnow);
        
        //状态判定
        if(ulnow < ultotal)
            data->nStatus=Send;
        
//        if(ultotal==ulnow )
//            data->nStatus=Response;
        
	}
    else
    {
        
//        data->nStatus=Receive;
    }

    
    
    if((curtime - data->lastruntime) >= TIMEOUT_INTERVAL) {
        data->lastruntime = curtime;
//        if(dlnow == data->lastdlnow && dltotal == data->lastdltotal && ulnow == data->lastdlnow && ultotal == data->lastultotal)
	}
        
	return 0;
}

size_t CMHttpC::head_callback(char *buffer, size_t size, size_t nitems,
		void *userp)
{
//	CM_ERRP("-%s", buffer);

	fcurl_data* data = (fcurl_data*)userp;

	if (data->resp == NULL) {
		data->resp = new CMHTTPRspHeader();
	}

	char* p = strchr(buffer, ':');
	if (p != NULL)
	{
		*p++ = '\0';
		//截取左边空格
		while (*p == ' ' && *p != '\0')
			p++;
		char* p1 = p;
		//截取末尾\r\n
		while (*p1 != '\0')
		{
			if (*p1 == '\r' || *p1 == '\n')
				*p1++ = '\0';
			else
				p1++;
		}

		data->resp->AddValue(buffer, p);

		if (strcasecmp(buffer, HH_LOCATION) == 0)
		{
			//有重定向信息
			if (data->autorloc)
			{
				//支持自动重定向
				data->save_resp = false;
			}
		}
	}


	if (strcmp(buffer, "\r\n") == 0)
	{
//		CM_ERRP("head_callback end %d", data->save_resp);
		
        CMHttpC* pHttp = (CMHttpC*)data->http;

        if(data->exit)
        {
            return 0;
        }
		if (data->save_resp)
		{
            data->nStatus=Response;
			curl_easy_getinfo(data->curl, CURLINFO_RESPONSE_CODE, &data->resp->m_nRet);
			pHttp->m_cRspHeader = *data->resp;
			pHttp->m_pNotify->OnResponse(MER_OK, &pHttp->m_cRspHeader);
//            data->nStatus=Receive;
		}
		else
		{
			SAFEDELETE(data->resp);
		}
		data->save_resp = true;

//		double downloaded;
//		curl_easy_getinfo(data->curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &downloaded);
//		fprintf(stderr, "resp header end, need download %lf", downloaded);

	}
	return size*nitems;
}

size_t CMHttpC::read_callback(char *buffer, size_t size, size_t nitems, void *userp)
{
//  struct WriteThis *pooh = (struct WriteThis *)userp;
//
//  if(size*nmemb sizeleft) {
//    *(char *)ptr = pooh->readptr[0]; /* copy one single byte */
//    pooh->readptr++;                 /* advance pointer */
//    pooh->sizeleft--;                /* less data left */
//    return 1;                        /* we return 1 byte at a time! */
//  }

  return 0;                          /* no more data left to deliver */
}

size_t CMHttpC::write_callback(char *buffer, size_t size, size_t nitems,
		void *userp) {
	size_t rembuff;

	fcurl_data* data = (fcurl_data*)userp;

//	CM_ERRP("write_callback %d", pthread_self());

	if (data->exit)
	{
		CM_LOG(CM_LOGL_DEBUG, "exit from write_callback");
		return 0;
	}

	size *= nitems;

//	CM_ERRP("make buffer_ext %d %d", size, pthread_self());
	size_t left = data->buffer_ext_max - data->buffer_ext_pos;
	size_t ext_len = size + left;
	if (left > 0 && data->buffer_ext_pos > 0)
	{
		memcpy(data->buffer_ext, &data->buffer_ext[data->buffer_ext_pos], left);
		data->buffer_ext_pos = 0;
		data->buffer_ext_max = left;
	}
    if (left == 0 && data->buffer_ext_pos > 0)
    {
		data->buffer_ext_pos = 0;
		data->buffer_ext_max = 0;
    }

	if (ext_len > data->buffer_ext_len)
	{
		char* buffer_ext = new char[ext_len];
		if (left > 0)
		{
			memcpy(buffer_ext, data->buffer_ext, left);
		}

		if(data->buffer_ext)
		{
			delete[] data->buffer_ext;
		}
		data->buffer_ext = buffer_ext;
		data->buffer_ext_len = ext_len;
	}

	memcpy(&data->buffer_ext[data->buffer_ext_max], buffer, size);
	data->buffer_ext_max += size;

	return size;
}

CMHttpC::CMHttpC(IMNotifyHttpC* pNotify, BOOL bAutoReloate):
		m_cReqHeader(),
		m_cRspHeader(),
		m_data(NULL),
		m_pt(0),
		m_bAutoRl(bAutoReloate)

{
#if defined(PLAT_IOS)
	CMNotifyHttpCIos *notify_ios= new CMNotifyHttpCIos(pNotify);
	m_pNotify=notify_ios;
#else

	m_pNotify = pNotify;
#endif
	pthread_mutex_init(&m_mutex, NULL);
}

CMHttpC::CMHttpC()
{
}

CMHttpC::~CMHttpC()
{
	Cancel();
#if defined(PLAT_IOS)
	SAFEDELETE(m_pNotify);
#endif
    pthread_mutex_destroy(&m_mutex);
}

//状态0, idle 状态1，recvheadering；状态2，headerready,直到头里数据用完
//状态3，recvdata；
void CMHttpC::Request(CMHTTPReqHeader &header)
{
    m_cReqHeader = header;
    Request();
}

void CMHttpC::Request()
{
	Cancel();

	CM_LOGP(CM_LOGL_INFO, "CMHttpC::Request url %s", (const char*)m_cReqHeader.GetUrl().Url());
	pthread_mutex_lock(&m_mutex);
	m_data = new fcurl_data;
	memset(m_data, 0, sizeof(fcurl_data));
	pthread_mutexattr_t   mta;
	pthread_mutexattr_init(&mta);
	/* or PTHREAD_MUTEX_RECURSIVE_NP */
	pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_data->mutex, &mta);
    pthread_cond_init (&m_data->cond, NULL);
    m_data->exit = false;
    
    //状态判定
    m_data->nStatus=Connect;
    
    m_data->autorloc = m_bAutoRl;
    m_data->http = this;
    m_data->save_resp = true;

    int iRet = pthread_create(&m_pt, NULL, curl_proc, m_data);

    if (iRet)
    {
        CM_ERR("CMHttpC::Request CreateThread failed");
    }
    pthread_mutex_unlock(&m_mutex);
}

void CMHttpC::Read(INT8* pBuf, INT32 nLen)
{
    CM_LOGP(CM_LOGL_DEBUG, "%x, Read start at:%x len:%d",pthread_self(), pBuf, nLen);
    
	pthread_mutex_lock(&m_data->mutex);

	if (IsRunning())
	{
        m_data->nStatus = Receive;
		m_data->buffer = pBuf;
		m_data->buffer_len = nLen;
		m_data->buffer_pos = 0;
		if (m_data->unpause)
		{
//			CM_ERRP("read %d unpause", nLen);
			m_data->unpause = false;
			pthread_cond_signal(&m_data->cond);
		}
	}
	pthread_mutex_unlock(&m_data->mutex);
}

const CMHTTPRspHeader& CMHttpC::LastResponse() const
{
       return m_cRspHeader;
}

void CMHttpC::Cancel()
{
	pthread_mutex_lock(&m_mutex);
	if (m_data != NULL)
	{
		CM_LOG(CM_LOGL_DEBUG, "CMHttpC::Cancel");
		//停掉当前的线程
		pthread_mutex_lock(&m_data->mutex);

		m_data->exit = true;
        m_data->nStatus=NoRequest;
        
		pthread_cond_signal(&m_data->cond);
        m_data->http = NULL;
        fcurl_data* data = m_data;
        m_data = NULL;
#if defined(PLAT_IOS)
	CMNotifyHttpCIos* notify_ios = (CMNotifyHttpCIos*)m_pNotify;
	notify_ios->Cancel();
#endif
		pthread_mutex_unlock(&data->mutex);

//		CM_LOG(CM_LOGL_INFO, "CMHttpC::Cancel wait");
//		pthread_join(m_pt, NULL);
	}
	pthread_mutex_unlock(&m_mutex);
}

BOOL CMHttpC::IsRunning()
{
    return (m_data != NULL && !m_data->exit);
}
