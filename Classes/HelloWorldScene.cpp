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

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add bird
	bird = Sprite::create("bird.png");
	auto birdBody = PhysicsBody::createBox(bird->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	bird->setPhysicsBody(birdBody);
	bird->setPosition(visibleSize / 4);
	addChild(bird);

	//add ground
	ground = Sprite::create("ground.png");
	ground->setContentSize(Size(visibleSize.width, ground->getContentSize().height));
	auto groundBody = PhysicsBody::createEdgeBox(Size(visibleSize.width, ground->getContentSize().height));
	ground->setPhysicsBody(groundBody);
	ground->setAnchorPoint(Vec2::ZERO);
	ground->setPosition(Vec2::ZERO);
	addChild(ground);

	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::addBars), 1.0f);
	scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt) {
	auto bodies = getScene()->getPhysicsWorld()->getAllBodies();

}

void HelloWorld::addBars(float dt) {
	Sprite* upBar = Sprite::create("up_bar.png");
	upBar->setPosition(visibleSize.width + 20, 
		visibleSize.height - upBar->getContentSize().height / 2);
	auto upBody = PhysicsBody::createBox(upBar->getContentSize(), 
		PhysicsMaterial(0.9f, 1.0f, 0.0f));
	upBody->setGravityEnable(false);
	upBody->setVelocity(Vec2(-50, 0));
	upBar->setPhysicsBody(upBody);
	addChild(upBar);

	Sprite* downBar = Sprite::create("down_bar.png");
	downBar->setPosition(visibleSize.width + 20, 
		downBar->getContentSize().height / 2 + ground->getContentSize().height + 2);
	auto downBody = PhysicsBody::createBox(downBar->getContentSize(), 
		PhysicsMaterial(0.9f, 1.0f, 0.0f));
	downBody->setGravityEnable(false);
	downBody->setVelocity(Vec2(-50, 0));
	downBar->setPhysicsBody(downBody);
	addChild(downBar);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
