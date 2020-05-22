package sample;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class DoctorIncome {
    private final StringProperty depname;
    private final StringProperty docid;
    private final StringProperty docname;
    private final StringProperty dregcat;
    private final StringProperty regnum;
    private final StringProperty income;
    public DoctorIncome(String depname,String docid,String docname,String dregcat,String regnum,String income){
        this.depname=new SimpleStringProperty(depname);
        this.docid=new SimpleStringProperty(docid);
        this.docname=new SimpleStringProperty(docname);
        this.dregcat=new SimpleStringProperty(dregcat);
        this.regnum=new SimpleStringProperty(regnum);
        this.income=new SimpleStringProperty(income);
    }
    public String getDepname(){
        return depname.get();
    }
    public String getDocid(){
        return docid.get();
    }
    public String getDocname(){
        return docname.get();
    }
    public String getDregcat(){
        return dregcat.get();
    }
    public String getRegnum(){
        return regnum.get();
    }
    public String getIncome(){
        return income.get();
    }
}
