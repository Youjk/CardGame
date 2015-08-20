#include "DialogLayer.h"


DialogLayer::DialogLayer(void):
	m_pMenu(NULL)
	,m_contentPadding(0)
	,m_contentPaddingTop(0)
	,m_sfBackGround(NULL)
	,m_s9BackGround(NULL)
	,m_ltContentText(NULL)
	,m_ltTitle(NULL)
{
}


DialogLayer::~DialogLayer(void)
{
	CC_SAFE_RELEASE(m_pMenu);
	CC_SAFE_RELEASE(m_sfBackGround);
	CC_SAFE_RELEASE(m_ltContentText);
	CC_SAFE_RELEASE(m_ltTitle);
	CC_SAFE_RELEASE(m_s9BackGround);
}


bool DialogLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setContentSize(Size::ZERO);

	//初始化Menu
	Menu* pMenu = Menu::create();
	pMenu->setPosition(Point::ZERO);
	this->setMenuButton(pMenu);

	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){
		log("dialog touched");
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

DialogLayer* DialogLayer::create(Sprite* backgroundImage)
{
	DialogLayer* dialog = DialogLayer::create();
	dialog->setSpriteBackGround(backgroundImage);
	dialog->setSprite9BackGround(Scale9Sprite::createWithSpriteFrame(backgroundImage->getSpriteFrame()->clone()));

	return dialog;
}

void DialogLayer::setTitle(const char* title, int fontsize /* = 25 */)
{
	LabelTTF* ltfTitle = LabelTTF::create(title, "Arial", fontsize);
	setLabelTitle(ltfTitle);
}

void DialogLayer::setContentText(const char* text ,int fontsize/* =25  */,int padding/* =50  */,int paddingTop/* =100 */)
{
	LabelTTF* ltf = LabelTTF::create(text, "Arial", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

bool DialogLayer::addButton(const char* title, Sprite* normalImage, Sprite* selectedImage, Sprite* disableImage, const ccMenuCallback& callback, int tag/* =0 */)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	// 创建图片菜单按钮
	MenuItemSprite* menuImage = MenuItemSprite::create(normalImage, selectedImage, disableImage, callback);
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);

	// 添加文字说明并设置位置
	Size imenu = menuImage->getContentSize();
	LabelTTF* ttf = CCLabelTTF::create(title, "Arial", 25);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(imenu.width / 2, imenu.height / 2);
	menuImage->addChild(ttf);

	getMenuButton()->addChild(menuImage);
	return true;
}

void DialogLayer::onEnter()
{
	Layer::onEnter();
     
    Size winSize = Director::getInstance()->getWinSize();
    Point pCenter = Point(winSize.width / 2, winSize.height / 2);
     
    Size contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(Size::ZERO)) {
        getSpriteBackGround()->setPosition(winSize.width / 2, winSize.height / 2);
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    } else {
        Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(winSize.width / 2, winSize.height / 2);
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }
     
     
    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
     
    Vector<Node*> vecArray = getMenuButton()->getChildren();
    Ref* pObj = NULL;
    int i = 0;
    for(auto& e : vecArray){
        Node* node = dynamic_cast<Node*>(e);
        node->setPosition(Point(winSize.width/2 - contentSize.width/2+btnWidth*(i+1),winSize.height/2-contentSize.height/3));
        i++;
    }

	// 显示对话框标题
	if (getLabelTitle()){
		getLabelTitle()->setPosition(pCenter + Vec2(0, contentSize.height / 2 - 30.0f));
		this->addChild(getLabelTitle());
	}

	// 显示文本内容
	if (getLabelContentText()){
		LabelTTF* ltf = getLabelContentText();
		ltf->setPosition(winSize.width / 2, winSize.height / 2 + 20);
		//ltf->setDimensions(Size(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}

	// 弹出效果
	Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.06, 1.05),
		ScaleTo::create(0.08, 0.95),
		ScaleTo::create(0.08, 1.0), NULL);
	this->runAction(popupLayer);
}

void DialogLayer::onExit()
{
	Layer::onExit();
}
