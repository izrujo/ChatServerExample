#include "ChatServerDialog.h"
#include "ClientSocket.h"

BEGIN_MESSAGE_MAP(ChatServerDialog, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

ChatServerDialog::ChatServerDialog(CWnd* parent) 
	: CDialog(IDD, parent) {

}

void ChatServerDialog::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHATLIST, this->list);
}

BOOL ChatServerDialog::OnInitDialog(){
	CDialog::OnInitDialog();

	if (this->listenSocket.Create(63620, SOCK_STREAM)) //소켓 생성(바인드되는 포트번호, TCP 소켓 플래그)
	{
		if (!this->listenSocket.Listen()) //서버가 클라이언트의 접속을 받을 수 있는 상태로 설정
		{
			AfxMessageBox(_T("ERROR: Listen() return FALSE"));
		}
	}
	else
	{
		DWORD error = GetLastError();
		AfxMessageBox(_T("ERROR: Failed to create server socket!"));
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void ChatServerDialog::OnDestroy(){
	CDialog::OnDestroy();

	POSITION position;
	position = this->listenSocket.clientSocketList.GetHeadPosition();
	ClientSocket* client = NULL;

	while (position != NULL) { //클라이언트 소켓 리스트 전부 삭제.
		client = (ClientSocket*)this->listenSocket.clientSocketList.GetNext(position);
		if (client != NULL) {
			client->ShutDown();
			client->Close();

			delete client;
		}
	}

	this->listenSocket.ShutDown();
	this->listenSocket.Close(); //서버 종료.
}