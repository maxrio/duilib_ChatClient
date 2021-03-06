// ChatClient.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Common.h"
#include "Client.h"
#include "LoginWnd.h"
#include "ChatMainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
		return 0;

	Client *client = new Client;


	LoginWnd *loginWnd = new LoginWnd(client, client->threadPool);
	if (loginWnd == NULL)
		return 0;
	ChatMainWnd *chatMainWnd = new ChatMainWnd(client, client->threadPool);
	if (chatMainWnd == NULL)
		return 0;
	client->loginWnd = loginWnd;
	client->chatMainWnd = chatMainWnd;
	loginWnd->Create(NULL, L"登录", UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	loginWnd->CenterWindow();
	if (2 != loginWnd->ShowModal())
	{
		client->Stop();
		//delete client;
		::CoUninitialize();
		return 0;
	}

	chatMainWnd->Create(NULL, L"聊天", UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	chatMainWnd->CenterWindow();
	chatMainWnd->ShowModal();

	//CPaintManagerUI::MessageLoop();

	client->Stop();
	//delete client;
	::CoUninitialize();
	return 0;
}

