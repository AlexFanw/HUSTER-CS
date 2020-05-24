package hust.cs.javacourse.search.index;

/**
 * <pre>
 * AbstractTerm是Term对象的抽象父类.
 *      Term对象表示文本文档里的一个单词.
 *      必须实现下面二个接口:
 *          Comparable：可比较大小（字典序）,为了加速检索过程，字典需要将单词进行排序.
 *          FileSerializable：可序列化到文件或从文件反序列化.
 *   </pre>
 */
public abstract class AbstractTerm implements  Comparable<AbstractTerm>, FileSerializable{
    /**
     * Term内容
     */
    protected String content;

    /**
     * 缺省构造函数
     */
    public AbstractTerm(){

    }

    /**
     * 因为要作为HashMap里面的key，因此必须要覆盖hashCode方法
     * 返回对象的HashCode
     * @return ：对象的HashCode
     */
    @Override
    public int hashCode() {
        return this.content.hashCode();
    }

    /**
     * 构造函数
     * @param content ：Term内容
     */
    public AbstractTerm(String content){
        this.content = content;
    }

    /**
     * 判断二个Term内容是否相同
     * @param obj ：要比较的另外一个Term
     * @return 如果内容相等返回true，否则返回false
     */
    @Override
    public abstract boolean equals(Object obj) ;

    /**
     * 返回Term的字符串表示
     * @return 字符串
     */
    @Override
    public abstract String toString() ;

    /**
     * 返回Term内容
     * @return Term内容
     */
    public abstract String getContent();

    /**
     * 设置Term内容
     * @param content：Term的内容
     */
    public abstract void setContent(String content);

    /**
     * 比较二个Term大小（按字典序）
     * @param o： 要比较的Term对象
     * @return ： 返回二个Term对象的字典序差值
     */
    @Override
    public abstract int compareTo(AbstractTerm o) ;
}
