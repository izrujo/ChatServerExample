#include "ListenSocket.h"
#include "ClientSocket.h"

ListenSocket::ListenSocket() {
	
}

ListenSocket::~ListenSocket() {

}

void ListenSocket::OnAccept(int nErrorCode) {
	ClientSocket* client = new ClientSocket;
	if (Accept(*client)) {
		client->SetListenSocket(this);
		this->clientSocketList.AddTail(client);
	}
	else {
		delete client;
		AfxMessageBox(_T("Error: Failed to accept new Client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void ListenSocket::CloseClientSocket(CSocket* client) {
	POSITION position;
	position = this->clientSocketList.Find(client); //����Ʈ���� ���� ���� �˻�
	if (position != NULL) {
		if (client != NULL) {
			client->ShutDown(); //��� ����
			client->Close(); //���� �ݱ�
		}

		this->clientSocketList.RemoveAt(position); //����Ʈ���� ����
		delete client; //����
	}
}

void ListenSocket::SendChatDataAll(TCHAR* message) {
	POSITION position;
	position = this->clientSocketList.GetHeadPosition();
	ClientSocket* client = NULL;
	
	while (position != NULL) {
		client = (ClientSocket*)this->clientSocketList.GetNext(position);
		if (client != NULL) {
			client->Send(message, lstrlen(message)); //�����ڵ带 ����ϹǷ� ���ڿ� ���̿� *2
			//��ȯ���� *2�� ���� ���ƾ� �Ѵ�.
		}
	}
}