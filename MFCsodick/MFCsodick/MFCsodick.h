
// MFCsodick.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFCsodickApp: 
// �аѾ\��@�����O�� MFCsodick.cpp
//

class CMFCsodickApp : public CWinApp
{
public:
	CMFCsodickApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFCsodickApp theApp;