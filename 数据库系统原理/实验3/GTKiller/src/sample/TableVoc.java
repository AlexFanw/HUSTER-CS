package sample;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class TableVoc {
    private final StringProperty No;
    private final StringProperty Word;
    private final StringProperty Paraphrase;
    public TableVoc(String No,String Word,String Paraphrase){
        this.No=new SimpleStringProperty(No);
        this.Word=new SimpleStringProperty(Word);
        this.Paraphrase=new SimpleStringProperty(Paraphrase);
    }
    public String getNo(){ return No.get(); }
    public String getWord(){ return Word.get();}
    public String getParaphrase(){ return Paraphrase.get();}
}
