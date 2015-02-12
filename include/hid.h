/********************************************************************/
/* 版权声明：本文件提供的SharpNow SDK的版权属于天津锋时互动科技有限公司。 */
/* 本文件提供的SDK源码可能会发生更新与修改，您需承担使用本SDK的风险。     */
/* 个人或公司可以复制和使用此源码用于微动(ViD)应用程序开发。             */
/* (C) 2011-2014 Tianjin SharpNow Technology. All rights reserved.  */
/********************************************************************/

//! @file
//! 操作虚拟设备相关的枚举变量

#ifndef __SHARPNOW_HID_H__
#define __SHARPNOW_HID_H__

namespace sharpnow
{
    //! @enum HandSide
    //! @brief 枚举常量：HID事件
    enum HIDEvent
    {
        Mouse_MoveX,        //!< 鼠标 X位置，取值取值范围 0~32767
        Mouse_MoveY,        //!< 鼠标 Y位置，取值范围 0~32767
        Mouse_Wheel,        //!< 鼠标 滚轮，取值范围 -127~127
        Mouse_ButtonDown,   //!< 鼠标 按键按下，取值范围 0~4
        Mouse_ButtonUp,     //!< 鼠标 按键抬起，取值范围 0~4
        Mouse_Flush,        //!< 鼠标 刷新

        Keyboard_Down,      //!< 键盘 按下按键（可见字符）
        Keyboard_Up,        //!< 键盘 抬起按键（可见字符）
        Keyboard_DownEx,    //!< 键盘 按下按键（特殊功能）
        Keyboard_UpEx,      //!< 键盘 抬起按键（特殊功能）
        Keyboard_Flush,     //!< 键盘 刷新

        Joystick_X,         //!< 游戏杆1 X轴，取值范围 -32767~32767
        Joystick_Y,         //!< 游戏杆1 Y轴，取值范围 -32767~32767
        Joystick_Z,         //!< 游戏杆1 Z轴，取值范围 -32767~32767
        Joystick_RX,        //!< 游戏杆1 X滚动，取值范围 -32767~32767
        Joystick_RY,        //!< 游戏杆1 Y滚动，取值范围 -32767~32767
        Joystick_RZ,        //!< 游戏杆1 Z滚动，取值范围 -32767~32767
        Joystick_Slider,    //!< 游戏杆1 滑动，取值范围 -32767~32767
        Joystick_Dial,      //!< 游戏杆1 拨号，取值范围 -32767~32767
        Joystick_Hat,       //!< 游戏杆1 瞄准键，取值范围 0~8
        Joystick_ButtonDown,//!< 游戏杆1 按键按下，取值范围 0~15
        Joystick_ButtonUp,  //!< 游戏杆1 按键抬起，取值范围 0~15
        Joystick_Flush,     //!< 游戏杆1 刷新

        Joystick2_X,        //!< 游戏杆2 X轴，取值范围 -32767~32767
        Joystick2_Y,        //!< 游戏杆2 Y轴，取值范围 -32767~32767
        Joystick2_Z,        //!< 游戏杆2 Z轴，取值范围 -32767~32767
        Joystick2_RX,       //!< 游戏杆2 X滚动，取值范围 -32767~32767
        Joystick2_RY,       //!< 游戏杆2 Y滚动，取值范围 -32767~32767
        Joystick2_RZ,       //!< 游戏杆2 Z滚动，取值范围 -32767~32767
        Joystick2_Slider,   //!< 游戏杆2 滑动，取值范围 -32767~32767
        Joystick2_Dial,     //!< 游戏杆2 拨号，取值范围 -32767~32767
        Joystick2_Hat,      //!< 游戏杆2 瞄准键，取值范围 0~8
        Joystick2_ButtonDown,//!< 游戏杆2 按键按下，取值范围 0~15
        Joystick2_ButtonUp, //!< 游戏杆2 按键抬起，取值范围 0~15
        Joystick2_Flush,    //!< 游戏杆2 刷新

        Touch_ContactID,    //!< 触摸屏 接触点ID，取值范围 0~9
        Touch_X,            //!< 触摸屏 X位置，取值范围 0~32767
        Touch_Y,            //!< 触摸屏 Y位置，取值范围 0~32767
        Touch_Height,       //!< 触摸屏 高度，取值范围 0~32767
        Touch_Flush,        //!< 触摸屏 刷新
    };

    //! @enum KeyEx
    //! @brief 枚举常量：特殊按键
    enum KeyEx
    {
        KeyEx_CtrL,         //!< 左control
        KeyEx_ShiftL,       //!< 左shift
        KeyEx_AltL,         //!< 左alter
        KeyEx_WinL,         //!< 左win
        KeyEx_CtrR,         //!< 右control
        KeyEx_ShiftR,       //!< 右shift
        KeyEx_AltR,         //!< 右alter
        KeyEx_WinR,         //!< 右win

        KeyEx_Left,         //!< 向左
        KeyEx_Right,        //!< 向右
        KeyEx_Up,           //!< 向上
        KeyEx_Down,         //!< 向下
        KeyEx_Home,         //!< 行首
        KeyEx_End,          //!< 行尾
        KeyEx_PageUp,       //!< 向前翻页
        KeyEx_PageDown,     //!< 向后翻页
        KeyEx_Insert,       //!< 插入
        KeyEx_Delete,       //!< 删除
        KeyEx_Esc,          //!< 退出
        KeyEx_Backspace,    //!< 回退
        KeyEx_Enter,        //!< 回车
        KeyEx_Tab,          //!< 制表符
        KeyEx_Space,        //!< 空格

        KeyEx_F1,           //!< F1
        KeyEx_F2,           //!< F2
        KeyEx_F3,           //!< F3
        KeyEx_F4,           //!< F4
        KeyEx_F5,           //!< F5
        KeyEx_F6,           //!< F6
        KeyEx_F7,           //!< F7
        KeyEx_F8,           //!< F8
        KeyEx_F9,           //!< F9
        KeyEx_F10,          //!< F10
        KeyEx_F11,          //!< F11
        KeyEx_F12,          //!< F12

        KeyEx_Pad0,         //!< 数字键盘 0
        KeyEx_Pad1,         //!< 数字键盘 1
        KeyEx_Pad2,         //!< 数字键盘 2
        KeyEx_Pad3,         //!< 数字键盘 3
        KeyEx_Pad4,         //!< 数字键盘 4
        KeyEx_Pad5,         //!< 数字键盘 5
        KeyEx_Pad6,         //!< 数字键盘 6
        KeyEx_Pad7,         //!< 数字键盘 7
        KeyEx_Pad8,         //!< 数字键盘 8
        KeyEx_Pad9,         //!< 数字键盘 9
        KeyEx_PadDot,       //!< 数字键盘 小数点
        KeyEx_PadAdd,       //!< 数字键盘 加
        KeyEx_PadSub,       //!< 数字键盘 减
        KeyEx_PadMul,       //!< 数字键盘 乘
        KeyEx_PadDiv,       //!< 数字键盘 除
        KeyEx_PadEnter,     //!< 数字键盘 回车
    };
}

#endif
