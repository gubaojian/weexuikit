package com.test.weex.render.activity;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by furture on 2018/7/19.
 */

public class FileUtils {

    private static Map<String,String>  fileCache = new HashMap<>();

    /**
     * Load file in asset directory.
     * @param path FilePath
     * @param context Weex Context
     * @return the Content of the file
     */
    public static String loadAsset(String path, Context context) {
        String content = fileCache.get(path);
        if(content != null){
            return content;
        }
        if (context == null || TextUtils.isEmpty(path)) {
            return null;
        }
        InputStream inputStream = null;
        try {
            inputStream = context.getAssets().open(path);
            content =  readStreamToString(inputStream);
            fileCache.put(path, content);
            return content;
        } catch (IOException e) {
            Log.e("Weex", "LOAD file" + path, e);
        }
        return "";
    }

    private static String readStreamToString(InputStream inputStream) {
        BufferedReader bufferedReader = null;
        try {
            StringBuilder builder = new StringBuilder(inputStream.available() + 10);
            bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            char[] data = new char[4096];
            int len = -1;
            while ((len = bufferedReader.read(data)) >= 0) {
                builder.append(data, 0, len);
            }

            return builder.toString();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (bufferedReader != null)
                    bufferedReader.close();
            } catch (IOException e) { }
            try {
                if (inputStream != null)
                    inputStream.close();
            } catch (IOException e) {}
        }

        return "";
    }

    public static byte[] loadAssetBytes(String path, Context context) {
        if (context == null || TextUtils.isEmpty(path)) {
            return null;
        }
        InputStream inputStream = null;
        try {

            byte[] bts = new byte[1024];
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            inputStream = context.getAssets().open(path);
            int length = inputStream.read(bts);
            while (length >= 0){
                byteArrayOutputStream.write(bts, 0, length);
                length = inputStream.read(bts);
            }
            return byteArrayOutputStream.toByteArray();
        } catch (IOException e) {
            Log.e("Weex", "LOAD file" + path, e);
        }
        return null;
    }
}
