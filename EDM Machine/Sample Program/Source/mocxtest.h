// mocxtest.h : MOCXTEST �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_MOCXTEST_H__9F7353B7_7D2E_11D3_8F07_0000E85B90F9__INCLUDED_)
#define AFX_MOCXTEST_H__9F7353B7_7D2E_11D3_8F07_0000E85B90F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CMocxtestApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� mocxtest.cpp �t�@�C�����Q�Ƃ��Ă��������B
//
	enum
	{
		STATUS_UNKNOWN = -1,
		STATUS_READY,
		STATUS_EXECUTE,
		STATUS_HALT,
		STATUS_ACK,
	};
class CMocxtestApp : public CWinApp
{
public:
	CMocxtestApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMocxtestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CMocxtestApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MOCXTEST_H__9F7353B7_7D2E_11D3_8F07_0000E85B90F9__INCLUDED_)
