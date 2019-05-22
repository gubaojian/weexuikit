//
// Created by furture on 2018/8/7.
//

#include <render/platform/common/log.h>
#include "Node.h"

namespace weexuikit{

     Node::Node(const std::string& pageId, const std::string& ref,
                const std::string& type,
                std::map<std::string, std::string> *styles,
                std::map<std::string, std::string> *attrs,
                std::set<std::string>* events)
                :mPageId(pageId),
                 mRef(ref),
                 mType(type),
                 mStyles(styles),
                 mAttrs(attrs),
                 mEvents(events),
                 mActiveStyle(nullptr),
                 mResetStyle(nullptr){
     }

    Node::~Node() {
        if(mEvents != nullptr){
            delete  mEvents;
            mEvents = nullptr;
        }
        if(mAttrs != nullptr){
            delete mAttrs;
            mAttrs = nullptr;
        }
        if(mStyles != nullptr){
            delete  mStyles;
            mStyles = nullptr;
        }
        if(mEvents != nullptr){
            delete  mEvents;
            mEvents = nullptr;
        }
        if(mActiveStyle != nullptr){
            delete mActiveStyle;
            mActiveStyle = nullptr;
        }
        if(mResetStyle != nullptr){
            delete mResetStyle;
            mResetStyle = nullptr;
        }
    }

     void Node::updateAttr(const std::string &key, const std::string &value) {
         if(mAttrs == nullptr){
             mAttrs = new std::map<std::string, std::string>();
         }
         insertOrAssign(mAttrs, key, value);
     }

     void Node::updateStyle(const std::string &key, const std::string &value) {
         if(mStyles == nullptr){
             mStyles = new std::map<std::string, std::string>();
         }
         insertOrAssign(mStyles, key, value);
     }

     void Node::addEvent(const std::string& event) {
         if(mEvents == nullptr){
             mEvents = new std::set<std::string>();
         }
         mEvents->insert(event);
     }

    std::string Node::getAttr(const std::string &key) {
        std::map<std::string, std::string>::iterator it = mAttrs->find(key);
        if(it != mAttrs->end()){
            return it->second;
        }
        return "";
    }

    std::string Node::getStyle(const std::string &key) {
        std::map<std::string, std::string>::iterator it = mStyles->find(key);
        if(it != mStyles->end()){
            return it->second;
        }
        return "";
    }

    bool Node::hasClickEvent() {
        if(mEvents != nullptr) {
            std::set<std::string>::iterator it = mEvents->find(Html::Event::CLICK);
            if (it != mEvents->end()) {
                return true;
            }
        }
        return  false;
    }

    bool Node::hasAccessibility(){
        if(mAttrs != nullptr) {
            std::map<std::string, std::string>::iterator it = mAttrs->find(Html::Attr::ATTR_ARIA_HIDDEN);
            if (it != mAttrs->end() && it->second == Html::Attr::Value::ATTR_VALUE_TRUE) {
                return false;
            }
            return getAccessibility().length() > 0;
        }
        return false;
    }

    bool Node::ariaHidden() {
        if(mAttrs != nullptr) {
            std::map<std::string, std::string>::iterator it = mAttrs->find(Html::Attr::ATTR_ARIA_HIDDEN);
            if (it != mAttrs->end()) {
                return it->second == Html::Attr::Value::ATTR_VALUE_TRUE;
            }
        }
        return false;
    }


    const std::string& Node::getAccessibility() {
        if(mAttrs != nullptr) {
            std::map<std::string, std::string>::iterator it = mAttrs->find(Html::Attr::ATTR_ARIA_LABEL);
            if (it != mAttrs->end()) {
                return it->second;
            }

            it = mAttrs->find(Html::Attr::ATTR_VALUE);
            if (it != mAttrs->end()) {
                return it->second;
            }
        }
        return  EMPTY_STRING;
    }


    void Node::insertOrAssign(std::map<std::string, std::string> *map, const std::string &key,
                              const std::string &value) {
        std::map<std::string, std::string>::iterator it = map->find(key);
        if (it != map->end()) {
            it->second = value;
        } else {
            map->insert({key, value});
        }
    }

    void Node::updateStyles(std::map<std::string, std::string> *styles) {
        std::map<std::string, std::string>::iterator it = styles->begin();
        for(;it != styles->end(); it ++){
            insertOrAssign(mStyles, it->first, it->second);
        }
    }


    std::map<std::string, std::string>* Node::getActiveStyle() {
         if(mActiveStyle == nullptr){
             mActiveStyle = new std::map<std::string, std::string>();
         }
         if(mResetStyle == nullptr){
             mResetStyle = new std::map<std::string, std::string>();
         }
         if(mStyles == nullptr){
             return mActiveStyle;
         }
         mActiveStyle->clear();
         mResetStyle->clear();
         std::map<std::string, std::string>::iterator it = mStyles->begin();
         for(;it != mStyles->end(); it ++){
             std::string::size_type  position = it->first.find(Html::Style::STYLE_ACTIVE_SUFFIX);
             if(position == std::string::npos){
                 continue;
             }
             std::string key = it->first.substr(0, position);
             std::string resetValue = getStyle(key);
             mResetStyle->insert({key, resetValue});
             mActiveStyle->insert({key, it->second});
         }

        return mActiveStyle;
     }

     std::map<std::string, std::string>* Node::getResetStyle() {
         return mResetStyle;
     }
}