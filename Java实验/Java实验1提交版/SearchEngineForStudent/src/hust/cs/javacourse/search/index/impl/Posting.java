package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Collections;
import java.util.List;

public class Posting extends AbstractPosting {

    public Posting(){}
    public Posting(int docId,int freq,List<Integer> p){
        super(docId,freq,p);
    }
    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Posting){
            return this.docId==((Posting) obj).docId
                    && this.freq == ((Posting) obj).freq
                    && this.positions.size() == ((Posting) obj).positions.size()
                    && this.positions.containsAll(((Posting) obj).positions)
                    && ((Posting) obj).positions.containsAll(this.positions);
        }
        return false;
    }

    @Override
    public String toString() {
        return "{\"docId\":" + docId + ",\"freq\":" + freq + ",\"positions\":" + positions + " }";
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
    public int getFreq() {
        return this.freq;
    }

    @Override
    public void setFreq(int freq) {
        this.freq=freq;
    }

    @Override
    public List<Integer> getPositions() {
        return positions;
    }

    @Override
    public void setPositions(List<Integer> positions) {
        this.positions=positions;
    }

    @Override
    public int compareTo(AbstractPosting o) {
        return this.docId-o.getDocId();
    }

    @Override
    public void sort() {
        Collections.sort(this.positions);
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try{
            out.writeObject(docId);
            out.writeObject(freq);
            out.writeObject(positions.size());
            for(Integer i:positions){
                out.writeObject(i);//输入坐标
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try{
            this.docId = (Integer)in.readObject();
            this.freq = (Integer)in.readObject();
            int size = (Integer) in.readObject();
            for(int i=0;i<size;i++){
                positions.add((Integer)in.readObject());//读取坐标
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
