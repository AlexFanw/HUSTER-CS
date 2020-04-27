package hust.cs.javacourse.search.query;

import hust.cs.javacourse.search.index.AbstractIndex;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Index;

/**
 * <pre>
 *  AbstractIndexSearcher是检索具体实现的抽象类
 * </pre>
 */
public abstract class AbstractIndexSearcher {
    /**
     * 内存中的索引，子类对象被初始化时为空
     */
    //Index是AbstractIndex的具体实现类，在hust.cs.javacourse.search.index.impl里定义，但没有实现任何覆盖方法，需要学生实现
    //如果学生AbstractIndex的具体实现类类名不是Index，这里需要相应修改
    protected AbstractIndex index = new Index();
    /**
     * 多个检索词的逻辑组合
     */
    public static enum LogicalCombination{
        /**
         * 与,即多个检索词必须都在命中文档里出现
         */
        AND,
        /**
         * 或, 即任意一个检索词在命中文档里出现
         */
        OR
    }
    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     * @param indexFile ：指定索引文件
     */
    public abstract void open(String indexFile);

    /**
     * 根据单个检索词进行搜索
     * @param queryTerm ：检索词
     * @param sorter ：排序器
     * @return ：命中结果数组
     */
    public abstract AbstractHit[] search(AbstractTerm queryTerm, Sort sorter);

    /**
     *
     * 根据二个检索词进行搜索
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter ：    排序器
     * @param combine ：   多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    public abstract AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine);

}
