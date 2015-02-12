using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
/**** Add this line first ****/
using System.Runtime.InteropServices;
/**** Add this line first ****/
namespace Sharpnow
{

    public class SDK
    {
        // -------------调用DLL 中的方法

        [DllImport("sharpnow", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool EmulateHID(HIDEvent hidEvent, int data);          //! 模拟标准输出设备
        [DllImport("sharpnow", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool RetrieveFrame(int device);      //! 获取指定的设备的最新帧数据
        [DllImport("sharpnow", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFrameInfo();     //! Return Frame*       //! 得到帧状态        
        [DllImport("sharpnow", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFinger(int finger);                      //! 得到指定手指状态       
        [DllImport("sharpnow")]
        public static extern IntPtr GetFingerFocus();   //! Return Finger*      //! 得到手指焦点状态       
        [DllImport("sharpnow", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetHand(int hand);                        //! 得到指定手掌状态
        [DllImport("sharpnow")]
        public static extern IntPtr GetHandFocus();   //! Return Hand*        //! 得到手掌焦点状态
    }

    
    /// <summary>
    ///  类：手指目标
    /// </summary>
    public struct Finger
    {
        /// <summary>
        /// 手指序号ID
        /// </summary>
        public int order_id;       

        /// <summary>
        /// 手指跟踪ID
        /// </summary>
        public int track_id;       

        /// <summary>
        /// 对应手部组号
        /// </summary>
        public int hand;          

        /// <summary>
        /// 是否接触
        /// </summary>
        public byte contact; 

        /// <summary>
        /// 是否有指戳动作
        /// </summary>
        public byte poke; 

        /// <summary>
        /// 是否有向下点击动作
        /// </summary>
        public byte tap;   

        /// <summary>
        /// 静止计数器
        /// </summary>
        public int stop;           

        /// <summary>
        /// 指尖位置
        /// </summary>
        public Vector3 position;       

        /// <summary>
        /// 指尖速度
        /// </summary>
        public Vector3 velocity;      


        /// <summary>
        /// 指尖方向
        /// </summary>
        public Vector3 direction;   

        /// <summary>
        /// 标准化光标位置
        /// </summary>
        public Vector2 cursor;     

        /// <summary>
        /// 滑动
        /// </summary>
        public Vector2 slide;
    }

    public struct Vector3
    {
        /// <summary>
        ///x轴分量 
        /// </summary>
        public float x; 

        /// <summary>
        /// Y轴分量
        /// </summary>
        public float y; 

        /// <summary>
        /// Z轴分量
        /// </summary>
        public float z; 
    }

    public struct Vector2
    {
        /// <summary>
        /// X轴分量
        /// </summary>
        public float x;  

        /// <summary>
        /// Y轴分量
        /// </summary>
        public float y;  
    }







    /// <summary>
    /// 类：帧信息
    /// </summary>
    public struct Frame
    {
        /// <summary>
        /// 帧是否更新
        /// </summary>
        public bool updated;

        /// <summary>
        /// 当前设备模式
        /// </summary>
        public DeviceMode mode;               

        /// <summary>
        /// 帧计数
        /// </summary>
        public int counter;            

        /// <summary>
        /// 帧时间
        /// </summary>
        public int time;              

        /// <summary>
        /// 遮盖计数
        /// </summary>
        public int blindfold;          

        /// <summary>
        /// 手部数量
        /// </summary>
        public int hand_number;        

        /// <summary>
        /// 手指数量
        /// </summary>
        public int finger_number;    

        /// <summary>
        /// 微距标准化光标位置
        /// </summary>
        public Vector2 relax_cursor;    

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 17)]
        public char[] nick_name;
    }


    /// <summary>
    /// 类：手部目标
    /// </summary>
    public struct Hand
    {
        /// <summary>
        /// 手部序号ID
        /// </summary>
        public int order_id;       //!< 序号ID

        /// <summary>
        /// 手部跟踪ID
        /// </summary>
        public int track_id;       //!< 跟踪ID

        /// <summary>
        /// 左右手
        /// </summary>
        public HandSide side;           //!< 左右手

        /// <summary>
        /// 手部姿态
        /// </summary>
        public HandGesture gesture;        //!< 手部姿态

        /// <summary>
        /// 手势计数器
        /// </summary>
        public int gesture_counter;

        /// <summary>
        /// 手心位置
        /// </summary>
        public Vector3 position;       //!< 手心位置

        /// <summary>
        /// 手心速度
        /// </summary>
        public Vector3 velocity;    

        /// <summary>
        /// 手部X轴，将设备正确摆放时，X轴指向设备左方
        /// </summary>
        public Vector3 axis_x;       

        /// <summary>
        /// 手部Y轴，将设备正确摆放时，Y轴指向玩家
        /// </summary>
        public Vector3 axis_y;         

        /// <summary>
        /// 手部Z轴。将设备正确摆放时，Z轴指向上方
        /// </summary>
        public Vector3 axis_z;        

        /// <summary>
        /// 手心标准化光标位置
        /// </summary>
        public Vector2 cursor;  

        /// <summary>
        /// 属于当前手的手指个数
        /// </summary>
        public int finger_number;  

        /// <summary>
        /// 属于当前手的第一根手指
        /// </summary>
        public int finger_first; 

        /// <summary>
        ///属于当前手的最后一根手指
        /// </summary>
        public int finger_last;    
    }

    /// <summary>
    /// 设备工作模式
    /// </summary>
    public enum DeviceMode
    {
        DM_Air,    //!< 空间模式
        DM_Touch,  //!< 触摸模式
    };

    /// <summary>
    /// 手所在的一侧，左右或者未知
    /// </summary>
    public enum HandSide
    {
        HS_Unknown, //!< 未知
        HS_Left,    //!< 左手
        HS_Right    //!< 右手
    };

    /// <summary>
    /// 手势
    /// </summary>
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


