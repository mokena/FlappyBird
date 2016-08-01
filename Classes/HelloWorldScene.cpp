#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//set world's gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, -10));

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add bird
	bird = Sprite::create("bird.png");
	auto birdBody = PhysicsBody::createBox(bird->getContentSize());
	bird->setPhysicsBody(birdBody);
	bird->setPosition(visibleSize / 4);
	addChild(bird);

	//add ground
	ground = Sprite::create("ground.png");
	auto groundBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, ground->getContentSize().height));
	ground->setPhysicsBody(groundBody);
	ground->setPosition(Vec2(visibleSize.width / 2, 0));
	addChild(ground);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
