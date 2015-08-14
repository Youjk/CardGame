
/*
	��ȡxml�ж�Ӧkey���ı�
*/


#pragma once
#include <string>
#include<map>
#include "cocos2d.h"
USING_NS_CC;

class AppStringFile : public SAXDelegator
{
public:
	AppStringFile(void);
	~AppStringFile(void);

	//����String.xml������
	virtual void startElement(void *ctx, const char *name, const char **atts);
    virtual void endElement(void *ctx, const char *name);
    virtual void textHandler(void *ctx, const char *s, int len);

	static AppStringFile* getInstance();
	const std::string getStringForKey(const std::string& key);

private:
	static AppStringFile* m_pAppStringFile;

	class  CGarbo
	{
	public:
		~ CGarbo(){
			if (m_pAppStringFile != NULL)
			{
				delete m_pAppStringFile;
			}
		}
	};

	bool init();  //����string.xml�õ�map
	static CGarbo m_garbo;
	std::map<std::string, std::string> stringmap;
	std::string key;
	std::string value;
	bool flag;   //�жϵ�ǰ��������key������value
};

