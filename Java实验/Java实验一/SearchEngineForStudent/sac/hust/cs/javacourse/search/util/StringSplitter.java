package hust.cs.javacourse.search.util;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 字符串分割类，根据标点符号和空白符将字符串分成一个个单词
 */
public class StringSplitter {
    public StringSplitter(){}
    private  String splitRegex = null;
    private  Pattern pattern = null;
    private  Matcher match = null;

    /**
     * 设置分词用的正则表达式
     * @param regex：分词用的正则表达式
     */
    public  void setSplitRegex(String regex){
        splitRegex = regex;
        pattern = Pattern.compile(splitRegex);
    }

    /**
     * 将字符串分割成单词列表
     * @param input： 输入字符串
     * @return ： 分词得到的单词列表
     */
    public  List<String> splitByRegex(String input){
        List<String> list = new ArrayList<String>();
        match = pattern.matcher(input);

        String part = null;
        int lastEnd = 0;
        while(match.find()){
            int start = match.start(0);
            int end = match.end(0);
            part = input.substring(lastEnd, match.start(0));
            lastEnd = match.end(0);
            if( (part != null && part.equals("")) || part == null) {
                continue;
            }
            list.add(part);
        }
        //取得最后一部分
        if(lastEnd < input.length()){
            part = input.substring(lastEnd);
            if(part != null && !part.equals(""))
                list.add(part);
        }

        return list;
    }

    public static void main(String[] args){
        StringSplitter splitter = new StringSplitter();
        String regex1TestInput = "key1,， ,Key2;Key3，:Key4;；;Key5；？?Key6，!Key7；Key8   key9\nkey10.。？key11";
//        String regex1TestInput = "\n\naaa bbb ccc\n\nddd is F17";
        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
        List<String> parts = splitter.splitByRegex(regex1TestInput);
        for(int i = 0; i < parts.size(); i++){
            System.out.print(parts.get(i) + "	");
        }
    }
}
