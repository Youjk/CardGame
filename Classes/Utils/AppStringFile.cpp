#include "AppStringFile.h"
using namespace std;

AppStringFile* AppStringFile::m_pAppStringFile = NULL;


AppStringFile::AppStringFile(void)
{
	key = "";
	value = "";
}


AppStringFile::~AppStringFile(void)
{
	
}

void AppStringFile::startElement(void *ctx, const char *name, const char **atts){
	string data = name;
	if(data == "key"){
		flag = true;
	}else{
		flag = false;
	}
}

void AppStringFile::endElement(void *ctx, const char *name){
	
}

void AppStringFile::textHandler(void *ctx, const char *s, int len){
	if (flag)
	{
		key = s;
	}else
	{
		value = s;
		//log(("key:" + key + "value" + value).c_str);
		stringmap.insert(make_pair(key, value));
	}
}

bool AppStringFile::init()
{
	SAXParser paraser;
	if(!paraser.init("UTF-8")){
		log("Please use utf-8 format");
		return false;
	}
	paraser.setDelegator(this);

	return paraser.parse("Strings.xml");
}

const string AppStringFile::getStringForKey(const std::string& key)
{
	return stringmap.at(key);
}

AppStringFile* AppStringFile::getInstance()
{
	if (!m_pAppStringFile)
	{
		m_pAppStringFile = new AppStringFile();
		m_pAppStringFile->init();
	}

	CCASSERT(m_pAppStringFile, "创建应用程序字符数据文件实例失败");

	return m_pAppStringFile;
}

