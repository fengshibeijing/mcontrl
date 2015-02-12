/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)
	sdk.LoadInPath("../../lib");
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5));
	Ogre::Light *light = mSceneMgr->createLight("Light");
	light->setType(Ogre::Light::LT_POINT);
	light->setDiffuseColour(0.3f,0.3f,0.3f);
	light->setSpecularColour(0.6f,0.6f,0.6f);
	light->setPosition(0,15,0);
	for (int i=0;i<10;i++)
	{
		fingerArray[i] = (mSceneMgr->getRootSceneNode()->createChildSceneNode());
		Ogre::Entity* entity = mSceneMgr->createEntity("sphere.mesh");
		entity->setMaterialName("SphereForSampleOgre");
		fingerArray[i]->attachObject(entity);
		fingerArray[i]->setVisible(false);
		fingerArray[i]->setScale(0.01f,0.01f,0.01f);
		Ogre::NameValuePairList pairList;   //参数列表
		pairList["numberOfChains"] = "1";
		pairList["maxElements"] = "1000";
		Ogre::RibbonTrail* trail = static_cast<Ogre::RibbonTrail*>(
			mSceneMgr->createMovableObject(Ogre::StringConverter::toString(i), "RibbonTrail", &pairList)); 
		trail->setMaterialName("LightRibbonTrail");
		trail->setTrailLength(5);
		trail->setInitialColour(0, 1.0, 1, 0);
		trail->setColourChange(0, 0.5, 0.5, 0.5, 0.5);
		trail->setInitialWidth(0.3, 0.3);
		trail->addNode(fingerArray[i]); 
		trail->setVisible(false);
		fingerTrails[i] = trail;
		mSceneMgr->getRootSceneNode()->attachObject(trail);
	}
	for (int i=0;i<2;i++)
	{
		handArray[i] = (mSceneMgr->getRootSceneNode()->createChildSceneNode());
		Ogre::Entity* entity = mSceneMgr->createEntity("sphere.mesh");
		entity->setMaterialName("Sphere");
		handArray[i]->attachObject(entity);
		handArray[i]->setVisible(false);
		handArray[i]->setScale(0.03f,0.03f,0.03f);
	}
	createFrames();
}
void TutorialApplication::createFrames(void)
{
	Ogre::ManualObject* backPlane =  mSceneMgr->createManualObject("BackPlane"); 
	Ogre::SceneNode* backPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BackPlaneNode"); 
	backPlane->begin("DigitalPlane", Ogre::RenderOperation::OT_LINE_LIST);
	{
		backPlane->position(-40,0,-15); 
		backPlane->normal(0,0,1);
		backPlane->position(40,0,-15);
		backPlane->normal(0,0,1);

		backPlane->position(40,0,-15);
		backPlane->normal(0,0,1);
		backPlane->position(40,50,-15);
		backPlane->normal(0,0,1);

		backPlane->position(40,50,-15);
		backPlane->normal(0,0,1);
		backPlane->position(-40,50,-15);
		backPlane->normal(0,0,1);

		backPlane->position(-40,50,-15);
		backPlane->normal(0,0,1);
		backPlane->position(-40,0,-15);
		backPlane->normal(0,0,1);
		for (int i=0;i<20;i++)
		{
			backPlane->position(-40+i*4,0,-15);
			backPlane->normal(0,0,1);
			backPlane->position(-40+i*4,50,-15);
			backPlane->normal(0,0,1);
		}
		for (int i=0;i<25;i++)
		{
			backPlane->position(-40,i*2,-15);
			backPlane->normal(0,0,1);
			backPlane->position(40,i*2,-15);
			backPlane->normal(0,0,1);
		}
	}
	backPlane->end();
	backPlaneNode->attachObject(backPlane);

	Ogre::ManualObject* leftPlane =  mSceneMgr->createManualObject("LeftPlane"); 
	Ogre::SceneNode* leftPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LeftPlaneNode"); 
	leftPlane->begin("DigitalPlane", Ogre::RenderOperation::OT_LINE_LIST);
	{
		leftPlane->position(-40,50,-15); 
		leftPlane->normal(1,0,0);
		leftPlane->position(-40,50,45);
		leftPlane->normal(1,0,0);

		leftPlane->position(-40,50,45);
		leftPlane->normal(1,0,0);
		leftPlane->position(-40,0,45);
		leftPlane->normal(1,0,0);

		leftPlane->position(-40,0,45);
		leftPlane->normal(1,0,0);
		leftPlane->position(-40,0,-15);
		leftPlane->normal(1,0,0);

		leftPlane->position(-40,0,-15);
		leftPlane->normal(1,0,0);
		leftPlane->position(-40,50,-15);
		leftPlane->normal(1,0,0);
		for (int i=0;i<20;i++)
		{
			leftPlane->position(-40,0,-15+i*3);
			leftPlane->normal(1,0,0);
			leftPlane->position(-40,50,-15+i*3);
			leftPlane->normal(1,0,0);
		}
		for (int i=0;i<25;i++)
		{
			leftPlane->position(-40,i*2,-15);
			leftPlane->normal(1,0,0);
			leftPlane->position(-40,i*2,45);
			leftPlane->normal(1,0,0);
		}
	}
	leftPlane->end();
	leftPlaneNode->attachObject(leftPlane);

	Ogre::ManualObject* rightPlane =  mSceneMgr->createManualObject("RightPlane"); 
	Ogre::SceneNode* rightPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RightPlaneNode"); 
	rightPlane->begin("DigitalPlane", Ogre::RenderOperation::OT_LINE_LIST);
	{
		rightPlane->position(40,50,-15); 
		rightPlane->normal(-1,0,0);
		rightPlane->position(40,50,45);
		rightPlane->normal(-1,0,0);

		rightPlane->position(40,50,45);
		rightPlane->normal(-1,0,0);
		rightPlane->position(40,0,45);
		rightPlane->normal(-1,0,0);

		rightPlane->position(40,0,45);
		rightPlane->normal(-1,0,0);
		rightPlane->position(40,0,-15);
		rightPlane->normal(-1,0,0);

		rightPlane->position(40,0,-15);
		rightPlane->normal(-1,0,0);
		rightPlane->position(40,50,-15);
		rightPlane->normal(-1,0,0);
		for (int i=0;i<20;i++)
		{
			rightPlane->position(40,0,-15+i*3);
			rightPlane->normal(-1,0,0);
			rightPlane->position(40,50,-15+i*3);
			rightPlane->normal(-1,0,0);
		}
		for (int i=0;i<25;i++)
		{
			rightPlane->position(40,i*2,-15);
			rightPlane->normal(-1,0,0);
			rightPlane->position(40,i*2,45);
			rightPlane->normal(-1,0,0);
		}
	}
	rightPlane->end();
	rightPlaneNode->attachObject(rightPlane);

	Ogre::ManualObject* bottomPlane =  mSceneMgr->createManualObject("BottomPlane"); 
	Ogre::SceneNode* bottomPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BottomPlaneNode"); 
	bottomPlane->begin("DigitalPlane", Ogre::RenderOperation::OT_LINE_LIST);
	{
		bottomPlane->position(-40,0,-15); 
		bottomPlane->normal(0,1,0);
		bottomPlane->position(-40,0,45);
		bottomPlane->normal(0,1,0);

		bottomPlane->position(-40,0,45);
		bottomPlane->normal(0,1,0);
		bottomPlane->position(40,0,45);
		bottomPlane->normal(0,1,0);

		bottomPlane->position(40,0,45);
		bottomPlane->normal(0,1,0);
		bottomPlane->position(40,0,-15);
		bottomPlane->normal(0,1,0);

		bottomPlane->position(40,0,-15);
		bottomPlane->normal(0,1,0);
		bottomPlane->position(-40,0,-15);
		bottomPlane->normal(0,1,0);
		for (int i=0;i<20;i++)
		{
			bottomPlane->position(-40,0,-15+i*3);
			bottomPlane->normal(0,1,0);
			bottomPlane->position(40,0,-15+i*3);
			bottomPlane->normal(0,1,0);
		}
		for (int i=0;i<20;i++)
		{
			bottomPlane->position(-40+i*4,0,-15);
			bottomPlane->normal(0,1,0);
			bottomPlane->position(-40+i*4,0,45);
			bottomPlane->normal(0,1,0);
		}
	}
	bottomPlane->end();
	bottomPlaneNode->attachObject(bottomPlane);

	Ogre::ManualObject* topPlane =  mSceneMgr->createManualObject("TopPlane"); 
	Ogre::SceneNode* topPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TopPlaneNode"); 
	topPlane->begin("DigitalPlane", Ogre::RenderOperation::OT_LINE_LIST);
	{
		topPlane->position(-40,50,-15); 
		topPlane->normal(0,1,0);
		topPlane->position(-40,50,45);
		topPlane->normal(0,-1,0);

		topPlane->position(-40,50,45);
		topPlane->normal(0,1,0);
		topPlane->position(40,50,45);
		topPlane->normal(0,-1,0);

		topPlane->position(40,50,45);
		topPlane->normal(0,-1,0);
		topPlane->position(40,50,-15);
		topPlane->normal(0,-1,0);

		topPlane->position(40,50,-15);
		topPlane->normal(0,-1,0);
		topPlane->position(-40,50,-15);
		topPlane->normal(0,-1,0);
		for (int i=0;i<20;i++)
		{
			topPlane->position(-40,50,-15+i*3);
			topPlane->normal(0,-1,0);
			topPlane->position(40,50,-15+i*3);
			topPlane->normal(0,-1,0);
		}
		for (int i=0;i<20;i++)
		{
			topPlane->position(-40+i*4,50,-15);
			topPlane->normal(0,-1,0);
			topPlane->position(-40+i*4,50,45);
			topPlane->normal(0,-1,0);
		}
	}
	topPlane->end();
	topPlaneNode->attachObject(topPlane);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
