#include "ClientSocket.h"
#include "ListenSocket.h"
#include "ChatServerDialog.h"

ClientSocket::ClientSocket(){
	this->listenSocket = NULL;
}

ClientSocket::~ClientSocket(){

}

void ClientSocket::SetListenSocket(CAsyncSocket* socket){
	this->listenSocket = socket;
}

void ClientSocket::OnClose(int nErrorCode){
	CSocket::OnClose(nErrorCode);

	ListenSocket* serverSocket = (ListenSocket*)this->listenSocket;
	serverSocket->CloseClientSocket(this);
}

void ClientSocket::OnReceive(int nErrorCode){
	CString strTemp = _T("");
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;

	TCHAR buffer[1024];
	::ZeroMemory(buffer, sizeof(buffer));

	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(buffer, sizeof(buffer)) > 0) {
		ChatServerDialog* main = (ChatServerDialog*)AfxGetMainWnd();
		strTemp.Format(_T("[%s:%d] : %s"), strIPAddress, uPortNumber, buffer);
		main->list.AddString(strTemp);
		main->list.SetCurSel(main->list.GetCount() - 1);

		ListenSocket* serverSocket = (ListenSocket*)this->listenSocket;
		serverSocket->SendChatDataAll(buffer);
	}

	CSocket::OnReceive(nErrorCode);
}