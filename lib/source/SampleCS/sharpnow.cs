using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Sharpnow;
using System.Runtime.InteropServices;
using System.Threading;
namespace SampleDLL
{
    unsafe class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                SDK.RetrieveFrame(0);
                IntPtr getFrameInfoPtr = SDK.GetFrameInfo();
                IntPtr getFingerPtr = SDK.GetFinger(0);
                IntPtr getFingerFocusPtr = SDK.GetFingerFocus();
                IntPtr getHandPtr = SDK.GetHand(0);
                IntPtr getHandFocusPtr = SDK.GetHandFocus();

                Frame frame = (Frame)Marshal.PtrToStructure(getFrameInfoPtr, typeof(Frame));
                if (frame.updated != 0)
                {

                    // Get Frame
                    Console.WriteLine("Frame Has been Updated");
                    Console.WriteLine(frame.mode.ToString());
                    Console.WriteLine(frame.blindfold);
                    Console.WriteLine(frame.finger_number);
                    Console.WriteLine(frame.nick_name.ToString());
                    if (frame.blindfold > 2)
                    {
                        break;
                    }

                    
                    // Get Finger
                    if (!getFingerFocusPtr.Equals(IntPtr.Zero))
                    {
                        Finger fingerFocused = (Finger)Marshal.PtrToStructure(getFingerFocusPtr, typeof(Finger));
                        Console.WriteLine("Got Finger");
                        Console.WriteLine("Finger Order Id : " + fingerFocused.order_id);
                        Console.WriteLine(fingerFocused.position.x + " , " + fingerFocused.position.y + " , " + fingerFocused.position.z + "\n");
                    }
                    /*
                     // Get Hand
                    if (!getHandFocusPtr.Equals(IntPtr.Zero))
                    {
                        Sharpnow.Hand handFocused = (Hand)Marshal.PtrToStructure(getHandFocusPtr, typeof(Hand));
                        Console.WriteLine("Got Hand\n");
                        Console.WriteLine("Fingers show on this hand: " + handFocused.finger_number + " \n");
                        Console.WriteLine(handFocused.position.x + " , " + handFocused.position.y + " , " + handFocused.position.z + "\n");
                    }
                    */
                }

            }
        }

    }

}
