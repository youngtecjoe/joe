// MocxtestDlg.h : ヘッダー ファイル
//

/*
		Update:
				 che.z.l 2007.04.24 for adding MahineStatusChaned event(@R010846)
				 liu.j.l 2008.02.02 Mk30Comm.ocxにメソッド追加： 電圧値： GetVoltage、電流値： GetElectricity、頻度値： GetFrequency、F値： GetFSpeed @10989
				 chen.x.c 2008.08.26 Mk30Comm.ocxにメソッド追加 (@10989.1)
				liu.j.l 2009.01.19 Mk30Comm.ocxにメソッド追加： GetCoordSys、GetCoordOrg、GetMachCoord、GetCoord @10989B
				yao.x.c 2011.07.26 add for @11168
*/

//{{AFX_INCLUDES()
#include "mk30comm.h"
//}}AFX_INCLUDES

#if !defined(AFX_MOCXTESTDLG_H__066E417B_63FE_11D3_8ED9_0000E85B90F9__INCLUDED_)
#define AFX_MOCXTESTDLG_H__066E417B_63FE_11D3_8ED9_0000E85B90F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SearchCondition.h"//@11168 
#include <afxtempl.h>//@11168 

//++@11168 
#define NCFILE_TEST_DATA_PATH		"D:\\Test"
#define NCFILE_TEST_DATA_NAME		"D:\\Test\\cond.tmp"
//--@11168

/////////////////////////////////////////////////////////////////////////////
// CMocxtestDlg dialog

class CMocxtestDlg : public CDialog
{
// 構築
public:
	// ++@11168
	int m_nInch;
	int m_nDigit;
	BOOL m_bC555Sign;
	CSearchCondition *m_pWndSearchCond;//@11168
	void GetC555Sign(CString strLqknd);
	CString GetDatabaseName(int nDatabaseType);
	void CreateCondSchInputInfo(CArray<CString, CString> &arrString, int nDatabaseType, SWF_CONDITION &swf);
	void CreateCondSchInputInfo(CArray<CString, CString> &arrString, int nDatabaseType, SWF_CONDITION_GE &swf);
	void CreateTestNcFileData(CArray<CString, CString> &arrString, int nCutNum, SWF_MchCon_SU *mchcon, SWF_MCB_SU *mcb, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, long *nMTRL);
	void CreateTestNcFileData(CArray<CString, CString> &arrString, int nCutNum, SWF_MchCon_SU *mchcon, SWF_MCB_SU_WS *mcb, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, long *nMTRL);
 	//--@11168

	// start @Test
	void TrimPreviousLine( CString &sString, int nMaxLine );
	void AddTextInEventOutputView(LPCTSTR lpText);
    void SetTextInEventOutputView(LPCTSTR lpText);
    void SetTextInMethodOutputView(LPCTSTR lpText);
    void AddTextInMethodOutputView(LPCTSTR lpText);

	CString	m_sEventResult;
	CString	m_sAttributeResult;
	CString	m_sMethodResult;
    DWORD m_nMethodStep;    // method step count
    DWORD m_nEventStep;     // Event step count
	BOOL m_bConnect;
	// end @Test

	BOOL m_bRunCycle;
	void run(int step);
	CMocxtestDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

	BOOL GetSafeArray(VARIANT* varValue);
// Dialog Data
	//{{AFX_DATA(CMocxtestDlg)
	enum { IDD = IDD_MOCXTEST_DIALOG };
	CEdit	m_SigOnMaxFreqEdit;
	CEdit	m_Resisitivity2Edit;
	CEdit	m_Resisitivity1Edit;
	CEdit	m_DigitEdit;
	CEdit	m_InchEdit;
	CEdit	m_MaxFrequencyEdit;
	CEdit	m_EventResultEdit;
	CEdit	m_MethodResultEdit;
	CEdit	m_FSpeedEdit;
	CEdit	m_FrequencyEdit;
	CEdit	m_ElectricityEdit;
	CEdit	m_VoltageEdit;
	CMk30Comm	m_mk30;
	CString	m_username;
	CString	m_password;
	CString	m_rasusername;
	CString	m_raspassword;
	CString	m_machine;
	CString	m_emkey;
	CString	m_sendfile;
	CString	m_delfile;
	CString	m_runfilename;
	CString	m_status;
	CString	m_commstatus;
	CString	m_offset;
	CString	m_history;
	CString	m_version;
	BOOL	m_bLoopRun;
	long	m_lCoordSysForGetCoordOrg;
	int		m_lCoordSysForGetCoord;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMocxtestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected: 
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMocxtestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton7();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	virtual void OnOK();
	afx_msg void OnButton5();
	afx_msg void OnButton15();
	afx_msg void OnButton6();
	afx_msg void OnButton10();
	afx_msg void OnDenyRemoteAccessMk30commctrl1();
	afx_msg void OnNetworkErrorMk30commctrl1(short intError);
	afx_msg void OnNcErrorMk30commctrl1(LPCTSTR strError);
	afx_msg void OnSendFileCompleteMk30commctrl1(short intError, LPCTSTR strError);
	afx_msg void OnDeleteFileCompleteMk30commctrl1(short intError, LPCTSTR strError);
	afx_msg void OnExecuteCompleteMk30commctrl1(short intError, LPCTSTR strError);
	afx_msg void OnVersionErrorMk30commctrl1(short wServerVersionMajor, short wServerVersionMinor, short wClientVersionMajor, short wClientVersionMinor);
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton4();
	afx_msg void OnButton13();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonLogstart();
	afx_msg void OnButtonLogend();
	afx_msg void OnMachineStatusChangedMk30commctrl1(short nOldStatus, short nNewStatus);
	afx_msg void OnBnGetVoltage();
	afx_msg void OnBnGetElectricity();
	afx_msg void OnBnGetFrequency();
	afx_msg void OnBnGetFSpeed();
	afx_msg void OnBnClearMethodMsg();
	afx_msg void OnBnClearEventMsg();
	afx_msg void OnCheckLoopRun();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnGetMaxFrequency();
	afx_msg void OnBnGetSigonMaxFrequency();
	afx_msg void OnBnGetResisitivity1();
	afx_msg void OnBnGetResisitivity2();
	afx_msg void OnBnGetInch();
	afx_msg void OnBnGetDigit();
	afx_msg void On10989();
	afx_msg void OnBnGetCoordOrg();
	afx_msg void OnBnGetCoordSys();
	afx_msg void OnBnGetMachCoord();
	afx_msg void OnBnGetCoord();
	afx_msg void OnBnPowerOn();
	afx_msg void OnBUTTONGetMachineKind();
	afx_msg void OnBUTTONGetCondition();
	afx_msg void OnBtnDoConditionSearch();
	afx_msg void OnBtnGetCondType();
	afx_msg void OnConditionSearch(WPARAM wParam,LPARAM lParam);//@11168
	afx_msg void OnBtnGetMachinelock();
	afx_msg void OnBtnGetOffsetValue();
	afx_msg void OnBtnSetMacrovar();
	afx_msg void OnBtnGetMacrovar();
	afx_msg void OnBtnGetMacrovarRange();
	afx_msg void OnBtnGetMacrovarSafearray();
	afx_msg void OnBtnSetMacrovarRange();
	afx_msg void OnGetRunningFileName();
	afx_msg void OnGetRunningMainNcFileFirstLine();
	afx_msg void OnBtnSetMacrovarSafearray();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MOCXTESTDLG_H__066E417B_63FE_11D3_8ED9_0000E85B90F9__INCLUDED_)
