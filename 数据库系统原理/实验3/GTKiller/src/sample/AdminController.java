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

public class AdminController {
    public void initialize() throws SQLException { //初始化
        setTableVoc();
        setTableUser();
    }
    @FXML
    private Button btn_quit;
    public void on_btn_quit_clicked() throws IOException { //退出按钮
        Stage currentStage=(Stage)btn_quit.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root= FXMLLoader.load(getClass().getResource("Login.fxml")); //转到登录界面
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
    @FXML
    private TableView<TableVoc> tview_tablevoc;
    @FXML
    private TableColumn<TableVoc,Integer> tc_ID;
    @FXML
    private TableColumn<TableVoc,String> tc_Word;
    @FXML
    private TableColumn<TableVoc,String> tc_Paraphrase;
    @FXML
    private TableColumn<TableVoc,String> tc_Username;



    public void setTableVoc() throws SQLException { //用于显示管理员
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String sql="select * from VocabularyBuilder";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        ResultSet rs=preparedStatement.executeQuery();
        ObservableList<TableVoc> data= FXCollections.observableArrayList();
        while(rs.next()){
            Integer ID=rs.getInt("ID");
            String Word=rs.getString("Word");
            String Paraphrase=rs.getString("Paraphrase");
            String Username=rs.getString("Username");
            data.add(new TableVoc(ID,Word,Paraphrase,Username));
        }
        tc_ID.setCellValueFactory(new PropertyValueFactory<TableVoc,Integer>("ID"));
        tc_Word.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Word"));
        tc_Paraphrase.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Paraphrase"));
        tc_Username.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Username"));
        tview_tablevoc.setItems(data);
        preparedStatement.close();
        connection.close();
    }

    @FXML
    private TableView<TableUser> tview_tableuser;
    @FXML
    private TableColumn<TableVoc,Integer> tu_ID;
    @FXML
    private TableColumn<TableVoc,String> tu_Username;
    @FXML
    private TableColumn<TableVoc,String> tu_Password;
    @FXML
    private TableColumn<TableVoc,Integer> tu_Age;
    @FXML
    private TableColumn<TableVoc,Integer> tu_Sex;



    public void setTableUser() throws SQLException { //用于显示用户数据

        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String sql="select * from User";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        ResultSet rs=preparedStatement.executeQuery();
        ObservableList<TableUser> data= FXCollections.observableArrayList();
        while(rs.next()){
            Integer ID=rs.getInt("ID");
            String Username=rs.getString("Username");
            String Password=rs.getString("Password");
            Integer Age=rs.getInt("Age");
            Integer Sex=rs.getInt("Sex");
            data.add(new TableUser(ID,Username,Password,Age,Sex));
        }
        tu_ID.setCellValueFactory(new PropertyValueFactory<TableVoc,Integer>("ID"));
        tu_Username.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Username"));
        tu_Password.setCellValueFactory(new PropertyValueFactory<TableVoc,String>("Password"));
        tu_Age.setCellValueFactory(new PropertyValueFactory<TableVoc,Integer>("Age"));
        tu_Sex.setCellValueFactory(new PropertyValueFactory<TableVoc,Integer>("Sex"));

        tview_tableuser.setItems(data);
        preparedStatement.close();
        connection.close();
    }
}

