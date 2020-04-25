package hust.cs.javacourse.search.index;

import java.util.ArrayList;
import java.util.List;

/**
 *<pre>
 *     AbstractDocument是文档对象的抽象父类.
 *          文档对象是解析一个文本文件得到结果，文档对象里面包含：
 *              文档id.
 *              文档的绝对路径.
 *              文档包含的三元组对象列表，一个三元组对象是抽象类AbstractTermTuple的子类实例
 *</pre>
 */
public abstract class AbstractDocument {
    /**
     * 文档id
     */
    protected int docId;
    /**
     * 文档绝对路径
     */
    protected String docPath;
    /**
     * 文档包含的三元组列表
     */
    protected List<AbstractTermTuple> tuples = new ArrayList<AbstractTermTuple>();

    /**
     * 缺省构造函数
     */
    public  AbstractDocument(){

    }

    /**
     * 构造函数
     * @param docId：文档id
     * @param docPath：文档绝对路径
     */
    public AbstractDocument(int docId, String docPath){
        this.docId  = docId;
        this.docPath = docPath;
    }

    public AbstractDocument(int docId, String docPath,List<AbstractTermTuple> tuples){
        this.docId  = docId;
        this.docPath = docPath;
        this.tuples = tuples;
    }

    /**
     * 获得文档id
     * @return ：文档id
     */
    public abstract int getDocId();

    /**
     * 设置文档id
     * @param docId：文档id
     */
    public abstract void setDocId(int docId);

    /**
     * 获得文档绝对路径
     * @return ：文档绝对路径
     */
    public abstract String getDocPath();

    /**
     * 设置文档绝对路径
     * @param docPath：文档绝对路径
     */
    public abstract void setDocPath(String docPath);

    /**
     * 获得文档包含的三元组列表
     * @return ：文档包含的三元组列表
     */
    public abstract List<AbstractTermTuple> getTuples();

    /**
     * 向文档对象里添加三元组, 要求不能有内容重复的三元组
     * @param tuple ：要添加的三元组
     */
    public abstract void addTuple(AbstractTermTuple tuple);

    /**
     * 判断是否包含指定的三元组
     * @param tuple ： 指定的三元组
     * @return ： 如果包含指定的三元组，返回true;否则返回false
     */
    public abstract boolean contains(AbstractTermTuple tuple);

    /**
     * 获得指定下标位置的三元组
     * @param index：指定下标位置
     * @return：三元组
     */
    public abstract AbstractTermTuple getTuple(int index);

    /**
     * 返回文档对象包含的三元组的个数
     * @return ：文档对象包含的三元组的个数
     */
    public  abstract  int getTupleSize();

    /**
     * 获得Document的字符串表示
     * @return ： Document的字符串表示
     */
    @Override
    public abstract String toString();

}
