
#pragma once

#include "StdAfx.h"
#include <exdisp.h>
#include <comdef.h>
#include "MMSystem.h"
#include "Tlhelp32.h"
#include "../../Common/QKMessages.h"
#include "flash10a.tlh"

#define STATUS_FLASH			0
#define STATUS_PROGRESS			1

#define			FLASH_LOADING			_T("loading.swf")

#pragma comment (lib, "winmm")

class CQKFlashPlayer : public CWindowWnd ,public INotifyUI
{
public:
	CQKFlashPlayer(){};
	LPCTSTR GetWindowClassName() const;
	void Initialize();
	void Notify(TNotifyUI& msg);

	void OnFinalMessage(HWND /*hWnd*/) 
	{
		delete this; 
	}

	BOOL Suspend_or_Resume_Process (unsigned int nSuspend);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnFlashPlay(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//需要文件路径
	LRESULT OnFlashPause(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//SendMessage(this.m_hWnd, WM_COPYDATA, 0, ref cds);
	LRESULT OnFlashReplay(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnMove (CRect rcDest);
	BOOL SetMute(BOOL bMute);

	void SetWindowClassName(CStdString strClassID)
	{
		m_strWindowClassName.Format(_T("QKFlashPlayer:%s"),strClassID.GetData());
	}
	void SetWindowClassID(CStdString strClssID)
	{
		m_strClassID = strClssID;
	}
private:
	CControlUI *pControl;
	CPaintManagerUI m_pm;
	IShockwaveFlash *m_pFlash;
	CActiveXUI* m_pActiveX;
	CStdString m_strGamePath;

	CStdString m_strWindowClassName;
	CStdString m_strClassID;

	CTabLayoutUI *m_pTabLayout;
	CProgressUI *m_pProgress;
	CLabelUI *m_pFlashTip;
};
