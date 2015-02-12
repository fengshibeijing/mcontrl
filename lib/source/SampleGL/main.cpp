#define FREEGLUT_STATIC
#include "../../include/sharpnow.hpp"
#include "GL/freeglut.h"
#include <list>
#include <iostream>

#define MAX_FNUM 10
#define MAX_HNUM 2

sharpnow::SDK sdk;
sharpnow::Vector3 finger_top[MAX_FNUM], finger_dir[MAX_FNUM];
sharpnow::Vector3 hand_center[MAX_HNUM], hand_norm[MAX_HNUM];
std::list<sharpnow::Vector3> trajectory[MAX_FNUM];
int traj_cnt[MAX_FNUM];

int window_width = 800;
int window_height = 450;
int window = 0;
int finger_num = 0, hand_num = 0;
float cam_z = 0.25f;

// 绘制当前场景，使用球体表示指尖空间位置，使用直线表示指尖朝向
void Draw()
{
    glColor3d(0,0,0.7);
    glLineWidth(1);
    glPushMatrix();
    glTranslated(0,0,1.0);
    glutWireSphere(2.0,128,64);
    glPopMatrix();

    glColor3d(0.3,0.3,0.3);
    glPushMatrix();
    glScaled(0.6,0.6,0.005);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();

    glLineWidth(3);
    for (int i = 0; i < finger_num; ++i)
    {
        sharpnow::Vector3 p = finger_top[i], d = finger_dir[i];
        glColor3d(0.8,0.8,0.8);
        glPushMatrix();
        glTranslatef(p.x, p.y, p.z);
        glutSolidSphere(0.003, 8, 8);
        glPopMatrix();

        glColor3d(0.4,0.4,0.8);
        glBegin(GL_LINES);
        glVertex3d(p.x, p.y, p.z);
        glVertex3d(p.x - d.x * 0.04, p.y - d.y * 0.04, p.z - d.z * 0.04);
        glEnd();
    }

    //for (int i = 0; i < hand_num; ++i)
    //{
    //    sharpnow::Vector3 p = hand_center[i], d = hand_norm[i];
    //    glColor3d(0.9,0.9,0.9);
    //    glPushMatrix();
    //    glTranslatef(p.x, p.y, p.z);
    //    glutSolidSphere(0.004, 8, 8);
    //    glPopMatrix();

    //    glColor3d(0.8,0.4,0.4);
    //    glBegin(GL_LINES);
    //    glVertex3d(p.x, p.y, p.z);
    //    glVertex3d(p.x + d.x * 0.02, p.y + d.y * 0.02, p.z + d.z * 0.02);
    //    glEnd();
    //}

    // 绘制各指尖轨迹
    glLineWidth(6);
    for (int i = 0; i < MAX_FNUM; ++i) if (trajectory[i].size() > 1)
    {
        std::list<sharpnow::Vector3>::const_reverse_iterator t = trajectory[i].rbegin(), p = t;
        ++p;
        double r = 0, g = 0, b = 0;
        switch (i % 5)
        {
        case 0: r = 1; break;
        case 1: g = 1; break;
        case 2: b = 1; break;
        case 3: r = g = 0.8; break;
        case 4: g = b = 0.8; break;
        }
        for (; p != trajectory[i].rend(); ++t, ++p)
        {
            glColor3d(r, g, b);
            glBegin(GL_LINES);
            glVertex3d(t->x, t->y, t->z);
            glVertex3d(p->x, p->y, p->z);
            glEnd();
            r *= 0.95; g *= 0.95; b *= 0.95;

            // 绘制投影
            glColor3d(0.4, 0.4, 0.4);
            glBegin(GL_LINES);
            glVertex3d(t->x, t->y, 0.01);
            glVertex3d(p->x, p->y, 0.01);
            glEnd();
        }
    }
}

// OpenGL渲染回调函数
void CALLBACK_Display() 
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
     
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(60.0, double(window_width) / window_height, 0.01, 1000.0);

    gluLookAt(0, 0.4, cam_z, 0,-0.3,0.1, 0,0,1);  

    float light_pos[] = { 0.0f, 0.0f, 2.0f, 1.0f };
    float para[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, para);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, para);
    glLightfv(GL_LIGHT0, GL_SPECULAR, para);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
    Draw();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glutSwapBuffers();
}

// OpenGL改变窗口大小回调函数
void CALLBACK_CallReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

// 更新帧数据
void UpdateFrameData() 
{
    // 查询设备状态，如果数据有更新，则将所有指尖的位置与朝向保存
    if (sdk.RetrieveFrame(0))
    {
        const sharpnow::Frame* frame = sdk.GetFrameInfo();
        if (!frame || !frame->updated) return;

        // 释放一段时间未更新轨迹，并维护轨迹长度
        for (int i = 0; i < MAX_FNUM; ++i)
        {
            while (trajectory[i].size() > 50) trajectory[i].pop_front();
            ++traj_cnt[i];
            if (traj_cnt[i] < 5) continue;
            traj_cnt[i] = 0;
            trajectory[i].clear();
        }

        finger_num = 0;
        float hmax = -100.0f;
        for (int i = 0; i < frame->finger_number && i < MAX_FNUM; ++i)
        {
            const sharpnow::Finger* finger = sdk.GetFinger(i);
            if (!finger) continue;
            finger_top[i] = finger->position;
            finger_dir[i] = finger->direction;
            trajectory[finger->track_id].push_back(finger->position);
            traj_cnt[finger->track_id] = 0;
            ++finger_num;

            if (finger_top[i].z > hmax) hmax = finger_top[i].z;
            float dst = hmax > 0.3f ? 0.55f : (hmax < 0.2f ? 0.25f : cam_z);
            cam_z = cam_z * 0.98f + dst * 0.02f;
        }

        hand_num = 0;
        for (int i = 0; i < frame->hand_number && i < MAX_HNUM; ++i)
        {
            const sharpnow::Hand* hand = sdk.GetHand(i);
            if (!hand) continue;
            ++hand_num;
            hand_center[i] = hand->position;
            hand_norm[i] = hand->axis_z;
        }
        glutPostWindowRedisplay(window);
    }
}

int main(int argc, char** argv)
{
    // 加载动态链接库
    sdk.LoadInPath("../../lib");

    // 初始化OpenGL渲染环境
    glutInit(&argc, argv);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(window_width,window_height);
    window = glutCreateWindow("SharpNow ViD OpenGL Sample");
    glutSetWindow(window);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);

    // 注册OpenGL回调函数
    glutDisplayFunc(CALLBACK_Display);
    glutReshapeFunc(CALLBACK_CallReshape);

    while (true)
    {
        UpdateFrameData();
        glutMainLoopEvent();
        ::Sleep(1);
    }
}

