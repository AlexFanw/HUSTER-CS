package hust.cs.javacourse.search.index;

/**
 * <pre>
 * AbstractIndexBuilder是索引构造器的抽象父类
 *      需要实例化一个具体子类对象完成索引构造的工作
 * </pre>
 */
public abstract class AbstractIndexBuilder {
    /**
     * 构建索引必须解析文档构建Document对象，因此包含AbstractDocumentBuilder的子类对象
     */
    protected AbstractDocumentBuilder docBuilder;

    /**
     * docId计数器，每当解析一个文档并写入索引，计数器应该+1
     */
    protected int docId = 0;

    public AbstractIndexBuilder(AbstractDocumentBuilder docBuilder){
        this.docBuilder = docBuilder;
    }

    /**
     * <pre>
     * 构建指定目录下的所有文本文件的倒排索引.
     *      需要遍历和解析目录下的每个文本文件, 得到对应的Document对象，再依次加入到索引，并将索引保存到文件.
     * @param rootDirectory ：指定目录
     * @return ：构建好的索引
     * </pre>
     */
    public abstract AbstractIndex buildIndex(String rootDirectory);

}
