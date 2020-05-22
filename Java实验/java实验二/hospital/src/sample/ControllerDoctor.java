package sample;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import javax.swing.*;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ControllerDoctor {
    @FXML
    private Label label_username;
    @FXML
    private Label label_starttime;
    @FXML
    private Label label_endtime;
    @FXML
    private TableView<PatientTable> tview_patientlist;
    @FXML
    private TableColumn<PatientTable,String> tc_regid;
    @FXML
    private TableColumn<PatientTable,String> tc_pname;
    @FXML
    private TableColumn<PatientTable,String> tc_regdatetime;
    @FXML
    private TableColumn<PatientTable,String> tc_pregcat;
    @FXML
    private TableView<DoctorIncome> tview_incomelist;
    @FXML
    private TableColumn<DoctorIncome,String> tc_depname;
    @FXML
    private TableColumn<DoctorIncome,String> tc_docid;
    @FXML
    private TableColumn<DoctorIncome,String> tc_docname;
    @FXML
    private TableColumn<DoctorIncome,String> tc_dregcat;
    @FXML
    private TableColumn<DoctorIncome,String> tc_regnum;
    @FXML
    private TableColumn<DoctorIncome,String> tc_income;
    @FXML
    private Button btn_quit;
    public void initialize() throws SQLException { //初始化
        setUserName();
        setTime();
        setPatientTable();
        setIncomeList();
    }
    public void setUserName() throws SQLException { //用于显示用户名
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();

            return;
        }
        String docid=new ControllerLoginDoctor().getLoginedDocid();
        String sql="select * from doctor where docid=?";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        preparedStatement.setString(1,docid);
        ResultSet rs=preparedStatement.executeQuery();
        rs.next();
        String docname=rs.getString("name");
        String text="用户:"+docname+"医生";
        label_username.setText(text);
        preparedStatement.close();
        connection.close();
    }
    public void setTime(){ //用于显示起始时间和截止时间
        String datetime=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
        label_starttime.setText("起始时间："+datetime.substring(0,11)+"00:00:00");
        label_endtime.setText("截止时间："+datetime);
    }
    public void setPatientTable() throws SQLException { //用于显示病人列表
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String docid=new ControllerLoginDoctor().getLoginedDocid();
        String sql="select * from register where docid=?";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        preparedStatement.setString(1,docid);
        ResultSet rs=preparedStatement.executeQuery();
        ObservableList<PatientTable> data=FXCollections.observableArrayList();
        while(rs.next()){
            String regid=rs.getString("reg_id");
            String pid=rs.getString("pid");
            String sql2="select * from patient where pid=?";
            preparedStatement=connection.prepareStatement(sql2);
            preparedStatement.setString(1,pid);
            ResultSet rs2=preparedStatement.executeQuery();
            rs2.next();
            String pname=rs2.getString("name");
            String regdatetime=rs.getString("reg_datetime");
            String catid=rs.getString("catid");
            String sql3="select * from register_category where catid=?";
            preparedStatement=connection.prepareStatement(sql3);
            preparedStatement.setString(1,catid);
            ResultSet rs3=preparedStatement.executeQuery();
            rs3.next();
            String pregcat;
            if(rs3.getString("speciallist").equals("1"))
                pregcat="专家号";
            else
                pregcat="普通号";
            data.add(new PatientTable(regid,pname,regdatetime,pregcat));
        }
        tc_regid.setCellValueFactory(new PropertyValueFactory<PatientTable,String>("regid"));
        tc_pname.setCellValueFactory(new PropertyValueFactory<PatientTable,String>("pname"));
        tc_regdatetime.setCellValueFactory(new PropertyValueFactory<PatientTable,String>("regdatetime"));
        tc_pregcat.setCellValueFactory(new PropertyValueFactory<PatientTable,String>("pregcat"));
        tview_patientlist.setItems(data);
        preparedStatement.close();
        connection.close();
    }
    public void setIncomeList() throws SQLException { //用于显示收入列表
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String sql="select * from register_category";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        ResultSet rs=preparedStatement.executeQuery();
        ObservableList<DoctorIncome> data=FXCollections.observableArrayList();
        while(rs.next()){
            String catid=rs.getString("catid");
            String depid=rs.getString("depid");
            String sql2="select * from department where depid=?";
            preparedStatement=connection.prepareStatement(sql2);
            preparedStatement.setString(1,depid);
            ResultSet rs2=preparedStatement.executeQuery();
            rs2.next();
            String depname=rs2.getString("name");
            String sql3="select * from doctor where depid=?";
            preparedStatement=connection.prepareStatement(sql3);
            preparedStatement.setString(1,depid);
            ResultSet rs3=preparedStatement.executeQuery();
            rs3.next();
            String docid=rs3.getString("docid");
            String docname=rs3.getString("name");
            String dregcat;
            if(rs.getString("speciallist").equals("1"))
                dregcat="专家号";
            else
                dregcat="普通号";
            String today="^"+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()).substring(0,10); //获得当天日期
            String sql4="select count(*) from register where catid=? and reg_datetime REGEXP ?";
            preparedStatement=connection.prepareStatement(sql4);
            preparedStatement.setString(1,catid);
            preparedStatement.setString(2,today);
            ResultSet rs4=preparedStatement.executeQuery();
            rs4.next();
            String regnum=rs4.getString(1);
            float regfee=rs.getBigDecimal("reg_fee").floatValue();
            String income=String.valueOf(regfee*Float.parseFloat(regnum));
            data.add(new DoctorIncome(depname,docid,docname,dregcat,regnum,income));
        }
        tc_depname.setCellValueFactory(new PropertyValueFactory<DoctorIncome,String>("depname"));
        tc_docid.setCellValueFactory(new PropertyValueFactory<DoctorIncome,String>("docid"));
        tc_docname.setCellValueFactory(new PropertyValueFactory<DoctorIncome,String>("docname"));
        tc_dregcat.setCellValueFactory(new PropertyValueFactory<DoctorIncome,String>("dregcat"));
        tc_regnum.setCellValueFactory(new PropertyValueFactory<DoctorIncome,String>("regnum"));
        tc_income.setCellValueFactory(new PropertyValueFactory<DoctorIncome,String>("income"));
        tview_incomelist.setItems(data);
        preparedStatement.close();
        connection.close();
    }
    public void on_btn_quit_clicked() throws IOException { //退出按钮
        Stage currentStage=(Stage)label_username.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("Login.fxml")); //转到登录界面
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}
