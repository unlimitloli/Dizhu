#pragma once
#include "csb_config.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"


// 查找csb资源控件
#define getWidgetByName(root, name)			cocos2d::ui::Helper::seekWidgetByName(dynamic_cast<cocos2d::ui::Widget *>(root), name)
