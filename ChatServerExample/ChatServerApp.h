#ifndef _CHATSERVERAPP_H
#define _CHATSERVERAPP_H

#include <afxwinappex.h>

class ChatServerApp : public CWinAppEx {
public:
	ChatServerApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern ChatServerApp chatServerApp;

#endif //_CHATSERVERAPP_H