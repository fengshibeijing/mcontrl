
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

class Sharpnow
{
	public interface SDK extends Library
	{
		SDK sdk = (SDK)Native.loadLibrary("sharpnow.dll",SDK.class);
		/***DLL 函数部分***/
		boolean EmulateHID(HIDEvent event, int data);
		boolean RetrieveFrame(int device);
		com.sun.jna.Pointer GetFrameInfo();  //return Frame*
		com.sun.jna.Pointer GetFinger(int finger);	//return Finger*
		com.sun.jna.Pointer GetFingerFocus();	//return Finger*
		com.sun.jna.Pointer GetHand(int hand);	//return Hand*
		com.sun.jna.Pointer GetHandFocus();		//return Hand*
		
		/***从DLL返回的指针生成JAVA的结构体类对象***/
		static Frame createFrameFromPointer(Pointer pointer,int offset)
		{
			
			Frame frame = new Frame();
			frame.nick_name = new char[17];
			Byte contactByte = pointer.getByte(offset);
			if((int)contactByte == 0)
				frame.updated = false;
			else
				frame.updated = true;
			offset += 1;
			int modeIndex = pointer.getInt(offset);
			if(modeIndex == 0)
			{
				frame.mode = DeviceMode.DM_Air;
			}
			else if(modeIndex == 1)
			{
				frame.mode = DeviceMode.DM_Touch;
			}
			offset += 4;
			frame.counter = pointer.getInt(offset);
			offset += 4;
			frame.time = pointer.getInt(offset);
			offset += 4;
			frame.blindfold = pointer.getInt(offset);
			offset += 4;
			frame.hand_number = pointer.getInt(offset);
			offset += 4;
			frame.finger_number = pointer.getInt(offset);
			offset += 4;
			Vector2 cursorVector = new Vector2();
			cursorVector.x = pointer.getFloat(offset);
			offset += 4;
			cursorVector.y = pointer.getFloat(offset);
			frame.relax_cursor = cursorVector;
			offset += 4;
			frame.nick_name = pointer.getCharArray(offset, 17);
			return frame;
		}
		static Finger createFingerFromPointer(Pointer pointer,int offset)
		{
			Finger finger = new Finger();
			finger.order_id = pointer.getInt(offset);
			offset += 4;
			finger.track_id = pointer.getInt(offset);
			offset += 4;
			finger.hand = pointer.getInt(offset);
			offset += 4;
			Byte contactByte = pointer.getByte(offset);
			if((int)contactByte == 0)
				finger.contact = false;
			else
				finger.contact = true;
			offset += 1;
			Byte pokeByte = pointer.getByte(offset);
			if((int)pokeByte == 0)
				finger.poke = false;
			else
				finger.poke = true;
			offset += 1;
			Byte tapByte = pointer.getByte(offset);
			if((int)tapByte == 0)
				finger.tap = false;
			else
				finger.tap = true;
			offset += 1;
			offset += 1;
			finger.stop = pointer.getInt(offset);
			offset += 4;
			Vector3 positionVector = new Vector3();
			positionVector.x = pointer.getFloat(offset);
			offset += 4;
			positionVector.y = pointer.getFloat(offset);
			offset += 4;
			positionVector.z = pointer.getFloat(offset);
			offset += 4;
			finger.position = positionVector;
			Vector3 velocityVector = new Vector3();
			velocityVector.x = pointer.getFloat(offset);
			offset += 4;
			velocityVector.y = pointer.getFloat(offset);
			offset += 4;
			velocityVector.z = pointer.getFloat(offset);
			offset += 4;
			finger.velocity = velocityVector;
			Vector3 directionVector = new Vector3();
			directionVector.x = pointer.getFloat(offset);
			offset += 4;
			directionVector.y = pointer.getFloat(offset);
			offset += 4;
			directionVector.z = pointer.getFloat(offset);
			offset += 4;
			finger.direction = directionVector;
			Vector2 cursorVector = new Vector2();
			cursorVector.x = pointer.getFloat(offset);
			offset += 4;
			cursorVector.y = pointer.getFloat(offset);
			offset += 4;
			finger.cursor = cursorVector;
			Vector2 slideVector = new Vector2();
			slideVector.x = pointer.getFloat(offset);
			offset += 4;
			slideVector.y = pointer.getFloat(offset);
			offset += 4;
			finger.slide = slideVector;
			return finger;
		}
		static Hand createHandFromPointer(Pointer pointer, int offset)
		{
			Hand hand = new Hand();
			hand.order_id = pointer.getInt(offset);
			offset += 4;
			hand.track_id = pointer.getInt(offset);
			offset += 4;
			int sideIndex = pointer.getInt(offset);
			if(sideIndex == 0)
			{
				hand.side = HandSide.HS_Unknown;
			}
			else if(sideIndex == 1)
			{
				hand.side = HandSide.HS_Left;
			}
			else if(sideIndex == 2)
			{
				hand.side = HandSide.HS_Right;
			}
			offset += 4;
			int gestureIndex = pointer.getInt(offset);
			if(gestureIndex == 0)
				hand.gesture = HandGesture.HG_Unknown;
			else if(gestureIndex == 1)
				hand.gesture = HandGesture.HG_Grip;
			else if(gestureIndex == 2)
				hand.gesture = HandGesture.HG_Point;
			else if(gestureIndex == 3)
				hand.gesture = HandGesture.HG_Gun;
			else if(gestureIndex == 4)
				hand.gesture = HandGesture.HG_Victory;
			else if(gestureIndex == 5)
				hand.gesture = HandGesture.HG_Metal;
			else if(gestureIndex == 6)
				hand.gesture = HandGesture.HG_Phone;
			else if(gestureIndex == 7)
				hand.gesture = HandGesture.HG_Fork;
			else if(gestureIndex == 8)
				hand.gesture = HandGesture.HG_Three;
			else if(gestureIndex == 9)
				hand.gesture = HandGesture.HG_Love;
			else if(gestureIndex == 10)
				hand.gesture = HandGesture.HG_Four;
			else if(gestureIndex == 11)
				hand.gesture = HandGesture.HG_Five;
			offset += 4;
			hand.gesture_counter = pointer.getInt(offset);
			offset += 4;
			Vector3 positionVector = new Vector3();
			positionVector.x = pointer.getFloat(offset);
			offset += 4;
			positionVector.y = pointer.getFloat(offset);
			offset += 4;
			positionVector.z = pointer.getFloat(offset);
			offset += 4;
			hand.position = positionVector;
			Vector3 velocityVector = new Vector3();
			velocityVector.x = pointer.getFloat(offset);
			offset += 4;
			velocityVector.y = pointer.getFloat(offset);
			offset += 4;
			velocityVector.z = pointer.getFloat(offset);
			offset += 4;
			hand.velocity = velocityVector;
			Vector3 axixXVector = new Vector3();
			axixXVector.x = pointer.getFloat(offset);
			offset += 4;
			axixXVector.y = pointer.getFloat(offset);
			offset += 4;
			axixXVector.z = pointer.getFloat(offset);
			offset += 4;
			hand.axis_x = axixXVector;
			Vector3 axixYVector = new Vector3();
			axixYVector.x = pointer.getFloat(offset);
			offset += 4;
			axixYVector.y = pointer.getFloat(offset);
			offset += 4;
			axixYVector.z = pointer.getFloat(offset);
			offset += 4;
			hand.axis_y = axixYVector;
			Vector3 axixZVector = new Vector3();
			axixZVector.x = pointer.getFloat(offset);
			offset += 4;
			axixZVector.y = pointer.getFloat(offset);
			offset += 4;
			axixZVector.z = pointer.getFloat(offset);
			offset += 4;
			hand.axis_z = axixZVector;
			Vector2 cursorVector = new Vector2();
			cursorVector.x = pointer.getFloat(offset);
			offset += 4;
			cursorVector.y = pointer.getFloat(offset);
			offset += 4;
			hand.cursor = cursorVector;
			hand.finger_number = pointer.getInt(offset);
			offset += 4;
			hand.finger_first = pointer.getInt(offset);
			offset += 4;
			hand.finger_last = pointer.getInt(offset);
			//offset += 4;
			return hand;
		}
	}
		/****结构体类部分****/
		public static class Frame
		{
			public boolean 			   updated;
	        public DeviceMode          mode;               //!< 设备当前模式
	        public int                 counter;            //!< 帧计数
	        public int                 time;               //!< 帧时间
	        public int                 blindfold;          //!< 遮盖计数
	
	        public int                 hand_number;        //!< 手部数量
	        public int                 finger_number;      //!< 手指数量
	
	        public Vector2             relax_cursor;       //!< 微距标准化光标位置
	        public char           	   nick_name[];
		}
	    // -----------------------------------------------------------------
	    //! 类：手指目标
		public static class Finger
	    {
	        public int                 order_id;       //!< 序号ID
	        public int                 track_id;       //!< 跟踪ID
	        public int                 hand;           //!< 对应手部分组号
	
	        public boolean             contact;        //!< 是否接触
	        public boolean             poke;           //!< 是否有指戳动作
	        public boolean		       tap;           //!< 是否有向下点击动作
	        public int                 stop;           //!< 静止计数器
	
	        public Vector3             position;       //!< 指尖位置
	        public Vector3             velocity;       //!< 指尖速度
	        public Vector3             direction;      //!< 指尖方向
	        public Vector2             cursor;         //!< 标准化光标位置
	        public Vector2             slide;
	    }
	    // -----------------------------------------------------------------
	    //! 类：手部目标
		public static class Hand
	    {
			public int          	   order_id;       //!< 序号ID
			public int                 track_id;       //!< 跟踪ID
			public HandSide            side;           //!< 左右手
			public HandGesture         gesture;        //!< 手部姿态
			public int				   gesture_counter;
			public Vector3             position;       //!< 手心位置
			public Vector3             velocity;       //!< 手心速度
			public Vector3             axis_x;         //!< 手部x轴
			public Vector3             axis_y;         //!< 手部y轴
			public Vector3             axis_z;         //!< 手部z轴
			public Vector2             cursor;         //!< 手心标准化光标位置
	
			public int                 finger_number;  //!< 属于当前手的手指个数
			public int                 finger_first;   //!< 属于当前手的首手指
			public int                 finger_last;    //!< 属于当前手的末手指
	    } 
		public static class Vector2
		{
			public float   x;  //!< x轴分量
			public float   y;  //!< y轴分量
		}
		
		public static class Vector3
		{
			public float   x;  //!< x轴分量
			public float   y;  //!< y轴分量
			public float   z;  //!< z轴分量
		}
	    // -----------------------------------------------------------------
	    //! 枚举：手部角色
	    public enum HandSide
	    {
	        HS_Unknown, //!< 未知
	        HS_Left,    //!< 左手
	        HS_Right    //!< 右手
	    };
	    // -----------------------------------------------------------------
	    //! 枚举：设备模式
	    public enum DeviceMode
	    {
	        DM_Air,     //!< 空间模式
	        DM_Touch,   //!< 触摸模式
	    };
		 // ----------------------------------------------------------------
	    //! 枚举：手势类型
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
	        Touch_Status,       //!< 状态
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

