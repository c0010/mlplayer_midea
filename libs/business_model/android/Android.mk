
LOCAL_PATH:= $(call my-dir)/..

include $(CLEAR_VARS)

LOCAL_MODULE:= business_model

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
	cmbrowser.cpp \
	cmcategory.cpp \
	cmcomment.cpp \
	cmcontacts.cpp \
	cmcontenthandler.cpp \
	cmcoursedownload.cpp \
	cmcourseinfo.cpp \
	cmexam.cpp \
	cmexamlist.cpp \
	cmexercise.cpp \
	cmexerciselist.cpp \
	cmfavorites.cpp \
	cmfeedback.cpp \
	cmgetnewcontent.cpp \
	cmglobal.cpp \
	cmglobal_and.cpp \
	cmlogin.cpp \
	cmmyinfo.cpp \
	cmmytrainlist.cpp \
	cmqacategory.cpp \
	cmqalist.cpp \
	cmquestioncategory.cpp \
	cmquestiondetail.cpp \
	cmquestionhandler.cpp \
	cmrecentcontent.cpp \
	cmresetpassword.cpp \
	cmsearch.cpp \
	cmsession.cpp \
	cmsettings.cpp \
	cmspecialtopic.cpp \
	cmsurvey.cpp \
	cmsurveylist.cpp \
	cmtrainapplylist.cpp \
	cmtrainsigninlist.cpp \
	cmundone.cpp\
	cmupdate.cpp \
	cmwebimage.cpp \
	cmwrongquestion.cpp \
	cmgeneral.cpp \
	cmsearchhotkey.cpp \
	cmgloballistener.cpp \
	cmdbhelper.cpp \
	cmquestionupload.cpp \
	cmshake.cpp \
	cmfileinfo.cpp \
	cmupload.cpp \
	cmwetools.cpp \
	cmreplaycomment.cpp \
	cmsearchcourse.cpp \
	cmretrievepass.cpp \
	cmgroup.cpp \
	cmmessage.cpp\
	cmsessionsequence.cpp\
	cmpushmsg.cpp\
	cmversionverify.cpp\
	android/cmbrowser_jni.cpp \
	android/cmcategory_jni.cpp \
	android/cmcomment_jni.cpp \
	android/cmcommon_jni.cpp \
	android/cmcontacts_jni.cpp \
	android/cmcontenthandler_jni.cpp \
	android/cmcoursedownload_jni.cpp \
	android/cmcourseinfo_jni.cpp \
	android/cmexamlist_jni.cpp \
	android/cmexam_jni.cpp \
	android/cmexercise_jni.cpp \
	android/cmexerciselist_jni.cpp \
	android/cmfavorites_jni.cpp \
	android/cmfeedback_jni.cpp \
	android/cmgetnewcontent_jni.cpp \
	android/cmlogin_jni.cpp \
	android/cmmyinfo_jni.cpp \
	android/cmmytrainlist_jni.cpp \
	android/cmqacategory_jni.cpp \
	android/cmqalist_jni.cpp \
	android/cmquestioncategory_jni.cpp \
	android/cmquestiondetail_jni.cpp \
	android/cmquestionhandler_jni.cpp \
	android/cmrecentcontent_jni.cpp \
	android/cmresetpassword_jni.cpp \
	android/cmsearch_jni.cpp \
	android/cmsettings_jni.cpp \
	android/cmspecialtopic_jni.cpp \
	android/cmsurveylist_jni.cpp \
	android/cmsurvey_jni.cpp \
	android/cmtrainapplylist_jni.cpp \
	android/cmtrainsigninlist_jni.cpp \
	android/cmundone_jni.cpp\
	android/cmupdate_jni.cpp \
	android/cmwebimage_jni.cpp \
	android/cmwrongquestion_jni.cpp \
	android/cmsession_jni.cpp \
	android/imcommon_jni.cpp \
	android/cmgeneral_jni.cpp \
	android/cmquestionupload_jni.cpp \
	android/cmshake_jni.cpp \
	android/cmupload_jni.cpp \
	android/cmfileinfo_jni.cpp \
	android/cmwetools_jni.cpp \
	android/cmreplaycomment_jni.cpp \
	android/cmsearchhotkey_jni.cpp \
	android/cmsearchcourse_jni.cpp \
	android/cmretrievepass_jni.cpp \
	android/cmgroup_jni.cpp \
	android/cmmessage_jni.cpp\
	android/cmsessionsequence_jni.cpp\
	android/cmpushmsg_jni.cpp\
	android/cmversionverify_jni.cpp\
	
LOCAL_C_INCLUDES += $(LOCAL_PATH) $(LOCAL_PATH)/../include $(LOCAL_PATH)/../minizip $(LOCAL_PATH)/../tools $(LOCAL_PATH)/../xmlparser $(LOCAL_PATH)/../network $(LOCAL_PATH)/../sqlite $(LOCAL_PATH)/../openssl/include

ifeq ($(LIBS_BUILD_SHARED),)
include $(BUILD_STATIC_LIBRARY)
else
LOCAL_SHARED_LIBRARIES := xmlparser network tools  minizip ssl
include $(BUILD_SHARED_LIBRARY)
endif


