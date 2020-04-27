package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

public class TermTupleScanner extends AbstractTermTupleScanner {
    public TermTupleScanner(BufferedReader input){
        super(input);
    }
    Queue<AbstractTermTuple> buffer = new LinkedList<>();
    int pos = 0;
    @Override
    public AbstractTermTuple next() throws IOException {
        if (buffer.isEmpty()) {
            String string = input.readLine();
            if (string == null) {
                return null;
            }
            while (string.trim().length() == 0) {
                string = input.readLine();
                if (string == null) {
                    return null;
                }
            }
            StringSplitter splitter = new StringSplitter();
            splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
            for (String word : splitter.splitByRegex(string)) {
                TermTuple tt = new TermTuple();
                tt.curPos = pos;
                if (Config.IGNORE_CASE) {
                    tt.term = new Term(word.toLowerCase());
                } else {
                    tt.term = new Term(word);
                }
                buffer.add(tt);
                pos ++;
            }
        }
        return buffer.poll();
    }
}

