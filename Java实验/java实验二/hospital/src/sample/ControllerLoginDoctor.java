package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import javax.swing.*;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ControllerLoginDoctor {
    @FXML
    private Button btn_login;
    @FXML
    private Button btn_back;
    @FXML
    private TextField field_number;
    @FXML
    private TextField field_password;
    public static String loginedDocid; //静态字符串，用于controller之间传递参数

    public String getLoginedDocid(){
        return loginedDocid;
    }
    //回车键登录
    public void onEnter(){
        on_btn_login_clicked();
    }
    public void on_btn_login_clicked(){
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
        }
        else{
            if(field_number.getText().equals("")){ //编号输入为空
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("此栏不可为空");
                alert.showAndWait();
                return;
            }
            try {
                String sql="select * from doctor where docid=?";
                PreparedStatement preparedStatement=connection.prepareStatement(sql);
                preparedStatement.setString(1,field_number.getText());
                ResultSet rs=preparedStatement.executeQuery();
                if(!(rs.next())){ //找不到编号
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("医生编号不存在");
                    alert.showAndWait();
                    return;
                }
                String realPassword=rs.getString("password");
                String inputPassword=field_password.getText();
                if(!(realPassword.equals(inputPassword))) {//密码错误
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("密码错误");
                    alert.showAndWait();}
                else{ //登录成功，更新登录日期
                    String docid=rs.getString("docid");
                    loginedDocid=docid;
                    String currentTime=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()); //获取登陆时间
                    String sql2="update doctor set last_login_datetime =? where docid=?";
                    preparedStatement=connection.prepareStatement(sql2);
                    preparedStatement.setString(1,currentTime);
                    preparedStatement.setString(2,docid);
                    preparedStatement.executeUpdate();
                    Stage currentStage=(Stage)btn_login.getScene().getWindow();
                    currentStage.close(); //关闭当前窗口
                    SplitPane root=FXMLLoader.load(getClass().getResource("Doctor.fxml")); //转到医生界面
                    Stage newStage=new Stage();
                    newStage.setTitle("医生报表");
                    newStage.setScene(new Scene(root));
                    newStage.show();
                    preparedStatement.close();
                    connection.close();
                }
            }
            catch (SQLException | IOException e){
                e.printStackTrace();
            }
        }
    }
    public void on_btn_back_clicked() throws IOException {
        Stage currentStage=(Stage)btn_login.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root= FXMLLoader.load(getClass().getResource("Login.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}
