package com.test.weex.render.activity;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by furture on 2018/9/2.
 */

public class MainTest {

    public static void main(String[] args){
        String time = "09-02 22:15:23.952 25424 25512 D WeexCore:";
        Pattern pattern = Pattern.compile("[\\d]{2}:[\\d]{2}:[\\d]{2}\\.\\d+");
        Matcher matcher = pattern.matcher(time);
        System.out.println(matcher.find());

        System.out.println(time.substring(matcher.start(), matcher.end()));

        System.out.println(getTimeOffset(time) - getTimeOffset("09-02 22:15:22.953"));

    }

    private static long getTimeOffset(String time){
        Pattern pattern = Pattern.compile("[\\d]{2}:[\\d]{2}:[\\d]{2}\\.\\d+");
        Matcher matcher = pattern.matcher(time);
        if(!matcher.find()){
            return -1;
        }
        String offset= time.substring(matcher.start(), matcher.end());
        int pos = offset.lastIndexOf('.');
        String minus = offset.substring(pos + 1);
        String hous = offset.substring(0, pos);
        String [] hms =hous.split(":");
        long second =  Long.parseLong(hms[0])*60*60 + Long.parseLong(hms[1])*60
                 + + Long.parseLong(hms[2]);
        return second*1000 + Long.parseLong(minus);
    }



}
