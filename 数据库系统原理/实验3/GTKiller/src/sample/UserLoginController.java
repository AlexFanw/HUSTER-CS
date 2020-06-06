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

public class UserLoginController {
    @FXML
    private Button btn_login;
    @FXML
    private Button btn_back;
    @FXML
    private TextField field_number;
    @FXML
    private TextField field_password;

    //回车键登录
    public void onEnter(){
        on_btn_login_clicked();
    }
    //病人登录
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
                alert.setHeaderText("账号不可为空");
                alert.showAndWait();
                return;
            }
            try {
                String sql="select * from User where Username=?";
                PreparedStatement preparedStatement=connection.prepareStatement(sql);
                preparedStatement.setString(1,field_number.getText());
                ResultSet rs=preparedStatement.executeQuery();
                if(!(rs.next())){ //找不到编号
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("该用户名不存在");
                    alert.showAndWait();
                    return;
                }
                String realPassword=rs.getString("Password");
                String inputPassword=field_password.getText();
                if(!(realPassword.equals(inputPassword))) {//密码错误
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("密码错误");
                    alert.showAndWait();}
                else{ //登录成功
                    Stage currentStage=(Stage)btn_login.getScene().getWindow();
                    currentStage.close(); //关闭当前窗口
                    SplitPane root=FXMLLoader.load(getClass().getResource("Toefl.fxml")); //转到挂号界面
                    Stage newStage=new Stage();
                    newStage.setTitle("");
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
    //返回
    public void on_btn_back_clicked() throws IOException {
        Stage currentStage=(Stage)btn_login.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("Login.fxml"));
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}
