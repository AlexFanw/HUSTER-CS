package sample;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class TableUser {
    private final IntegerProperty ID;
    private final StringProperty Username;
    private final StringProperty Password;
    private final IntegerProperty Age;
    private final IntegerProperty Sex;
    public TableUser(Integer ID,String Username,String Password,Integer Age,Integer Sex){
        this.ID=new SimpleIntegerProperty(ID);
        this.Username=new SimpleStringProperty(Username);
        this.Password=new SimpleStringProperty(Password);
        this.Age=new SimpleIntegerProperty(Age);
        this.Sex=new SimpleIntegerProperty(Sex);
    }
    public Integer getID(){ return ID.get(); }
    public String getUsername(){ return Username.get();}
    public String getPassword(){ return Password.get();}
    public Integer getAge(){ return Age.get(); }
    public Integer getSex(){ return Sex.get(); }
}
