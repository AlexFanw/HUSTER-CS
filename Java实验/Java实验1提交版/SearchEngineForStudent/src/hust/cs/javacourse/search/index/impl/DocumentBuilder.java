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
        AbstractDocument document = new Document(docId, docPath);
        AbstractTermTuple termTuple = termTupleStream.next();
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
        AbstractTermTupleStream ts = null;
        try {
            ts = new TermTupleScanner(new BufferedReader(new InputStreamReader(new
                    FileInputStream(file))));
            ts = new StopWordTermTupleFilter(ts); //再加上停用词过滤器
            ts = new PatternTermTupleFilter(ts); //再加上正则表达式过滤器
            ts = new LengthTermTupleFilter(ts); //再加上单词长度过滤器
            document = build(docId, docPath, ts);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            ts.close();
        }
        return document;
    }
}
