package hust.cs.javacourse.search.index;

import java.util.Map;
import java.io.File;
import java.util.Set;
import java.util.TreeMap;

/**
 * <pre>
 * AbstractIndex是内存中的倒排索引对象的抽象父类.
 *      一个倒排索引对象包含了一个文档集合的倒排索引.
 *      内存中的倒排索引结构为HashMap，key为Term对象，value为对应的PostingList对象.
 *      另外在AbstractIndex里还定义了从docId和docPath之间的映射关系.
 *      必须实现下面接口:
 *          FileSerializable：可序列化到文件或从文件反序列化.
 * </pre>
 */
public abstract class AbstractIndex implements FileSerializable{
    /**
     * 内存中的docId和docPath的映射关系, key为docId，value为对应的docPath.
     *      TreeMap可以对键值排序
     */
    public Map<Integer, String> docIdToDocPathMapping = new TreeMap<>();

    /**
     * 内存中的倒排索引结构为HashMap，key为Term对象，value为对应的PostingList对象.
     */
    public Map<AbstractTerm, AbstractPostingList> termToPostingListMapping = new TreeMap<AbstractTerm, AbstractPostingList>();

    /**
     *  缺省构造函数,构建空的索引
     */
    public AbstractIndex(){

    }

    /**
     * 返回索引的字符串表示
     * @return 索引的字符串表示
     */
    @Override
    public abstract String toString();

    /**
     * 添加文档到索引，更新索引内部的HashMap
     * @param document ：文档的AbstractDocument子类型表示
     */
    public abstract void addDocument(AbstractDocument document);

    /**
     * <pre>
     * 从索引文件里加载已经构建好的索引.内部调用FileSerializable接口方法readObject即可
     * @param file ：索引文件
     * </pre>
     */
    public abstract void load(File file);

    /**
     * <pre>
     * 将在内存里构建好的索引写入到文件. 内部调用FileSerializable接口方法writeObject即可
     * @param file ：写入的目标索引文件
     * </pre>
     */
    public abstract void save(File file);

    /**
     * 返回指定单词的PostingList
     * @param term : 指定的单词
     * @return ：指定单词的PostingList;如果索引字典没有该单词，则返回null
     */
    public abstract AbstractPostingList search(AbstractTerm term);

    /**
     * 返回索引的字典.字典为索引里所有单词的并集
     * @return ：索引中Term列表
     */
    public abstract Set<AbstractTerm> getDictionary();

    /**
     * <pre>
     * 对索引进行优化，包括：
     *      对索引里每个单词的PostingList按docId从小到大排序
     *      同时对每个Posting里的positions从小到大排序
     * 在内存中把索引构建完后执行该方法
     * </pre>
     */
    public abstract void optimize();

    /**
     * 根据docId获得对应文档的完全路径名
     * @param docId ：文档id
     * @return : 对应文档的完全路径名
     */
    public abstract String getDocName(int docId);
}
