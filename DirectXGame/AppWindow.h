#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Window��(��) ���� ��ӵ�
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* mSwapChain;
	VertexBuffer* mVb;
};
