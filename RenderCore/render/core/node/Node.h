
//
// Created by furture on 2018/8/7.
//

#ifndef FLUTTERCORE_NODE_H
#define FLUTTERCORE_NODE_H
#include "render/platform/graphics/ImageInfo.h"
#include "NodeStyles.h"
#include <string>
#include <set>
#include <map>

namespace weexuikit {

    class Node {
    public:
        Node(const std::string& pageId, const std::string& ref, const std::string& type,
             std::map<std::string, std::string> *styles,
             std::map<std::string, std::string> *attrs,
             std::set<std::string>* events);

        ~Node();

    public:
        void updateAttr(const std::string &key, const std::string &value);
        void updateStyle(const std::string &key, const std::string &value);
        void addEvent(const std::string& event);

        void updateStyles(std::map<std::string, std::string> *styles);

        std::string getAttr(const std::string& key);
        std::string getStyle(const std::string& key);

        std::map<std::string, std::string>* getActiveStyle();
        std::map<std::string, std::string>* getResetStyle();


    public:
        inline std::string& getPageId(){
            return mPageId;
        }

        inline const std::string &ref() const { return mRef; }

        inline const std::string &type(){ return mType; }

        inline std::set<std::string> *events(){
            if(mEvents == nullptr){
                mEvents = new std::set<std::string>();
            }
            return mEvents;
        }

        inline std::map<std::string, std::string> *styles(){
            if(mStyles == nullptr){
                mStyles = new std::map<std::string, std::string>();
            }
            return mStyles;
        }

        inline std::map<std::string, std::string>* attrs(){
            if(mAttrs == nullptr){
                mAttrs = new std::map<std::string, std::string>();
            }
            return mAttrs;
        };


    public:
        bool hasClickEvent();
        bool hasAccessibility();
        bool ariaHidden();
        const std::string& getAccessibility();


    private:
        void insertOrAssign(std::map<std::string, std::string> *map, const std::string &key, const std::string &value);

    private:
        std::string mPageId;//FIXME Use Pointer
        std::string mRef;
        std::string mType; //FIXME
        std::map<std::string, std::string> *mAttrs;
        std::map<std::string, std::string> *mStyles;
        std::set<std::string> *mEvents;
        std::map<std::string, std::string>* mActiveStyle;
        std::map<std::string, std::string>* mResetStyle;
    };
}



#endif //FLUTTERCORE_NODE_H
