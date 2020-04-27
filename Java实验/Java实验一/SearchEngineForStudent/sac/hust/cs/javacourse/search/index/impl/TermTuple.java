package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.Objects;

public class TermTuple extends AbstractTermTuple {
    public TermTuple(){}
    public TermTuple(AbstractTerm term,int curpos){
        this.curPos = curpos;
        this.term = term;
    }
    @Override
    public boolean equals(Object obj) {
        if(obj instanceof TermTuple){
            return this.curPos == ((TermTuple)obj).curPos
                    && Objects.equals(this.term,((TermTuple) obj).term);
        }
        return false;
    }

    @Override
    public String toString() {
        return "{Term: "+term+",CurPos"+curPos+",Freq: "+freq+"}\n";
    }
}
