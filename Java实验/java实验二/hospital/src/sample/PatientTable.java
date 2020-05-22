package sample;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class PatientTable {
    private final StringProperty regid;
    private final StringProperty pname;
    private final StringProperty regdatetime;
    private final StringProperty pregcat;
    public PatientTable(String regid,String pname,String regdatetime,String pregcat){
        this.regid=new SimpleStringProperty(regid);
        this.pname=new SimpleStringProperty(pname);
        this.regdatetime=new SimpleStringProperty(regdatetime);
        this.pregcat=new SimpleStringProperty(pregcat);
    }
    public String getRegid(){
        return regid.get();
    }
    public String getPname(){
        return pname.get();
    }
    public String getRegdatetime(){
        return regdatetime.get();
    }
    public String getPregcat(){
        return pregcat.get();
    }
}
