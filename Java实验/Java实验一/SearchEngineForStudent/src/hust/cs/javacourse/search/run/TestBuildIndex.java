package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractIndexBuilder;
import hust.cs.javacourse.search.index.impl.DocumentBuilder;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.index.impl.IndexBuilder;
import hust.cs.javacourse.search.util.Config;

import java.io.File;
import java.io.IOException;

/**
 * 测试索引构建
 */
public class TestBuildIndex {
    public static void main(String[] args) throws IOException {
        AbstractDocumentBuilder documentBuilder = new DocumentBuilder();//构建文件夹路径集合
        AbstractIndexBuilder indexBuilder = new IndexBuilder(documentBuilder);//构建index集合
        String rootDir = Config.DOC_DIR+"/真实测试数据集/";
        System.out.println("Start build index ...");
        AbstractIndex index = indexBuilder.buildIndex(rootDir);
        index.optimize();
        System.out.println(index);
        //控制台打印 index 的内容
        //测试保存到文件
        String indexFile = Config.INDEX_DIR + "index.dat";
        index.save(new File(indexFile));
        ((Index) index).writePlainText(new File(Config.INDEX_DIR + "index.txt"));
        //索引保存到文件
        //测试从文件读取
        AbstractIndex index2 = new Index(); //创建一个空的 index
        index2.load(new File(indexFile));
        //从文件加载对象的内容
        System.out.println("\n-------------------\n");
        System.out.println(index2);
        //控制台打印 index2 的内容
    }
}
