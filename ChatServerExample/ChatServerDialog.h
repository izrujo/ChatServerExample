#ifndef _CHATSERVERDIALOG_H
#define _CHATSERVERDIALOG_H

#include "afxwin.h"
#include "resource.h"
#include "ListenSocket.h"

class ChatServerDialog : public CDialog {
public:
	enum { IDD = IDD_CHATSERVERDIALOG };
public:
	ChatServerDialog(CWnd* parent = NULL);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	ListenSocket listenSocket;
	CListBox list;
	afx_msg void OnDestroy();
};

#endif //_CHATSERVERDIALOG_H