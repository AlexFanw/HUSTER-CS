package hust.cs.javacourse.search.index;

import hust.cs.javacourse.search.parse.AbstractTermTupleStream;

import java.io.File;

/**
 * <pre>
 * AbstractDocumentBuilder是Document构造器的抽象父类.
 *      Document构造器的功能应该是由解析文本文档得到的TermTupleStream，产生Document对象.
 * </pre>
 */
public abstract class AbstractDocumentBuilder {

    /**
     * <pre>
     * 由解析文本文档得到的TermTupleStream,构造Document对象.
     * @param docId             : 文档id
     * @param docPath           : 文档绝对路径
     * @param termTupleStream   : 文档对应的TermTupleStream
     * @return ：Document对象
     * </pre>
     */
    public  abstract AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream);

//    /**
//     * <pre>
//     * 由给定的File,构造Document对象。
//     * 该方法利用输入参数file构造出AbstractTermTupleStream子类对象后,可以调用AbstractDocument build(AbstractTermTupleStream termTupleStream)
//     * @param file: 给定的File对象
//     * @return ：Document对象
//     * </pre>
//     */

    /**
     * <pre>
     * 由给定的File,构造Document对象.
     * 该方法利用输入参数file构造出AbstractTermTupleStream子类对象后,内部调用
     *      AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream)
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param file      : 文档对应File对象
     * @return          : Document对象
     * </pre>
     */
    public abstract AbstractDocument build(int docId, String docPath, File file);
}
