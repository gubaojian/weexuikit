//
// Created by furture on 2018/8/27.
//

#include "ColorMap.h"


namespace weexuikit {

    ColorMap* ColorMap::mColorMapInstance = nullptr;

    ColorMap* ColorMap::getInstance() {
        if(mColorMapInstance == nullptr){
            mColorMapInstance = new ColorMap();
        }
        return mColorMapInstance;
    }

    ColorMap::ColorMap() {
        mColorMap = new std::map<std::string,blink::RGBA32>();
        mColorMap->insert({"aliceblue", 0XFFF0F8FF});
        mColorMap->insert({"antiquewhite", 0XFFFAEBD7});
        mColorMap->insert({"aqua", 0XFF00FFFF});
        mColorMap->insert({"aquamarine", 0XFF7FFFD4});
        mColorMap->insert({"azure", 0XFFF0FFFF});
        mColorMap->insert({"beige", 0XFFF5F5DC});
        mColorMap->insert({"bisque", 0XFFFFE4C4});
        mColorMap->insert({"black", 0XFF000000});
        mColorMap->insert({"blanchedalmond", 0XFFFFEBCD});
        mColorMap->insert({"blue", 0XFF0000FF});
        mColorMap->insert({"blueviolet", 0XFF8A2BE2});
        mColorMap->insert({"brown", 0XFFA52A2A});
        mColorMap->insert({"burlywood", 0XFFDEB887});
        mColorMap->insert({"cadetblue", 0XFF5F9EA0});
        mColorMap->insert({"chartreuse", 0XFF7FFF00});
        mColorMap->insert({"chocolate", 0XFFD2691E});
        mColorMap->insert({"coral", 0XFFFF7F50});
        mColorMap->insert({"cornflowerblue", 0XFF6495ED});
        mColorMap->insert({"cornsilk", 0XFFFFF8DC});
        mColorMap->insert({"crimson", 0XFFDC143C});
        mColorMap->insert({"cyan", 0XFF00FFFF});
        mColorMap->insert({"darkblue", 0XFF00008B});
        mColorMap->insert({"darkcyan", 0XFF008B8B});
        mColorMap->insert({"darkgoldenrod", 0XFFB8860B});
        mColorMap->insert({"darkgray", 0XFFA9A9A9});
        mColorMap->insert({"darkgreen", 0XFF006400});
        mColorMap->insert({"darkkhaki", 0XFFBDB76B});
        mColorMap->insert({"darkmagenta", 0XFF8B008B});
        mColorMap->insert({"darkolivegreen", 0XFF556B2F});
        mColorMap->insert({"darkorange", 0XFFFF8C00});
        mColorMap->insert({"darkorchid", 0XFF9932CC});
        mColorMap->insert({"darkred", 0XFF8B0000});
        mColorMap->insert({"darksalmon", 0XFFE9967A});
        mColorMap->insert({"darkseagreen", 0XFF8FBC8F});
        mColorMap->insert({"darkslateblue", 0XFF483D8B});
        mColorMap->insert({"darkslategray", 0XFF2F4F4F});
        mColorMap->insert({"darkslategrey", 0XFF2F4F4F});
        mColorMap->insert({"darkturquoise", 0XFF00CED1});
        mColorMap->insert({"darkviolet", 0XFF9400D3});
        mColorMap->insert({"deeppink", 0XFFFF1493});
        mColorMap->insert({"deepskyblue", 0XFF00BFFF});
        mColorMap->insert({"dimgray", 0XFF696969});
        mColorMap->insert({"dimgrey", 0XFF696969});
        mColorMap->insert({"dodgerblue", 0XFF1E90FF});
        mColorMap->insert({"firebrick", 0XFFB22222});
        mColorMap->insert({"floralwhite", 0XFFFFFAF0});
        mColorMap->insert({"forestgreen", 0XFF228B22});
        mColorMap->insert({"fuchsia", 0XFFFF00FF});
        mColorMap->insert({"gainsboro", 0XFFDCDCDC});
        mColorMap->insert({"ghostwhite", 0XFFF8F8FF});
        mColorMap->insert({"gold", 0XFFFFD700});
        mColorMap->insert({"goldenrod", 0XFFDAA520});
        mColorMap->insert({"gray", 0XFF808080});
        mColorMap->insert({"grey", 0XFF808080});
        mColorMap->insert({"green", 0XFF008000});
        mColorMap->insert({"greenyellow", 0XFFADFF2F});
        mColorMap->insert({"honeydew", 0XFFF0FFF0});
        mColorMap->insert({"hotpink", 0XFFFF69B4});
        mColorMap->insert({"indianred", 0XFFCD5C5C});
        mColorMap->insert({"indigo", 0XFF4B0082});
        mColorMap->insert({"ivory", 0XFFFFFFF0});
        mColorMap->insert({"khaki", 0XFFF0E68C});
        mColorMap->insert({"lavender", 0XFFE6E6FA});
        mColorMap->insert({"lavenderblush", 0XFFFFF0F5});
        mColorMap->insert({"lawngreen", 0XFF7CFC00});
        mColorMap->insert({"lemonchiffon", 0XFFFFFACD});
        mColorMap->insert({"lightblue", 0XFFADD8E6});
        mColorMap->insert({"lightcoral", 0XFFF08080});
        mColorMap->insert({"lightcyan", 0XFFE0FFFF});
        mColorMap->insert({"lightgoldenrodyellow", 0XFFFAFAD2});
        mColorMap->insert({"lightgray", 0XFFD3D3D3});
        mColorMap->insert({"lightgrey", 0XFFD3D3D3});
        mColorMap->insert({"lightgreen", 0XFF90EE90});
        mColorMap->insert({"lightpink", 0XFFFFB6C1});
        mColorMap->insert({"lightsalmon", 0XFFFFA07A});
        mColorMap->insert({"lightseagreen", 0XFF20B2AA});
        mColorMap->insert({"lightskyblue", 0XFF87CEFA});
        mColorMap->insert({"lightslategray", 0XFF778899});
        mColorMap->insert({"lightslategrey", 0XFF778899});
        mColorMap->insert({"lightsteelblue", 0XFFB0C4DE});
        mColorMap->insert({"lightyellow", 0XFFFFFFE0});
        mColorMap->insert({"lime", 0XFF00FF00});
        mColorMap->insert({"limegreen", 0XFF32CD32});
        mColorMap->insert({"linen", 0XFFFAF0E6});
        mColorMap->insert({"magenta", 0XFFFF00FF});
        mColorMap->insert({"maroon", 0XFF800000});
        mColorMap->insert({"mediumaquamarine", 0XFF66CDAA});
        mColorMap->insert({"mediumblue", 0XFF0000CD});
        mColorMap->insert({"mediumorchid", 0XFFBA55D3});
        mColorMap->insert({"mediumpurple", 0XFF9370DB});
        mColorMap->insert({"mediumseagreen", 0XFF3CB371});
        mColorMap->insert({"mediumslateblue", 0XFF7B68EE});
        mColorMap->insert({"mediumspringgreen", 0XFF00FA9A});
        mColorMap->insert({"mediumturquoise", 0XFF48D1CC});
        mColorMap->insert({"mediumvioletred", 0XFFC71585});
        mColorMap->insert({"midnightblue", 0XFF191970});
        mColorMap->insert({"mintcream", 0XFFF5FFFA});
        mColorMap->insert({"mistyrose", 0XFFFFE4E1});
        mColorMap->insert({"moccasin", 0XFFFFE4B5});
        mColorMap->insert({"navajowhite", 0XFFFFDEAD});
        mColorMap->insert({"navy", 0XFF000080});
        mColorMap->insert({"oldlace", 0XFFFDF5E6});
        mColorMap->insert({"olive", 0XFF808000});
        mColorMap->insert({"olivedrab", 0XFF6B8E23});
        mColorMap->insert({"orange", 0XFFFFA500});
        mColorMap->insert({"orangered", 0XFFFF4500});
        mColorMap->insert({"orchid", 0XFFDA70D6});
        mColorMap->insert({"palegoldenrod", 0XFFEEE8AA});
        mColorMap->insert({"palegreen", 0XFF98FB98});
        mColorMap->insert({"paleturquoise", 0XFFAFEEEE});
        mColorMap->insert({"palevioletred", 0XFFDB7093});
        mColorMap->insert({"papayawhip", 0XFFFFEFD5});
        mColorMap->insert({"peachpuff", 0XFFFFDAB9});
        mColorMap->insert({"peru", 0XFFCD853F});
        mColorMap->insert({"pink", 0XFFFFC0CB});
        mColorMap->insert({"plum", 0XFFDDA0DD});
        mColorMap->insert({"powderblue", 0XFFB0E0E6});
        mColorMap->insert({"purple", 0XFF800080});
        mColorMap->insert({"rebeccapurple", 0XFF663399});
        mColorMap->insert({"red", 0XFFFF0000});
        mColorMap->insert({"rosybrown", 0XFFBC8F8F});
        mColorMap->insert({"royalblue", 0XFF4169E1});
        mColorMap->insert({"saddlebrown", 0XFF8B4513});
        mColorMap->insert({"salmon", 0XFFFA8072});
        mColorMap->insert({"sandybrown", 0XFFF4A460});
        mColorMap->insert({"seagreen", 0XFF2E8B57});
        mColorMap->insert({"seashell", 0XFFFFF5EE});
        mColorMap->insert({"sienna", 0XFFA0522D});
        mColorMap->insert({"silver", 0XFFC0C0C0});
        mColorMap->insert({"skyblue", 0XFF87CEEB});
        mColorMap->insert({"slateblue", 0XFF6A5ACD});
        mColorMap->insert({"slategray", 0XFF708090});
        mColorMap->insert({"slategrey", 0XFF708090});
        mColorMap->insert({"snow", 0XFFFFFAFA});
        mColorMap->insert({"springgreen", 0XFF00FF7F});
        mColorMap->insert({"steelblue", 0XFF4682B4});
        mColorMap->insert({"tan", 0XFFD2B48C});
        mColorMap->insert({"teal", 0XFF008080});
        mColorMap->insert({"thistle", 0XFFD8BFD8});
        mColorMap->insert({"tomato", 0XFFFF6347});
        mColorMap->insert({"turquoise", 0XFF40E0D0});
        mColorMap->insert({"violet", 0XFFEE82EE});
        mColorMap->insert({"wheat", 0XFFF5DEB3});
        mColorMap->insert({"white", 0XFFFFFFFF});
        mColorMap->insert({"whitesmoke", 0XFFF5F5F5});
        mColorMap->insert({"yellow", 0XFFFFFF00});
        mColorMap->insert({"yellowgreen", 0XFF9ACD32});
        mColorMap->insert({"transparent", 0x00000000});
    }

    ColorMap::~ColorMap() {
        if(mColorMap != nullptr){
            delete  mColorMap;
            mColorMap = nullptr;
        }
    }
}
