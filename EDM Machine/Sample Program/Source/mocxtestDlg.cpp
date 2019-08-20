// MocxtestDlg.cpp : インプリメンテーション ファイル
//
/*
		Update:
				 che.z.l 2007.04.24 for adding MahineStatusChaned event(@R010846)
				 liu.j.l 2008.02.02 Mk30Comm.ocxにメソッド追加： 電圧値： GetVoltage、電流値： GetElectricity、頻度値： GetFrequency、F値： GetFSpeed @10989
				 chen.x.c 2008.08.26 Mk30Comm.ocxにメソッド追加 (@10989.1)
				 liu.j.l 2009.01.19 Mk30Comm.ocxにメソッド追加： GetCoordSys、GetCoordOrg、GetMachCoord、GetCoord @10989B
				 liu.j.l 2010.02.10 for the bug file cannot be found when Far Run @11125
				 liu.j.l 2010.02.19 for the bug file cannot be found when Far Run @11125B
				 yao.x.c 2011.07.26 add for @11168
				 lu.x.d  2016.03.21 get Macro number and set Macro value @4905
				 lu.x.d  2016.06.01	@4905D: Set Macro from nStartNo to nEndNo
*/

#include "stdafx.h"
#include "Mocxtest.h"
#include "MocxtestDlg.h"
#include "Log.h" // @11125
#include  <math.h>//@11168


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ
#define MAX_LINES_FOR_MSG	999 // max lines for message @Test
// start @10989B
#define E_SUCCESS		-1 
#define E_FAILED		 0
// end @10989B

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMocxtestDlg ダイアログ

CMocxtestDlg::CMocxtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMocxtestDlg::IDD, pParent)
{
	// start @Test
	m_bConnect = FALSE;
    m_nMethodStep = 0;
	m_nEventStep = 0;
	// end @Test
	//{{AFX_DATA_INIT(CMocxtestDlg) 
	m_username = _T("administrator");	// @10989B
	m_password = _T("gakumon");			// @10989B
	m_rasusername = _T("rasperson");	// @10989B
	m_raspassword = _T("enkaku");		// @10989B
 	m_machine = _T("lion4");  
	m_emkey = _T("");
	m_sendfile = _T("");
	m_delfile = _T("");
	m_runfilename = _T("");
	m_status = _T("");
	m_commstatus = _T("");
	m_offset = _T("");
	m_history = _T("");
	m_version = _T("");
	m_bLoopRun = FALSE;
	m_lCoordSysForGetCoordOrg = 0;
	m_lCoordSysForGetCoord = 0;
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bC555Sign = FALSE;//@11168
}

void CMocxtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMocxtestDlg)
	DDX_Control(pDX, IDC_EDIT_SIGON_MAX_FREQUENCY, m_SigOnMaxFreqEdit);
	DDX_Control(pDX, IDC_EDIT_RESISITIVITY_2, m_Resisitivity2Edit);
	DDX_Control(pDX, IDC_EDIT_RESISITIVITY_1, m_Resisitivity1Edit);
	DDX_Control(pDX, IDC_EDIT_DIGIT, m_DigitEdit);
	DDX_Control(pDX, IDC_EDIT_INCH, m_InchEdit);
	DDX_Control(pDX, IDC_EDIT_MAX_FREQUENCY, m_MaxFrequencyEdit);
	DDX_Control(pDX, IDC_EDIT_EVENT_RESULT, m_EventResultEdit);
	DDX_Control(pDX, IDC_EDIT_METHOD_RESULT, m_MethodResultEdit);
	DDX_Control(pDX, IDC_EDIT_F_SPEED, m_FSpeedEdit);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_FrequencyEdit);
	DDX_Control(pDX, IDC_EDIT_ELECTRICITY, m_ElectricityEdit);
	DDX_Control(pDX, IDC_EDIT_VOLTAGE, m_VoltageEdit);
	DDX_Control(pDX, IDC_MK30COMMCTRL1, m_mk30);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_rasusername);
	DDX_Text(pDX, IDC_EDIT4, m_raspassword);
	DDX_Text(pDX, IDC_EDIT6, m_machine);
	DDX_CBString(pDX, IDC_COMBO1, m_emkey);
	DDX_Text(pDX, IDC_EDIT7, m_sendfile);
	DDX_Text(pDX, IDC_EDIT8, m_delfile);
	DDX_Text(pDX, IDC_EDIT9, m_runfilename);
	DDX_Text(pDX, IDC_MACHINE_STATUS, m_status);
	DDX_Text(pDX, IDC_COMM_STATUS, m_commstatus);
	DDX_Text(pDX, IDC_EDIT10, m_offset);
	DDX_Text(pDX, IDC_EDIT11, m_history);
	DDX_Text(pDX, IDC_OCX_VERSION, m_version);
	DDX_Check(pDX, IDC_CHECK_LOOP_RUN, m_bLoopRun);
	DDX_Text(pDX, IDC_EDIT_GET_COORD_ORG, m_lCoordSysForGetCoordOrg);
	DDX_Text(pDX, IDC_EDIT_GET_COORD, m_lCoordSysForGetCoord);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMocxtestDlg, CDialog)
	//{{AFX_MSG_MAP(CMocxtestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_LOGSTART, OnButtonLogstart)
	ON_BN_CLICKED(IDC_BUTTON_LOGEND, OnButtonLogend)
	ON_BN_CLICKED(IDC_BN_GET_VOLTAGE, OnBnGetVoltage)
	ON_BN_CLICKED(IDC_BN_GET_ELECTRICITY, OnBnGetElectricity)
	ON_BN_CLICKED(IDC_BN_GET_FREQUENCY, OnBnGetFrequency)
	ON_BN_CLICKED(IDC_BN_GET_F_SPEED, OnBnGetFSpeed)
	ON_BN_CLICKED(IDC_BN_CLEAR_METHOD_MSG, OnBnClearMethodMsg)
	ON_BN_CLICKED(IDC_BN_CLEAR_EVENT_MSG, OnBnClearEventMsg)
	ON_BN_CLICKED(IDC_CHECK_LOOP_RUN, OnCheckLoopRun)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BN_GET_MAX_FREQUENCY, OnBnGetMaxFrequency)
	ON_BN_CLICKED(IDC_BN_GET_SIGON_MAX_FREQUENCY, OnBnGetSigonMaxFrequency)
	ON_BN_CLICKED(IDC_BN_GET_RESISITIVITY_1, OnBnGetResisitivity1)
	ON_BN_CLICKED(IDC_BN_GET_RESISITIVITY_2, OnBnGetResisitivity2)
	ON_BN_CLICKED(IDC_BN_GET_INCH, OnBnGetInch)
	ON_BN_CLICKED(IDC_BN_GET_DIGIT, OnBnGetDigit)
	ON_BN_CLICKED(IDC_BN_GET_10989, On10989)
	ON_BN_CLICKED(IDC_BN_GET_COORD_ORG, OnBnGetCoordOrg)
	ON_BN_CLICKED(IDC_BN_GET_COORD_SYS, OnBnGetCoordSys)
	ON_BN_CLICKED(IDC_BN_GET_MACH_COORD, OnBnGetMachCoord)
	ON_BN_CLICKED(IDC_BN_GET_COORD, OnBnGetCoord)
	ON_BN_CLICKED(IDC_BN_POWER_ON, OnBnPowerOn)
	ON_BN_CLICKED(IDC_BUTTON_GetMachineKind, OnBUTTONGetMachineKind)
	ON_BN_CLICKED(IDC_BUTTON_GetCondition, OnBUTTONGetCondition)
	ON_BN_CLICKED(IDC_BTN_DoConditionSearch, OnBtnDoConditionSearch)
	ON_BN_CLICKED(IDC_BTN_GET_COND_TYPE, OnBtnGetCondType)
	ON_MESSAGE(WM_COND_SEARCH,OnConditionSearch)
	ON_BN_CLICKED(IDC_BTN_GET_MACHINELOCK, OnBtnGetMachinelock)
	ON_BN_CLICKED(IDC_BTN_GET_OFFSETVAR, OnBtnGetOffsetValue)
	ON_BN_CLICKED(IDC_BTN_SET_MACROVAR, OnBtnSetMacrovar)
	ON_BN_CLICKED(IDC_BTN_GET_MACROVAR, OnBtnGetMacrovar)
	ON_BN_CLICKED(IDC_BTN_GET_MACROVAR_RANGE, OnBtnGetMacrovarRange)
	ON_BN_CLICKED(IDC_BTN_GET_MACROVAR_SAFEARRAY, OnBtnGetMacrovarSafearray)
	ON_BN_CLICKED(IDC_BTN_SET_MACROVAR_RANGE, OnBtnSetMacrovarRange)
	ON_BN_CLICKED(IDC_GETRUNNINGFILENAME, OnGetRunningFileName)
	ON_BN_CLICKED(IDC_GETRUNNINGMAINNCFILEFIRSTLINE, OnGetRunningMainNcFileFirstLine)
	ON_BN_CLICKED(IDC_BTN_SET_MACROVAR_SAFEARRAY, OnBtnSetMacrovarSafearray)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMocxtestDlg メッセージ ハンドラ

BOOL CMocxtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	m_bRunCycle = FALSE;

	m_version = m_mk30.GetVersion();
	UpdateData(FALSE);

	//++@11168
	m_pWndSearchCond = new CSearchCondition;
	m_pWndSearchCond->Create(CSearchCondition::IDD,this);
	m_pWndSearchCond->ShowWindow(SW_HIDE);
	//--@11168

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CMocxtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CMocxtestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CMocxtestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMocxtestDlg::OnButton1() 
{
	UpdateData(TRUE);

	m_mk30.SetUserName(m_username);
	m_mk30.SetPassword(m_password);
	m_mk30.SetRasUserName(m_rasusername);
	m_mk30.SetRasPassword(m_raspassword);
}

void CMocxtestDlg::OnButton2() 
{
	
}

void CMocxtestDlg::OnButton3() 
{
	UpdateData(TRUE);

	if (m_mk30.Connect(m_machine) == -1)
	{
		m_bConnect = TRUE; // @Test
		m_commstatus = "connecting...";
		UpdateData(FALSE);
	}
}

void CMocxtestDlg::OnButton7() 
{
	UpdateData(TRUE);

	m_mk30.SendEmKey(m_emkey);	
}

void CMocxtestDlg::OnButton11() 
{
	short ret;
	if (m_mk30.GetMachineStatus() == STATUS_HALT)
		m_mk30.Execute("\0");
	else
	{
		UpdateData(TRUE);
		ret = m_mk30.Execute(m_runfilename);
	}
	CString strMsg;
	strMsg.Format("Execute:return = %d,Last error = %d.",ret,m_mk30.GetLastError());
	AddTextInMethodOutputView(strMsg);

}

void CMocxtestDlg::OnButton12() 
{
	m_mk30.Disconnect();
	m_commstatus = "Disconnect";
	UpdateData(FALSE);
	m_bConnect = FALSE; // @Test
}

void CMocxtestDlg::OnOK() 
{
	m_mk30.Disconnect();
	m_commstatus = "Disconnect";
	UpdateData(FALSE);
	CDialog::OnOK();
}

void CMocxtestDlg::OnButton5() 
{
	UpdateData(TRUE);
	short ret = m_mk30.SendFile(m_sendfile);
	CString strMsg;
	strMsg.Format("SendFile : return = %d,Last error = %d.",ret,m_mk30.GetLastError());
	AddTextInMethodOutputView(strMsg);
}

void CMocxtestDlg::OnButton6() 
{
	UpdateData(TRUE);
	int ret;
	ret = m_mk30.DeleteFile(m_delfile);
	CString strMsg;
	strMsg.Format("DeleteFile : return = %d,Last error = %d.",ret,m_mk30.GetLastError());
	AddTextInMethodOutputView(strMsg);
//	if (ret == FALSE)
//		AfxMessageBox("cannot find this file in ram");
}

void CMocxtestDlg::OnButton10() 
{
	UpdateData(TRUE);
	int ret = ((CButton *)GetDlgItem(IDC_PAUSE))->GetCheck();
	m_mk30.Pause(ret);
	if (ret)
		m_commstatus = "Disconnect(Pause)";
	else
		m_commstatus = "connect...";
	UpdateData(FALSE);
}

BEGIN_EVENTSINK_MAP(CMocxtestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMocxtestDlg)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 2 /* DenyRemoteAccess */, OnDenyRemoteAccessMk30commctrl1, VTS_NONE)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 4 /* NetworkError */, OnNetworkErrorMk30commctrl1, VTS_I2)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 5 /* NcError */, OnNcErrorMk30commctrl1, VTS_BSTR)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 6 /* SendFileComplete */, OnSendFileCompleteMk30commctrl1, VTS_I2 VTS_BSTR)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 1 /* DeleteFileComplete */, OnDeleteFileCompleteMk30commctrl1, VTS_I2 VTS_BSTR)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 3 /* ExecuteComplete */, OnExecuteCompleteMk30commctrl1, VTS_I2 VTS_BSTR)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 8 /* MachineStatusChanged */, OnMachineStatusChangedMk30commctrl1, VTS_I2 VTS_I2)
	ON_EVENT(CMocxtestDlg, IDC_MK30COMMCTRL1, 7 /* VersionError */, OnVersionErrorMk30commctrl1, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CMocxtestDlg::OnDenyRemoteAccessMk30commctrl1() 
{
	AddTextInEventOutputView("DenyRemoteAccessMk30commctrl1 : Deny remote access");	
	// start @11125B
	m_bRunCycle = FALSE;
	// end @11125B
}

void CMocxtestDlg::OnNetworkErrorMk30commctrl1(short intError) 
{
	AddTextInEventOutputView("NetworkErrorMk30commctrl1 : network error");
}

void CMocxtestDlg::OnNcErrorMk30commctrl1(LPCTSTR strError) 
{
	// start @10989B
	CString s;
	s.Format( "NcErrorMk30commctrl1: %s", strError);

	AddTextInEventOutputView(s); 
	// end @10989B
	//AfxMessageBox(strError);
}

void CMocxtestDlg::OnSendFileCompleteMk30commctrl1(short intError, LPCTSTR strError) 
{
	AddTextInEventOutputView(strError);	
		
	if (m_bRunCycle && intError==17)
		run(1);
	else
		m_bRunCycle = FALSE;
}

void CMocxtestDlg::OnDeleteFileCompleteMk30commctrl1(short intError, LPCTSTR strError) 
{
	if (m_bRunCycle && intError==19)
	{
		AddTextInEventOutputView(strError);
		run(0);
	}
	else
	{
		m_bRunCycle = FALSE;
		AddTextInEventOutputView(strError);
	}
}

void CMocxtestDlg::OnExecuteCompleteMk30commctrl1(short intError, LPCTSTR strError) 
{
	CString sMsg; // @11125
	sMsg.Format( "ExecuteComplete: m_bRunCycle = %d, intError = %d, strError=%s", m_bRunCycle, intError, strError);

	AddTextInEventOutputView(sMsg);
	//AfxMessageBox(strError);
	if (m_bRunCycle)
		run(2);
}

void CMocxtestDlg::OnButton8() 
{
	UpdateData(TRUE);
	if (m_offset.IsEmpty())
	{
		m_offset = "offset.dat";
		UpdateData(FALSE);
	}
	BSTR offset;
	if (m_mk30.GetOffset(&offset) == 1)
	{
		CStdioFile fp;
		CString file;
		char name[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD nSize = MAX_COMPUTERNAME_LENGTH + 1;

		::GetComputerName(LPTSTR(name), &nSize);
		file = "\\\\" + CString(name) + "\\PCShare\\" + m_offset;
		if (fp.Open( file, CFile::modeCreate | CFile::modeWrite))
		{
			fp.WriteString(CString(offset));
			fp.Close();
			AddTextInMethodOutputView("GetOffset : file write in PCShare " + m_offset);
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format("GetOffset : Get offset error, LastError = %d", m_mk30.GetLastError());

		AddTextInMethodOutputView(strTemp);
	}
}

void CMocxtestDlg::OnButton9() 
{
	UpdateData(TRUE);
	if (m_history.IsEmpty())
	{
		m_history = "history.dat";
		UpdateData(FALSE);
	}
	BSTR history;
	if (m_mk30.GetHistory(&history) == 1)
	{
		CStdioFile fp;
		CString file;
		char name[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD nSize = MAX_COMPUTERNAME_LENGTH + 1;

		::GetComputerName(LPTSTR(name), &nSize);
		file = "\\\\" + CString(name) + "\\PCShare\\" + m_history;
		if (fp.Open( file, CFile::modeCreate | CFile::modeWrite))
		{
			fp.WriteString(CString(history));
			fp.Close();
			AddTextInMethodOutputView("GetHistory : file write in PCShare " + m_history);
		}
	}
	else
		AddTextInMethodOutputView("GetHistory : Get history file error");
}

void CMocxtestDlg::OnButton4() 
{
	CString str;
	int ret = m_mk30.GetMachineStatus();	
	switch (ret)
	{
	case 0:
		str = "GetMachineStatus:ready";
		break;
	case 1:
		str = "GetMachineStatus:running";
		break;
	case 2:
		str = "GetMachineStatus:HALT";
		break;
	case 3:
		str = "GetMachineStatus:ACK";
		break;
	}
	AddTextInMethodOutputView(str);
}

void CMocxtestDlg::OnButton13() 
{
	// @11125B
	if( m_bRunCycle )
	{
		AddTextInMethodOutputView("The Machine is running loop.");
		return;
	}
	else
	AddTextInMethodOutputView("Click [RUN CYCLE!!!]");
	// @11125B

	run(0);
	m_bRunCycle = TRUE;
}
void CMocxtestDlg::OnButtonLogstart() 
{
	m_mk30.LogStart();
}
void CMocxtestDlg::OnButtonLogend() 
{
	m_mk30.LogEnd();
}
void CMocxtestDlg::run(int step)
{
	int ret = 0; // @11125
	CString strMsg; // @11125
	switch(step)
	{
	case 0:
		ret = m_mk30.SendFile("ENKAKU.NC"); // @11125
		strMsg.Format("run(SendFile) : return = %d,Last error = %d.",ret,m_mk30.GetLastError()); // @11125
		AddTextInMethodOutputView(strMsg); // @11125
		break;
	case 1:
		ret = m_mk30.Execute("ENKAKU");
		strMsg.Format("run(Execute) : return = %d,Last error = %d.",ret,m_mk30.GetLastError()); // @11125
		AddTextInMethodOutputView(strMsg); // @11125
		break;
	case 2:
		ret = m_mk30.DeleteFile("ENKAKU");
		strMsg.Format("run(DeleteFile) : return = %d,Last error = %d.",ret,m_mk30.GetLastError()); // @11125
		AddTextInMethodOutputView(strMsg); // @11125
		break;
	}
}

int CMocxtestDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください

	return 0;
}
void CMocxtestDlg::OnButton15()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
	GetDlgItem(IDC_EDIT7)->SetWindowText(dlg.GetFileName());

}


void CMocxtestDlg::OnMachineStatusChangedMk30commctrl1(short nOldStatus, short nNewStatus) 
{
	// TODO: Add your control notification handler code here
	//++@@@@@
	CString strTemp;
	strTemp.Format("Machine Status changed,old = %d,new status = %d!",nOldStatus,nNewStatus);
	AddTextInEventOutputView(strTemp);
//	// @Test
	if( m_bLoopRun )
	{
		if( nNewStatus != nOldStatus ) // status change
		{
			switch(nNewStatus)
			{
			default:
				break;
			case STATUS_READY: // ready
				{
					int ret = m_mk30.Execute(m_runfilename);
					CString strMsg;
					strMsg.Format("Execute:return = %d,Last error = %d.",ret,m_mk30.GetLastError());
					AddTextInMethodOutputView(strMsg);
					return ;
				}
			case STATUS_EXECUTE: // exe
				break;
			case STATUS_HALT:	// halt
				{
					int ret = m_mk30.SendEmKey("OFF");
					CString strMsg;
					strMsg.Format("SendEmKey(\"OFF\"):return = %d,Last error = %d.",ret,m_mk30.GetLastError());
					AddTextInMethodOutputView(strMsg);
					return ;
				}
			case STATUS_ACK:	// ack
				{
					int ret = m_mk30.SendEmKey("ACK");
					CString strMsg;
					strMsg.Format("SendEmKey(\"ACK\"):return = %d,Last error = %d.",ret,m_mk30.GetLastError());
					AddTextInMethodOutputView(strMsg);
					return ;
				}
				break;
			}
		}
	}
//	// end @Test

	//--@@@@@
	
}
// start @10989
void CMocxtestDlg::OnBnGetVoltage() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nVoltage = m_mk30.GetVoltage();
	CString s;
	s.Format( "%d", nVoltage );
	m_VoltageEdit.SetWindowText( s );
	
}

void CMocxtestDlg::OnBnGetElectricity() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nElectricity = m_mk30.GetElectricity();
	CString s;
	s.Format( "%d", nElectricity );
	m_ElectricityEdit.SetWindowText( s );
	
}

void CMocxtestDlg::OnBnGetFrequency() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nFrequency = m_mk30.GetFrequency();
	CString s;
	s.Format( "%d", nFrequency );
	m_FrequencyEdit.SetWindowText( s );
	
}

void CMocxtestDlg::OnBnGetFSpeed() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nFSpeed = m_mk30.GetFSpeed();
	CString s;
	s.Format( "%d", nFSpeed );
	m_FSpeedEdit.SetWindowText( s );
	
}
// end @10989

void CMocxtestDlg::OnBnClearMethodMsg() 
{
	// TODO: Add your control notification handler code here
	SetTextInMethodOutputView(_T(""));

}

void CMocxtestDlg::OnBnClearEventMsg() 
{
	// TODO: Add your control notification handler code here
	SetTextInEventOutputView(_T(""));
}

/*
Function : Add Text in Event output View
Parameter: lpText[in] : text
return :
*/
void CMocxtestDlg::AddTextInEventOutputView(LPCTSTR lpText)
{
	DWORD dwID = GetCurrentThreadId(); // @10989B
    CString &s = m_sEventResult;
	//s.Empty();
    int nLen = s.GetLength();
    if( nLen >= 1 && s.GetAt(nLen-1) != 0xd && s.GetAt(nLen-1) != 0x0a ) // not empty
    {
        s += _T("\r\n");
    }
    CString sStep;
    sStep.Format( _T("Step %d(Thread ID=%X): "), m_nEventStep++, dwID ); // @10989B
    m_sEventResult += sStep;

    m_sEventResult += lpText;
	TrimPreviousLine( m_sEventResult, MAX_LINES_FOR_MSG );
    m_EventResultEdit.SetWindowText(m_sEventResult);
    nLen = m_sEventResult.GetLength();
    m_EventResultEdit.SetSel(nLen, nLen);
	g_Log.Add( "%s%s", sStep, lpText ); // @11125
}

/*
Function : Set Text in Event output View
Parameter: lpText[in] : text
return :
*/
void CMocxtestDlg::SetTextInEventOutputView(LPCTSTR lpText)
{
    m_nEventStep = 0;

    m_sEventResult = lpText;
    m_EventResultEdit.SetWindowText(m_sEventResult);
    

}

/*
Function : Set Text in Method output View
Parameter: lpText[in] : text
return :
*/
void CMocxtestDlg::SetTextInMethodOutputView(LPCTSTR lpText)
{
    m_nMethodStep = 0;

    m_sMethodResult = lpText;
    m_MethodResultEdit.SetWindowText(m_sMethodResult);
    

}

/*
Function : Add Text in Method output View
Parameter: lpText[in] : text
return :
*/
void CMocxtestDlg::AddTextInMethodOutputView(LPCTSTR lpText)
{
	DWORD dwID = GetCurrentThreadId(); // @10989B
    CString &s = m_sMethodResult;
	// s.Empty();
    int nLen = s.GetLength();
    if( nLen >= 1 && s.GetAt(nLen-1) != 0xd && s.GetAt(nLen-1) != 0x0a ) // not empty
    {
        s += _T("\r\n");
    }
    CString sStep;
    sStep.Format( _T("Step %d(Thread ID=%X): "), m_nMethodStep++, dwID ); // @10989B
    m_sMethodResult += sStep;

    m_sMethodResult += lpText;
	TrimPreviousLine( m_sMethodResult, MAX_LINES_FOR_MSG );
    m_MethodResultEdit.SetWindowText(m_sMethodResult);
    nLen = m_sMethodResult.GetLength();
    m_MethodResultEdit.SetSel(nLen, nLen);
	g_Log.Add( "%s%s", sStep, lpText ); // @11125
}

/*
Function : Trim previous lines
Parameter: sString[in/out] : lines-string
		   nMaxLine[in] : max - line
return :
*/
void CMocxtestDlg::TrimPreviousLine( CString &sString, int nMaxLine )
{
	int n0Dcount = 0;
	int n0Acount = 0;
	LPCTSTR p = sString;
	int nLen = sString.GetLength();
	TCHAR c = 0;
	int nLastPos = nLen-1;

	for( int i = nLen - 1; i >= 0; i-- )
	{
		c = sString.GetAt(i);
		if( c == 0x0D ) // 0x0D
		{
			if( nMaxLine <= n0Dcount || nMaxLine <= n0Acount ) // reach  the maxline
			{
				sString = sString.Mid(nLastPos);
				return;
			}
			n0Dcount++;

		}
		else if( c == 0x0a ) // 0x0a
		{
			if( nMaxLine <= n0Dcount || nMaxLine <= n0Acount ) // reach  the maxline
			{
				sString = sString.Mid(nLastPos);
				return;
			}
			n0Acount++;
		}
		else
			nLastPos = i;
	}
	
}

void CMocxtestDlg::OnCheckLoopRun() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
}

void CMocxtestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if( m_bConnect == TRUE && m_bLoopRun ) // connect & loop run
	{
		int ret = m_mk30.GetMachineStatus();
		if( ret == 0 ) // ready
		{
			UpdateData(TRUE);
			ret = m_mk30.Execute(m_runfilename);
			
			CString strMsg;
			strMsg.Format("Execute:return = %d,Last error = %d.",ret,m_mk30.GetLastError());
			AddTextInMethodOutputView(strMsg);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

//2008-08-26 Modified by chen.x.c for request @10989.1 Begin
void CMocxtestDlg::OnBnGetMaxFrequency() 
{
	// TODO: Add your control notification handler code here
	int nVoltage = m_mk30.GetMaxFrequency();
	CString s;
	s.Format( "%d", nVoltage );
	m_MaxFrequencyEdit.SetWindowText( s );
}

void CMocxtestDlg::OnBnGetSigonMaxFrequency() 
{
	// TODO: Add your control notification handler code here
	int nVoltage = m_mk30.GetSigOnMaxFrequency();
	CString s;
	s.Format( "%d", nVoltage );
	m_SigOnMaxFreqEdit.SetWindowText( s );	
}

void CMocxtestDlg::OnBnGetResisitivity1() 
{
	// TODO: Add your control notification handler code here
	int nVoltage = m_mk30.GetResistivity1();
	CString s;
	s.Format( "%d", nVoltage );
	m_Resisitivity1Edit.SetWindowText( s );	
}

void CMocxtestDlg::OnBnGetResisitivity2() 
{
	// TODO: Add your control notification handler code here
	int nVoltage = m_mk30.GetResistivity2();
	CString s;
	s.Format( "%d", nVoltage );
	m_Resisitivity2Edit.SetWindowText( s );		
}

void CMocxtestDlg::OnBnGetInch() 
{
	// TODO: Add your control notification handler code here
	int nVoltage = m_mk30.GetInch();
	CString s;
	s.Format( "%d", nVoltage );
	m_InchEdit.SetWindowText( s );

}

void CMocxtestDlg::OnBnGetDigit() 
{
	// TODO: Add your control notification handler code here
	int nVoltage = m_mk30.GetDigit();
	CString s;
	s.Format( "%d", nVoltage );
	m_DigitEdit.SetWindowText( s );	
}

void CMocxtestDlg::On10989() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_VOLTAGE, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_ELECTRICITY, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_FREQUENCY, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_F_SPEED, BN_CLICKED),(LPARAM)0);

	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_MAX_FREQUENCY, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_SIGON_MAX_FREQUENCY, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_RESISITIVITY_1, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_RESISITIVITY_2, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_INCH, BN_CLICKED),(LPARAM)0);
	SendMessage(WM_COMMAND, (WPARAM)MAKEWPARAM(IDC_BN_GET_DIGIT, BN_CLICKED),(LPARAM)0);
}
//2008-08-26 Modified by chen.x.c for request @10989.1 End
// start @10989B
void CMocxtestDlg::OnBnGetCoordSys() 
{
	// TODO: Add your control notification handler code here
	DWORD dwTick = GetTickCount();
	long lCoordSys = m_mk30.GetCoordSys();
	CString strMsg;
	strMsg.Format("GetCoordSys : return = %d",lCoordSys );
	AddTextInMethodOutputView(strMsg);
	
}

void CMocxtestDlg::OnBnGetCoordOrg() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor WaitCursor;
	UpdateData(TRUE);
	double adCoord[8] = {0,0,0,0,0,0,0,0};
	DWORD dwTick = GetTickCount();
	long lRet = m_mk30.GetCoordOrg(m_lCoordSysForGetCoordOrg, adCoord );
	CString strMsg;
	if( lRet == E_FAILED ) // FAILED
	{
		strMsg.Format("GetCoordOrg : return = %d,Last error = %d.",lRet,m_mk30.GetLastError());
	}
	else
	{
		strMsg.Format("GetCoordOrg : return = %d\r\n"
			"X = %lf\r\n"
			"Y = %lf\r\n"
			"Z = %lf\r\n"
			"U = %lf\r\n"
			"V = %lf\r\n"
			"W = %lf\r\n"
			"UU = %lf\r\n"
			"VV = %lf\r\n"
			,lRet,
			adCoord[0],
			adCoord[1],
			adCoord[2],
			adCoord[3],
			adCoord[4],
			adCoord[5],
			adCoord[6],
			adCoord[7]
			);
	}
	AddTextInMethodOutputView(strMsg);
	
	
}


void CMocxtestDlg::OnBnGetMachCoord() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor WaitCursor;
	UpdateData(TRUE);
	double adCoord[8] = {0,0,0,0,0,0,0,0};
	DWORD dwTick = GetTickCount();
	long lRet = m_mk30.GetMachCoord( adCoord );
	CString strMsg;
	if( lRet == E_FAILED ) // FAILED
	{
		strMsg.Format("GetMachCoord : return = %d,Last error = %d.",lRet,m_mk30.GetLastError());
	}
	else
	{
		strMsg.Format("GetMachCoord : return = %d\r\n"
			"X = %lf\r\n"
			"Y = %lf\r\n"
			"Z = %lf\r\n"
			"U = %lf\r\n"
			"V = %lf\r\n"
			"W = %lf\r\n"
			"UU = %lf\r\n"
			"VV = %lf\r\n"
			,lRet,
			adCoord[0],
			adCoord[1],
			adCoord[2],
			adCoord[3],
			adCoord[4],
			adCoord[5],
			adCoord[6],
			adCoord[7]
			);
	}
	AddTextInMethodOutputView(strMsg);
	
	
}

void CMocxtestDlg::OnBnGetCoord() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor WaitCursor;
	UpdateData(TRUE);
	double adCoord[8] = {0,0,0,0,0,0,0,0};
	DWORD dwTick = GetTickCount();
	long lRet = m_mk30.GetCoord(m_lCoordSysForGetCoord, adCoord );
	CString strMsg;
	if( lRet == E_FAILED ) // FAILED
	{
		strMsg.Format("GetCoord : return = %d,Last error = %d.",lRet,m_mk30.GetLastError());
	}
	else
	{
		strMsg.Format("GetCoord : return = %d\r\n"
			"X = %lf\r\n"
			"Y = %lf\r\n"
			"Z = %lf\r\n"
			"U = %lf\r\n"
			"V = %lf\r\n"
			"W = %lf\r\n"
			"UU = %lf\r\n"
			"VV = %lf\r\n"
			,lRet,
			adCoord[0],
			adCoord[1],
			adCoord[2],
			adCoord[3],
			adCoord[4],
			adCoord[5],
			adCoord[6],
			adCoord[7]
			);
	}
	AddTextInMethodOutputView(strMsg);
}

void CMocxtestDlg::OnVersionErrorMk30commctrl1(short wServerVersionMajor, short wServerVersionMinor, short wClientVersionMajor, short wClientVersionMinor) 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	strTemp.Format("OnVersionErrorMk30commctrl1: MDComServer.exe version is not right: MDComServer.exe ver = %d.%d, OCX version = %d.%d",
		wServerVersionMajor, wServerVersionMinor, wClientVersionMajor, wClientVersionMinor);
	AddTextInEventOutputView(strTemp);
	
}
void CMocxtestDlg::OnBnPowerOn() 
{
	// TODO: Add your control notification handler code here
	BOOL ret = m_mk30.GetPowerOn();	
	CString str;
	str.Format( "GetPowerOn : PowerOn=%s", ret ? "ON" : "OFF" );
	AddTextInMethodOutputView(str);
	
}

// end @10989B



void CMocxtestDlg::OnBUTTONGetMachineKind() 
{
	// TODO: Add your control notification handler code here

	CString str;
	long x,y;
	if (m_mk30.GetMachineKind(&x,&y))
	{
		str.Format("mainKind = %d;subKind = %d",x,y);
	}
	else
	{
		str.Format("GetMachineKind Failed!LastError = %d",m_mk30.GetLastError());
	}
	AfxMessageBox(str);
	
}

void CMocxtestDlg::OnBUTTONGetCondition() 
{
	// TODO: Add your control notification handler code here
	BSTR bstrTemp;
	CString str;

	if (m_mk30.GetCondition(&bstrTemp))
	{
		str = CString(bstrTemp);
	}
	else
	{
		str.Format("GetMachineKind Failed!LastError = %d",m_mk30.GetLastError());
	}

	AfxMessageBox(str);
	
}

//++@11168
void CMocxtestDlg::OnBtnDoConditionSearch() 
{  
	m_pWndSearchCond->ShowWindow(SW_SHOW); 
	
	m_nInch = m_mk30.GetInch();
	m_nDigit = m_mk30.GetDigit();
}
//--@11168

//++@11168
void CMocxtestDlg::OnBtnGetCondType() 
{
	// TODO: Add your control notification handler code here
	int nCondType = m_mk30.GetConditionType();
	CString s;
	s.Format( "%d", nCondType );
	GetDlgItem(IDC_EDIT_COND_TYPE)->SetWindowText( s ); 
}
//--@11168

//++@11168	
void CMocxtestDlg::CreateTestNcFileData(CArray<CString, CString> &arrString, int nCutNum, SWF_MchCon_SU *mchcon, SWF_MCB_SU *mcb, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, long *nMTRL)
{ 
	CString strFormat("");	
	CString strTemp(""); 
	CString strText(""); 
	int nIndex = 0;

 	strTemp = "(          ";
	for(int i=0; i<15; i++ )
	{
		strText.LoadString( IDS_ITEMNAMENEW0 + i );
		strTemp += strText;
		if( i != 14 )
			strTemp += " ";
	}
	strTemp += ");\n"; 
	arrString.Add(strTemp); 

	for (nIndex = 0; nIndex< nCutNum+1; nIndex++)
	{
		if( mcb[nIndex].MCB_PIK_FLAG == TRUE )
			strTemp.Format( "C%03lu",900+mcb[nIndex].MCB_Code);
		else
		{
			if (m_bC555Sign && (1 == nIndex))
				strTemp = "C555";
			else
				strTemp.Format( "C%03lu",mcb[nIndex].MCB_Code);
		}
		strTemp += "   =  ";
			
		for(int j=0; j<15; j ++ )
		{
			int CForm[] = { 3,3,4,3,3,3,1,4,1,3,4,3,3,3,3 };
			switch( j )
			{
			case 0:
				strText.Format("%lu", mcb[nIndex].MCB_ON );
				break;
			case 1:
				strText.Format("%lu", mcb[nIndex].MCB_OFF );
				break;
			case 2:
				strText.Format("%lu", mcb[nIndex].MCB_IP );
				break;
			case 3:
				strText.Format("%lu", mcb[nIndex].MCB_HRP );
				break;
			case 4:
				strText.Format("%lu", mcb[nIndex].MCB_MAO );
				break;
			case 5:
				strText.Format("%lu", mcb[nIndex].MCB_SV );
				break;
			case 6:
				strText.Format("%lu", mcb[nIndex].MCB_V );
				break;
			case 7:
				{	int MCB_SF = mcb[nIndex].MCB_SF;
					if( m_nInch )
					{
						int MCB_SF_MAX = MCB_SF/1000*1000;
						int MCB_SF_MIN = MCB_SF%1000;
						if( MCB_SF_MIN < 4 )
							MCB_SF_MIN = 1;
						else
							MCB_SF_MIN = (double(MCB_SF_MIN)/2.54-int(double(MCB_SF_MIN)/2.54) >= 0.5 )
							? int(double(MCB_SF_MIN)/2.54) +1 : int(double(MCB_SF_MIN)/2.54);
						MCB_SF = MCB_SF_MAX + MCB_SF_MIN;
					}
					strText.Format("%lu",  MCB_SF );
				} 
				break;
			case 8:
				strText.Format("%lu", mcb[nIndex].MCB_C );
				break;
			case 9:
				strText.Format("%lu",mcb[nIndex].MCB_PIK );
				break;
			case 10:
				strText.Format("%lu",mcb[nIndex].MCB_CTRL );
				break;
			case 11:
				strText.Format("%lu", mcb[nIndex].MCB_WK );
				break;
			case 12:
				strText.Format("%lu", mcb[nIndex].MCB_WT );
				break;
			case 13:
				strText.Format("%lu", mcb[nIndex].MCB_WS );
				break;
			case 14:
				strText.Format("%lu", mcb[nIndex].MCB_WP );
				break;
			}
			
			while( strText.GetLength() < CForm[j] )
				strText = "0" + strText;
 
			strTemp += " ";
			if( j == 4 && strText.GetLength() == 4 )
				strTemp += ( strText.Right(3) );
			else
				strTemp += strText;
		} 
		strTemp += ";\n";  
		arrString.Add(strTemp);
	}

	for( nIndex=0; nIndex<nCutNum+1; nIndex++)
	{ 
		strTemp.Format("H%03lu   = ",mchcon[nIndex].MC_Offset ); 

		if( mchcon[nIndex].MC_Offset_V >= 0 )
			strTemp += "+";
		else
			strTemp += "-";

		if( m_nInch )
			strTemp += " ";
		
		if( m_nDigit == 0 )
		{
			if( m_nInch )
				strText.Format("%010.4f  ", fabs(mchcon[nIndex].MC_Offset_V/25.40005083) );	//(@51586/60937)
			else
				strText.Format("%010.3f   ", fabs(mchcon[nIndex].MC_Offset_V) );
		}
		else if( m_nDigit == 1 )
		{
			if( m_nInch )
				strText.Format("%011.5f ", fabs(mchcon[nIndex].MC_Offset_V/25.40005083) );	//(@51586/60937)
			else
				strText.Format("%011.4f  ", fabs(mchcon[nIndex].MC_Offset_V) );
		}
		else
		{
			if( m_nInch )
				strText.Format("%012.6f", fabs(mchcon[nIndex].MC_Offset_V/25.40005083) );	//(@51586/60937)
			else
				strText.Format("%012.5f ", fabs(mchcon[nIndex].MC_Offset_V) );
		}
		strTemp += strText; 

		CString sttemp("                                                                       ;"); 
		strTemp += sttemp.Right(sttemp.GetLength() - strTemp.GetLength());
		
		strTemp += "\n";
		arrString.Add(strTemp);
	}
			
	strFormat = "%s  \n"; 
	strTemp.Format("%s", nc_proc[0].NC_code);
	strTemp = strTemp.Left(strTemp.Find('|'));
	strTemp += ";\n";
	arrString.Add(strTemp);

	if (*plnNcProcNum > 2)
	{
		strTemp.Format("%s", nc_proc[2].NC_code);
		strTemp = strTemp.Left(strTemp.Find('|'));
		strTemp += ";\n";
		arrString.Add(strTemp);
	}
 
	if( fin->FN_Ad_Tp >= 0 )
		strTemp = "BSA+";
	else
		strTemp = "BSA-";	
	
	if( m_nDigit == 0 )
	{
		if( m_nInch )
			strText.Format("%010.4f  ;\n", fabs(fin->FN_Ad_Tp) );
		else
			strText.Format("%010.3f   ;\n", fabs(fin->FN_Ad_Tp) );
	}
	else if( m_nDigit == 1 )
	{
		if( m_nInch )
			strText.Format("%011.5f ;\n", fabs(fin->FN_Ad_Tp) );
		else
			strText.Format("%011.4f  ;\n", fabs(fin->FN_Ad_Tp) );
	}
	else
	{
		if( m_nInch )
			strText.Format("%012.6f;\n", fabs(fin->FN_Ad_Tp) );
		else
			strText.Format("%012.5f ;\n", fabs(fin->FN_Ad_Tp) );
	}
	strTemp += strText;
	arrString.Add(strTemp);

	strTemp.Format("MTRL%02ld;\n", *nMTRL);
	arrString.Add(strTemp); 
}

void CMocxtestDlg::CreateTestNcFileData(CArray<CString, CString> &arrString, int nCutNum, SWF_MchCon_SU *mchcon, SWF_MCB_SU_WS *mcb, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, long *nMTRL)
{ 
	CString strFormat("");	
	CString strTemp(""); 
	CString strText(""); 
	int nIndex = 0;
 	strTemp = "(          ";
	for(int i=0; i<17; i++ )		//@LQ33WS
	{
		if (i == 15)		
			strText.LoadString(IDS_ITEMNAMENEW15);			//@LQ33WS
		else if (i == 16)		
			strText.LoadString(IDS_ITEMNAMENEW16);			//@LQ33WS
		else
			strText.LoadString( IDS_ITEMNAMENEW0 + i );

		if (i == 5)				
			strText = "   "+strText;
		if (i == 6)				
			strText = "  "+strText;

		strTemp += strText;

		if( i != 16 )			strTemp += " ";
	}
	strTemp += ");\n"; 
	arrString.Add(strTemp);
	
	for (nIndex = 0; nIndex< nCutNum+1; nIndex++)
	{
		if( mcb[nIndex].MCB_PIK_FLAG == TRUE )
			strTemp.Format( "C%03lu",900+mcb[nIndex].MCB_Code);
		else
		{
			if (m_bC555Sign && (1 == nIndex))
				strTemp = "C555";
			else
				strTemp.Format( "C%03lu",mcb[nIndex].MCB_Code);
		}
		strTemp += "   =  ";

		for(int j=0; j<17; j ++ )
		{
			int CForm[] = { 3/*ON*/,3/*OFF*/,4/*IP*/,3/*HRP*/,3/*MAO*/,6/*SV*/,3/*V*/,
					4/*SF*/,1/*C*/,3/*PIK*/,4/*CTRL*/,3/*WK*/,3/*WT*/,3/*WS*/,3/*WP*/,
					4/*PC*/,2/*SK*/};	//@LQ33WS
			switch( j )
			{
			case 0:
				strText.Format("%lu", mcb[nIndex].MCB_ON );
				break;
			case 1:
				strText.Format("%lu", mcb[nIndex].MCB_OFF );
				break;
			case 2:
				strText.Format("%lu", mcb[nIndex].MCB_IP );
				break;
			case 3:
				strText.Format("%lu", mcb[nIndex].MCB_HRP );
				break;
			case 4:
				strText.Format("%lu", mcb[nIndex].MCB_MAO );
				break;
			case 5:
				strText.Format("%+06.1f", mcb[nIndex].MCB_SV );
				break;
			case 6:
				strText.Format("%3.1f", mcb[nIndex].MCB_V );
				break;
			case 7:
				{	int MCB_SF = mcb[nIndex].MCB_SF;
					if( m_nInch )
					{
						int MCB_SF_MAX = MCB_SF/1000*1000;
						int MCB_SF_MIN = MCB_SF%1000;
						if( MCB_SF_MIN < 4 )
							MCB_SF_MIN = 1;
						else
							MCB_SF_MIN = (double(MCB_SF_MIN)/2.54-int(double(MCB_SF_MIN)/2.54) >= 0.5 )
							? int(double(MCB_SF_MIN)/2.54) +1 : int(double(MCB_SF_MIN)/2.54);
						MCB_SF = MCB_SF_MAX + MCB_SF_MIN;
					}
					strText.Format("%lu",  MCB_SF );
				} 
				break;
			case 8:
				strText.Format("%lu", mcb[nIndex].MCB_C );
				break;
			case 9:
				strText.Format("%lu",mcb[nIndex].MCB_PIK );
				break;
			case 10:
				strText.Format("%lu",mcb[nIndex].MCB_CTRL );
				break;
			case 11:
				strText.Format("%lu", mcb[nIndex].MCB_WK );
				break;
			case 12:
				strText.Format("%lu", mcb[nIndex].MCB_WT );
				break;
			case 13:
				strText.Format("%lu", mcb[nIndex].MCB_WS );
				break;
			case 14:
				strText.Format("%lu", mcb[nIndex].MCB_WP );
				break;
			case 15:
					strText.Format("%lu", mcb[nIndex].MCB_PC );
					break;
				case 16:
					strText.Format("%lu", mcb[nIndex].MCB_SK );
					break;		
			}
			
			while( strText.GetLength() < CForm[j] )
				strText = "0" + strText;
 
			strTemp += " ";
			if( j == 4 && strText.GetLength() == 4 )
				strTemp += ( strText.Right(3) );
			else
				strTemp += strText;

		} 
		strTemp += ";\n";  
		arrString.Add(strTemp);
	}

	for( nIndex=0; nIndex<nCutNum+1; nIndex++)
	{ 
		strTemp.Format("H%03lu   = ",mchcon[nIndex].MC_Offset ); 

		if( mchcon[nIndex].MC_Offset_V >= 0 )
			strTemp += "+";
		else
			strTemp += "-";

		if( m_nInch )
			strTemp += " ";
		
		if( m_nDigit == 0 )
		{
			if( m_nInch )
				strText.Format("%010.4f  ", fabs(mchcon[nIndex].MC_Offset_V/25.40005083) );	//(@51586/60937)
			else
				strText.Format("%010.3f   ", fabs(mchcon[nIndex].MC_Offset_V) );
		}
		else if( m_nDigit == 1 )
		{
			if( m_nInch )
				strText.Format("%011.5f ", fabs(mchcon[nIndex].MC_Offset_V/25.40005083) );	//(@51586/60937)
			else
				strText.Format("%011.4f  ", fabs(mchcon[nIndex].MC_Offset_V) );
		}
		else
		{
			if( m_nInch )
				strText.Format("%012.6f", fabs(mchcon[nIndex].MC_Offset_V/25.40005083) );	//(@51586/60937)
			else
				strText.Format("%012.5f ", fabs(mchcon[nIndex].MC_Offset_V) );
		}
		strTemp += strText; 

		CString sttemp("                                                                       ;"); 
		strTemp += sttemp.Right(sttemp.GetLength() - strTemp.GetLength());
		
		strTemp += "\n";
		arrString.Add(strTemp);
	}
			
	strFormat = "%s  \n"; 
	strTemp.Format("%s", nc_proc[0].NC_code);
	strTemp = strTemp.Left(strTemp.Find('|'));
	strTemp += ";\n";
	arrString.Add(strTemp);

	if (*plnNcProcNum > 2)
	{
		strTemp.Format("%s", nc_proc[2].NC_code);
		strTemp = strTemp.Left(strTemp.Find('|'));
		strTemp += ";\n";
		arrString.Add(strTemp);
	}
 
	if( fin->FN_Ad_Tp >= 0 )
		strTemp = "BSA+";
	else
		strTemp = "BSA-";	
	
	if( m_nDigit == 0 )
	{
		if( m_nInch )
			strText.Format("%010.4f  ;\n", fabs(fin->FN_Ad_Tp) );
		else
			strText.Format("%010.3f   ;\n", fabs(fin->FN_Ad_Tp) );
	}
	else if( m_nDigit == 1 )
	{
		if( m_nInch )
			strText.Format("%011.5f ;\n", fabs(fin->FN_Ad_Tp) );
		else
			strText.Format("%011.4f  ;\n", fabs(fin->FN_Ad_Tp) );
	}
	else
	{
		if( m_nInch )
			strText.Format("%012.6f;\n", fabs(fin->FN_Ad_Tp) );
		else
			strText.Format("%012.5f ;\n", fabs(fin->FN_Ad_Tp) );
	}
	strTemp += strText;
	arrString.Add(strTemp);

	strTemp.Format("MTRL%02ld;\n", *nMTRL);
	arrString.Add(strTemp); 
}
//--@11168
 	 
// create @11168 
void CMocxtestDlg::OnConditionSearch(WPARAM wParam,LPARAM lParam)
{
	SWF_NC_PROC		*nc_proc = new SWF_NC_PROC[6]; 
	SWF_MchCon_SU	*pstMchcon; 
	S_FINISH		fin;
	int		nDataBaseType;
	long	plnNcProcNum;
	long	plnMTRL;
	int nRet = 0;

	memset(&fin, 0, sizeof(S_FINISH));
	nDataBaseType = -1;
	plnNcProcNum = NULL;  

	int nParamType  = 0;
	int nResearchNumber = 1;
	int nIndex = 0;
	BOOL bCreateFile = FALSE;

	int nCondType = m_mk30.GetConditionType();
	BOOL bPresion = FALSE; 
 
	CFileFind fileFind;
	CString str;
	str = CString(NCFILE_TEST_DATA_PATH);
	BOOL bFind = fileFind.FindFile(str);
	if (!bFind)
		CreateDirectory(NCFILE_TEST_DATA_PATH, NULL);

	m_pWndSearchCond->GetPresion(bPresion);

	CArray<CString, CString> arrTemp;
	arrTemp.RemoveAll();
 
	if (nCondType == 1)
	{	
		SWF_MCB_SU_WS	*pstMcb;

		if (bPresion)
		{
			SWF_CONDITION_GE	cnd;	 
			memset(&cnd, 0, sizeof(SWF_CONDITION_GE));
			m_pWndSearchCond->GetConditionSearchData(cnd, nDataBaseType,nResearchNumber); 

			pstMchcon = new SWF_MchCon_SU[cnd.cutn+1]; 
			pstMcb = new SWF_MCB_SU_WS[cnd.cutn+1];   
			nParamType = 1;
	
			for (nIndex=0; nIndex<nResearchNumber; nIndex++)
			{

				nRet = m_mk30.CreateNcCond( nParamType,			nDataBaseType, 			(double *) &cnd,	  
									(double *) pstMchcon,	(double *) pstMcb,		(double *) nc_proc,
									&plnNcProcNum, 			(long *) &fin,			&plnMTRL);  
 
				GetC555Sign(cnd.lqknd);

				if (nRet == 1)
				{
					bCreateFile = TRUE;
					CreateCondSchInputInfo(arrTemp, nDataBaseType, cnd);
					CreateTestNcFileData(arrTemp, cnd.cutn, pstMchcon, pstMcb, nc_proc, &plnNcProcNum, &fin, &plnMTRL);
				}
				else if (nRet == 0) 
					AfxMessageBox("data synchro timeoutd");	
				else if (nRet == -1) 
					AfxMessageBox("condition failed");
				else if (nRet == CONDSCH_ERR_OTHER_CONDSCHING) 
					AfxMessageBox("other condition searching");
				else if (nRet == CONDSCH_ERR_FILENOTFIND) 
					AfxMessageBox("condition file not find");
				else if (nRet == CONDSCH_ERR_FILEOPENERROR) 
					AfxMessageBox("condition file open error");
				else if (nRet == CONDSCH_ERR_COND_ERROR) 
					AfxMessageBox("COND_COND Database error");
				else if (nRet == CONDSCH_ERR_FORMATERROR) 
					AfxMessageBox("Can't write error input data in database.");
				else if (nRet == CONDSCH_ERR_MSGNOTFOUND) 
					AfxMessageBox("MSG_COND.DAT not found.");
			}
			
			delete	pstMcb; 
		}
		else
		{
			SWF_CONDITION	cnd;	
			memset(&cnd, 0, sizeof(SWF_CONDITION));
			m_pWndSearchCond->GetConditionSearchData(cnd, nDataBaseType,nResearchNumber); 
			
			pstMchcon = new SWF_MchCon_SU[cnd.cutn+1];  
			pstMcb = new SWF_MCB_SU_WS[cnd.cutn+1];   
			nParamType = 3;	

			for (nIndex=0; nIndex<nResearchNumber; nIndex++)
			{
				nRet = m_mk30.CreateNcCond( nParamType,		nDataBaseType, 			(double *) &cnd,	  
									(double *) pstMchcon,	(double *) pstMcb,		(double *) nc_proc,
 									&plnNcProcNum, 			(long *) &fin,			&plnMTRL);    
				
				GetC555Sign(cnd.lqknd);
				
				if (nRet == 1)
				{
					bCreateFile = TRUE;		
					CreateCondSchInputInfo(arrTemp, nDataBaseType, cnd);	
					CreateTestNcFileData(arrTemp, cnd.cutn, pstMchcon, pstMcb, nc_proc, &plnNcProcNum, &fin, &plnMTRL);
				}
				else if (nRet == 0) 
					AfxMessageBox("data synchro timeoutd");	
				else if (nRet == -1) 
					AfxMessageBox("condition failed");
				else if (nRet == CONDSCH_ERR_OTHER_CONDSCHING) 
					AfxMessageBox("other condition searching");
				else if (nRet == CONDSCH_ERR_FILENOTFIND) 
					AfxMessageBox("condition file not find");
				else if (nRet == CONDSCH_ERR_FILEOPENERROR) 
					AfxMessageBox("condition file open error");
				else if (nRet == CONDSCH_ERR_COND_ERROR) 
					AfxMessageBox("COND_COND Database error");
				else if (nRet == CONDSCH_ERR_FORMATERROR) 
					AfxMessageBox("Can't write error input data in database.");
				else if (nRet == CONDSCH_ERR_MSGNOTFOUND) 
					AfxMessageBox("MSG_COND.DAT not found.");
			}
		 
			delete	pstMcb; 
		}
	}
	else
	{
		SWF_MCB_SU *pstMcb;
		
		if (bPresion)
		{ 
			SWF_CONDITION_GE	cnd;	
			memset(&cnd, 0, sizeof(SWF_CONDITION_GE));
			m_pWndSearchCond->GetConditionSearchData(cnd, nDataBaseType,nResearchNumber); 

			pstMcb = new SWF_MCB_SU[cnd.cutn+1];   
			pstMchcon = new SWF_MchCon_SU[cnd.cutn+1];  
			nParamType = 2;

			for (nIndex=0; nIndex<nResearchNumber; nIndex++)
			{
				nRet = m_mk30.CreateNcCond( nParamType,			nDataBaseType, 			(double *) &cnd,	  
										(double *) pstMchcon,	(double *) pstMcb,		(double *) nc_proc,
										&plnNcProcNum, 			(long *) &fin,			&plnMTRL);        
				
				GetC555Sign(cnd.lqknd);
				
				if (nRet == 1)
				{
					bCreateFile = TRUE;
					CreateCondSchInputInfo(arrTemp, nDataBaseType, cnd);
					CreateTestNcFileData(arrTemp, cnd.cutn, pstMchcon, pstMcb, nc_proc, &plnNcProcNum, &fin, &plnMTRL);
				}
				else if (nRet == 0) 
					AfxMessageBox("data synchro timeoutd");	
				else if (nRet == -1) 
					AfxMessageBox("condition failed");
				else if (nRet == CONDSCH_ERR_OTHER_CONDSCHING) 
					AfxMessageBox("other condition searching");
				else if (nRet == CONDSCH_ERR_FILENOTFIND) 
					AfxMessageBox("condition file not find");
				else if (nRet == CONDSCH_ERR_FILEOPENERROR) 
					AfxMessageBox("condition file open error");
				else if (nRet == CONDSCH_ERR_COND_ERROR) 
					AfxMessageBox("COND_COND Database error");
				else if (nRet == CONDSCH_ERR_FORMATERROR) 
					AfxMessageBox("Can't write error input data in database.");
				else if (nRet == CONDSCH_ERR_MSGNOTFOUND) 
					AfxMessageBox("MSG_COND.DAT not found.");
			}
	
			delete	pstMcb; 
		}
		else
		{	
			SWF_CONDITION	cnd;	
			memset(&cnd, 0, sizeof(SWF_CONDITION));
			m_pWndSearchCond->GetConditionSearchData(cnd, nDataBaseType,nResearchNumber);    
				
			GetC555Sign(cnd.lqknd);
				
			pstMcb = new SWF_MCB_SU[cnd.cutn+1];    
			pstMchcon = new SWF_MchCon_SU[cnd.cutn+1];  
			nParamType = 4;

			for (nIndex=0; nIndex<nResearchNumber; nIndex++)
			{
				nRet = m_mk30.CreateNcCond( nParamType,			nDataBaseType, 			(double *) &cnd,	  
										(double *) pstMchcon,	(double *) pstMcb,		(double *) nc_proc,
										&plnNcProcNum, 			(long *) &fin,			&plnMTRL);    
		
				if (nRet == 1)
				{
					bCreateFile = TRUE;
					CreateCondSchInputInfo(arrTemp, nDataBaseType, cnd);
					CreateTestNcFileData(arrTemp, cnd.cutn, pstMchcon, pstMcb, nc_proc, &plnNcProcNum, &fin, &plnMTRL);
				}
				else if (nRet == 0) 
					AfxMessageBox("data synchro timeoutd");	
				else if (nRet == -1) 
					AfxMessageBox("condition failed");
				else if (nRet == CONDSCH_ERR_OTHER_CONDSCHING) 
					AfxMessageBox("other condition searching");
				else if (nRet == CONDSCH_ERR_FILENOTFIND) 
					AfxMessageBox("condition file not find");
				else if (nRet == CONDSCH_ERR_FILEOPENERROR) 
					AfxMessageBox("condition file open error");
				else if (nRet == CONDSCH_ERR_COND_ERROR) 
					AfxMessageBox("COND_COND Database error");
				else if (nRet == CONDSCH_ERR_FORMATERROR) 
					AfxMessageBox("Can't write error input data in database.");
				else if (nRet == CONDSCH_ERR_MSGNOTFOUND) 
					AfxMessageBox("MSG_COND.DAT not found.");
			}

			delete	pstMcb; 
		}
	}  
		
	if (bCreateFile)
	{
		CStdioFile file;	
		if (file.Open(NCFILE_TEST_DATA_NAME, CFile::modeWrite|CFile::modeCreate))
		{
			for (nIndex = 0; nIndex < arrTemp.GetSize(); nIndex++)
			{
				file.WriteString(arrTemp[nIndex]);
			}
			file.Close();
		}
	}

	arrTemp.RemoveAll();
	delete  nc_proc; 
	delete  pstMchcon;
}

// create @11168
void CMocxtestDlg::GetC555Sign(CString strLqknd)
{
	if  (NULL != strstr(strLqknd, "TC"))
		m_bC555Sign = TRUE;
	else
		m_bC555Sign = FALSE;
}

// create @11168
void CMocxtestDlg::CreateCondSchInputInfo(CArray<CString, CString> &arrString, int nDatabaseType, SWF_CONDITION &swf)
{
	CString strTemp("");
	
	strTemp = GetDatabaseName(nDatabaseType);
	arrString.Add(strTemp);

	strTemp.Format("( Search Data : %s, %f, %s, %s, %f, %s, %s, %dtimes,  %f  );\n", 
					swf.lquid,		swf.wrdiam,		swf.wirem,		swf.mater,		swf.thick,		swf.kind,
					swf.lqknd,		swf.cutn,		swf.rough);
	arrString.Add(strTemp);

	strTemp.Format("( Change Offset: %f, AIC: %d, Comment: %s, ConditionFlag: %d, SFCC: %d );\n", 
					swf.ofstajst,	swf.aicon,		swf.comment,	swf.cndflg,		swf.SFCCFlag);
	arrString.Add(strTemp);
}

// create @11168
void CMocxtestDlg::CreateCondSchInputInfo(CArray<CString, CString> &arrString, int nDatabaseType, SWF_CONDITION_GE &swf)
{
	CString strTemp("");
	
	strTemp = GetDatabaseName(nDatabaseType);
	arrString.Add(strTemp);

	strTemp.Format("( Search Data : %s, %f, %s, %s, %f, %s, %s, %dtimes,  %f  );\n", 
					swf.lquid,		swf.wrdiam,		swf.wirem,		swf.mater,		swf.thick,		swf.kind,
					swf.lqknd,		swf.cutn,		swf.rough);
	arrString.Add(strTemp);

	strTemp.Format("( Change Offset: %f, AIC: %d, Comment: %s, ConditionFlag: %d, SFCC: %d );\n", 
					swf.ofstajst,	swf.aicon,		swf.comment,	swf.cndflg,		swf.SFCCFlag);
	arrString.Add(strTemp);

	strTemp.Format("( Precision: %ld );\n" , swf.precision );
	arrString.Add(strTemp);

}

CString CMocxtestDlg::GetDatabaseName(int nDatabaseType)
{
	CString stDatabaseName("");
	stDatabaseName.Format("( DataBase Type : %d	", nDatabaseType);

	switch(nDatabaseType) {
	case 0:		
		stDatabaseName += "Sodick DataBase";
		break;
	case 1:
		stDatabaseName += "Option DataBase";
		break;
	case 2:
		stDatabaseName += "User DataBase";
		break;
	case 3:
		stDatabaseName += "The Kantan DataBase";
		break;
	case 4:
		stDatabaseName += "ECO DataBase";
		break;
	case 5:
		stDatabaseName += "HECW DataBase";
		break;
	case 6:
		stDatabaseName += "Reference Database";
		break;  
	}

	stDatabaseName +=  " );\n";
	return stDatabaseName;
}


void CMocxtestDlg::OnBtnGetMachinelock() 
{
	// TODO: Add your control notification handler code here
	DWORD dwData = m_mk30.GetMachineLock();
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_GET_MACHINELOCK);
	if (pEdit != NULL)
	{
		CString str;
		str.Format("%d",dwData);
		pEdit->SetWindowText(str);
	}
}

void CMocxtestDlg::OnBtnGetOffsetValue() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor WaitCursor;
	UpdateData(TRUE);
	int ret = 0;
	CString strOffsetNumber;	
	GetDlgItemText(IDC_EDIT_OFFSET_NUMBER, strOffsetNumber);

	if (strOffsetNumber == "")
	{
		MessageBox(_T("Please input data!"));
		return ;
	} 
	else
	{
		long nOffsetNumber = atol(strOffsetNumber);
		double dblOffsetValue = 0;
		ret = m_mk30.GetOffsetVar(nOffsetNumber, &dblOffsetValue);
		
		CString str;
		str.Format("%f", dblOffsetValue);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_OFFSET_VALUE);
		pEdit->SetWindowText(str);
	}

	CString strMsg;
	strMsg.Format("GetOffsetVar : return = %d,Last error = %d.", ret, m_mk30.GetLastError());
	AddTextInMethodOutputView(strMsg);
}

void CMocxtestDlg::OnBtnSetMacrovar() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor WaitCursor;
	UpdateData(TRUE);
	int ret = 0;
	CString strMacroNumber;
	CString strMacroValue;

	GetDlgItemText(IDC_EDIT_MACRO_NUMBER, strMacroNumber);
	GetDlgItemText(IDC_EDIT_MACRO_VALUE, strMacroValue);
	if (strMacroNumber == "" || strMacroValue == "")
	{
		MessageBox(_T("Please input data!"));
		return ;
	} 
	else
	{
		long nMacroNumber = atol(strMacroNumber);
		double dblMacroValue = atof(strMacroValue);
		ret = m_mk30.SetMacroVar(nMacroNumber, dblMacroValue);
	}

	CString strMsg;
	strMsg.Format("SetMacroVar : return = %d,Last error = %d.", ret, m_mk30.GetLastError());
	AddTextInMethodOutputView(strMsg);
}

void CMocxtestDlg::OnBtnGetMacrovar() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor WaitCursor;
	UpdateData(TRUE);
	int ret = 0;
	CString strMacroNumber;	
	GetDlgItemText(IDC_EDIT_GET_MACRO_NUMBER, strMacroNumber);
	
	if (strMacroNumber == "")
	{
		MessageBox(_T("Please input data!"));
		return ;
	} 
	else
	{
		long nMacroNumber = atol(strMacroNumber);
		double dblMacroValue = 0;
		ret = m_mk30.GetMacroVar(nMacroNumber, &dblMacroValue);
		
		CString str;
		str.Format("%f", dblMacroValue);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_GET_MACRO_VALUE);
		pEdit->SetWindowText(str);
	}

	CString strMsg;
	strMsg.Format("GetMacroVar : return = %d,Last error = %d.", ret, m_mk30.GetLastError());
	AddTextInMethodOutputView(strMsg);

}

void CMocxtestDlg::OnBtnGetMacrovarRange() 
{
	// TODO: Add your control notification handler code here
	CString strStartNo;
	CString strEndNo;

	GetDlgItemText(IDC_EDIT_GET_MACROVAR_STARTNO, strStartNo);
	GetDlgItemText(IDC_EDIT_GET_MACROVAR_ENDNO, strEndNo);
	if (strStartNo == "" || strEndNo == "")
	{
		MessageBox(_T("Please input data!"));
		return;
	}

	long nStartNo = atol(strStartNo);
	long nEndNo = atol(strEndNo);
// 	int num = nEndNo - nStartNo + 1;

	double dblMacroVar[100] = {0};
	long nRet = m_mk30.GetMacroVarRange(nStartNo, nEndNo, dblMacroVar);

	long nMacroNum = nStartNo;
	CString strTemp = "";	
	if (nRet <= 0)
	{
		strTemp.Format("GetMacroVarRange : return = %d, Last error = %d.", nRet, m_mk30.GetLastError());
	}
	else
	{
		for (int i = 0; i < nRet; i++)
		{
			CString str;
			if (i == 0)
			{
				str.Format("GetMacroVarRange : return = %d, Last error = %d.\r\n"
					"Macro[%d] = %lf", nRet, m_mk30.GetLastError(), nMacroNum + i, dblMacroVar[i]);
			}
			else
			{
				str.Format("Macro[%d] = %lf", nMacroNum + i, dblMacroVar[i]);
			}
			strTemp = strTemp + "\r\n" + str;
		}
	}
	AddTextInMethodOutputView(strTemp);
}

void CMocxtestDlg::OnBtnGetMacrovarSafearray() 
{
	// TODO: Add your control notification handler code here
	CString strStartNo;
	CString strEndNo;

	GetDlgItemText(IDC_EDIT_GET_MACROVAR_STARTNO, strStartNo);
	GetDlgItemText(IDC_EDIT_GET_MACROVAR_ENDNO, strEndNo);
	if (strStartNo == "" || strEndNo == "")
	{
		MessageBox(_T("Please input data!"));
		return;
	}

	long nStartNo = atol(strStartNo);
	long nEndNo = atol(strEndNo);
// 	int num = nEndNo - nStartNo + 1;

	COleVariant va;
	double d[100] = {0.0};

	long nRet = m_mk30.GetMacroVarRangeSafeArray(nStartNo, nEndNo, &va);

	double *temp;
	if (SUCCEEDED(SafeArrayAccessData(va.parray, (void **)&temp)))
	{
		for (int i = 0; i < nRet; i++)
		{
			d[i] = temp[i];
		}
		SafeArrayUnaccessData(va.parray);
	}

	long nMacroNum = nStartNo;
	CString strTemp = "";	
	if (nRet <= 0)
	{
		strTemp.Format("GetMacroVarRange : return = %d, Last error = %d.", nRet, m_mk30.GetLastError());
	}
	else
	{
		for (int i = 0; i < nRet; i++)
		{
			CString str;
			if (i == 0)
			{
				str.Format("GetMacroVarRange : return = %d, Last error = %d.\r\n"
					"Macro[%d] = %lf", nRet, m_mk30.GetLastError(), nMacroNum + i, d[i]);
			}
			else
			{
				str.Format("Macro[%d] = %lf", nMacroNum + i, d[i]);
			}
			strTemp = strTemp + "\r\n" + str;
		}
	}
	AddTextInMethodOutputView(strTemp);
}

void CMocxtestDlg::OnBtnSetMacrovarRange() 
{
	// TODO: Add your control notification handler code here
	CString strStartNo;
	CString strEndNo;
	CString strFirstMacroVal;
	
	GetDlgItemText(IDC_EDIT_GET_MACROVAR_STARTNO, strStartNo);
	GetDlgItemText(IDC_EDIT_GET_MACROVAR_ENDNO, strEndNo);
	GetDlgItemText(IDC_EDIT_SET_1STMACRO_VALUE, strFirstMacroVal);
	
	if (strStartNo == "" || strEndNo == "" || strFirstMacroVal =="")
	{
		MessageBox(_T("Please input data!"));
		return;
	}
	
	long nStartNo = atol(strStartNo);
	long nEndNo = atol(strEndNo);
	double dblFirstMacroVal = atof(strFirstMacroVal);
	int num = nEndNo - nStartNo + 1;

	CString Temp;
	if (nStartNo < 0 || nStartNo > 999 || nEndNo < 0 || nEndNo > 999)
	{
		Temp.Format("SetMacroVarRange : return = 0,Last error = 17");
		AddTextInMethodOutputView(Temp);
		return ;
	}
	if (num <= 0 || num > 100)
	{
		Temp.Format("SetMacroVarRange : return = 0,Last error = 5");
		AddTextInMethodOutputView(Temp);
		return ;
	}

	srand((unsigned)time(NULL));
	

	double dblMacroVar[100] = {0};
	for (int i = 0; i < num; i++)
	{
		if (i==0)
		{
			dblMacroVar[i] = dblFirstMacroVal;
		} 
		else
		{
			int nInt = rand();
			double dblDec = (double)rand()/10000;
			double dblMacro = nInt + dblDec;
			dblMacroVar[i] = dblMacro;
		}
	}
	long nRet = m_mk30.SetMacroVarRange(nStartNo, nEndNo, dblMacroVar);

	CString strTemp = "";
	strTemp.Format("SetMacroVarRange : return = %d,Last error = %d.", nRet, m_mk30.GetLastError());


	for (int j = 0; j < nRet; j++)
	{
		CString str;
		str.Format("Macro[%d] = %lf", nStartNo + j, dblMacroVar[j]);
		strTemp = strTemp + "\r\n" + str;
	}

	AddTextInMethodOutputView(strTemp);
}

void CMocxtestDlg::OnBtnSetMacrovarSafearray() 
{
	// TODO: Add your control notification handler code here
	CString strStartNo;
	CString strEndNo;
	CString strFirstMacroVal;
	
	GetDlgItemText(IDC_EDIT_GET_MACROVAR_STARTNO, strStartNo);
	GetDlgItemText(IDC_EDIT_GET_MACROVAR_ENDNO, strEndNo);
	GetDlgItemText(IDC_EDIT_SET_1STMACRO_VALUE, strFirstMacroVal);
	
	if (strStartNo == "" || strEndNo == "" || strFirstMacroVal =="")
	{
		MessageBox(_T("Please input data!"));
		return;
	}
	
	long nStartNo = atol(strStartNo);
	long nEndNo = atol(strEndNo);
	double dblFirstMacroVal = atof(strFirstMacroVal);
	int num = nEndNo - nStartNo + 1;

	CString Temp;
	if (nStartNo < 0 || nStartNo > 999 || nEndNo < 0 || nEndNo > 999)
	{
		Temp.Format("SetMacroVarRange : return = 0,Last error = 17");
		AddTextInMethodOutputView(Temp);
		return ;
	}
	if (num <= 0 || num > 100)
	{
		Temp.Format("SetMacroVarRange : return = 0,Last error = 5");
		AddTextInMethodOutputView(Temp);
		return ;
	}

	CString strTemp;
	double *dTemp;
	double dblMacroVar[100] = {0};
	COleVariant vTemp;
	SAFEARRAY *pArray = SafeArrayCreateVector(VT_R8, 0, num);	//Create SafeArray
	if (pArray)
	{
		if (FAILED(SafeArrayAccessData(pArray, (void **)&dTemp)))
		{
			strTemp.Format("SetMacroVarRangeSafeArray : Failed to create SafeArray.");
			AddTextInMethodOutputView(strTemp);
			return;
		}
// 		for (int i = 0; i < num; i++)
// 		{
// 			dTemp[i] = nStartNo + i;
// 		}
		srand((unsigned)time(NULL));
		for (int i = 0; i < num; i++)
		{
			if (i==0)
			{
				dTemp[i] = dblFirstMacroVal;
				
			} 
			else
			{
				int nInt = rand();
				double dblDec = (double)rand()/10000;
				double dblMacro = nInt + dblDec;
				dTemp[i] = dblMacro;
			}
			dblMacroVar[i] = dTemp[i];
		}

		SafeArrayUnaccessData(pArray);
		vTemp.vt = VT_R8 | VT_ARRAY;
		vTemp.parray = pArray;
	} 
	else
	{
		strTemp.Format("SetMacroVarRangeSafeArray : Failed to create SafeArray.");
		AddTextInMethodOutputView(strTemp);
		return;
	}
	
	long nRet = m_mk30.SetMacroVarRangeSafeArray(nStartNo, nEndNo, &vTemp);

	strTemp.Format("SetMacroVarRangeSafeArray: return = %d, Last error = %d.", nRet, m_mk30.GetLastError());

	for (int j = 0; j < nRet; j++)
	{
		CString str;
		str.Format("Macro[%d] = %lf", nStartNo + j, dblMacroVar[j]);
		strTemp = strTemp + "\r\n" + str;
	}

	AddTextInMethodOutputView(strTemp);
}

void CMocxtestDlg::OnGetRunningFileName() 
{
	// TODO: Add your control notification handler code here

	BSTR temp = CString("").AllocSysString();
	long type;
	m_mk30.GetRunningFileName(&temp,&type);

	AfxMessageBox(CString(temp));
	
}

void CMocxtestDlg::OnGetRunningMainNcFileFirstLine() 
{
	// TODO: Add your control notification handler code here
	BSTR temp = CString("").AllocSysString();

	m_mk30.GetRunningMainNcFileFirstLine(&temp);

	AfxMessageBox(CString(temp));
	
}
