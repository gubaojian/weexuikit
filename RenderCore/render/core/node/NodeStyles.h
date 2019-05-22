//
// Created by furture on 2018/8/9.
//

#ifndef WEEX_UIKIT_NODESTYLES_H
#define WEEX_UIKIT_NODESTYLES_H
#include <string>

namespace weexuikit {


    namespace Html {

        namespace Tag {
            static const char* DIV = "div";
            static const char* TEXT = "text";
            static const char* IMAGE = "image";
            static const char* IMG = "img";
            static const char* P = "p";
            static const char* PARAGRAPH = "paragraph";
            static const char* SPAN = "span";
            static const char* A = "a";
            static const char* SCROLLER = "scroller";
            static const char* LIST = "list";
            static const char* SLIDER = "slider";
            static const char* INPUT = "input";
            static const char* VIDEO = "video";
            static const char* WEB = "web";
            static const char* ANIMATION = "animation";
            static const char* WWEB = "wweb";

        }


        namespace Event{
            static const char* CLICK = "click";
            static const char* SCROLL = "scroll";
            static const char* SCROLL_OFFSET = "offset";
        }

        namespace Style {

            static const char* STYLE_ACTIVE_SUFFIX = ":active";
            static const char* STYLE_BACKGROUND = "background";
            static const char* STYLE_BACKGROUND_IMAGE = "backgroundImage";
            static const char* STYLE_BACKGROUND_COLOR = "backgroundColor";
            static const char* STYLE_WIDTH = "width";
            static const char* STYLE_MIN_WIDTH = "minWidth";
            static const char* STYLE_MAX_WIDTH = "maxWidth";
            static const char* STYLE_HEIGHT = "height";
            static const char* STYLE_MIN_HEIGHT = "minHeight";
            static const char* STYLE_MAX_HEIGHT = "maxHeight";
            static const char* STYLE_LEFT = "left";
            static const char* STYLE_RIGHT = "right";
            static const char* STYLE_BOTTOM = "bottom";
            static const char* STYLE_TOP = "top";
            static const char* STYLE_MARGIN_TOP = "marginTop";
            static const char* STYLE_MARGIN_LEFT = "marginLeft";
            static const char* STYLE_MARGIN_RIGHT = "marginRight";
            static const char* STYLE_MARGIN_BOTTOM = "marginBottom";
            static const char* STYLE_MARGIN = "margin";
            static const char* STYLE_PADDING_TOP = "paddingTop";
            static const char* STYLE_PADDING_LEFT = "paddingLeft";
            static const char* STYLE_PADDING_RIGHT = "paddingRight";
            static const char* STYLE_PADDING_BOTTOM = "paddingBottom";
            static const char* STYLE_PADDING = "padding";
            static const char* STYLE_BORDER_TOP_STYLE = "borderTopStyle";
            static const char* STYLE_BORDER_TOP_WIDTH = "borderTopWidth";
            static const char* STYLE_BORDER_TOP_COLOR = "borderTopColor";
            static const char* STYLE_BORDER_TOP = "borderTop";
            static const char* STYLE_BORDER_RIGHT_STYLE = "borderRightStyle";
            static const char* STYLE_BORDER_RIGHT_WIDTH = "borderRightWidth";
            static const char* STYLE_BORDER_RIGHT_COLOR = "borderRightColor";
            static const char* STYLE_BORDER_RIGHT = "borderRight";
            static const char* STYLE_BORDER_BOTTOM_STYLE = "borderBottomStyle";
            static const char* STYLE_BORDER_BOTTOM_WIDTH = "borderBottomWidth";
            static const char* STYLE_BORDER_BOTTOM_COLOR = "borderBottomColor";
            static const char* STYLE_BORDER_BOTTOM = "borderBottom";
            static const char* STYLE_BORDER_LEFT_STYLE = "borderLeftStyle";
            static const char* STYLE_BORDER_LEFT_WIDTH = "borderLeftWidth";
            static const char* STYLE_BORDER_LEFT_COLOR = "borderLeftColor";
            static const char* STYLE_BORDER_LEFT = "borderLeft";
            static const char* STYLE_BORDER_RADIUS = "borderRadius";
            static const char* STYLE_BORDER_COLOR = "borderColor";
            static const char* STYLE_BORDER_STYLE = "borderStyle";
            static const char* STYLE_BORDER_WIDTH = "borderWidth";
            static const char* STYLE_BORDER = "border";
            static const char* STYLE_BORDER_STYLE_SOLID = "solid";
            static const char* STYLE_BORDER_STYLE_DOUBLE = "double";
            static const char* STYLE_BORDER_STYLE_DASHED = "dashed";
            static const char* STYLE_BORDER_STYLE_DOTTED = "dotted";
            static const char* STYLE_BORDER_STYLE_RIDGE = "ridge";
            static const char* STYLE_BORDER_STYLE_OUTSET = "outset";
            static const char* STYLE_BORDER_STYLE_GROOVE = "groove";
            static const char* STYLE_BORDER_STYLE_INSET = "inset";
            static const char* STYLE_BORDER_STYLE_HIDDEN = "hidden";
            static const char* STYLE_BORDER_STYLE_NONE = "none";
            static const char* STYLE_BORDER_TOP_LEFT_RADIUS = "borderTopLeftRadius";
            static const char* STYLE_BORDER_TOP_RIGHT_RADIUS = "borderTopRightRadius";
            static const char* STYLE_BORDER_BOTTOM_LEFT_RADIUS = "borderBottomLeftRadius";
            static const char* STYLE_BORDER_BOTTOM_RIGHT_RADIUS = "borderBottomRightRadius";
            static const char* STYLE_DISPLAY = "display";
            static const char* STYLE_DISPLAY_FLEX = "flex";
            static const char* STYLE_DISPLAY_INLINE = "inline";
            static const char* STYLE_DISPLAY_INLINE_FLEX = "inlineFlex";
            static const char* STYLE_DISPLAY_PARAGRAPH = "paragraph";
            static const char* STYLE_DISPLAY_NONE = "none";
            static const char* STYLE_FONT_SIZE = "fontSize";
            static const char* STYLE_POSITION = "position";
            static const char* STYLE_POSITION_ABSOLUTE = "absolute";
            static const char* STYLE_POSITION_STATIC = "static";
            static const char* STYLE_POSITION_RELATIVE = "relative";
            static const char* STYLE_FLEX_DIRECTION = "flexDirection";
            static const char* STYLE_FLEX_DIRECTION_ROW = "row";
            static const char* STYLE_FLEX_DIRECTION_ROW_REVERSE = "rowReverse";
            static const char* STYLE_FLEX_DIRECTION_ROW_REVERSE_MIDDLE_LINE = "row-reverse";
            static const char* STYLE_FLEX_DIRECTION_COLUMN = "column";
            static const char* STYLE_FLEX_DIRECTION_COLUMN_REVERSE = "columnReverse";
            static const char* STYLE_FLEX_DIRECTION_COLUMN_REVERSE_MIDDLE_LINE = "column-reverse";
            static const char* STYLE_FLEX_FLOW = "flexFlow";
            static const char* STYLE_FLEX_GROW = "flexGrow";
            static const char* STYLE_FLEX_SHRINK = "flexShrink";
            static const char* STYLE_FLEX_BASIS = "flexBasis";
            static const char* STYLE_FLEX_WRAP = "flexWrap";
            static const char* STYLE_FLEX_WRAP_NO_WRAP = "nowrap";
            static const char* STYLE_FLEX_WRAP_REVERSE = "wrapReverse";
            static const char* STYLE_FLEX_WRAP_REVERSE_MIDDLE_LINE = "wrap-reverse";
            static const char* STYLE_FLEX_WRAP_WRAP = "wrap";
            static const char* STYLE_FLEX_FLEX = "flex";
            static const char* STYLE_ALIGN_ITEMS = "alignItems";
            static const char* STYLE_FLEX_AUTO = "auto";
            static const char* STYLE_ITEM_POSITION_NORMAL = "normal";
            static const char* STYLE_ITEM_POSITION_BASE_LINE = "baseline";
            static const char* STYLE_ITEM_POSITION_LAST_BASE_LINE = "lastBaseline";
            static const char* STYLE_ITEM_POSITION_CENTER = "center";
            static const char* STYLE_ITEM_POSITION_END = "end";
            static const char* STYLE_ITEM_POSITION_FLEX_START = "flexStart";
            static const char* STYLE_ITEM_POSITION_FLEX_START_MIDDLE_LINE = "flex-start";
            static const char* STYLE_ITEM_POSITION_FLEX_END = "flexEnd";
            static const char* STYLE_ITEM_POSITION_FLEX_END_MIDDLE_LINE = "flex-end";
            static const char* STYLE_ITEM_POSITION_LEFT = "left";
            static const char* STYLE_ITEM_POSITION_RIGHT = "right";
            static const char* STYLE_ITEM_POSITION_START = "start";
            static const char* STYLE_ITEM_POSITION_STRETCH = "stretch";
            static const char* STYLE_ITEM_POSITION_SELF_START = "selfStart";
            static const char* STYLE_ITEM_POSITION_SELF_END = "selfEnd";
            static const char* STYLE_ITEM_POSITION_SELF_START_MIDDLE_LINE = "self-start";
            static const char* STYLE_ITEM_POSITION_SELF_END_MIDDLE_LINE = "self-end";
            static const char* STYLE_ALIGN_CONTENT = "alignContent";
            static const char* STYLE_ALIGN_CONTENT_FLEX_START = "flexStart";
            static const char* STYLE_ALIGN_CONTENT_FLEX_END = "flexEnd";
            static const char* STYLE_ALIGN_CONTENT_FLEX_START_MIDDLE_LINE = "flex-start";
            static const char* STYLE_ALIGN_CONTENT_FLEX_END_MIDDLE_LINE = "flex-end";
            static const char* STYLE_ALIGN_CONTENT_CENTER = "center";
            static const char* STYLE_ALIGN_CONTENT_SPACE_AROUND = "spaceAround";
            static const char* STYLE_ALIGN_CONTENT_SPACE_BETWEEN = "spaceBetween";
            static const char* STYLE_ALIGN_CONTENT_SPACE_AROUND_MIDDLE_LINE = "space-around";
            static const char* STYLE_ALIGN_CONTENT_SPACE_BETWEEN_MIDDLE_LINE = "space-between";
            static const char* STYLE_ALIGN_CONTENT_STRETCH = "stretch";
            static const char* STYLE_JUSTIFY_CONTENT = "justifyContent";
            static const char* STYLE_JUSTIFY_CONTENT_CENTER = "center";
            static const char* STYLE_JUSTIFY_CONTENT_FLEX_END = "flexEnd";
            static const char* STYLE_JUSTIFY_CONTENT_FLEX_START = "flexStart";
            static const char* STYLE_JUSTIFY_CONTENT_SPACE_BETWEEN = "spaceBetween";
            static const char* STYLE_JUSTIFY_CONTENT_SPACE_AROUND = "spaceAround";
            static const char* STYLE_JUSTIFY_CONTENT_FLEX_END_MIDDLE_LINE = "flex-end";
            static const char* STYLE_JUSTIFY_CONTENT_FLEX_START_MIDDLE_LINE = "flex-start";
            static const char* STYLE_JUSTIFY_CONTENT_SPACE_BETWEEN_MIDDLE_LINE = "space-between";
            static const char* STYLE_JUSTIFY_CONTENT_SPACE_AROUND_MIDDLE_LINE = "space-around";
            static const char* STYLE_ALIGN_SELF = "alignSelf";
            static const char* STYLE_ALIGN_SELF_NORMAL = "normal";
            static const char* STYLE_ALIGN_SELF_BASELINE = "baseline";
            static const char* STYLE_ALIGN_SELF_LAST_BASE_LINE = "lastBaseline";
            static const char* STYLE_ALIGN_SELF_CENTER = "center";
            static const char* STYLE_ALIGN_SELF_END = "end";
            static const char* STYLE_ALIGN_SELF_FLEX_END = "flexEnd";
            static const char* STYLE_ALIGN_SELF_FLEX_START = "flexStart";
            static const char* STYLE_ALIGN_SELF_LEFT = "left";
            static const char* STYLE_ALIGN_SELF_RIGHT = "right";
            static const char* STYLE_ALIGN_SELF_START = "start";
            static const char* STYLE_ALIGN_SELF_STRETCH = "stretch";
            static const char* STYLE_ALIGN_SELF_SELF_START = "selfStart";
            static const char* STYLE_ALIGN_SELF_SELF_END = "selfEnd";
            static const char* STYLE_VERTICAL_ALIGN = "verticalAlign";
            static const char* STYLE_VERTICAL_ALIGN_BASELINE_MIDDLE = "baselineMiddle";
            static const char* STYLE_VERTICAL_ALIGN_BASELINE_MIDDLE_MIDDLE_LINE = "baseline-middle";
            static const char* STYLE_VERTICAL_ALIGN_BASELINE = "baseline";
            static const char* STYLE_VERTICAL_ALIGN_MIDDLE = "middle";
            static const char* STYLE_VERTICAL_ALIGN_BOTTOM = "bottom";
            static const char* STYLE_VERTICAL_ALIGN_TOP = "top";
            static const char* STYLE_VERTICAL_ALIGN_SUB = "sub";
            static const char* STYLE_VERTICAL_ALIGN_SUPER = "super";
            static const char* STYLE_VERTICAL_ALIGN_TEXT_BOTTOM = "textBottom";
            static const char* STYLE_VERTICAL_ALIGN_TEXT_TOP  = "textTop";
            static const char* STYLE_VERTICAL_ALIGN_TEXT_BOTTOM_MIDDLE_LINE = "text-bottom";
            static const char* STYLE_VERTICAL_ALIGN_TEXT_TOP_MIDDLE_LINE  = "text-top";
            static const char* STYLE_ORDER = "order";
            static const char* STYLE_OPACITY  = "opacity";
            static const char* STYLE_Z_INDEX  = "zIndex";
            static const char* STYLE_VISIBILITY  = "visibility";
            static const char* STYLE_VISIBILITY_HIDDEN  = "hidden";
            static const char* STYLE_VISIBILITY_COLLAPSE  = "collapse";
            static const char* STYLE_VISIBILITY_VISIBLE  = "visible";
            static const char* STYLE_FONT_WEIGHT = "fontWeight";
            static const char* STYLE_FONT_WEIGHT_NORMAL = "normal";
            static const char* STYLE_FONT_WEIGHT_BOLD = "bold";
            static const char* STYLE_FONT_WEIGHT_100 = "100";
            static const char* STYLE_FONT_WEIGHT_200 = "200";
            static const char* STYLE_FONT_WEIGHT_300 = "300";
            static const char* STYLE_FONT_WEIGHT_400 = "400";
            static const char* STYLE_FONT_WEIGHT_500 = "500";
            static const char* STYLE_FONT_WEIGHT_600 = "600";
            static const char* STYLE_FONT_WEIGHT_700 = "700";
            static const char* STYLE_FONT_WEIGHT_800 = "800";
            static const char* STYLE_FONT_WEIGHT_900 = "900";
            static const char* STYLE_FONT_STYLE = "fontStyle";
            static const char* STYLE_FONT_STYLE_NORMAL = "normal";
            static const char* STYLE_FONT_STYLE_ITALIC = "italic";
            static const char* STYLE_FONT_FAMILY = "fontFamily";
            static const char* STYLE_FONT_COLOR = "fontColor";
            static const char* STYLE_LINE_HEIGHT = "lineHeight";
            static const char* STYLE_LINES = "lines";
            static const char* STYLE_COLOR = "color";
            static const char* STYLE_TEXT_ALIGN = "textAlign";
            static const char* STYLE_TEXT_ALIGN_START = "start";
            static const char* STYLE_TEXT_ALIGN_END = "end";
            static const char* STYLE_TEXT_ALIGN_LEFT = "left";
            static const char* STYLE_TEXT_ALIGN_RIGHT = "right";
            static const char*STYLE_TEXT_ALIGN_CENTER = "center";
            static const char* STYLE_TEXT_JUSTIFY = "textJustify";
            static const char* STYLE_TEXT_JUSTIFY_AUTO = "auto";
            static const char* STYLE_TEXT_JUSTIFY_NONE = "none";
            static const char* STYLE_TEXT_JUSTIFY_INTER_WORD = "inter-word";
            static const char* STYLE_TEXT_JUSTIFY_INNER_IDEOGRAPH = "inter-ideograph";
            static const char* STYLE_TEXT_JUSTIFY_INNER_CLUSTER = "inter-cluster";
            static const char* STYLE_TEXT_JUSTIFY_DISTRIBUTE = "distribute";
            static const char* STYLE_TEXT_JUSTIFY_KASHIDA = "kashida";
            static const char* STYLE_BOX_SHADOW = "boxShadow";
            static const char* STYLE_BOX_SHADOW_INSET = "inset";
            static const char* STYLE_BOX_SHADOW_OUTSET = "outset";
            static const char* STYLE_TEXT_SHADOW = "textShadow";
            static const char* STYLE_OVERFLOW_WRAP = "overflowWrap";
            static const char* STYLE_OVERFLOW_WRAP_NORMAL = "normal";
            static const char* STYLE_OVERFLOW_WRAP_BREAK_WORLD = "breakWorld";
            static const char* STYLE_OVERFLOW_X = "overflowX";
            static const char* STYLE_OVERFLOW_Y = "overflowY";
            static const char* STYLE_OVERFLOW = "overflow";
            static const char* STYLE_OVERFLOW_VISIBLE = "visible";
            static const char* STYLE_OVERFLOW_HIDDEN = "hidden";
            static const char* STYLE_OVERFLOW_AUTO = "auto";
            static const char* STYLE_OVERFLOW_OVERLAY = "overlay";
            static const char* STYLE_WORD_BREAK = "wordBreak";
            static const char* STYLE_WORD_BREAK_NORMAL = "normal";
            static const char* STYLE_WORD_BREAK_BREAK_ALL = "breakAll";
            static const char* STYLE_WORD_BREAK_KEEP_ALL = "keepAll";
            static const char* STYLE_WHITE_SPACE = "whiteSpace";
            static const char* STYLE_WHITE_SPACE_NORMAL = "normal";
            static const char* STYLE_WHITE_SPACE_PRE = "pre";
            static const char* STYLE_WHITE_SPACE_NO_WRAP = "nowrap";
            static const char* STYLE_WHITE_SPACE_PRE_WRAP = "preWrap";
            static const char* STYLE_WHITE_SPACE_PRE_LINE = "preLine";
            static const char* STYLE_TEXT_OVERFLOW = "textOverflow";
            static const char* STYLE_TEXT_OVERFLOW_CLIP = "clip";
            static const char* STYLE_TEXT_OVERFLOW_ELLIPSIS = "ellipsis";
            static const char* STYLE_TEXT_INDENT = "textIndent";
            static const char* STYLE_TEXT_DIRECTION = "direction";
            static const char* STYLE_TEXT_DIRECTION_RTL = "rtl";
            static const char* STYLE_TEXT_DIRECTION_LTR = "ltr";
            static const char* STYLE_TEXT_DECORATION = "textDecoration";
            static const char* STYLE_TEXT_DECORATION_NONE = "none";
            static const char* STYLE_TEXT_DECORATION_UNDERLINE = "underline";
            static const char* STYLE_TEXT_DECORATION_OVERLINE = "overline";
            static const char* STYLE_TEXT_DECORATION_LINE_THROUGH = "line-through";
            static const char* STYLE_TEXT_DECORATION_BLINK = "blink";
            static const char* STYLE_TEXT_DECORATION_COLOR = "textDecorationColor";
            static const char* STYLE_TEXT_DECORATION_STYLE = "textDecorationStyle";
            static const char* STYLE_TEXT_DECORATION_STYLE_SOLID = "solid";
            static const char* STYLE_TEXT_DECORATION_STYLE_DOUBLE = "double";
            static const char* STYLE_TEXT_DECORATION_STYLE_DOTTED = "dotted";
            static const char* STYLE_TEXT_DECORATION_STYLE_DASHED = "dashed";
            static const char* STYLE_TEXT_DECORATION_STYLE_WAVY = "wavy";
            static const char* STYLE_LETTER_SPACING = "letterSpacing";
            static const char* STYLE_WORD_SPACING = "wordSpacing";
            static const char* STYLE_BOX_SIZING = "boxSizing";
            static const char* STYLE_BOX_SIZING_CONTENT_BOX = "contentBox";
            static const char* STYLE_BOX_SIZING_BORDER_BOX = "borderBox";
            static const char* STYLE_RGBA = "rgba";
            static const char* STYLE_RGBA_PREFIX = "rgba(";
            static const char STYLE_RGBA_SEPARATOR = ',';
            static const char* STYLE_RGB = "rgb";
            static const char* STYLE_RGB_PREFIX = "rgb(";
            static const char  STYLE_RGB_SEPARATOR = ',';
            static const char* STYLE_BACKGROUND_IMAGE_URL = "url";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR = "linear-gradient";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_RIGHT = "toright";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_LEFT = "toleft";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_BOTTOM = "tobottom";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_TOP = "totop";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_BOTTOM_RIGHT = "tobottomright";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_RIGHT_BOTTOM = "torightbottom";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_TOP_RIGHT = "totopright";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_RIGHT_TOP = "torighttop";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_BOTTOM_LEFT = "tobottomleft";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_LEFT_BOTTOM = "toleftbottom";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_TOP_LEFT = "totopleft";
            static const char* STYLE_BACKGROUND_IMAGE_LINEAR_TO_LEFT_TOP = "tolefttop";
            static const char* STYLE_BACKGROUND_REPEAT = "backgroundRepeat";
            static const char* STYLE_BACKGROUND_REPEAT_REPEAT = "repeat";
            static const char* STYLE_BACKGROUND_REPEAT_REPEAT_X = "repeat-x";
            static const char* STYLE_BACKGROUND_REPEAT_REPEAT_Y = "repeat-y";
            static const char* STYLE_BACKGROUND_REPEAT_NO_REPEAT = "no-repeat";
            static const char* STYLE_BACKGROUND_SIZE = "backgroundSize";
            static const char* STYLE_BACKGROUND_SIZE_COVER = "cover";
            static const char* STYLE_BACKGROUND_SIZE_CONTAIN = "contain";
            static const char* STYLE_BACKGROUND_POSITION  = "backgroundPosition";
            static const char* STYLE_BACKGROUND_POSITION_LEFT = "left";
            static const char* STYLE_BACKGROUND_POSITION_RIGHT = "right";
            static const char* STYLE_BACKGROUND_POSITION_BOTTOM = "bottom";
            static const char* STYLE_BACKGROUND_POSITION_TOP = "top";
            static const char* STYLE_BACKGROUND_POSITION_CENTER = "center";
            static const char* STYLE_TRANSITION_DURATION = "transitionDuration";
            static const char* STYLE_TRANSITION_PROPERTY = "transitionProperty";
            static const char* STYLE_TRANSITION_DELAY = "transitionDelay";
            static const char* STYLE_TRANSITION_TIMING_FUNCTION = "transitionTimingFunction";
            static const char* STYLE_TRANSITION_TIME_FUNCTION_CUBIC_BEZIER = "cubic-bezier";
            static const char* STYLE_TRANSITION_TIME_FUNCTION_EASE = "ease";
            static const char* STYLE_TRANSITION_TIME_FUNCTION_EASE_IN = "ease-in";
            static const char* STYLE_TRANSITION_TIME_FUNCTION_EASE_OUT = "ease-out";
            static const char* STYLE_TRANSITION_TIME_FUNCTION_EASE_IN_OUT = "ease-in-out";
            static const char* STYLE_TRANSITION_TIME_FUNCTION_LINEAR = "linear";
            static const char* STYLE_TRANSFORM = "transform";
            static const char* STYLE_TRANSFORM_TRANSLATE = "translate";
            static const char* STYLE_TRANSFORM_TRANSLATE_X = "translateX";
            static const char* STYLE_TRANSFORM_TRANSLATE_Y = "translateY";
            static const char* STYLE_TRANSFORM_TRANSLATE_Z = "translateZ";
            static const char* STYLE_TRANSFORM_TRANSLATE_3D = "translate3d";
            static const char* STYLE_TRANSFORM_SCALE = "scale";
            static const char* STYLE_TRANSFORM_SCALE_X = "scaleX";
            static const char* STYLE_TRANSFORM_SCALE_Y = "scaleY";
            static const char* STYLE_TRANSFORM_SCALE_Z = "scaleY";
            static const char* STYLE_TRANSFORM_SCALE_3D = "scale3d";
            static const char* STYLE_TRANSFORM_ROTATE = "rotate";
            static const char* STYLE_TRANSFORM_ROTATE_X = "rotateX";
            static const char* STYLE_TRANSFORM_ROTATE_Y = "rotateY";
            static const char* STYLE_TRANSFORM_ROTATE_Z = "rotateY";
            static const char* STYLE_TRANSFORM_ROTATE_3D = "rotate3d";
            static const char* STYLE_TRANSFORM_PERSPECTIVE = "perspective";
            static const char* STYLE_TRANSFORM_SKEW  = "skew";
            static const char* STYLE_TRANSFORM_SKEW_X = "skewX";
            static const char* STYLE_TRANSFORM_SKEW_Y = "skewY";
            static const char* STYLE_TRANSFORM_MATRIX  = "matrix";
            static const char* STYLE_TRANSFORM_MATRIX_3D = "matrix3d";
            static const char* STYLE_TRANSFORM_ORIGIN = "transformOrigin";
            static const char* STYLE_TRANSFORM_ORIGIN_LEFT = "left";
            static const char* STYLE_TRANSFORM_ORIGIN_CENTER = "center";
            static const char* STYLE_TRANSFORM_ORIGIN_RIGHT = "right";
            static const char* STYLE_TRANSFORM_ORIGIN_TOP = "top";
            static const char* STYLE_TRANSFORM_ORIGIN_BOTTOM = "bottom";
            static const char* STYLE_TRANSFORM_STYLE = "transformStyle";
            static const char* STYLE_TRANSFORM_STYLE_FLAT = "flat";
            static const char* STYLE_TRANSFORM_STYLE_PRESERVE_3D = "preserve-3d";
        }

        namespace Attr{

            static const char* ATTR_SRC = "src";
            static const char* ATTR_VALUE = "value";
            static const char* ATTR_RESIZE = "resize";
            static const char* ATTR_PLACEHOLDER = "placeholder";
            static const char* ATTR_PLACE_HOLDER = "placeHolder";
            static const char* ATTR_RESIZE_COVER = "cover";
            static const char* ATTR_RESIZE_CONTAIN = "contain";
            static const char* ATTR_ARIA_LABEL = "ariaLabel";
            static const char* ATTR_ARIA_HIDDEN = "ariaHidden";
            static const char* ATTR_ROLE = "role";
            static const char* ATTR_SPACE_RID_ONE = "spaceridone";

            namespace Value{
                static const char* VALUE_ELLIPSIS  = "...";
                static const char* ATTR_VALUE_TRUE = "true";
            }

        }

        namespace Unit {
            static const char* PERCENT = "%";
            static const char* DEG = "deg";
            static const char* TURN = "turn";
            static const char* RAD = "rad";
        }

        namespace Color{
            static const char* STYLE_COLOR_A_LINK = "#018efb";
        }

        namespace Font{
            static const char* STYLE_FONT_NAME_SANS_SERIF = "sans-serif";
            static const char* STYLE_FONT_NAME_SERIF = "serif";
            static const char* STYLE_FONT_NAME_SERIF_MONOSPACE = "serif-monospace";
        }
    }

    static const int NODE_LAYOUT_EDGE_LEFT = 0;
    static const int NODE_LAYOUT_EDGE_TOP = 1;
    static const int NODE_LAYOUT_EDGE_WIDTH = 2;
    static const int NODE_LAYOUT_EDGE_HEIGHT = 3;

    static const std::string EMPTY_STRING = "";

    namespace Event{

        namespace RequestEventType{
            static const int HITTEST = 0;
            static const int ACCESSIBILITY = 16;
        }
    }

    namespace Scroller{
        static const char* SCROLL_DIRECTION = "scrollDirection";
        static const char* SCROLL_DIRECTION_VERTICAL = "vertical";
        static const char* SCROLL_DIRECTION_HORIZONTAL = "horizontal";
    }
}

#endif //FLUTTERCORE_NODESTYLES_H
