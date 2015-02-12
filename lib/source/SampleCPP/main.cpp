#include "../../include/sharpnow.hpp"
#include <iostream>
#include <Windows.h>

sharpnow::SDK sdk;

int main(int argc, char** argv)
{
    // 加载动态链接库
    if (!sdk.LoadInPath("../../lib")) return -1;

    std::cout << "等待设备连接 ... " << std::endl;
    bool connected[] = { false, false };
    while (true)
    {
        for (int device = 0; device < 2; ++device)
        {
            if (sdk.RetrieveFrame(device))
            {
                // 检测是否为新连接设备
                if (!connected[device])
                {
                    std::cout << "检测到微动 " << device << " 连接" << std::endl;
                    std::cout << "伸出单指可控制屏幕光标移动" << std::endl;
                    connected[device] = true;
                }

                // 确认收到最新数据
                const sharpnow::Frame* frame = sdk.GetFrameInfo();
                if (!frame->updated) continue;

                // 单手指时，控制屏幕光标
                const sharpnow::Finger* finger = sdk.GetFingerFocus();
                if (frame->finger_number == 1 && finger)
                {
                    std::cout << "\r" << finger->cursor.x << " " << finger->cursor.y;
                    SetCursorPos(
                        int(finger->cursor.x * ::GetSystemMetrics(SM_CXSCREEN)),
                        int(finger->cursor.y * ::GetSystemMetrics(SM_CYSCREEN)));
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

