#pragma once

#include "resource.h"
#include "QKMessages.h"
#include <exdisp.h>
#include <comdef.h>
#include "flash10a.tlh"
#include "MMSystem.h"
#include "CImageCutFrame.h"
#include <string>
#include <io.h>
#include "../Common/tools.h"
#include "FlashPlayer.h"
#include <vector>
using namespace std;

#pragma comment (lib, "winmm")

#define FILE_NAME_CUT_PNG					_T("player-screen.png")
#define FILE_NAME_PAUSE_PNG					_T("player-pause.png")
#define FILE_NAME_BLACK_PNG					_T("player-black.png")

#define FLASH_LOADINGTIPS_TIMER_ID			80


class CQKFlashGameFrameWnd :public CWindowWnd, public INotifyUI
{
public:
	//无参数的构造函数
	CQKFlashGameFrameWnd();
	~CQKFlashGameFrameWnd();

	//获取窗体类名
	LPCTSTR GetWindowClassName() const										
	{ 
		return m_strWindowClassName;
	}

	//类的风格
	UINT GetClassStyle() const												
	{ 
		return UI_CLASSSTYLE_DIALOG;										
	}

	void OnFinalMessage(HWND /*hWnd*/) 
	{ 
		delete this; 
	}

	void Init() ;
	void SetContainerBgImage(bool bSetBgImage);
	void Notify(TNotifyUI& msg);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CStdString GetClassID() {return m_strClassID;}
	CStdString GetGamePath() { return m_strGamePath; };
	CStdString GetGameID() { return m_strGameID; };
	CStdString GetGameSign1(){ return m_strGameSign1;}
	CStdString GetGameSign2() {return m_strGameSign2;}
	CStdString GetGameOnLine(){return m_strGameOnLine;}
	CStdString GetUserID() { return m_strUserID; };
	CStdString GetUserKK() { return m_strUserKK; };
	bool GetNetStatus(){ return m_bNetStatus; };
	bool GetLogStatus(){ return m_bLogStatus; };

	void SetGameURL(CStdString strGameURL){ m_strGameURL = strGameURL; };
	void SetDownloadGamePath(CStdString DownloadPath){m_strDownloadGamePath = DownloadPath;}
	void SetGameID(CStdString GameID){ m_strGameID = GameID;};

	void SetGameSign1(CStdString GameSign1)
	{
		m_strGameSign1 = GameSign1;
		m_sign1 = str2ulong(GameSign1.GetChar());
		//lsdebug
	}

	void SetGameSign2(CStdString GameSign2)
	{
		m_strGameSign2 = GameSign2;
		m_sign2 = str2ulong(GameSign2.GetChar());
		//lsdebug
	}
	void SetGameOnLine(CStdString GameOnLine){m_strGameOnLine = GameOnLine;}
	void SetNetStatus(bool NetStatus){ m_bNetStatus = NetStatus;};
	void SetLogStatus(bool LogStatus){ m_bLogStatus = LogStatus;};
	void SetUserID(CStdString UserID){ m_strUserID = UserID;};
	void SetUserKK(CStdString UserKK){ m_strUserKK = UserKK;};

	void SetGameName();
	void SetGameTitle(CStdString GameTitle){m_strOpenGameTitle = GameTitle;};
	void SetWindowClassName(CStdString ClassID)
	{
		m_strWindowClassName.Format(_T("QKFlashGame:%s"),ClassID.GetData());
	}
	void SetWindowClassID(CStdString ClassID)
	{
		m_strClassID = ClassID;
	}
	bool FlashIsDownload(CStdString strGameName);//查找文件是否存在，如果在就下载完了，没有就没下载

	static DWORD WINAPI ListenProgressThread(LPVOID pData);//监听线程，获取下载进度，下载完成进行播放

	int SendMessageToQKDownload(HWND mhWnd, UINT uMsg, LPVOID lpParam, DWORD cbData);
	int StartDownloadFlash(unsigned long sign1,unsigned long sign2);//发送消息到p2p接口，开始下载
	int GetFlashPercent(unsigned long sign1,unsigned long sign2);	//得到下载进度

	void PlayerToFullScreen();		//全屏

	void PreCloseLight();         //关灯前的准备工作
	void PreOpenLight();          //开灯前的准备工作
	void AdjustFlashPlayerPos();  //调整子窗口的位置
	BOOL Suspend_or_Resume_Process (unsigned int nSuspend);//挂起或者开始子线程
	void CutFlashPlayerImg(CStdString strFileName);  //截取客户区，并保存
	void CreatePlayerWnd();      //创建子线程，线程中创建子窗口，开始播放
	void StartGame();            //第一次开始播放游戏
	BOOL SetMute(BOOL bMute);    //设置静音
	void OpenLight();			 //打开灯

	void DisableSomeButtons();   //下载小游戏时禁用播放器的重玩、暂停按钮
	void EnableSomeButtons();    //下载完成启用被禁掉的按钮

public:
	CPaintManagerUI m_pm;
	double m_startTime;          //开始时间

private:
	CButtonUI* m_pCloseBtn;									//关闭按钮
	CButtonUI* m_pMaxBtn;									//最大化按钮
	CButtonUI* m_pRestoreBtn;								//恢复按钮
	CButtonUI* m_pMinBtn;									//最小化按钮
	CButtonUI* m_pPlayBtn;									//开始按钮
	CButtonUI* m_pPauseBtn;									//暂停按钮
	CButtonUI* m_pReplayBtn;								//重玩按钮
	CButtonUI* m_pMuteBtn;									//静音按钮
	CButtonUI* m_pVolubleBtn;								//开启声音按钮
	CButtonUI* m_pScreenshotBtn;
	CButtonUI* m_pCommentBtn;
	CButtonUI* m_pFullScreenBtn;                             //全屏
	CButtonUI* m_pRestoreFullScreenBtn;                             
	CButtonUI* m_pOpenLightBtn;                              //开灯
	CButtonUI* m_pCloseLightBtn;                              
    CControlUI* m_pVertical;
	CContainerUI* m_pHorizen;

	CContainerUI* m_Container;

	bool m_bNetStatus;
	bool m_bLogStatus;

	CStdString m_strDownloadGamePath;
	CStdString m_strGameID;
	
	CStdString m_strGameOnLine;
	CStdString m_strUserID;
	CStdString m_strUserKK;

	CStdString m_strGameSign1;
	CStdString m_strGameSign2;

	unsigned long m_sign1;
	unsigned long m_sign2;

	CStdString m_strGameURL;
	CStdString m_strGameName;

	HANDLE m_hListenProgress;
	DWORD m_dwThreadID;

	HWND m_hQKDownload;

	CStdString m_strWindowClassName;
	CStdString m_strClassID;

	//vector <CStdString> m_flashTips;
	//int m_iTipsNext;
	bool m_bIsDownload;

	CStdString m_strOpenGameTitle;

	BOOL  m_bFullScreen;
	RECT  m_rcPrePositon;

	POINT m_ptPre;
	BOOL m_bLButtonDown;

public:
	CFlashPlayer* m_pFlashPlayer;	//子窗口指针
	HANDLE m_hThread;				//子线程句柄
	DWORD  m_dwFlashPlayerThreadID; //子线程ID
	BOOL   m_bReplay;
	BOOL   m_bSuspend;

	CStdString m_strGamePath;
};

extern CQKFlashGameFrameWnd* g_pMainFrame;