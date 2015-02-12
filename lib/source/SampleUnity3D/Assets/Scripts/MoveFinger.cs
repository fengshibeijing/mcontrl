using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Sharpnow;
using System.Runtime.InteropServices;
using System.Threading;
using UnityEngine;
using System.Collections;

public class MoveFinger : MonoBehaviour {

    //指尖距离的放大倍数
    public float power = 10f;

    public GameObject[] fingerPrefab;
	
	// Update is called once per frame
	void Update () {
        //连接设备
        SDK.RetrieveFrame(0);

        //获取帧信息
        IntPtr getFrameInfoPtr = SDK.GetFrameInfo();
        Frame frame = (Frame)Marshal.PtrToStructure(getFrameInfoPtr, typeof(Frame));
        if(frame.updated){

            for (int i = 0; i < fingerPrefab.Length; i++ )
            {
                if (i<frame.finger_number)
                {
                    fingerPrefab[i].gameObject.SetActive(true);
                }
                else
                {
                    fingerPrefab[i].gameObject.SetActive(false);
                }
            }

            //遍历每个手
            for (int i = 0; i < frame.hand_number; i++)
            {
                //获取手掌信息
                IntPtr getHandInfoPtr = SDK.GetHand(i);
                if(!getHandInfoPtr.Equals(IntPtr.Zero)){
                    Hand hand = (Hand)Marshal.PtrToStructure(getHandInfoPtr, typeof(Hand));

                    //遍历每个手指
                    for (int j = hand.finger_first; j <= hand.finger_last ; j++ )
                    {
                        //获取各个手指信息
                        IntPtr getFingerInfoPtr = SDK.GetFinger(j);
                        if(!getFingerInfoPtr.Equals(IntPtr.Zero)){
                            
                            Finger finger = (Finger)Marshal.PtrToStructure(getFingerInfoPtr, typeof(Finger));

                            //获取当前手指的位置
                            UnityEngine.Vector3 fingerPos = Vector3ToUnity(finger.position);
                            
                            fingerPrefab[j].transform.position = fingerPos * power;
                        }
                    }
                }
            }

        }
	}


    //坐标转化，将微动的三维坐标转化为Unity引擎的三维坐标
    UnityEngine.Vector3 Vector3ToUnity(Sharpnow.Vector3 vec3_vid) {

        UnityEngine.Vector3 vec3 = new UnityEngine.Vector3();

        vec3.x = -vec3_vid.x;
        vec3.y = vec3_vid.z;
        vec3.z = -vec3_vid.y;

        return vec3;
    }


}
