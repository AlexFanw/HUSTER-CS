package hust.cs.javacourse.search.util;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * 文件操作的工具类
 */
public class FileUtil {
    private FileUtil(){}

    /**
     * 一次读取指定文本文件的所有内容
     * @param filePath ：指定文本文件的绝对路径
     * @return  ： 文本文件的内容
     */
    public static String read(String filePath){
        String s = null;
        BufferedReader reader = null;
        try{
            StringBuffer buf = new StringBuffer();
            reader = new BufferedReader(new InputStreamReader(new FileInputStream(new File(filePath))));
            while( (s = reader.readLine()) != null){
                buf.append(s).append("\n"); //reader.readLine())返回的字符串会去掉换行符，因此这里要加上
            }
            s = buf.toString().trim(); //去掉最后一个多的换行符
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        finally {
            if(reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return s;
    }

    /**
     * 将字符串写入到指定的文本文件
     * @param content  ：  写入的内容
     * @param filePath ： 指定的文本文件路径
     */
    public static void write(String content, String filePath){
        PrintWriter writer = null;
        try{
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(new File(filePath)))));
            writer.print(content);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        finally {
            if(writer != null){
                writer.close();
            }
        }
    }

    /**
     * 列出指定目录下所有文件的绝对路径(不递归)
     * @param dirPath : 指定目录
     * @return ： 指定目录下所有文件的绝对路径的列表
     */
    public static List<String> list(String dirPath){
        List<String> filePaths = new ArrayList<String>();
        try{
            File dir = new File(dirPath);
            if(dir.isDirectory()){
                File[] files = dir.listFiles();
                for(File f: files){
                    if(f.isFile()) {
                        filePaths.add(f.getCanonicalPath()); //File类的getCanonicalPath方法返回绝对路径
                    }
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return filePaths;
    }

    /**
     * 列出指定目录下的匹配指定后缀名的所有文件的绝对路径(不递归)
     * @param dirPath : 指定目录
     * @param suffix  ：指定后缀名, 如 .txt
     * @return : 所有匹配指定后缀名的文件绝对路径列表
     */
    public static List<String> list(String dirPath, String suffix){
        List<String> filePaths = new ArrayList<String>();
        try{
            File dir = new File(dirPath);
            if(dir.isDirectory()){
                File[] files = dir.listFiles();
                for(File f: files){
                    if(f.isFile()) {
                        String path = f.getCanonicalPath(); //File类的getCanonicalPath方法返回绝对路径
                        if(path.toLowerCase().endsWith(suffix.toLowerCase())) {
                            filePaths.add(path);
                        }
                    }
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return filePaths;
    }

    public static void main(String[] args){
        //从文件读
        String fileName = Config.DOC_DIR + "1.txt";
        String s = FileUtil.read(fileName);
        System.out.println(s);

        //写入到另一个文件
        String fileName2 = Config.DOC_DIR + "2.txt";
        FileUtil.write(s,fileName2);

        //列出指定目录下所有文件
        String dirName = Config.PROJECT_HOME_DIR + "/javadoc";
        List<String> fileNames = FileUtil.list(dirName);
        for(String p: fileNames){
            System.out.println(p);
        }

        System.out.println("----------------");
        //列出指定目录下所有.html文件
        String dirName1 = Config.PROJECT_HOME_DIR + "/javadoc";
        List<String> fileNames1 = FileUtil.list(dirName,".html");
        for(String p: fileNames1){
            System.out.println(p);
        }
    }
}
