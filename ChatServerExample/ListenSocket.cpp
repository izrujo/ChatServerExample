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
	position = this->clientSocketList.Find(client); //리스트에서 소켓 선형 검색
	if (position != NULL) {
		if (client != NULL) {
			client->ShutDown(); //통신 중지
			client->Close(); //소켓 닫기
		}

		this->clientSocketList.RemoveAt(position); //리스트에서 제거
		delete client; //삭제
	}
}

void ListenSocket::SendChatDataAll(TCHAR* message) {
	POSITION position;
	position = this->clientSocketList.GetHeadPosition();
	ClientSocket* client = NULL;
	
	while (position != NULL) {
		client = (ClientSocket*)this->clientSocketList.GetNext(position);
		if (client != NULL) {
			client->Send(message, lstrlen(message)); //유니코드를 사용하므로 문자열 길이에 *2
			//반환값은 *2한 값과 같아야 한다.
		}
	}
}