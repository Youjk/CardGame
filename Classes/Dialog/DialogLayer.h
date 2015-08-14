#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
	模态对话框
*/
class DialogLayer :
	public Layer
{
public:
	DialogLayer(void);
	~DialogLayer(void);

	CREATE_FUNC(DialogLayer);
	static DialogLayer* create(Sprite* backgroundImage);
	void setTitle(const char* title, int fontsize = 30);
	void setContentText(const char* text ,int fontsize=25 ,int padding=50 ,int paddingTop=200);
	bool addButton(const char* title, Sprite* normalImage, Sprite* selectedImage, Sprite* disableImage, const ccMenuCallback& callback, int tag = 0);
	
	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

private:
	//文字内容两边的空白区
	int m_contentPadding;
	int m_contentPaddingTop;

	CC_SYNTHESIZE_RETAIN(Menu*, m_pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, m_sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m_s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m_ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m_ltContentText, LabelContentText);
};

