#include "../../include/sharpnow.h"
#include <iostream>
#include <Windows.h>

sharpnow::Proto_RetrieveFrame     RetrieveFrame;
sharpnow::Proto_GetFrameInfo      GetFrameInfo;
sharpnow::Proto_GetFinger         GetFinger;
sharpnow::Proto_GetFingerFocus    GetFingerFocus;
sharpnow::Proto_GetHand           GetHand;
sharpnow::Proto_GetHandFocus      GetHandFocus;

int main(int argc, char** argv)
{
    // 加载动态链接库
    HMODULE dll = NULL;
#ifdef _DEBUG
    dll = LoadLibraryA("../../lib/sharpnowD.dll");
#else
    dll = LoadLibraryA("../../lib/sharpnow.dll");
#endif
    if (!dll) return -1;    

    // 加载接口函数
    RetrieveFrame  = (sharpnow::Proto_RetrieveFrame)GetProcAddress(dll, "RetrieveFrame");
    GetFrameInfo   = (sharpnow::Proto_GetFrameInfo)GetProcAddress(dll, "GetFrameInfo");
    GetHand        = (sharpnow::Proto_GetHand)GetProcAddress(dll, "GetHand");
    GetHandFocus   = (sharpnow::Proto_GetHandFocus)GetProcAddress(dll, "GetHandFocus");
    if (!RetrieveFrame || !GetFrameInfo || !GetHand || !GetHandFocus) return -1;

    std::cout << "等待设备连接 ... " << std::endl;
    bool connected[] = { false, false };
    while (true)
    {
        for (int device = 0; device < 2; ++device)
        {
            if (RetrieveFrame(device))
            {
                // 检测是否为新连接设备
                if (!connected[device])
                {
                    std::cout << "检测到微动 " << device << " 连接" << std::endl;
                    connected[device] = true;
                }

                // 确认收到最新数据
                const sharpnow::Frame* frame = GetFrameInfo();
                if (!frame->updated) continue;

                // 检查当前手势类型
                const sharpnow::Hand* hand = GetHandFocus();
                if (hand 
                    && hand->gesture != sharpnow::HS_Unknown
                    && hand->gesture != sharpnow::HG_Grip 
                    && hand->gesture_counter <= 25) 
                {
                    // 确认手势类型
                    std::cout << "\r当前手势姿态：";
                    switch (hand->gesture)
                    {
                    case sharpnow::HG_Point:    std::cout << "Point   "; break;
                    case sharpnow::HG_Gun:      std::cout << "Gun     "; break;
                    case sharpnow::HG_Victory:  std::cout << "Victory "; break;
                    case sharpnow::HG_Metal:    std::cout << "Metel   "; break;
                    case sharpnow::HG_Phone:    std::cout << "Phone   "; break;
                    case sharpnow::HG_Fork:     std::cout << "Fork    "; break;
                    case sharpnow::HG_Three:    std::cout << "Three   "; break;
                    case sharpnow::HG_Love:     std::cout << "Love    "; break;
                    case sharpnow::HG_Four:     std::cout << "Four    "; break;
                    case sharpnow::HG_Five:     std::cout << "Five    "; break;
                    }

                    for (int i = 0; i < 25; ++i) std::cout << (i < hand->gesture_counter ? "." : " ");
                    if (hand->gesture_counter == 25) std::cout << " OK\n";
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
        }
        ::Sleep(1);
    }

    return 0;
}

