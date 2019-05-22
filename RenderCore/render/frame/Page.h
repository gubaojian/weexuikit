//
// Created by furture on 2018/12/29.
//

#ifndef WEEX_UIKIT_PAGE_H
#define WEEX_UIKIT_PAGE_H
#include "Frame.h"
#include "FramePipeline.h"
#include "FrameView.h"
#include "FrameController.h"

namespace weexuikit{

    class Page {

      public:
            Page();
            ~Page();

      public:
          inline Frame* getFrame(){
              return mFrame;
          }

          inline FrameView* getFrameView(){
              return mFrameView;
          }

          inline FramePipeline* getFramePipeline(){
              return mFramePipeline;
          }

          /**
           * not thread safe?
           * */
          inline FrameController* getFrameController(){
              return mFrameController;
          }

          inline void setPageId(const std::string& pageId){
              mPageId = pageId;
          }

      private:
            std::string mPageId;
            Frame* mFrame;
            FrameView* mFrameView;
            FramePipeline* mFramePipeline;
            FrameController* mFrameController;
    };

}



#endif //WEEX_UIKIT_PAGE_H
