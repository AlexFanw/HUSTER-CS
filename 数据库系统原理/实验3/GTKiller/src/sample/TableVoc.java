package sample;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class TableVoc {
    private final IntegerProperty ID;
    private final StringProperty Word;
    private final StringProperty Paraphrase;
    private final StringProperty Username;
    public TableVoc(Integer ID,String Word,String Paraphrase,String Username){
        this.ID=new SimpleIntegerProperty(ID);
        this.Word=new SimpleStringProperty(Word);
        this.Paraphrase=new SimpleStringProperty(Paraphrase);
        this.Username=new SimpleStringProperty(Username);


    }
    public Integer getID(){ return ID.get(); }
    public String getWord(){ return Word.get();}
    public String getParaphrase(){ return Paraphrase.get();}
    public String getUsername(){ return Username.get();}

}
