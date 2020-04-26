package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.List;

public class Document extends AbstractDocument {

    @Override
    public int getDocId() {
        return 0;
    }

    @Override
    public void setDocId(int docId) {

    }

    @Override
    public String getDocPath() {
        return null;
    }

    @Override
    public void setDocPath(String docPath) {

    }

    @Override
    public List<AbstractTermTuple> getTuples() {
        return null;
    }

    @Override
    public void addTuple(AbstractTermTuple tuple) {

    }

    @Override
    public boolean contains(AbstractTermTuple tuple) {
        return false;
    }

    @Override
    public AbstractTermTuple getTuple(int index) {
        return null;
    }

    @Override
    public int getTupleSize() {
        return 0;
    }

    @Override
    public String toString() {
        return null;
    }


}
