
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.win32.*;
import com.sun.jna.*;

public class SampleJava
{
	public static void main(String[] args)
	{

		while(true)
		{
			Sharpnow.SDK.sdk.RetrieveFrame(0);
			com.sun.jna.Pointer getFrameInfoPointer = Sharpnow.SDK.sdk.GetFrameInfo();
			com.sun.jna.Pointer getFingerPointer = Sharpnow.SDK.sdk.GetFinger(0);
			com.sun.jna.Pointer getFingerFocusPointer = Sharpnow.SDK.sdk.GetFingerFocus();
			com.sun.jna.Pointer getHandPointer = Sharpnow.SDK.sdk.GetHand(0);
			com.sun.jna.Pointer getHandFocusPointer = Sharpnow.SDK.sdk.GetHandFocus();
			

			Sharpnow.Frame frame = Sharpnow.SDK.createFrameFromPointer(getFrameInfoPointer, 0);
			if(frame.updated ==  true)
			{
				 // Get Frame
				System.out.printf("Frame Has been Updated\n");
				System.out.printf(frame.mode.toString() +"\n");
				System.out.printf(frame.blindfold +"\n");
				System.out.printf(frame.finger_number +"\n");
				System.out.printf(frame.nick_name.toString() +"\n");
				if(frame.blindfold > 2)
					break;
				
				/* // Get Finger
				if(getFingerFocusPointer != null)
				{
					Sharpnow.Finger fingerFocused = Sharpnow.SDK.createFingerFromPointer(getFingerFocusPointer, 0);
					System.out.printf("Got Finger\n");
					System.out.printf("Finger Order Id : "+fingerFocused.order_id+"\n");
					System.out.printf(fingerFocused.position.x+" , " +fingerFocused.position.y+" , "+fingerFocused.position.z+"\n");
				}
				*/
				
				/* // Get Hand
				if(getHandFocusPointer != null)
				{
					Sharpnow.Hand handFocused = Sharpnow.SDK.createHandFromPointer(getHandFocusPointer, 0);
					System.out.printf("Got Hand\n");
					System.out.printf("Fingers show on this hand: " + handFocused.finger_number + " \n");
					System.out.printf(handFocused.position.x+" , " +handFocused.position.y+" , "+handFocused.position.z+"\n");
				}	
				*/			
			}

		}
		
	}
}

