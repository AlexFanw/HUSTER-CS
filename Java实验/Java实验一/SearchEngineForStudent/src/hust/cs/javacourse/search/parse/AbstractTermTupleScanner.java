package hust.cs.javacourse.search.parse;

import java.io.BufferedReader;
import java.io.IOException;

/**
 * <pre>
 *     AbstractTermTupleScanner是AbstractTermTupleStream的抽象子类，即一个具体的TermTupleScanner对象就是
 *     一个AbstractTermTupleStream流对象，它利用java.io.BufferedReader去读取文本文件得到一个个三元组TermTuple.
 *
 *     其具体子类需要重新实现next方法获得文本文件里的三元组
 * </pre>
 */
public abstract class AbstractTermTupleScanner extends AbstractTermTupleStream {
    /**
     * input作为输入流对象，读取文本文件得到一个个三元组TermTuple
     */
    protected BufferedReader input = null;

    /**
     * 缺省构造函数
     */
    public  AbstractTermTupleScanner(){

    }

    /**
     * 构造函数
     * @param input：指定输入流对象，应该关联到一个文本文件
     */
    public  AbstractTermTupleScanner(BufferedReader input){
        this.input = input;
    }

    /**
     * 实现父类AbstractTermTupleStream的close方法，关闭流
     */
    @Override
    public void close(){
        try {
            input.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
