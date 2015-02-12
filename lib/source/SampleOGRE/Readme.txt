示例工程使用Ogre 1.9

请到官网下载并按照下面网址中的步骤建立和配置Ogre工程：
http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+Visual+Studio

工程配置好之后，将BaseApplication.h BaseApplication.cpp TutorialApplication.h TutorialApplication.cpp用SampleOGRE中的同名文件替换，并加入vid.h hid.h sharpnow.h sharpnow.hpp到工程中
将sharpnow.dll放到\OGRE\OgreSDK_vc10_v1-9-0\lib下
将resources文件夹下的SampleOGREMaterial文件拷贝到OGRE\OgreSDK_vc10_v1-9-0\resource\materials 下。