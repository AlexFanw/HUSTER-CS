package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class PostingList extends AbstractPostingList {
    public PostingList(){
    }
    @Override
    public void add(AbstractPosting posting) {
        for(AbstractPosting p:list){
            if(p.getDocId() == posting.getDocId()){
                return;
            }//判断是否有重复的
        }
        list.add(posting);
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        boolean flag = false;
        for(AbstractPosting p:list){
            builder.append(p.toString());
            builder.append("->");
            flag = true;
        }
        if(flag){
            builder.delete(builder.length()-2,builder.length());}
        builder.append("\n");
        return builder.toString();
    }

    @Override
    public void add(List<AbstractPosting> postings) {
        for(AbstractPosting p:postings){
            list.add(p);
        }
    }

    @Override
    public AbstractPosting get(int index) {
        return list.get(index);
    }

    @Override
    public int indexOf(AbstractPosting posting) {
        return list.indexOf(posting);
    }

    @Override
    public int indexOf(int docId) {
        return list.indexOf(docId);
    }

    @Override
    public boolean contains(AbstractPosting posting) {
        return list.contains(posting);
    }

    @Override
    public void remove(int index) {
        list.remove(index);
    }

    @Override
    public void remove(AbstractPosting posting) {
        list.remove(posting);
    }

    @Override
    public int size() {
        return list.size()          ;
    }

    @Override
    public void clear() {
        list.clear();//what can  it do?
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public void sort() {
        Collections.sort(list, AbstractPosting::compareTo);
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try{
            out.writeObject(list.size());
            for(AbstractPosting p:list){
                p.writeObject(out);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void readObject(ObjectInputStream in) {
        try{
            int size = (Integer)in.readObject();
            for(int i=0;i<size;i++){
                AbstractPosting p =new Posting();
                p.readObject(in);
                list.add(p);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
