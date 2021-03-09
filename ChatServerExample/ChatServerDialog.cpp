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

	if (this->listenSocket.Create(63620, SOCK_STREAM)) //���� ����(���ε�Ǵ� ��Ʈ��ȣ, TCP ���� �÷���)
	{
		if (!this->listenSocket.Listen()) //������ Ŭ���̾�Ʈ�� ������ ���� �� �ִ� ���·� ����
		{
			AfxMessageBox(_T("ERROR: Listen() return FALSE"));
		}
	}
	else
	{
		DWORD error = GetLastError();
		AfxMessageBox(_T("ERROR: Failed to create server socket!"));
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void ChatServerDialog::OnDestroy(){
	CDialog::OnDestroy();

	POSITION position;
	position = this->listenSocket.clientSocketList.GetHeadPosition();
	ClientSocket* client = NULL;

	while (position != NULL) { //Ŭ���̾�Ʈ ���� ����Ʈ ���� ����.
		client = (ClientSocket*)this->listenSocket.clientSocketList.GetNext(position);
		if (client != NULL) {
			client->ShutDown();
			client->Close();

			delete client;
		}
	}

	this->listenSocket.ShutDown();
	this->listenSocket.Close(); //���� ����.
}