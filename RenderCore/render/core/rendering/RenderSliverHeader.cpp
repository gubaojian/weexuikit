//
// Created by furture on 2019/1/8.
//

#include "RenderSliverHeader.h"
#include "RenderParagraph.h"
#include "RenderText.h"

namespace blink{

    #define PULL_TO_REFRESH_TEXT  "下拉刷新"
    #define PULL_TO_REFRESH_REFRESHING  "刷新中"
    #define PULL_TO_RELEASE_REFRESH  "松开刷新"


    RenderSliverHeader::RenderSliverHeader() {
        mPullDistance = -200;
        mHeaderState  = RefreshState::DisableRefresh;
        PassRefPtr<RenderStyle>  renderStyle = RenderStyle::createDefaultStyle();
        renderStyle->setWidth({100, LengthType::Percent});
        renderStyle->setBackgroundColor(StyleColor(Color::darkGray));
        renderStyle->setFlexDirection(EFlexDirection::FlowColumn);
        setStyle(renderStyle);
    }


    void RenderSliverHeader::refreshHeaderLayout() {
        if(mHeaderState == RefreshState::DisableRefresh){
            if(firstChild() == nullptr){
                return;
            }
            RenderParagraph* paragraph = (RenderParagraph*)childAt(0);
            paragraph->remove();
            paragraph->destroy();
            forceLayout();
            return;
        }
        RenderText* renderText = nullptr;
        RenderParagraph* paragraph = nullptr;
        if(childAt(0) == nullptr){
            WTF::String string = WTF::String::fromUTF8(PULL_TO_REFRESH_TEXT);
            renderText = new RenderText(string.impl());
            RefPtr<RenderStyle>  renderTextStyle = RenderStyle::createDefaultStyle();
            renderTextStyle->inheritFrom(style());
            renderTextStyle->setFontSize(56);
            renderText->setStyle(renderTextStyle);

            paragraph = new RenderParagraph();
            PassRefPtr<RenderStyle> paragraphStyle = RenderStyle::createDefaultStyle();
            paragraphStyle->inheritFrom(style());
            paragraph->setStyle(paragraphStyle);
            paragraph->addChild(renderText);
            addChild(paragraph);
        }else{
            paragraph = (RenderParagraph*)childAt(0);
            if(paragraph != nullptr){
                renderText =(RenderText *)(paragraph->childAt(0));
            }
        }
        if(renderText == nullptr){
            return;
        }

        if(getRefreshState() == RefreshState::RefreshIng){
            WTF::String string = WTF::String::fromUTF8(PULL_TO_REFRESH_REFRESHING);
            renderText->setText(string.impl());
        }else{
            if(mSliverScrollOffset.y().toInt() <= mPullDistance){
                WTF::String string = WTF::String::fromUTF8(PULL_TO_RELEASE_REFRESH);
                renderText->setText(string.impl());
                mHeaderState = RefreshState::RelaseToRefresh;
            }else{
                WTF::String string = WTF::String::fromUTF8(PULL_TO_REFRESH_TEXT);
                renderText->setText(string.impl());
                mHeaderState = RefreshState::PullToRefresh;
            }
        }
        paragraph->layoutIfNeeded();
        layoutIfNeeded();

        LayoutPoint location;
        location.move((width() - renderText->maxLogicalWidth())/2, mSliverScrollOffset.y() - logicalHeight());
        setLocation(location);

        printf("RenderRefreshHeader Location frame %d %d %d %d \n", location.x().toInt(), location.y().toInt(),
               width().toInt(), height().toInt());
    }


    RenderSliverHeader::~RenderSliverHeader(){

    }


    LayoutUnit RenderSliverHeader::getPullDistance() {
        return mPullDistance;
    }


    void RenderSliverHeader::setPullDistance(blink::LayoutUnit pullDistance) {
        mPullDistance = pullDistance;
    }

    float RenderSliverHeader::getScrollOffset() {
        if(mHeaderState == RefreshState::DisableRefresh){
            return 0;
        }
        if(mHeaderState == RefreshState::RefreshIng){
            return mPullDistance.toInt();
        }
        return 0;
    }

}