package com.test.weex.render.html;

import android.text.TextUtils;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.util.Map;
import java.util.Set;

/**
 * Created by furture on 2018/9/7.
 */

public class HtmlTool {

    public static String toHtml(JSONObject root){
        StringBuilder tags = new StringBuilder();
        tags.append("<template>\n" +
                "  <scroller class=\"wrapper\">\n");
        toHtmlTag(tags, root, 2);
        tags.append("  </scroller>\n" +
                "</template>\n");

        StringBuilder styles = new StringBuilder();
        styles.append("<style scoped>\n");
        toHtmlStyle(styles, root);
        styles.append("</style>\n");

        return tags  + "\n"+ styles;
    }

    public static void toHtmlTag(StringBuilder sb, JSONObject root, int level){
        StringBuilder space = new StringBuilder();
        for(int i=0 ;i< level; i++){
            space.append("    ");
        }
        String type = root.getString("type");
        sb.append(space.toString() + "<" + type);
        if(root.containsKey("style")){
            sb.append(" class=\"" + toClassName(root.getString("ref")) + "\"");
        }

        JSONObject attr = root.getJSONObject("attr");
        Object value = null;
        if(attr != null){
            value = attr.remove("value");
            Set<Map.Entry<String,Object>> entrySet = attr.entrySet();
            for(Map.Entry<String,Object> entry : entrySet){
                if(entry.getValue() == null){
                    continue;
                }
                if(entry.getKey().length() > 0 && entry.getKey().charAt(0) == '@'){
                    continue;
                }
                sb.append(" ");
                sb.append(entry.getKey());
                sb.append("=");
                sb.append("\"");
                sb.append(entry.getValue());
                sb.append("\"");
            }
        }
        if(type.equals("text")){
            sb.append(">");
            if(value != null){
                sb.append(value.toString());
            }
            sb.append("</" +    root.getString("type") + ">\n");
            return;
        }else{
            sb.append(">\n");
        }


        if(root.containsKey("children")){
           JSONArray array =  root.getJSONArray("children");
           for(int i=0; i<array.size(); i++){
               toHtmlTag(sb, array.getJSONObject(i), level + 1);
           }
        }
        sb.append(space.toString() + "</" +    root.getString("type") + ">\n");
    }

    public static void toHtmlStyle(StringBuilder style, JSONObject root){
        JSONObject styleObject = root.getJSONObject("style");
        if(styleObject != null && styleObject.size() > 0){
            style.append("." +    toClassName(root.getString("ref")) + "{\n");
            Set<Map.Entry<String,Object>> entrySet = styleObject.entrySet();
            for(Map.Entry<String,Object> entry : entrySet){
                style.append("    ");
                style.append(toStyleKey(entry.getKey()));
                style.append(":");
                style.append(entry.getValue());
                style.append(';');
                style.append('\n');
            }
            style.append("}\n");
        }
        if(root.containsKey("children")){
            JSONArray array =  root.getJSONArray("children");
            for(int i=0; i<array.size(); i++){
                toHtmlStyle(style, array.getJSONObject(i));
            }
        }
    }

    private static String toStyleKey(String key) {
        StringBuilder builder = new StringBuilder(key);
        for(int i=0; i<builder.length(); i++){
            if(Character.isUpperCase(builder.charAt(i))){
                builder.setCharAt(i, Character.toLowerCase(builder.charAt(i)));
                builder.insert(i, '-');
            }
        }
        return builder.toString();
    }

    private static String toClassName(String ref){
        StringBuilder builder = new StringBuilder(ref);
        for(int i=0; i<builder.length(); i++){
            if(Character.isDigit(builder.charAt(i))){
                int space =  'a' + builder.charAt(i) - '0';
                builder.setCharAt(i, (char)space);
            }
        }
        return builder.toString();
    }

    public static void main(String[] args){
        String html = "{\n" +
                "    \"attr\": {\n" +
                "        \"doctype\": \"weexrender\"\n" +
                "    }, \n" +
                "    \"children\": [\n" +
                "        {\n" +
                "            \"attr\": {\n" +
                "                \"href\": \"https://market.m.taobao.com/app/idleFish-F2e/idleFish-circleRangel/rentlist?wh_weex=true&wx_navbar_transparent=true&spm=widle.tbhome.1.1\"\n" +
                "            }, \n" +
                "            \"children\": [\n" +
                "                {\n" +
                "                    \"children\": [\n" +
                "                        {\n" +
                "                            \"children\": [\n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"value\": \"闲鱼租房\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39632\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"color\": \"#FF7936\", \n" +
                "                                        \"fontFamily\": \"PingFangSC-Medium\", \n" +
                "                                        \"fontSize\": \"32px\", \n" +
                "                                        \"lineHeight\": \"32px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"text\"\n" +
                "                                }, \n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"value\": \"免中介费\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39634\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"backgroundColor\": \"#FF7936\", \n" +
                "                                        \"borderRadius\": \"6px\", \n" +
                "                                        \"color\": \"rgb(255,255,255)\", \n" +
                "                                        \"fontFamily\": \"PingFangSC-Medium\", \n" +
                "                                        \"fontSize\": \"20px\", \n" +
                "                                        \"marginLeft\": \"8px\", \n" +
                "                                        \"paddingBottom\": \"4px\", \n" +
                "                                        \"paddingLeft\": \"10px\", \n" +
                "                                        \"paddingRight\": \"10px\", \n" +
                "                                        \"paddingTop\": \"4px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"text\"\n" +
                "                                }\n" +
                "                            ], \n" +
                "                            \"ref\": \"39630\", \n" +
                "                            \"style\": {\n" +
                "                                \"alignItems\": \"center\", \n" +
                "                                \"flexDirection\": \"row\", \n" +
                "                                \"height\": \"32px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"div\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"value\": \"真实房东 超多房源\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39636\", \n" +
                "                            \"style\": {\n" +
                "                                \"color\": \"rgb(136,136,136)\", \n" +
                "                                \"fontFamily\": \"PingFangSC-Regular\", \n" +
                "                                \"fontSize\": \"26px\", \n" +
                "                                \"lineHeight\": \"28px\", \n" +
                "                                \"marginTop\": \"8px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"text\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"children\": [\n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"defaultHeight\": \"750\", \n" +
                "                                        \"src\": \"https://gw.alicdn.com/tfs/TB16kr.fbGYBuNjy0FoXXciBFXa-160-160.png\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39642\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"display\": \"flex\", \n" +
                "                                        \"height\": \"120px\", \n" +
                "                                        \"marginLeft\": \"14px\", \n" +
                "                                        \"marginRight\": \"6px\", \n" +
                "                                        \"width\": \"120px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"image\"\n" +
                "                                }, \n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"defaultHeight\": \"750\", \n" +
                "                                        \"src\": \"https://gw.alicdn.com/tfs/TB1qi3WfhGYBuNjy0FnXXX5lpXa-160-160.png\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39645\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"display\": \"flex\", \n" +
                "                                        \"height\": \"120px\", \n" +
                "                                        \"marginLeft\": \"14px\", \n" +
                "                                        \"marginRight\": \"6px\", \n" +
                "                                        \"width\": \"120px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"image\"\n" +
                "                                }\n" +
                "                            ], \n" +
                "                            \"ref\": \"39639\", \n" +
                "                            \"style\": {\n" +
                "                                \"alignItems\": \"center\", \n" +
                "                                \"flexDirection\": \"row\", \n" +
                "                                \"marginTop\": \"12px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"div\"\n" +
                "                        }\n" +
                "                    ], \n" +
                "                    \"ref\": \"39627\", \n" +
                "                    \"style\": {\n" +
                "                        \"backgroundColor\": \"rgba(120,123,128,0.1)\", \n" +
                "                        \"borderRadius\": \"10px\", \n" +
                "                        \"flex\": \"1\", \n" +
                "                        \"marginBottom\": \"8px\", \n" +
                "                        \"marginLeft\": \"8px\", \n" +
                "                        \"marginRight\": \"8px\", \n" +
                "                        \"marginTop\": \"8px\", \n" +
                "                        \"paddingBottom\": \"20px\", \n" +
                "                        \"paddingLeft\": \"24px\", \n" +
                "                        \"paddingTop\": \"20px\", \n" +
                "                        \"width\": \"334px\"\n" +
                "                    }, \n" +
                "                    \"type\": \"div\"\n" +
                "                }\n" +
                "            ], \n" +
                "            \"event\": [\n" +
                "                \"click\"\n" +
                "            ], \n" +
                "            \"ref\": \"39624\", \n" +
                "            \"style\": {\n" +
                "                \"cursor\": \"pointer\"\n" +
                "            }, \n" +
                "            \"type\": \"div\"\n" +
                "        }, \n" +
                "        {\n" +
                "            \"attr\": {\n" +
                "                \"href\": \"https://market.m.taobao.com/markets/idletrade/recycle/all_out?wh_weex=true&spm=widle.tbhome.1.1\"\n" +
                "            }, \n" +
                "            \"children\": [\n" +
                "                {\n" +
                "                    \"children\": [\n" +
                "                        {\n" +
                "                            \"children\": [\n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"value\": \"信用速卖\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39656\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"color\": \"#FF5338\", \n" +
                "                                        \"fontFamily\": \"PingFangSC-Medium\", \n" +
                "                                        \"fontSize\": \"32px\", \n" +
                "                                        \"lineHeight\": \"32px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"text\"\n" +
                "                                }, \n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"value\": \"加价10%\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39658\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"backgroundColor\": \"#FF5338\", \n" +
                "                                        \"borderRadius\": \"6px\", \n" +
                "                                        \"color\": \"rgb(255,255,255)\", \n" +
                "                                        \"fontFamily\": \"PingFangSC-Medium\", \n" +
                "                                        \"fontSize\": \"20px\", \n" +
                "                                        \"marginLeft\": \"8px\", \n" +
                "                                        \"paddingBottom\": \"4px\", \n" +
                "                                        \"paddingLeft\": \"10px\", \n" +
                "                                        \"paddingRight\": \"10px\", \n" +
                "                                        \"paddingTop\": \"4px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"text\"\n" +
                "                                }\n" +
                "                            ], \n" +
                "                            \"ref\": \"39654\", \n" +
                "                            \"style\": {\n" +
                "                                \"alignItems\": \"center\", \n" +
                "                                \"flexDirection\": \"row\", \n" +
                "                                \"height\": \"32px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"div\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"value\": \"极速回收 先收钱后寄货\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39660\", \n" +
                "                            \"style\": {\n" +
                "                                \"color\": \"rgb(136,136,136)\", \n" +
                "                                \"fontFamily\": \"PingFangSC-Regular\", \n" +
                "                                \"fontSize\": \"26px\", \n" +
                "                                \"lineHeight\": \"28px\", \n" +
                "                                \"marginTop\": \"8px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"text\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"children\": [\n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"defaultHeight\": \"750\", \n" +
                "                                        \"src\": \"https://gw.alicdn.com/tfs/TB1UQg4qHSYBuNjSspiXXXNzpXa-200-200.png\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39666\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"display\": \"flex\", \n" +
                "                                        \"height\": \"120px\", \n" +
                "                                        \"marginLeft\": \"14px\", \n" +
                "                                        \"marginRight\": \"6px\", \n" +
                "                                        \"width\": \"120px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"image\"\n" +
                "                                }, \n" +
                "                                {\n" +
                "                                    \"attr\": {\n" +
                "                                        \"defaultHeight\": \"750\", \n" +
                "                                        \"src\": \"https://gw.alicdn.com/tfs/TB1hat0qY9YBuNjy0FgXXcxcXXa-200-200.png\"\n" +
                "                                    }, \n" +
                "                                    \"ref\": \"39669\", \n" +
                "                                    \"style\": {\n" +
                "                                        \"display\": \"flex\", \n" +
                "                                        \"height\": \"120px\", \n" +
                "                                        \"marginLeft\": \"14px\", \n" +
                "                                        \"marginRight\": \"6px\", \n" +
                "                                        \"width\": \"120px\"\n" +
                "                                    }, \n" +
                "                                    \"type\": \"image\"\n" +
                "                                }\n" +
                "                            ], \n" +
                "                            \"ref\": \"39663\", \n" +
                "                            \"style\": {\n" +
                "                                \"alignItems\": \"center\", \n" +
                "                                \"flexDirection\": \"row\", \n" +
                "                                \"marginTop\": \"12px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"div\"\n" +
                "                        }\n" +
                "                    ], \n" +
                "                    \"ref\": \"39651\", \n" +
                "                    \"style\": {\n" +
                "                        \"backgroundColor\": \"rgba(120,123,128,0.1)\", \n" +
                "                        \"borderRadius\": \"10px\", \n" +
                "                        \"flex\": \"1\", \n" +
                "                        \"marginBottom\": \"8px\", \n" +
                "                        \"marginLeft\": \"8px\", \n" +
                "                        \"marginRight\": \"8px\", \n" +
                "                        \"marginTop\": \"8px\", \n" +
                "                        \"paddingBottom\": \"20px\", \n" +
                "                        \"paddingLeft\": \"24px\", \n" +
                "                        \"paddingTop\": \"20px\", \n" +
                "                        \"width\": \"334px\"\n" +
                "                    }, \n" +
                "                    \"type\": \"div\"\n" +
                "                }\n" +
                "            ], \n" +
                "            \"event\": [\n" +
                "                \"click\"\n" +
                "            ], \n" +
                "            \"ref\": \"39648\", \n" +
                "            \"style\": {\n" +
                "                \"cursor\": \"pointer\"\n" +
                "            }, \n" +
                "            \"type\": \"div\"\n" +
                "        }, \n" +
                "        {\n" +
                "            \"attr\": {\n" +
                "                \"href\": \"https://m.jiaoyimao.com/xianyu/index?from=xy004&spm=widle.tbhome.1.1\"\n" +
                "            }, \n" +
                "            \"children\": [\n" +
                "                {\n" +
                "                    \"children\": [\n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"value\": \"游戏交易\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39677\", \n" +
                "                            \"style\": {\n" +
                "                                \"color\": \"#222\", \n" +
                "                                \"fontFamily\": \"PingFangSC-Medium\", \n" +
                "                                \"fontSize\": \"32px\", \n" +
                "                                \"left\": \"24px\", \n" +
                "                                \"lineHeight\": \"32px\", \n" +
                "                                \"position\": \"absolute\", \n" +
                "                                \"top\": \"34px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"text\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"value\": \"账号金币1分抢\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39679\", \n" +
                "                            \"style\": {\n" +
                "                                \"bottom\": \"34px\", \n" +
                "                                \"color\": \"rgb(136,136,136)\", \n" +
                "                                \"fontFamily\": \"PingFangSC-Regular\", \n" +
                "                                \"fontSize\": \"26px\", \n" +
                "                                \"left\": \"24px\", \n" +
                "                                \"lineHeight\": \"28px\", \n" +
                "                                \"marginTop\": \"8px\", \n" +
                "                                \"position\": \"absolute\"\n" +
                "                            }, \n" +
                "                            \"type\": \"text\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"defaultHeight\": \"750\", \n" +
                "                                \"src\": \"https://gw.alicdn.com/tfs/TB1u9vTleuSBuNjy1XcXXcYjFXa-112-112.png\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39682\", \n" +
                "                            \"style\": {\n" +
                "                                \"display\": \"flex\", \n" +
                "                                \"height\": \"104px\", \n" +
                "                                \"position\": \"absolute\", \n" +
                "                                \"right\": \"20px\", \n" +
                "                                \"top\": \"16px\", \n" +
                "                                \"width\": \"104px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"image\"\n" +
                "                        }\n" +
                "                    ], \n" +
                "                    \"ref\": \"39675\", \n" +
                "                    \"style\": {\n" +
                "                        \"backgroundColor\": \"rgba(120,123,128,0.1)\", \n" +
                "                        \"borderRadius\": \"10px\", \n" +
                "                        \"height\": \"136px\", \n" +
                "                        \"marginBottom\": \"8px\", \n" +
                "                        \"marginLeft\": \"8px\", \n" +
                "                        \"marginRight\": \"8px\", \n" +
                "                        \"marginTop\": \"8px\", \n" +
                "                        \"paddingBottom\": \"20px\", \n" +
                "                        \"paddingLeft\": \"24px\", \n" +
                "                        \"paddingTop\": \"20px\", \n" +
                "                        \"width\": \"334px\"\n" +
                "                    }, \n" +
                "                    \"type\": \"div\"\n" +
                "                }\n" +
                "            ], \n" +
                "            \"event\": [\n" +
                "                \"click\"\n" +
                "            ], \n" +
                "            \"ref\": \"39672\", \n" +
                "            \"style\": {\n" +
                "                \"cursor\": \"pointer\"\n" +
                "            }, \n" +
                "            \"type\": \"div\"\n" +
                "        }, \n" +
                "        {\n" +
                "            \"attr\": {\n" +
                "                \"href\": \"https://market.m.taobao.com/app/idleFish-F2e/app-home-second/sevenFoldTaobao?wh_weex=true&wx_navbar_transparent=true&spm=widle.tbhome.1.1\"\n" +
                "            }, \n" +
                "            \"children\": [\n" +
                "                {\n" +
                "                    \"children\": [\n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"value\": \"七折转手\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39690\", \n" +
                "                            \"style\": {\n" +
                "                                \"color\": \"#222\", \n" +
                "                                \"fontFamily\": \"PingFangSC-Medium\", \n" +
                "                                \"fontSize\": \"32px\", \n" +
                "                                \"left\": \"24px\", \n" +
                "                                \"lineHeight\": \"32px\", \n" +
                "                                \"position\": \"absolute\", \n" +
                "                                \"top\": \"34px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"text\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"value\": \"退坑回血来捡漏\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39692\", \n" +
                "                            \"style\": {\n" +
                "                                \"bottom\": \"34px\", \n" +
                "                                \"color\": \"rgb(136,136,136)\", \n" +
                "                                \"fontFamily\": \"PingFangSC-Regular\", \n" +
                "                                \"fontSize\": \"26px\", \n" +
                "                                \"left\": \"24px\", \n" +
                "                                \"lineHeight\": \"28px\", \n" +
                "                                \"marginTop\": \"8px\", \n" +
                "                                \"position\": \"absolute\"\n" +
                "                            }, \n" +
                "                            \"type\": \"text\"\n" +
                "                        }, \n" +
                "                        {\n" +
                "                            \"attr\": {\n" +
                "                                \"defaultHeight\": \"750\", \n" +
                "                                \"src\": \"https://gw.alicdn.com/tfs/TB1gvFrqY9YBuNjy0FgXXcxcXXa-800-800.png\"\n" +
                "                            }, \n" +
                "                            \"ref\": \"39695\", \n" +
                "                            \"style\": {\n" +
                "                                \"display\": \"flex\", \n" +
                "                                \"height\": \"104px\", \n" +
                "                                \"position\": \"absolute\", \n" +
                "                                \"right\": \"20px\", \n" +
                "                                \"top\": \"16px\", \n" +
                "                                \"width\": \"104px\"\n" +
                "                            }, \n" +
                "                            \"type\": \"image\"\n" +
                "                        }\n" +
                "                    ], \n" +
                "                    \"ref\": \"39688\", \n" +
                "                    \"style\": {\n" +
                "                        \"backgroundColor\": \"rgba(120,123,128,0.1)\", \n" +
                "                        \"borderRadius\": \"10px\", \n" +
                "                        \"height\": \"136px\", \n" +
                "                        \"marginBottom\": \"8px\", \n" +
                "                        \"marginLeft\": \"8px\", \n" +
                "                        \"marginRight\": \"8px\", \n" +
                "                        \"marginTop\": \"8px\", \n" +
                "                        \"paddingBottom\": \"20px\", \n" +
                "                        \"paddingLeft\": \"24px\", \n" +
                "                        \"paddingTop\": \"20px\", \n" +
                "                        \"width\": \"334px\"\n" +
                "                    }, \n" +
                "                    \"type\": \"div\"\n" +
                "                }\n" +
                "            ], \n" +
                "            \"event\": [\n" +
                "                \"click\"\n" +
                "            ], \n" +
                "            \"ref\": \"39685\", \n" +
                "            \"style\": {\n" +
                "                \"cursor\": \"pointer\"\n" +
                "            }, \n" +
                "            \"type\": \"div\"\n" +
                "        }\n" +
                "    ], \n" +
                "    \"event\": [ ], \n" +
                "    \"ref\": \"39621\", \n" +
                "    \"style\": {\n" +
                "        \"backgroundColor\": \"yellow\", \n" +
                "        \"flexDirection\": \"row\", \n" +
                "        \"flexWrap\": \"wrap\", \n" +
                "        \"marginBottom\": \"16px\", \n" +
                "        \"paddingBottom\": \"16px\", \n" +
                "        \"paddingLeft\": \"24px\", \n" +
                "        \"paddingRight\": \"24px\", \n" +
                "        \"paddingTop\": \"16px\"\n" +
                "    }, \n" +
                "    \"type\": \"div\"\n" +
                "}";

        System.out.println(HtmlTool.toHtml(JSON.parseObject(html)));
    }
}
