// mocxtest.h : MOCXTEST アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MOCXTEST_H__9F7353B7_7D2E_11D3_8F07_0000E85B90F9__INCLUDED_)
#define AFX_MOCXTEST_H__9F7353B7_7D2E_11D3_8F07_0000E85B90F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMocxtestApp:
// このクラスの動作の定義に関しては mocxtest.cpp ファイルを参照してください。
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

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMocxtestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMocxtestApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MOCXTEST_H__9F7353B7_7D2E_11D3_8F07_0000E85B90F9__INCLUDED_)
