// SearchCondition.cpp : implementation file
//

#include "stdafx.h"
#include "mocxtest.h"
#include "SearchCondition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchCondition dialog


CSearchCondition::CSearchCondition(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchCondition::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchCondition)
	//}}AFX_DATA_INIT 
}


void CSearchCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchCondition)
	DDX_Control(pDX, IDC_COMBO_WRIDAM, m_comboWridam);
	DDX_Control(pDX, IDC_COMBO_WIREM, m_comboWirem);
	DDX_Control(pDX, IDC_COMBO_THICK, m_comboThick);
	DDX_Control(pDX, IDC_COMBO_SFCC, m_comboSFCC);
	DDX_Control(pDX, IDC_COMBO_ROUGH, m_comboRough);
	DDX_Control(pDX, IDC_COMBO_OFSTAJST, m_comboOfstAjst);	
	DDX_Control(pDX, IDC_EDIT_RESEARCH_NUM, m_editResearchNumber); 
	DDX_Control(pDX, IDC_EDIT_PRECISION, m_editPrecision); 
	DDX_Control(pDX, IDC_COMBO_MATER, m_comboMater);
	DDX_Control(pDX, IDC_COMBO_LQUID, m_comboLQUid);
	DDX_Control(pDX, IDC_COMBO_LQKND, m_comboLQKnd);
	DDX_Control(pDX, IDC_COMBO_KIND, m_comboKind);
	DDX_Control(pDX, IDC_COMBO_DATABASE, m_comboDatabaseType);
	DDX_Control(pDX, IDC_COMBO_CUTN, m_comboCutn);
	DDX_Control(pDX, IDC_COMBO_COMMENT, m_comboComment);
	DDX_Control(pDX, IDC_COMBO_BSA, m_comboBSA);
	DDX_Control(pDX, IDC_COMBO_BS, m_comboBS);
	DDX_Control(pDX, IDC_COMBO_AIC, m_comboAic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchCondition, CDialog)
	//{{AFX_MSG_MAP(CSearchCondition)
	ON_EN_KILLFOCUS(IDC_EDIT_PRECISION, OnKillfocusEditPrecision)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchCondition message handlers

BOOL CSearchCondition::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow(); 
	InitComboBox();
	m_editResearchNumber.SetWindowText("1");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchCondition::InitComboBox()
{
	int nIndex = 0;
	
	// 数据库类型
 	CString strDatabaseType[] = 
	{
		"0.Sodick DataBase",		"1.Option DataBase",	"2.User DataBase",
		"3.The Kantan DataBase",	"4.ECO DataBase",		"5.HECW DataBase",
		"6.Refernce DataBase" 
	};
	for (nIndex = 0; nIndex<sizeof(strDatabaseType)/sizeof(strDatabaseType[0]); nIndex++) 
		m_comboDatabaseType.AddString(strDatabaseType[nIndex]); 
	m_comboDatabaseType.SetCurSel(0);

	// 加工液种纴E
	CString strLQUid[] = 
	{
		"Flush-W",		"Water",		"Water-Oil",		"Oil",			"Water-2",	
		"Water-3",   	"WaterMi33",	"Water1_33",		"Water3_33",	"Water-5"   
	};
	for (nIndex = 0; nIndex<sizeof(strLQUid)/sizeof(strLQUid[0]); nIndex++)
		m_comboLQUid.AddString(strLQUid[nIndex]);
	m_comboLQUid.SetCurSel(0);

	// 线材质
	CString strWirem[] = 
	{
		"Brass",		"AP",		"TWs",		"Zn",			"SZW",	 
	};
	for (nIndex = 0; nIndex<sizeof(strWirem)/sizeof(strWirem[0]); nIndex++)
		m_comboWirem.AddString(strWirem[nIndex]);
	m_comboWirem.SetCurSel(0);

	// 线径
	CString strWridam[] = 
	{
		"0.03",	"0.05",	"0.08",	"0.10",	"0.15", "0.20",	"0.25",	"0.30"
	};
	for (nIndex = 0; nIndex<sizeof(strWridam)/sizeof(strWridam[0]); nIndex++)
		m_comboWridam.AddString(strWridam[nIndex]);
	m_comboWridam.SetCurSel(3);	

	// 加工状态
	CString strKind[] = 
	{  
		"Punch",		"Die",		"Both" 
	};
	for (nIndex = 0; nIndex<sizeof(strKind)/sizeof(strKind[0]); nIndex++)
		m_comboKind.AddString(strKind[nIndex]);
	m_comboKind.SetCurSel(0);

	// 液处纴E
	CString strLQKnd[] = 
	{
		"Close",		"Open-U",		"Open-D",	"Open",		"TC"
	};
	for (nIndex = 0; nIndex<sizeof(strLQKnd)/sizeof(strLQKnd[0]); nIndex++)
		m_comboLQKnd.AddString(strLQKnd[nIndex]);
	m_comboLQKnd.SetCurSel(0);

	// 工件材质
	CString strMater[] = 
	{        
		"Steel",		"Cu",		"WC",	"Al",		"Gr(ED3)",
		"Gr(ISO63)",	"NAK",		"SUS",	"SUS",		"CuW"
	};
	for (nIndex = 0; nIndex<sizeof(strMater)/sizeof(strMater[0]); nIndex++)
		m_comboMater.AddString(strMater[nIndex]);
	m_comboMater.SetCurSel(0);

	// 板簛E		
	CString strThick[] = 
	{  
		"5",	"10",	"15",	"20",	"30",	"40",	"50",	"60",	"70",		
		"80",	"90",	"100",	"150",	"200",	"250",	"300",	"350",	"400",
		"500",	"0.5",	"1",	"2",	"3",	"4",	"6",	"7",	"8",	
		"9",	"550",	"600"
	};
	for (nIndex = 0; nIndex<sizeof(strThick)/sizeof(strThick[0]); nIndex++)
		m_comboThick.AddString(strThick[nIndex]);
	m_comboThick.SetCurSel(0);

	// 面粗度		m_comboRough
	CString strRough[] = 
	{        
		"0.6000",		"1.0000",		"5.0000",	
		"10.000",		"15.000",		"20.000",		
		"25.000"

	};
	for (nIndex = 0; nIndex<sizeof(strRough)/sizeof(strRough[0]); nIndex++)
		m_comboRough.AddString(strRough[nIndex]);
	m_comboRough.SetCurSel(0);

	// 切耕形数		m_comboCutn
	CString strCutn[] = 
	{        
		"1","2","3"	,"4","5","6","7","8","9","10"
	};
	for (nIndex = 0; nIndex<sizeof(strCutn)/sizeof(strCutn[0]); nIndex++)
		m_comboCutn.AddString(strCutn[nIndex]);
	m_comboCutn.SetCurSel(0);

	// BS ON/OFF	m_comboBS 
	CString strBS[] = 
	{        
		"ON",		"OFF" 
	};
	for (nIndex = 0; nIndex<sizeof(strBS)/sizeof(strBS[0]); nIndex++)
		m_comboBS.AddString(strBS[nIndex]);
	m_comboBS.SetCurSel(0);

	// 备注			
	CString strComment[] = 
	{        
		"Comment",		" " 
	};
	for (nIndex = 0; nIndex<sizeof(strComment)/sizeof(strComment[0]); nIndex++)
		m_comboComment.AddString(strComment[nIndex]);
	m_comboComment.SetCurSel(0);

	// 补正调整书据	
	CString strOfstAjst[] = 
	{        
		"0.000000",		"1.2345",		"10.0000",		"20.0000",
	};
	for (nIndex = 0; nIndex<sizeof(strOfstAjst)/sizeof(strOfstAjst[0]); nIndex++)
		m_comboOfstAjst.AddString(strOfstAjst[nIndex]);
	m_comboOfstAjst.SetCurSel(0);
	
	// AIC输硜E	
	CString strAic[] = 
	{        
		"1.mm",		"2.inch",	"0.other" 
	};
	for (nIndex = 0; nIndex<sizeof(strAic)/sizeof(strAic[0]); nIndex++)
		m_comboAic.AddString(strAic[nIndex]);
	m_comboAic.SetCurSel(0);

	// SFCC是否输硜E
	CString strSFCC[] = 
	{        
		"1.mm",		"2.inch",	"0.other" 
	};
	for (nIndex = 0; nIndex<sizeof(strSFCC)/sizeof(strSFCC[0]); nIndex++)
		m_comboSFCC.AddString(strSFCC[nIndex]);
	m_comboSFCC.SetCurSel(0);

	// Precision	m_comboPrecision

	// BSA			
	CString strBSA[] = 
	{        
		"ON",		"OFF" 
	};
	for (nIndex = 0; nIndex<sizeof(strBSA)/sizeof(strBSA[0]); nIndex++)
		m_comboBSA.AddString(strBSA[nIndex]);
	m_comboBSA.SetCurSel(0);
}


BOOL CSearchCondition::GetConditionSearchData(SWF_CONDITION &swf, int &nDataBaseType, int &nResearchNum)
{
	memcpy(&swf, &m_stSwfCond, sizeof(SWF_CONDITION));
	nDataBaseType = m_nDataBaseType; 
	nResearchNum = m_nResearchNum; 

	return TRUE;
}

BOOL CSearchCondition::GetConditionSearchData(SWF_CONDITION_GE &swf, int &nDataBaseType, int &nResearchNum)
{
	memcpy(&swf, &m_stSwfCondGE, sizeof(SWF_CONDITION_GE));
	nDataBaseType = m_nDataBaseType; 
	nResearchNum = m_nResearchNum;
	
	return TRUE;
}

void CSearchCondition::OnOK() 
{
	CString strTemp(""); 

	m_editPrecision.GetWindowText(strTemp);
	if (strTemp.IsEmpty())
		m_bPresion = FALSE;
	else
		m_bPresion = TRUE;
 
	m_editResearchNumber.GetWindowText(strTemp);
	if (strTemp.IsEmpty())
		m_nResearchNum = 1;
	else
		m_nResearchNum = atol(strTemp);

	if (m_bPresion)
	{
		memset(&m_stSwfCondGE,'\0', sizeof(SWF_CONDITION_GE));

		// 数据库类型 
		m_nDataBaseType = m_comboDatabaseType.GetCurSel(); 
		// 加工液种纴E
		m_comboLQUid.GetWindowText(strTemp);
		strcpy(m_stSwfCondGE.lquid, strTemp); 
 		// 线材质
		m_comboWirem.GetWindowText(strTemp);
		strcpy(m_stSwfCondGE.wirem, strTemp); 
		// 线径 
		m_comboWridam.GetWindowText(strTemp);
		m_stSwfCondGE.wrdiam = atof(strTemp);
		// 加工状态
		m_comboKind.GetWindowText(strTemp); 
		strcpy(m_stSwfCondGE.kind, strTemp); 
		// 液处纴E
		m_comboLQKnd.GetWindowText(strTemp);
		strcpy(m_stSwfCondGE.lqknd, strTemp); 
		// 工件材质
		m_comboMater.GetWindowText(strTemp);
		strcpy(m_stSwfCondGE.mater, strTemp); 
		// 板簛E
		m_comboThick.GetWindowText(strTemp);
		m_stSwfCondGE.thick = atof(strTemp); 
		// 面粗度		
		m_comboRough.GetWindowText(strTemp);
		m_stSwfCondGE.rough = atof(strTemp);  
		// 切耕形数		
		m_comboCutn.GetWindowText(strTemp);
		m_stSwfCondGE.cutn = atol(strTemp);   
		// BS ON/OFF	
		m_comboBS.GetWindowText(strTemp);
		strcpy(m_stSwfCondGE.bson, strTemp); 
		// 备注			
		m_comboComment.GetWindowText(strTemp);
		strcpy(m_stSwfCondGE.comment, strTemp); 
		// 补正调整书据	
		m_comboOfstAjst.GetWindowText(strTemp);
		m_stSwfCondGE.ofstajst = atof(strTemp);   
		// AIC输硜E
		m_comboAic.GetWindowText(strTemp);
		strTemp = strTemp.Left(1);
		m_stSwfCondGE.aicon = atol(strTemp);    
		// SFCC是否输硜E
		m_comboSFCC.GetWindowText(strTemp);
		strTemp = strTemp.Left(1);
		m_stSwfCondGE.SFCCFlag = atol(strTemp);   
		// Precision	m_editPrecision
		m_editPrecision.GetWindowText(strTemp); 
		m_stSwfCondGE.precision = atoi(strTemp);
	}
	else
	{
		memset(&m_stSwfCond,'\0', sizeof(SWF_CONDITION));

		// 数据库类型 
		m_nDataBaseType = m_comboDatabaseType.GetCurSel(); 
		// 加工液种纴E
		m_comboLQUid.GetWindowText(strTemp);
		strcpy(m_stSwfCond.lquid, strTemp); 
 		// 线材质
		m_comboWirem.GetWindowText(strTemp);
		strcpy(m_stSwfCond.wirem, strTemp); 
		// 线径 
		m_comboWridam.GetWindowText(strTemp);
		m_stSwfCond.wrdiam = atof(strTemp);
		// 加工状态
		m_comboKind.GetWindowText(strTemp); 
		strcpy(m_stSwfCond.kind, strTemp); 
		// 液处纴E
		m_comboLQKnd.GetWindowText(strTemp);
		strcpy(m_stSwfCond.lqknd, strTemp); 
		// 工件材质
		m_comboMater.GetWindowText(strTemp);
		strcpy(m_stSwfCond.mater, strTemp); 
		// 板簛E
		m_comboThick.GetWindowText(strTemp);
		m_stSwfCond.thick = atof(strTemp); 
		// 面粗度		
		m_comboRough.GetWindowText(strTemp);
		m_stSwfCond.rough = atof(strTemp);  
		// 切耕形数		
		m_comboCutn.GetWindowText(strTemp);
		m_stSwfCond.cutn = atol(strTemp);   
		// BS ON/OFF	
		m_comboBS.GetWindowText(strTemp);
		strcpy(m_stSwfCond.bson, strTemp); 
		// 备注			
		m_comboComment.GetWindowText(strTemp);
		strcpy(m_stSwfCond.comment, strTemp); 
		// 补正调整书据	
		m_comboOfstAjst.GetWindowText(strTemp);
		m_stSwfCond.ofstajst = atof(strTemp);   
		// AIC输硜E
		m_comboAic.GetWindowText(strTemp);
		strTemp = strTemp.Left(1);
		m_stSwfCond.aicon = atol(strTemp);    
		// SFCC是否输硜E
		m_comboSFCC.GetWindowText(strTemp);
		strTemp = strTemp.Left(1);
		m_stSwfCond.SFCCFlag = atol(strTemp);  
	}

	CWnd *pParent = GetParent();
	if(::IsWindow(pParent->m_hWnd))
		::PostMessage(pParent->m_hWnd,WM_COND_SEARCH,0,0);
// 	CDialog::OnOK();
}

void CSearchCondition::GetPresion(BOOL &bPresion)
{
	bPresion = m_bPresion;
}

void CSearchCondition::OnKillfocusEditPrecision() 
{
	CString strTemp("");
	m_editPrecision.GetWindowText(strTemp);  
	char c;

	for (int i=0; i< strTemp.GetLength(); i++)
	{
		c = strTemp.GetAt(i);
		if (c < '0' || c > '9')
		{
			MessageBox("The input data is not in the valid range!");
			m_editPrecision.SetFocus();
			m_editPrecision.SetSel(0,-1);
			m_editPrecision.Clear();
			return;
		}
	}
}
 

void CSearchCondition::OnCancel() 
{
	ShowWindow(SW_HIDE);
	// CDialog::OnCancel();
}
