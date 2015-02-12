/********************************************************************/
/* 版权声明：本文件提供的SharpNow SDK的版权属于天津锋时互动科技有限公司。 */
/* 本文件提供的SDK源码可能会发生更新与修改，您需承担使用本SDK的风险。     */
/* 个人或公司可以复制和使用此源码用于微动(ViD)应用程序开发。             */
/* (C) 2011-2014 Tianjin SharpNow Technology. All rights reserved.  */
/********************************************************************/

//! @file
//! 微动C++接口封装

#ifndef __SHARPNOW_HPP__
#define __SHARPNOW_HPP__

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN 1
#endif
#include <Windows.h>
#include "sharpnow.h"

namespace sharpnow
{
    //! @brief SDK面向对象封装
    //! 
    class SDK
    {
    public:
        SDK() { mIsValid = false; mDLL = NULL; }
        ~SDK() { if (mDLL) FreeLibrary(mDLL); }

        //! @brief 装载指定设备的最新帧数据
        //! @param[in] device 设备编号
        //! @return 装载是否成功，若失败表示设备尚未连接。
        //! @note 目前最多允许两台设备连接相同主机，device的取值仅可为 0 或 1 。
        //!
        //! 微动允许多台设备连接于同一台主机上。 \n
        //! 使用device参数可选择指定序号的设备，并加载该设备最新数据帧。 \n
        inline bool RetrieveFrame(int device)       { return mIsValid && mRetrieveFrame(device);    }

        //! @brief 得到当前数据帧的状态信息
        //! @return 数据帧状态信息的结构体指针
        //!
        //! 帧状态信息中包括设备工作状态等，请参考 Frame 结构体。 \n
        inline const Frame*  GetFrameInfo()         { return mIsValid ? mGetFrameInfo() : NULL;     }

        //! @brief 得到指定手指的状态信息
        //! @param[in] finger 指定手指的序号 ( order_id )
        //! @return 手指信息的结构体指针
        //!
        //! 手指状态信息包括指尖的定位与跟踪状态，请参考 Finger 结构体。 \n
        inline const Finger* GetFinger(int finger)  { return mIsValid ? mGetFinger(finger) : NULL;  }

        //! @brief 得到焦点手指的状态信息
        //! @return 焦点手指信息的结构体指针
        //!
        //! 当手部处于设备视野内，一旦有手指目标被检测到，设备将尽可能保持对其中 \n
        //! 一个手指（焦点）的跟踪，避免目标发生切换。该目标通常可用于光标控制。 \n \n
        //! 手指状态信息包括指尖的定位与跟踪状态，请参考 Finger 结构体。 \n
        inline const Finger* GetFingerFocus()       { return mIsValid ? mGetFingerFocus() : NULL;   }

        //! @brief 得到指定手掌的状态信息
        //! @param[in] hand 指定手掌的序号 ( order_id )
        //! @return 手掌信息的结构体指针
        //!
        //! 手掌状态信息包括掌心的定位与姿态，请参考 Hand 结构体。 \n
        inline const Hand*   GetHand(int hand)      { return mIsValid ? mGetHand(hand) : NULL;      }

        //! @brief 得到焦点手掌的状态信息
        //! @return 焦点手掌信息的结构体指针
        //!
        //! 当手部处于设备视野内，一旦有手掌目标被检测到，设备将尽可能保持对其中 \n
        //! 一个手掌（焦点）的跟踪，避免目标发生切换。 \n \n
        //! 手掌状态信息包括掌心的定位与姿态，请参考 Hand 结构体。 \n
        inline const Hand*   GetHandFocus()         { return mIsValid ? mGetHandFocus() : NULL;     }

        //! @brief 模拟标准输出设备
        //! @param event 模拟事件的枚举类型
        //! @param data 模拟事件的数据信息
        //! @return 是否成功发送模拟事件
        //!
        //! 微动可以对键盘、鼠标、游戏杆与多点触摸屏进行驱动级模拟。模拟动作通过 \n
        //! 连续调用本接口实现，具体方式与注意事项请参考相关文档。 \n \n
        inline bool EmulateHID(HIDEvent event, int data) { return mIsValid ? mEmulateHID(event, data) : false; }

        //! @brief 在指定路径中加载动态链接库
        //! @param path 动态链接库的路径名
        //! @return 是否成功加载动态链接库
        inline bool LoadInPath(const char* path)
        {
            if (mIsValid) return true;
            char name[MAX_PATH];
            strcpy_s(name, path);
            if (strlen(path) > 0) strcat_s(name, "/");
#ifdef _DEBUG
            strcat_s(name, "sharpnowD.dll");
#else
            strcat_s(name, "sharpnow.dll");
#endif
            mDLL = LoadLibraryA(name);
            if (!mDLL) return false;

            mRetrieveFrame   = (Proto_RetrieveFrame)GetProcAddress(mDLL, "RetrieveFrame");
            mGetFrameInfo   = (Proto_GetFrameInfo)GetProcAddress(mDLL, "GetFrameInfo");
            mGetFinger      = (Proto_GetFinger)GetProcAddress(mDLL, "GetFinger");
            mGetFingerFocus = (Proto_GetFingerFocus)GetProcAddress(mDLL, "GetFingerFocus");
            mGetHand        = (Proto_GetHand)GetProcAddress(mDLL, "GetHand");
            mGetHandFocus   = (Proto_GetHandFocus)GetProcAddress(mDLL, "GetHandFocus");
            mEmulateHID     = (Proto_EmulateHID)GetProcAddress(mDLL, "EmulateHID");
            mIsValid = mRetrieveFrame && mEmulateHID && mGetFinger && mGetFingerFocus && mGetHand && mGetHandFocus;
            return mIsValid;
        }
    private:
        bool                    mIsValid;           //!< DLL是否成功加载
        HMODULE                 mDLL;               //!< 动态链接库
        Proto_EmulateHID        mEmulateHID;        //!< 模拟设备
        Proto_RetrieveFrame     mRetrieveFrame;     //!< 加载最新帧
        Proto_GetFrameInfo      mGetFrameInfo;      //!< 获取帧信息
        Proto_GetFinger         mGetFinger;         //!< 获取手指
        Proto_GetFingerFocus    mGetFingerFocus;    //!< 获取手指焦点
        Proto_GetHand           mGetHand;           //!< 获取手部
        Proto_GetHandFocus      mGetHandFocus;      //!< 获取手部焦点
    };
};

#endif
