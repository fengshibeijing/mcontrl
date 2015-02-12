/********************************************************************/
/* 版权声明：本文件提供的SharpNow SDK的版权属于天津锋时互动科技有限公司。 */
/* 本文件提供的SDK源码可能会发生更新与修改，您需承担使用本SDK的风险。     */
/* 个人或公司可以复制和使用此源码用于微动(ViD)应用程序开发。             */
/* (C) 2011-2014 Tianjin SharpNow Technology. All rights reserved.  */
/********************************************************************/

//! @file
//! 微动C接口封装

#ifndef __SHARPNOW_H__
#define __SHARPNOW_H__

#include "hid.h"
#include "vid.h"

namespace sharpnow
{
    //! 接口原型：装载指定设备的最新帧数据
    typedef bool (*Proto_RetrieveFrame)(int device);

    //! 接口原型：得到当前数据帧的状态信息
    typedef const Frame* (*Proto_GetFrameInfo)();

    //! 接口原型：得到指定手指的状态信息
    typedef const Finger* (*Proto_GetFinger)(int finger);

    //! 接口原型：得到焦点手指的状态信息
    typedef const Finger* (*Proto_GetFingerFocus)();

    //! 接口原型：得到指定手掌的状态信息
    typedef const Hand* (*Proto_GetHand)(int hand);

    //! 接口原型：得到焦点手掌的状态信息
    typedef const Hand* (*Proto_GetHandFocus)();

    //! 接口原型：模拟标准输出设备
    typedef bool (*Proto_EmulateHID)(HIDEvent event, int data);
}

#endif
