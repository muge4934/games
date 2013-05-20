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
	//�޲����Ĺ��캯��
	CQKFlashGameFrameWnd();
	~CQKFlashGameFrameWnd();

	//��ȡ��������
	LPCTSTR GetWindowClassName() const										
	{ 
		return m_strWindowClassName;
	}

	//��ķ��
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
	bool FlashIsDownload(CStdString strGameName);//�����ļ��Ƿ���ڣ�����ھ��������ˣ�û�о�û����

	static DWORD WINAPI ListenProgressThread(LPVOID pData);//�����̣߳���ȡ���ؽ��ȣ�������ɽ��в���

	int SendMessageToQKDownload(HWND mhWnd, UINT uMsg, LPVOID lpParam, DWORD cbData);
	int StartDownloadFlash(unsigned long sign1,unsigned long sign2);//������Ϣ��p2p�ӿڣ���ʼ����
	int GetFlashPercent(unsigned long sign1,unsigned long sign2);	//�õ����ؽ���

	void PlayerToFullScreen();		//ȫ��

	void PreCloseLight();         //�ص�ǰ��׼������
	void PreOpenLight();          //����ǰ��׼������
	void AdjustFlashPlayerPos();  //�����Ӵ��ڵ�λ��
	BOOL Suspend_or_Resume_Process (unsigned int nSuspend);//������߿�ʼ���߳�
	void CutFlashPlayerImg(CStdString strFileName);  //��ȡ�ͻ�����������
	void CreatePlayerWnd();      //�������̣߳��߳��д����Ӵ��ڣ���ʼ����
	void StartGame();            //��һ�ο�ʼ������Ϸ
	BOOL SetMute(BOOL bMute);    //���þ���
	void OpenLight();			 //�򿪵�

	void DisableSomeButtons();   //����С��Ϸʱ���ò����������桢��ͣ��ť
	void EnableSomeButtons();    //����������ñ������İ�ť

public:
	CPaintManagerUI m_pm;
	double m_startTime;          //��ʼʱ��

private:
	CButtonUI* m_pCloseBtn;									//�رհ�ť
	CButtonUI* m_pMaxBtn;									//��󻯰�ť
	CButtonUI* m_pRestoreBtn;								//�ָ���ť
	CButtonUI* m_pMinBtn;									//��С����ť
	CButtonUI* m_pPlayBtn;									//��ʼ��ť
	CButtonUI* m_pPauseBtn;									//��ͣ��ť
	CButtonUI* m_pReplayBtn;								//���水ť
	CButtonUI* m_pMuteBtn;									//������ť
	CButtonUI* m_pVolubleBtn;								//����������ť
	CButtonUI* m_pScreenshotBtn;
	CButtonUI* m_pCommentBtn;
	CButtonUI* m_pFullScreenBtn;                             //ȫ��
	CButtonUI* m_pRestoreFullScreenBtn;                             
	CButtonUI* m_pOpenLightBtn;                              //����
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
	CFlashPlayer* m_pFlashPlayer;	//�Ӵ���ָ��
	HANDLE m_hThread;				//���߳̾��
	DWORD  m_dwFlashPlayerThreadID; //���߳�ID
	BOOL   m_bReplay;
	BOOL   m_bSuspend;

	CStdString m_strGamePath;
};

extern CQKFlashGameFrameWnd* g_pMainFrame;