#include <windows.h>
#include <gdiplus.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment (lib,"user32.lib") 
#pragma comment (lib,"Gdi32.lib") 
#include "include/sharpnow.hpp"
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")   
#pragma comment(lib, "User32.lib")  
using namespace System;
using namespace System::Threading;



typedef unsigned long ULONG_PTR, *PULONG_PTR;
using namespace Gdiplus;
#pragma comment (lib, "GdiPlus.lib")
sharpnow::SDK sdk;

public ref class ThreadWork
{

public:
	//定义一个可被监控变量，通过对其修改，完成线程间的切换
	volatile static int rollint=1000;
	//定义三个线程函数，完成手势操作:TAP进程完成短翻，Roll进程完成长翻，Stops进程完成停止长翻。
	static void Tap()
	{
		try
		{
			rollint=0;
			mouse_event(MOUSEEVENTF_WHEEL,0,0,-200,0);
		}
		catch (CMemoryException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		catch (CFileException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		catch (CException* e)
		{
			std::cout<<e->GetErrorMessage();
		}


	}
	static void StopS()
	{
		try
		{
			rollint=0;
		}
		catch (CMemoryException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		catch (CFileException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		catch (CException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		


	}
	static void Roll()
	{
		rollint=2000;
		while(rollint>0)
		{try
		{
			mouse_event(MOUSEEVENTF_WHEEL,0,0,-30,0);
			rollint--;
			Sleep(200);
		}
		catch (CMemoryException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		catch (CFileException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
		catch (CException* e)
		{
			std::cout<<e->GetErrorMessage();
		}
			//Sleep(200);


		}


	}



};
int main(int argc, char** argv)
{
	HWND hwnd=::FindWindow(L"ConsoleWindowClass",0);
	if(hwnd) ::SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	//加载需要用到的GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR pGdiToken;
	GdiplusStartup(&pGdiToken,&gdiplusStartupInput,NULL);
	//初始化GDI+
	HWND hWnd=::FindWindow(NULL,L"无标题.txt - 记事本");
	HDC hDC=::GetDC(hWnd);
	Graphics graphics(hDC);
	Image* img=new Image(L"ICON.png");
	Image* img2=new Image(L"ICON2.png");
	//定义控制进入操作的标识变量state和z轴比较变量z，以及初始化定义设备号0
	int state=0;
	float z=0;
	int device = 0;
	// 加载动态链接库
	if (!sdk.LoadInPath("lib")) return -1;
	std::cout << "等待设备连接 ... " << std::endl;
	bool connected[] = { false, false };
	while (true)
	{
		if (sdk.RetrieveFrame(device))
		{
			// 检测是否为新连接设备
			if (!connected[device])
			{
				std::cout << "检测到微动 " << device << " 连接" << std::endl;
				std::cout<<"用户您好：本程序运行方式如下，手掌置于设备上方握拳然后张开即进入运行模式，作手腕不动的挥掌动作完成短翻；"<<std::endl<<"手指张开的下压动作为持续下翻，停止下翻需要您做伸出两只手指的手势。"<<std::endl;
				connected[device] = true;
			}

			const sharpnow::Frame* frame = sdk.GetFrameInfo();

			//获取手掌和手指的焦点		
			//std::cout<<"555";
			const sharpnow::Hand* hand=sdk.GetHandFocus();
			const sharpnow::Finger*finger=sdk.GetFingerFocus();
			//设备识别到一只手在区域内，进行下面的操作
			if (frame->hand_number==1&&hand)
			{
				//通过握拳的手势，开始设置动作开始标一步使用
				if (hand->gesture==1&&finger)
				{
					state=1; 
					z=finger->position.z;
				}
				//启动标志位置1时进入操作模式
				if (state)
				{
					//判断侦内手指多于1时启用动作操作鼠标
					if(frame->finger_number>=1&&hand)
					{		

						//用tap事件触发较短的滚动
						if (hand->finger_number>=3&&hand)
						{
							if(finger->tap)
							{
								graphics.DrawImage(img,0,100,100,100);
								ThreadStart^ ThreadWork1=gcnew ThreadStart(&ThreadWork::Tap);
								Thread^ thread1=gcnew Thread(ThreadWork1);
								thread1->Start();								
								Sleep(10);
								InvalidateRect(hWnd,NULL,FALSE);
							}

						}
						//std::cout<<hand->finger_number;

						//伸出两个手指退出操作模式
						if (hand->finger_number==2&&hand)
						{
							//std::cout<<1;
							ThreadStart^ ThreadWork3=gcnew ThreadStart(&ThreadWork::StopS);
							Thread^ thread3=gcnew Thread(ThreadWork3);
							thread3->Priority=ThreadPriority::Highest;
							thread3->Start();
							InvalidateRect(hWnd,NULL,FALSE);
							Sleep(10);

						}


						//启用滚动线程，手掌下压一段距离，启动向下连续滚动翻页的效果
						if (hand->velocity.z<-0.03&&z-hand->position.z>=0.12&&hand)
						{
							ThreadStart^ ThreadWork2=gcnew ThreadStart(&ThreadWork::Roll);
							Thread^ thread2=gcnew Thread(ThreadWork2);
							thread2->Priority=ThreadPriority::BelowNormal;
							thread2->Start();
							graphics.DrawImage(img2,0,100,100,100);

						}   

					}

				}

			}
			//区域内检测不到手掌目标时，调用线程stops并将标识位置0，以防止误操作
			else
			{
				ThreadStart^ ThreadWork3=gcnew ThreadStart(&ThreadWork::StopS);
				Thread^ thread3=gcnew Thread(ThreadWork3);
				thread3->Priority=ThreadPriority::Highest;
				thread3->Start();
				state=0;
			}
			//手掌捂住设备一段时间，退出程序
			if (frame->blindfold>=50)
			{
				InvalidateRect(hWnd,NULL,FALSE);
				return 0;
			}
		}


		else
		{
			// 检测设备断开
			if (connected[device])
			{
				std::cout << "检测到微动 " << device << " 断开" << std::endl;
				connected[device] = false;
			}
			continue;
		}

		::Sleep(1);
	}

	//死循环，下面这句不会调用，只是想把那个意思表明
	//关闭GDI+
	GdiplusShutdown(pGdiToken);
	//system("pause");
	return 0;



	

}






