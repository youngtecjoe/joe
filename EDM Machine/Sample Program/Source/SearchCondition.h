#if !defined(AFX_SEARCHCONDITION_H__78982666_BFD6_4862_8C46_B30360BE4AE2__INCLUDED_)
#define AFX_SEARCHCONDITION_H__78982666_BFD6_4862_8C46_B30360BE4AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchCondition.h : header file
//
 
#include "Cond_Sch_Interface.h"//@11168

#define WM_COND_SEARCH     WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CSearchCondition dialog

class CSearchCondition : public CDialog
{
// Construction
public:
	void GetPresion(BOOL &bPresion);
	BOOL GetConditionSearchData(SWF_CONDITION &swf, int &nDataBaseType, int &nResearchNum);
	BOOL GetConditionSearchData(SWF_CONDITION_GE &swf, int &nDataBaseType, int &nResearchNum);
	CSearchCondition(CWnd* pParent = NULL);   // standard constructor

	SWF_CONDITION m_stSwfCond;
	SWF_CONDITION_GE m_stSwfCondGE;

	int m_nDataBaseType;
	int m_nResearchNum;
	BOOL m_bPresion; 
// Dialog Data
	//{{AFX_DATA(CSearchCondition)
	enum { IDD = IDD_DLG_SEARCHCONDITION };
	CComboBox	m_comboWridam;
	CComboBox	m_comboWirem;
	CComboBox	m_comboThick;
	CComboBox	m_comboSFCC;
	CComboBox	m_comboRough;
	CComboBox	m_comboOfstAjst;
	CComboBox	m_comboMater;
	CComboBox	m_comboLQUid;
	CComboBox	m_comboLQKnd;
	CComboBox	m_comboKind;
	CComboBox	m_comboDatabaseType;
	CComboBox	m_comboCutn;
	CComboBox	m_comboComment;
	CComboBox	m_comboBSA;
	CComboBox	m_comboBS;
	CComboBox	m_comboAic;
	CEdit		m_editPrecision; 
	CEdit		m_editResearchNumber; 
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchCondition)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitComboBox();

	// Generated message map functions
	//{{AFX_MSG(CSearchCondition)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusEditPrecision(); 
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHCONDITION_H__78982666_BFD6_4862_8C46_B30360BE4AE2__INCLUDED_)
