package hust.cs.javacourse.search.parse;


/**
 * <pre>
 * 抽象类AbstractTermTupleFilter类型是AbstractTermTupleStream的子类,里面包含另一个
 * AbstractTermTupleStream对象作为输入，并对输入的AbstractTermTupleStream进行过滤,
 * 例如过滤掉所有停用词（the，is are...)对应的三元组
 *
 * 其具体子类需要重新实现next方法以过滤掉不需要的单词对应的三元组.同时可以实现多个不同的过滤器
 * 完成不同的过滤功能，多个过滤器可以形成过滤管道.
 * </pre>
 */
public abstract class AbstractTermTupleFilter extends AbstractTermTupleStream{
    /**
     * Filter的输入，类型为AbstractTermTupleStream
     */
    protected AbstractTermTupleStream input;

    /**
     * 构造函数
     * @param input：Filter的输入，类型为AbstractTermTupleStream
     */
    public AbstractTermTupleFilter(AbstractTermTupleStream input){
        this.input = input;
    }

    /**
     * 实现父类AbstractTermTupleStream的close方法，关闭流
     */
    @Override
    public void close(){
        input.close();
    }
}
