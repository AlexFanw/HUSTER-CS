package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import java.util.List;

public class Document extends AbstractDocument {
    public Document(){}
    public Document(int docId,String docPath){
        super(docId,docPath);
    }
    public Document(int docId,String docPath,List<AbstractTermTuple> tuples){
        super(docId,docPath,tuples);
    }
    @Override
    public int getDocId() {
        return this.docId;
    }

    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    @Override
    public String getDocPath() {
        return docPath;
    }

    @Override
    public void setDocPath(String docPath) {
        this.docPath = docPath;
    }

    @Override
    public List<AbstractTermTuple> getTuples() {
        return tuples;
    }

    @Override
    public void addTuple(AbstractTermTuple tuple) {
        if(contains(tuple)){
            return ;
        }
        tuples.add(tuple);
    }

    @Override
    public boolean contains(AbstractTermTuple tuple) {
        return tuples.contains(tuple);
    }

    @Override
    public AbstractTermTuple getTuple(int index) {
        return tuples.get(index);
    }

    @Override
    public int getTupleSize() {
        return tuples.size();
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for(AbstractTermTuple tuple:tuples){
            builder.append(tuple.toString());
        }
        return "{ docId:" + docId + ", docPath:" +docPath+", tuples:\n" + builder.toString() + "}\n";
    }


}
