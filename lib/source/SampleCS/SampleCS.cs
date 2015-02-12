using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
/**** Add this line first ****/
using System.Runtime.InteropServices;
/**** Add this line first ****/
namespace Sharpnow
{

    unsafe public class SDK
    {
        // -------------调用DLL 中的方法

        [DllImport("sharpnow.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool EmulateHID(HIDEvent hidEvent, int data);          //! 模拟标准输出设备
        [DllImport("sharpnow.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool RetrieveFrame(int device);      //! 获取指定的设备的最新帧数据
        [DllImport("sharpnow.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFrameInfo();     //! Return Frame*       //! 得到帧状态        
        [DllImport("sharpnow.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFinger(int finger);                      //! 得到指定手指状态       
        [DllImport("sharpnow.dll")]
        public static extern IntPtr GetFingerFocus();   //! Return Finger*      //! 得到手指焦点状态       
        [DllImport("sharpnow.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetHand(int hand);                        //! 得到指定手掌状态
        [DllImport("sharpnow.dll")]
        public static extern IntPtr GetHandFocus();   //! Return Hand*        //! 得到手掌焦点状态
    }

    // -------------vid Part
    //! 类：手指目标
    unsafe public struct Finger
    {
        public int order_id;       //!< 序号ID
        public int track_id;       //!< 跟踪ID
        public int hand;           //!< 对应手部分组号


        public byte contact;        //!< 是否接触
        public byte poke;           //!< 是否有指戳动作
        public byte tap;            //!< 是否有向下点击动作
        public int stop;           //!< 静止计数器

        public Vector3 position;       //!< 指尖位置
        public Vector3 velocity;       //!< 指尖速度
        public Vector3 direction;      //!< 指尖方向
        public Vector2 cursor;         //!< 标准化光标位置
        public Vector2 slide;
    }

    unsafe public struct Vector3
    {
        public float x;  //!< x轴分量
        public float y;  //!< y轴分量
        public float z;  //!< z轴分量
    }

    unsafe public struct Vector2
    {
        public float x;  //!< x轴分量
        public float y;  //!< y轴分量
    }
    //! 类：帧信息
    unsafe public struct Frame
    {
        public byte updated;
        public DeviceMode mode;               //!< 设备当前模式
        public int counter;            //!< 帧计数
        public int time;               //!< 帧时间
        public int blindfold;          //!< 遮盖计数

        public int hand_number;        //!< 手部数量
        public int finger_number;      //!< 手指数量

        public Vector2 relax_cursor;       //!< 微距标准化光标位置

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 17)]
        public char[] nick_name;
    }


    //! 类：手部目标
    unsafe public struct Hand
    {
        public int order_id;       //!< 序号ID
        public int track_id;       //!< 跟踪ID
        public HandSide side;           //!< 左右手
        public HandGesture gesture;        //!< 手部姿态
        public int gesture_counter;

        public Vector3 position;       //!< 手心位置
        public Vector3 velocity;       //!< 手心速度
        public Vector3 axis_x;         //!< 手部x轴
        public Vector3 axis_y;         //!< 手部y轴
        public Vector3 axis_z;         //!< 手部z轴
        public Vector2 cursor;         //!< 手心标准化光标位置

        public int finger_number;  //!< 属于当前手的手指个数
        public int finger_first;   //!< 属于当前手的首手指
        public int finger_last;    //!< 属于当前手的末手指
    }
    public enum DeviceMode
    {
        DM_Air,    //!< 空间模式
        DM_Touch,  //!< 触摸模式
    };
    public enum HandSide
    {
        HS_Unknown, //!< 未知
        HS_Left,    //!< 左手
        HS_Right    //!< 右手
    };
    public enum HandGesture
    {
        HG_Unknown, //!< 未知
        HG_Grip,    //!< 握拳
        HG_Point,   //!< 单手指
        HG_Gun,     //!< 手枪
        HG_Victory, //!< 胜利
        HG_Metal,   //!< 金属
        HG_Phone,   //!< 电话
        HG_Fork,    //!< 叉子
        HG_Three,   //!< 数字三
        HG_Love,    //!< 爱LOVE
        HG_Four,    //!< 数字四
        HG_Five,    //!< 数字五
    };

    // -------------hid Part 
    // -----------------------------------------------------------------
    //! 枚举：HID事件
    public enum HIDEvent
    {
        // 鼠标事件
        Mouse_MoveX,        //!< X位置
        Mouse_MoveY,        //!< Y位置
        Mouse_Wheel,        //!< 滚轮
        Mouse_ButtonDown,   //!< 按键按下
        Mouse_ButtonUp,     //!< 按键抬起
        Mouse_Flush,        //!< 刷新

        // 键盘事件
        Keyboard_Down,      //!< 按下按键（可见字符）
        Keyboard_Up,        //!< 抬起按键（可见字符）
        Keyboard_DownEx,    //!< 按下按键（特殊功能）
        Keyboard_UpEx,      //!< 抬起按键（特殊功能）
        Keyboard_Flush,     //!< 刷新

        // 游戏杆事件
        Joystick_X,         //!< X轴
        Joystick_Y,         //!< Y轴
        Joystick_Z,         //!< Z轴
        Joystick_RX,        //!< X滚动
        Joystick_RY,        //!< Y滚动
        Joystick_RZ,        //!< Z滚动
        Joystick_Slider,    //!< 滑动
        Joystick_Dial,      //!< 拨号
        Joystick_Hat,       //!< 瞄准
        Joystick_ButtonDown,//!< 按键按下
        Joystick_ButtonUp,  //!< 按键抬起
        Joystick_Flush,     //!< 刷新

        // 游戏杆2事件
        Joystick2_X,        //!< X轴
        Joystick2_Y,        //!< Y轴
        Joystick2_Z,        //!< Z轴
        Joystick2_RX,       //!< X滚动
        Joystick2_RY,       //!< Y滚动
        Joystick2_RZ,       //!< Z滚动
        Joystick2_Slider,   //!< 滑动
        Joystick2_Dial,     //!< 拨号
        Joystick2_Hat,      //!< 瞄准
        Joystick2_ButtonDown,//!< 按键按下
        Joystick2_ButtonUp, //!< 按键抬起
        Joystick2_Flush,    //!< 刷新

        // 多点触摸屏事件
        Touch_ContactID,    //!< 接触点ID
        Touch_X,            //!< X位置
        Touch_Y,            //!< Y位置
        Touch_Height,       //!< 高度
        Touch_Flush,        //!< 刷新
    };

    // -----------------------------------------------------------------
    //! 枚举：特殊按键
    public enum KeyEx
    {
        KeyEx_CtrL,
        KeyEx_ShiftL,
        KeyEx_AltL,
        KeyEx_WinL,
        KeyEx_CtrR,
        KeyEx_ShiftR,
        KeyEx_AltR,
        KeyEx_WinR,

        KeyEx_Left,
        KeyEx_Right,
        KeyEx_Up,
        KeyEx_Down,
        KeyEx_Home,
        KeyEx_End,
        KeyEx_PageUp,
        KeyEx_PageDown,
        KeyEx_Insert,
        KeyEx_Delete,
        KeyEx_Esc,
        KeyEx_Backspace,
        KeyEx_Enter,
        KeyEx_Tab,
        KeyEx_Space,

        KeyEx_F1,
        KeyEx_F2,
        KeyEx_F3,
        KeyEx_F4,
        KeyEx_F5,
        KeyEx_F6,
        KeyEx_F7,
        KeyEx_F8,
        KeyEx_F9,
        KeyEx_F10,
        KeyEx_F11,
        KeyEx_F12,

        KeyEx_Pad0,
        KeyEx_Pad1,
        KeyEx_Pad2,
        KeyEx_Pad3,
        KeyEx_Pad4,
        KeyEx_Pad5,
        KeyEx_Pad6,
        KeyEx_Pad7,
        KeyEx_Pad8,
        KeyEx_Pad9,
        KeyEx_PadDot,
        KeyEx_PadAdd,
        KeyEx_PadSub,
        KeyEx_PadMul,
        KeyEx_PadDiv,
        KeyEx_PadEnter,
    };
}


