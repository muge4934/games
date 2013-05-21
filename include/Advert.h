#pragma once
#include "StdAfx.h"

#include "../../Common/flash10a.tlh"


#define   FILE_ADVERT_DEFAULT			_T("Adv_Default.png")
//#define   DIR_ADVERT					_T("\\HallData\\")
#define   FILE_ADVERT_HEAD				_T("\\Advs\\Data_")
#define   FILE_NAME_ADVERT_INI			_T("HallData.ini")
#define   ADVERT_SETTING_MODULE_NAME	_T("DataConfig")
#define   ADVERT_SETTING_DATA_NUM		_T("DataNum")
#define   ADVERT_SETTING_DATA_LAST		 _T("LastNum")
#define   ADVERT_SETTING_DATA			_T("DataNote")
#define   ADVERT_RES_MODULE_NAME		_T("DataRes")
#define   ADVERT_TIME_MODULE_NAME		_T("TimeSpace")
#define   ADVERT_TIME_DATA_NUM			_T("DataTime")
#define   ADVERT_TIME_DATA_UNIT			_T("DataUnit")   //时间单位h，m为分钟，s秒，默认空或者ms为毫秒
#define   ADVERT_TIME_LAST_DATA			_T("DataLast")
#define   ADVERT_ADDRESS_DEFAULT		_T("http://box.7k7k.com/index.html")
#define   ADVERT_OPTION_ALLNUM			9
#define   ADVERT_TIME_DEFAULT			3000
#define   ADVERT_TIME_MAXTIME			ADVERT_TIME_DEFAULT*15
#define   ADVERT_TYPE_IN				0
#define   ADVERT_TYPE_OUT				1
#define   ADVERT_TYPE_WB				2
#define   ADVERT_TYPE_DEFAULT			1

#define   ADVERT_GROUP_MODULE_NAME		_T("GroupConfig")
#define   ADVERT_GROUP_NUM				_T("GroupNum")
#define   ADVERT_GROUP_LAST			    _T("LastGroup")

/**********************************************************
调用本类，父窗口类必须提供其本身名为g_pMainFrame的全局变量，
同时在父窗口类中实现GoToAdvertUrl(std::string strUrl)供
广告地址跳转
***********************************************************/

class CAdvert :public CContainerUI,public INotifyUI
{
public:
	//构造函数中，pManger不能为空，cstrContainerName必须为布局中的容器名。
	CAdvert(CPaintManagerUI* pManager,CStdString cstrContainerName, int nAdvertType=0,bool bIsNeedActiveX=false,bool bIsWeb=false);
	CAdvert(CPaintManagerUI* pManager,CStdString cstrContainerName, CStdString cstrFileNamePart, int nWidth,int nHeigth,bool bNeedAutoChange=true, bool bNeedOptionBtn=true,int nAdvertType=0,bool bIsNeedActiveX=false,bool bIsWeb=false);
	~CAdvert(void);

	void Notify(TNotifyUI& msg);
	void Initialize();

	void CreateAdvert(CStdString cstrUIXmlDir=_T(""));

	void SetNetAdvertExtCall(bool bNext=false);
	void SetNextAdvert();
	void SetAdvert(int nIndex);

	void ReloadFalsh();
	void ReloadWeb();

	void StartAdvertTime();
	void KillAdvertTime();

	void SetNeedTime(bool bIsNeed);
	void SetOptionVisible(bool bNormal=true,int nOptionBeg=0,int nOptionEnd=-1,bool bVisible= false);
	void StartNoChangeAdvert();

	void SetLastNum(int nGroup,int nIndex);

	CStdString GetAdvertData(){return m_cstrData;};
	int GetAdvertType(){return m_nAdvertType;};
	int GetAdvertIndex(){return m_nCurrIndex;};
	void ResponseClick();
	CStdString GetAdvFileName(){return m_cstrFileName;};

private:

public:
	int m_nCurrIndex;

private:

	CPaintManagerUI* m_pManager;

	int m_nWidth;
	int m_nHeight;
	int m_nAdvertType;

	int m_nTimeId;        //由构造函数传入
	int m_nTimeSpace;

	int m_nAdvertResNum;  //总资源个数

	int m_nGroupNum;
	int m_nLastGroup;
	CStdString m_cstrConfigModule;
	CStdString m_cstrResModule;

	CStdString m_cstrFileName;
	CStdString m_cstrFlashRes;

	CStdString m_cstrData;

	CStdString m_cstrKeyBtn;

	bool m_bIsCreatedNeedData;
	bool m_bIsNeedActiveX;
	bool m_bIsWeb;
	bool m_bIsInited;

	bool m_bIsNeedTime;
	bool m_bIsNeedAutoChange;
	bool m_bIsNeedOptionBtn;

	CContainerUI* m_pContainerParent; 

	CTabLayoutUI* m_pTabAdv;
	CVerticalLayoutUI* m_pVLFrame;

	CHorizontalLayoutUI* m_pHLGif;
	CHorizontalLayoutUI* m_pHLImgFrame;
	CHorizontalLayoutUI* m_pHLOption;
	CActiveXUI* m_pActivex;

	CButtonUI* m_pAdvBtn;
	CButtonUI* m_pAdvBtnOption;

	CGifControlUI* m_pGifControl;

	COptionUI* m_pOptionAdv[ADVERT_OPTION_ALLNUM];

	IWebBrowser2* m_pWebBrowser;

	CStdString m_strAdvPostion;

	WIN32_FIND_DATA m_fdDataInfo;
};
