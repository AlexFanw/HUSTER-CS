package hust.cs.javacourse.search.index.impl;
import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.*;

import java.io.*;

public class DocumentBuilder extends AbstractDocumentBuilder {
    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream) throws IOException {
        AbstractDocument document = new Document(docId, docPath);//加上文件名，文件路径
        AbstractTermTuple termTuple = termTupleStream.next();//跳转至下一个termTuple
        while (termTuple != null) {
            document.addTuple(termTuple);
            termTuple = termTupleStream.next();
        }
        termTupleStream.close();
        return document;
    }

    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        AbstractDocument document = null;
        AbstractTermTupleStream termTupleStream = null;
        try {
            termTupleStream = new TermTupleScanner(new BufferedReader(new InputStreamReader(new FileInputStream(file))));
            termTupleStream = new StopWordTermTupleFilter(termTupleStream); //再加上停用词过滤器
            termTupleStream = new PatternTermTupleFilter(termTupleStream); //再加上正则表达式过滤器
            termTupleStream = new LengthTermTupleFilter(termTupleStream); //再加上单词长度过滤器
            document = build(docId, docPath, termTupleStream);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            termTupleStream.close();
        }
        return document;
    }
}
