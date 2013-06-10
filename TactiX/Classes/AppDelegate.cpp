#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "LuaScene.h"
#include "MainScene.h"
#include "LuaBind.h"
#include "LuaObject.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::sharedEngine()->end();
    //CCScriptEngineManager::purgeSharedManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720, 960, kResolutionNoBorder);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // register lua engine
    CCLuaEngine* 
        pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    tolua_TactiX_open(pEngine->getLuaStack()->getLuaState());

    CCDirector::sharedDirector()->setDepthTest(false);
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    
    
    // Pathの設定
        std::vector<std::string> paths;

    paths.push_back("Script");

    paths.push_back("Music");

    paths.push_back("Image");

    paths.push_back("SE");
    paths.push_back("Map");

    CCFileUtils::sharedFileUtils()->setSearchPaths(paths);

    /*LuaObject *pathObj = LuaObject::create("resource_path.lua");
    boost::shared_ptr<CCLuaValueArray> array = pathObj->getArray("pathes");
    std::vector<std ::string> pathes;
    for (CCLuaValueArrayIterator it = array->begin(); it != array->end(); ++it) {
        pathes.push_back(it->stringValue());
    }
    CCFileUtils::sharedFileUtils()->setSearchPaths(pathes);*/
    
    CCScene *scene = CCScene::create();
    MainScene *layer = new MainScene();
    layer->autorelease();
    scene->addChild(layer);
    CCDirector::sharedDirector()->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
