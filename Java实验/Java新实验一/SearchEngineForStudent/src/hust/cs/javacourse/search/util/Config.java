package hust.cs.javacourse.search.util;

/**
 * <pre>
 *
 * 保存搜索引擎的配置信息，例如：
 *      索引文件所在目录
 *      要建立索引的文本文件所在目录
 *      构建索引时是否忽略单词大小写
 *      分词所需要的正则表达式
 *      基于正则表达式的三元组过滤器所需的正则表达式
 *      基于单词长度的三元组过滤器所需的最小单词长度和最大单词长度
 *      ...
 * </pre>
 *
 */
public class Config {

    /**
     * Java工程HOME目录, System.getProperty("user.dir")返回当前JAVA工程目录
     */
    public static String PROJECT_HOME_DIR= System.getProperty("user.dir");
    /**
     * <pre>
     * 索引文件的目录,以相对路径指定索引文件目录,将索引文件保存在当前工程目录下的index子目录中.
     * 这样做的好处：索引文件目录是相对路径,无论你把整个工程放在什么位置，程序都可以正常运行.
     * </pre>
     */
    public static String INDEX_DIR = PROJECT_HOME_DIR + "/index/";
    /**
     * <pre>
     *  文本文件的目录,以相对路径指定文本文件目录 ,将文本文件保存在当前工程目录下的text子目录中
     *  这样做的好处：文本文件目录是相对路径,无论你把整个工程放在什么位置，程序都可以正常运行.
     * </pre>
     *
     */
    public static String DOC_DIR  = PROJECT_HOME_DIR + "/text/";

    /**
     * 构建索引和检索时是否忽略单词大小写
     */
    public static boolean IGNORE_CASE = true;

    /**
     * <pre>
     * 将字符串切分成单词时所需的正则表达式.
     * 例如根据中英文的逗号,分号,句号，问号，冒号,感叹号，中文顿号，空白分割符进行切分
     * </pre>
     *
     */
    public static String STRING_SPLITTER_REGEX = "[,|，|;|；|.|。|?|？|:|：|!|！|、|\\s]+";

    /**
     * <pre>
     * 单词过滤的正则表达式.
     * 例如正则表达式指定只保留由字母组成的term,其他的term全部过滤掉,不写入倒排索引
     * </pre>
     */
    public static String TERM_FILTER_PATTERN = "[a-zA-z]+";

    /**
     * <pre>
     * 基于单词的最小长度过滤单词.
     * 例如指定最短单词长度为3，长度小于3的单词过滤掉，不写入倒排索引
     * </pre>
     */
    public static int TERM_FILTER_MINLENGTH = 3;

    /**
     * <pre>
     * 基于单词的最小长度过滤单词.
     * 例如指定最长单词长度为20，长度大于20的单词过滤掉，不写入倒排索引
     * </pre>
     */
    public static int TERM_FILTER_MAXLENGTH = 20;
}
