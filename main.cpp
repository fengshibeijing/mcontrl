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
	//����һ���ɱ���ر�����ͨ�������޸ģ�����̼߳���л�
	volatile static int rollint=1000;
	//���������̺߳�����������Ʋ���:TAP������ɶ̷���Roll������ɳ�����Stops�������ֹͣ������
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
	//������Ҫ�õ���GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR pGdiToken;
	GdiplusStartup(&pGdiToken,&gdiplusStartupInput,NULL);
	//��ʼ��GDI+
	HWND hWnd=::FindWindow(NULL,L"�ޱ���.txt - ���±�");
	HDC hDC=::GetDC(hWnd);
	Graphics graphics(hDC);
	Image* img=new Image(L"ICON.png");
	Image* img2=new Image(L"ICON2.png");
	//������ƽ�������ı�ʶ����state��z��Ƚϱ���z���Լ���ʼ�������豸��0
	int state=0;
	float z=0;
	int device = 0;
	// ���ض�̬���ӿ�
	if (!sdk.LoadInPath("lib")) return -1;
	std::cout << "�ȴ��豸���� ... " << std::endl;
	bool connected[] = { false, false };
	while (true)
	{
		if (sdk.RetrieveFrame(device))
		{
			// ����Ƿ�Ϊ�������豸
			if (!connected[device])
			{
				std::cout << "��⵽΢�� " << device << " ����" << std::endl;
				std::cout<<"�û����ã����������з�ʽ���£����������豸�Ϸ���ȭȻ���ſ�����������ģʽ�������󲻶��Ļ��ƶ�����ɶ̷���"<<std::endl<<"��ָ�ſ�����ѹ����Ϊ�����·���ֹͣ�·���Ҫ���������ֻ��ָ�����ơ�"<<std::endl;
				connected[device] = true;
			}

			const sharpnow::Frame* frame = sdk.GetFrameInfo();

			//��ȡ���ƺ���ָ�Ľ���		
			//std::cout<<"555";
			const sharpnow::Hand* hand=sdk.GetHandFocus();
			const sharpnow::Finger*finger=sdk.GetFingerFocus();
			//�豸ʶ��һֻ���������ڣ���������Ĳ���
			if (frame->hand_number==1&&hand)
			{
				//ͨ����ȭ�����ƣ���ʼ���ö�����ʼ��һ��ʹ��
				if (hand->gesture==1&&finger)
				{
					state=1; 
					z=finger->position.z;
				}
				//������־λ��1ʱ�������ģʽ
				if (state)
				{
					//�ж�������ָ����1ʱ���ö����������
					if(frame->finger_number>=1&&hand)
					{		

						//��tap�¼������϶̵Ĺ���
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

						//���������ָ�˳�����ģʽ
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


						//���ù����̣߳�������ѹһ�ξ��룬������������������ҳ��Ч��
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
			//�����ڼ�ⲻ������Ŀ��ʱ�������߳�stops������ʶλ��0���Է�ֹ�����
			else
			{
				ThreadStart^ ThreadWork3=gcnew ThreadStart(&ThreadWork::StopS);
				Thread^ thread3=gcnew Thread(ThreadWork3);
				thread3->Priority=ThreadPriority::Highest;
				thread3->Start();
				state=0;
			}
			//������ס�豸һ��ʱ�䣬�˳�����
			if (frame->blindfold>=50)
			{
				InvalidateRect(hWnd,NULL,FALSE);
				return 0;
			}
		}


		else
		{
			// ����豸�Ͽ�
			if (connected[device])
			{
				std::cout << "��⵽΢�� " << device << " �Ͽ�" << std::endl;
				connected[device] = false;
			}
			continue;
		}

		::Sleep(1);
	}

	//��ѭ����������䲻����ã�ֻ������Ǹ���˼����
	//�ر�GDI+
	GdiplusShutdown(pGdiToken);
	//system("pause");
	return 0;



	

}






