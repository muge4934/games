
#pragma once

#define STAR1_BK_IMAGE                   _T("comment-brightstar-1.png")
#define STAR2_BK_IMAGE                   _T("comment-brightstar-2.png")
#define STAR3_BK_IMAGE                   _T("comment-brightstar-3.png")
#define STAR4_BK_IMAGE                   _T("comment-brightstar-4.png")
#define STAR5_BK_IMAGE                   _T("comment-brightstar-5.png")

#define STAR_BK_DEFAUL_IMAGE            _T("comment-darkstar.png")


class CQKComment : public CWindowWnd, public INotifyUI
{
public:
	CPaintManagerUI m_pm;
	CStdString m_CommentTextCotentstr;

	CQKComment(void);
	~CQKComment(void);
	
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);
	void Init();
	void Notify(TNotifyUI& msg);
	LPCTSTR  GetWindowClassName() const;
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetImageStarBtnBK(LPCTSTR strname, CButtonUI *pstartBtn);
	void ClearImageStarBtnBK();
	bool PostStarToServer(CStdString strGameID, int nGradeStar);
	int  PostCommentToServer ();
	void ShowGrade(CTextUI* TextGrade,CTextUI* MessageGrade);

private:
	int m_nGradeStar;

	CButtonUI *m_pImageCutBackBtn;
	CButtonUI *m_pCommentCloseBtn;
	CButtonUI *m_pCommentGradeBtn;
	CButtonUI *m_pCommentStarBtn1;
	CButtonUI *m_pCommentStarBtn2;
	CButtonUI *m_pCommentStarBtn3;
	CButtonUI *m_pCommentStarBtn4;
	CButtonUI *m_pCommentStarBtn5;
	CButtonUI *m_pTextCommentBtn;
	CRichEditUI *m_pCommentTextCotent;

	//CTextUI *m_pCommentTextGrade1;
	//CTextUI *m_pCommentTextGrade2;
	//CTextUI *m_pCommentTextGrade3;
	//CTextUI *m_pCommentTextGrade4;
	//CTextUI *m_pCommentTextGrade5;
	CTextUI *m_pCommentTextPromptMessage;

	CTextUI *m_pCommentMessageGrade1;
	CTextUI *m_pCommentMessageGrade2;
	CTextUI *m_pCommentMessageGrade3;
	CTextUI *m_pCommentMessageGrade4;
	CTextUI *m_pCommentMessageGrade5;
	CTextUI *m_pCommentTextSuccess;

};
