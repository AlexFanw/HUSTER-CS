package hust.cs.javacourse.search.query;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.util.FileUtil;

import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * <pre>
 * AbstractHit是一个搜索命中结果的抽象类. 该类子类要实现Comparable接口.
 * 实现该接口是因为需要必须比较大小，用于命中结果的排序.
 * </pre>
 */
public abstract class AbstractHit implements Comparable<AbstractHit>{
    /**
     * 文档id
     */
    protected int docId;
    /**
     * 文档绝对路径
     */
    protected String docPath;
    /**
     * 文档原文内容，显示搜索结果时有用
     */
    protected String content;
    /**
     * 命中的单词和对应的Posting键值对，对计算文档得分有用，对于一个查询命中结果，一个term对应的是Posting而不是PostingList
     */
    protected Map<AbstractTerm, AbstractPosting> termPostingMapping = new TreeMap<AbstractTerm, AbstractPosting>();

    /**
     * 该命中文档的得分，文档的得分通过Sort接口计算.每个文档得分默认值为1.0
     */
    protected double score = 1.0;

    /**
     * 默认构造函数
     */
    public AbstractHit(){

    }

    /**
     * 构造函数
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     */
    public AbstractHit(int docId, String docPath){
        this.docId = docId;
        this.docPath = docPath;
        this.content = FileUtil.read(docPath);
    }

    /**
     * 构造函数
     * @param docId              ：文档id
     * @param docPath            ：文档绝对路径
     * @param termPostingMapping ：命中的三元组列表
     */
    public AbstractHit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping){
        this.docId = docId;
        this.docPath = docPath;
        this.termPostingMapping.putAll(termPostingMapping);
        this.content = FileUtil.read(docPath);
    }

    /**
     * 获得文档id
     * @return ： 文档id
     */
    public abstract int getDocId();

    /**
     * 获得文档绝对路径
     * @return ：文档绝对路径
     */
    public abstract String getDocPath();

    /**
     * 获得文档内容
     * @return ： 文档内容
     */
    public abstract String getContent();

    /**
     * 设置文档内容
     * @param content ：文档内容
     */
    public abstract  void setContent(String content);

    /**
     * 获得文档得分
     * @return ： 文档得分
     */
    public abstract double getScore();

    /**
     * 设置文档得分
     * @param score ：文档得分
     */
    public abstract  void setScore(double score);

    /**
     * 获得命中的单词和对应的Posting键值对
     * @return ：命中的单词和对应的Posting键值对
     */
    public abstract  Map<AbstractTerm, AbstractPosting> getTermPostingMapping();

    /**
     * 获得命中结果的字符串表示, 用于显示搜索结果.
     * @return : 命中结果的字符串表示
     */
    @Override
    public abstract  String toString();

    /**
     * 比较二个命中结果的大小，根据score比较
     * @param o     ：要比较的名字结果
     * @return      ：二个命中结果得分的差值
     */
    @Override
    public abstract int compareTo(AbstractHit o);


}
