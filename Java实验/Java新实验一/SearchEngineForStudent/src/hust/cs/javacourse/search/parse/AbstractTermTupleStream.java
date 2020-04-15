package hust.cs.javacourse.search.parse;

import hust.cs.javacourse.search.index.AbstractTermTuple;

/**
 * <pre>
 * AbstractTermTupleStream是各种TermFreqPosTupleStream对象的抽象父类
 *      TermFreqPosTupleStream是三元组TermTuple流对象，包含了解析文本文件得到的三元组序列
 * </pre>
 */
public abstract class AbstractTermTupleStream {
    /**
     * 获得下一个三元组
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    public abstract AbstractTermTuple next() ;

    /**
     * 关闭流
     */
    public abstract void close();
}
