package hust.cs.javacourse.search.index;

import java.util.ArrayList;
import java.util.List;

/**
 * <pre>
 * AbstractPosting是Posting对象的抽象父类.
 *      Posting对象代表倒排索引里每一项， 一个Posting对象包括:
 *          包含单词的文档id.
 *          单词在文档里出现的次数.
 *          单词在文档里出现的位置列表（位置下标不是以字符为编号，而是以单词为单位进行编号.
 *      必须实现下面二个接口:
 *          Comparable：可比较大小（按照docId大小排序）,
 *                      当检索词为二个单词时，需要求这二个单词对应的PostingList的交集,
 *                      如果每个PostingList按docId从小到大排序，可以提高求交集的效率.
 *          FileSerializable：可序列化到文件或从文件反序列化
 *  </pre>
 */
public abstract class AbstractPosting implements Comparable<AbstractPosting>, FileSerializable {
    /**
     * 包含单词的文档id
     */
    protected int docId;
    /**
     * 单词在文档里出现的次数
     */
    protected int freq;
    /**
     * 单词在文档里出现的位置列表（以单词为单位进行编号，如第1个单词，第2个单词，...), 单词可能在文档里出现多次，因此需要一个List来保存
     */
    protected List<Integer> positions = new ArrayList<>();

    /**
     * 缺省构造函数
     */
    public AbstractPosting(){

    }

    /**
     * 构造函数
     * @param docId ：包含单词的文档id
     * @param freq  ：单词在文档里出现的次数
     * @param positions   ：单词在文档里出现的位置
     */
    public AbstractPosting(int docId, int freq, List<Integer> positions){
        this.docId = docId;
        this.freq = freq;
        this.positions = positions;
    }

    /**
     * 判断二个Posting内容是否相同
     * @param obj ：要比较的另外一个Posting
     * @return 如果内容相等返回true，否则返回false
     */
    @Override
    public abstract boolean equals(Object obj) ;

    /**
     * 返回Posting的字符串表示
     * @return 字符串
     */
    @Override
    public abstract String toString() ;

    /**
     * 返回包含单词的文档id
     * @return ：文档id
     */
    public abstract int getDocId();

    /**
     * 设置包含单词的文档id
     * @param docId：包含单词的文档id
     */
    public abstract void setDocId(int docId);

    /**
     * 返回单词在文档里出现的次数
     * @return ：出现次数
     */
    public abstract int getFreq();

    /**
     * 设置单词在文档里出现的次数
     * @param freq:单词在文档里出现的次数
     */
    public abstract void setFreq(int freq);

    /**
     * 返回单词在文档里出现的位置列表
     * @return ：位置列表
     */
    public abstract  List<Integer> getPositions();

    /**
     * 设置单词在文档里出现的位置列表
     * @param positions：单词在文档里出现的位置列表
     */
    public abstract void setPositions(List<Integer> positions);

    /**
     * 比较二个Posting对象的大小（根据docId）
     * @param o： 另一个Posting对象
     * @return ：二个Posting对象的docId的差值
     */
    @Override
    public abstract int compareTo(AbstractPosting o);

    /**
     * 对内部positions从小到大排序
     */
    public abstract void sort();
}
